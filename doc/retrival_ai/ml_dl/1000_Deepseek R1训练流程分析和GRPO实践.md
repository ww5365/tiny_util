# DeepSeek R1 完整训练流程概览

* DeepSeek-R1-Zero：**突破关键**
  1. 通过大规模强化学习（RL）训练的模型，而没有经过监督微调（SFT）作为预处理步骤，但展示了显著的推理能力。
  2. 为什么那么好的推理能力？阶段的目标，探索LLMs在没有任何监督数据的情况下，开发推理能力的潜力，专注于通过纯RL过程的自我进化。具体实现上，使用DeepSeek-V3-Base作为基础模型，并采用GRPO作为强化学习框架，极大提升模型推理上表现。
* DeepSeek-R1：**能力提升**
  1. Zero 面临一些挑战，比如可读性差和语言混合等问题。
  2. DeepSeek-R1 如何解决？RL之前融合了多步训练和冷启动数据。DeepSeek-R1在推理任务上的表现与OpenAI-o1相当。
* 蒸馏：**能力拓展**
  1. 小模型同样可以强大：DeepSeek R1 Distill Qwen...
  2. 证明了大模型学到的推理模式可以被蒸馏到小模型中，其推理能力优于直接在小模型上应用强化学习（RL）所得的推理能力。

![image](./8f2edfd2-9da0-4934-93f8-33762db6507f.jpeg)

## 第一阶段：训练deepseek R1 Zero

### Zero 训练流程

![image](./3d9314e4-d977-4845-9ec8-1e54e4d7f48a.png)

### 实现推理能力的自我进化核心-GRPO

#### GRPO

群组相对策略优化（Group Relative Policy Optimization，GRPO） 方法（Shao et al.,2024）
**创新点**：省去了通常与策略模型同等大小的评价模型（critic model），并通过群体得分来估算基准（baseline）。
**算法流程**：

![image](./9732e1fd-4f95-42ab-b755-19b57ffa54f2.png)

**计算过程**：
![image](./e981b234-5a77-4cc0-a2b8-20097e1fc5a1.png)

#### 奖励函数

奖励是训练信号的来源，决定了强化学习（RL）优化的方向。DeepSeek-R1-Zero，采用了一种基于规则的奖励系统，主要包含两种类型的奖励：

* 准确性奖励（Accuracy rewards）：准确性奖励模型用于评估响应是否正确。例如，在数学问题中要求模型给出确定结果的最终答案, 并按照指定格式呈现（例如，在框内）。这样，便可以进行可靠的基于规则的正确性验证。
* 格式奖励（Format rewards）：除了准确性奖励模型外，我们还采用了格式奖励模型，要求模型将其思考过程放置在"和 "标签之间。示例模板：
  
  ![image](./a4db5013-7958-4b2a-84be-56716f05f1bd.png)

#### 算法效果

![image](./aac64c81-550e-4315-91b8-482afcdf4e3c.png)

* 随着RL训练的推进，DeepSeek-R1-Zero表现出稳定且持续的性能提升。特别地，AIME 2024上的平均pass@1分数显著提高，从最初的15.6%跃升至71.0%，达到了与OpenAI-o1-0912相媲美的性能水平。
* 这一显著提升突显了RL算法在随着时间优化模型性能方面的有效性。

## 第二阶段：训练deepseek R1

### R1训练流程总览

![image](./f7a7f06d-4ef2-4f5b-a6cf-c4be59e349b8.png)

### step1 - 冷启动，SFT有监督微调

**详细流程**：

![image](./ab5029b7-72c8-4d7f-b269-3cf221e37702.png)

**COT数据构建**：

1. 原因： 为了避免 RL训练在基础模型上的早期不稳定冷启动阶段，DeepSeek-R1 采用了一种不同的方法：构建并收集了一小部分长链式思维（Chainof-Thought, CoT）数据，用于微调模型，使其成为初始的 RL Actor 即：强化学习的策略模型。
2. 样式：![image](./f7727ebd-3316-4186-aaee-23690af59916.png)
3. 效果:DeepSeek-R1 通过冷启动数据的SFT，模型更好的学习到推理模式和输出格式。

### step2 - GRPO强化学习训练

**详细流程**：

![image](./0cf9aa95-a210-434a-bf89-ef951ecf0cc0.png)

**和zero不同点**：

1. 引入语言一致性奖励，原因如下。
2. 训练过程中，我们观察到链式思维（CoT）推理过程中常常出现语言混杂（Language Mixing），
   特别是当 RL 训练涉及多种语言的提示（prompts）时。这种语言混杂可能会影响可读性，使得模型输出难以理解，为了缓解语言混杂问题。

### step3 - SFT有监督微调

**详细流程**：

![image](./a91cb251-d8fb-4e46-b489-fd3d8e9d4197.png)

**目标**：增强模型在写作、角色扮演和其他通用QA任务方面的能力

**不同点**

1. 推理数据：60w条  V2.0 创建
2. 非推理数据：20W 包括写作、事实问答、自我认知和翻译等。V3审核，可能生成推理过程。
3. 混合原因：减少遗忘，保留模型原始能力。

### step4 - GRPO强化学习训练

**详细流程**：

![image](./e1bd94f4-7700-4ff0-bdb1-42701ef17995.png)

**不同点 - 奖励函数**：

1. 有用性（Helpfulness）: 对在有用性训练中，我们专注于优化最终摘要（final summary），确保评估时关注回答的实用性和相关性，而不会干扰底层的推理过程。
2. 无害性（Harmlessness）: 在无害性训练中，我们评估整个模型的输出，包括推理过程和最终摘要，以识别并缓解可能出现的风险、偏见或有害内容，确保模型生成 的内容符合安全和伦理标准。

## 第三阶段：deepseek R1 模型蒸馏

### 蒸馏过程

![image](./9dfa507b-3f9e-49a0-8516-f578b58786d9.png)

### 模型蒸馏与强化学习对比

如果不进行蒸馏，模型能否通过文中讨论的大规模强化学习训练实现相当的效果？

* 蒸馏更强大的模型到小型模型中可以获得出色的效果，而依赖于文中所提到的大规模强化学习的小型模型需要巨大的计算能力，并且可能无法达到蒸馏的性能。
* 虽然蒸馏策略成本低且有效，但超越智能的边界仍然可能需要更强大的基础模型和更大规模的强化学习。

# GRPO训练实践（DeepSeek R1 Zero微调）

## 环境准备

### 支持GRPO常见的主流强化学习框架

- **trl库**：https://github.com/huggingface/trl
- unsloth:https://github.com/unslothai/unsloth

```bash
pip install torch
pip install transformers
pip install trl
```

### 基模型和数据集

* 基模型

GRPO训练过程控制在20G显存左右，运行时间4-6个小时左右

Qwen2.5-0.5B-Instruct：可以从魔搭社区中下载模型权重：https://www.modelscope.cn/models/Qwen/Qwen2.5-0.5B-Instruct

* 数据集

OpenAI/GSM8K数据集：https://huggingface.co/datasets/openai/gsm8k

**OpenAI GSM8K 数据集** 是一个广泛用于评估推理和数学能力的多样化数学题目数据集。该数据集包含大约 **8,000** 个数学问题，涵盖了从小学到高中的各种数学领域，包括算术、代数、几何等。GSM8K 旨在挑战大型语言模型在没有显式提示的情况下，解决更复杂的数学推理问题。数据集中的问题通常需要模型进行多步推理，远超基本的算术计算，因此它被广泛用于测试模型在理解和处理数字推理的能力。
GSM8K 数据集的设计基于自然语言形式，呈现为问题-解答对的形式，且包含了问题的详细解析步骤。该数据集被广泛应用于模型的 **零样本推理** 和 **少样本学习** 任务，是当前研究中用于验证语言模型推理能力的重要基准之一。

![image](./9e396fae-da1a-43d1-b8de-43a6ae512df3.png)

## GRPO强化学习训练实践

```python
import re
import torch
from datasets import load_dataset, Dataset
from transformers import AutoTokenizer, AutoModelForCausalLM
from trl import GRPOConfig, GRPOTrainer

# 定义了系统提示（prompt）的格式：
# 这个字符串的作用通常是在生成型模型中，指导模型如何组织它的回复
SYSTEM_PROMPT = """
Respond in the following format:
<reasoning>
...
</reasoning>
<answer>
...
</answer>
"""

# XML 风格的格式，并允许动态插入 `reasoning` 和 `answer` 的内容。
# 模型的输出需要符合某种特定的格式（比如 XML 格式）
XML_COT_FORMAT = """\
<reasoning>
{reasoning}
</reasoning>
<answer>
{answer}
</answer>
"""

# 格式处理函数组
## 用于从 XML 风格的文本中提取 `<answer>` 标签之间的内容。

def extract_xml_answer(text: str) -> str:
    answer = text.split("<answer>")[-1]
    answer = answer.split("</answer>")[0]
    return answer.strip()

## 用于从文本中提取 `####` 后的内容，若没有找到 `####`，返回 `None`。
def extract_hash_answer(text: str) -> str | None:
    if "####" not in text:
        return None
    return text.split("####")[1].strip()


## 加载 `GSM8K` 数据集，并将问题与系统提示结合，格式化后返回。
def get_gsm8k_questions(split = "train") -> Dataset:
    # data = load_dataset('openai/gsm8k', 'main')[split] 

    data_files = {
        "train": "./dataset/gsm8k/main/train-*.parquet",
        "test": "./dataset/gsm8k/main/test-*.parquet"
    }

    data = load_dataset("parquet", data_files=data_files)[split].select(range(500)) # 为了快我取了500条

    data = data.map(lambda x: {
        'prompt': [
            {'role': 'system', 'content': SYSTEM_PROMPT},
            {'role': 'user', 'content': x['question']}
        ],
        'answer': extract_hash_answer(x['answer'])
    }) 
    return data


dataset = get_gsm8k_questions("train")
print(f"{dataset[0]}") # 1条示例数据


# Reward functions

## 准确性奖励：该函数检查模型输出是否与正确答案匹配，并根据匹配情况返回奖励分数。
def correctness_reward_func(prompts, completions, answer, **kwargs) -> list[float]:
    responses = [completion[0]['content'] for completion in completions]
    q = prompts[0][-1]['content']
    extracted_responses = [extract_xml_answer(r) for r in responses]
    print('-'*20, f"Question:\n{q}", f"\nAnswer:\n{answer[0]}", f"\nResponse:\n{responses[0]}", f"\nExtracted:\n{extracted_responses[0]}")
    return [2.0 if r == a else 0.0 for r, a in zip(extracted_responses, answer)]

## 格式奖励：检查模型输出是否为有效的整数，并根据结果给予奖励。
def int_reward_func(completions, **kwargs) -> list[float]:
    responses = [completion[0]['content'] for completion in completions]
    extracted_responses = [extract_xml_answer(r) for r in responses]
    return [0.5 if r.isdigit() else 0.0 for r in extracted_responses]

## 格式奖励：检查模型的输出是否符合严格的格式要求，包括 <reasoning> 和 <answer> 标签。
def strict_format_reward_func(completions, **kwargs) -> list[float]:
    """Reward function that checks if the completion has a specific format."""
    pattern = r"^<reasoning>\n.*?\n</reasoning>\n<answer>\n.*?\n</answer>\n$"
    responses = [completion[0]["content"] for completion in completions]
    matches = [re.match(pattern, r) for r in responses]
    return [0.5 if match else 0.0 for match in matches]

## 格式奖励：检查模型的输出是否符合稍微宽松的格式要求，<reasoning> 和 <answer> 标签之间可以有空白字符
def soft_format_reward_func(completions, **kwargs) -> list[float]:
    """Reward function that checks if the completion has a specific format."""
    pattern = r"<reasoning>.*?</reasoning>\s*<answer>.*?</answer>"
    responses = [completion[0]["content"] for completion in completions]
    matches = [re.match(pattern, r) for r in responses]
    return [0.5 if match else 0.0 for match in matches]


## 格式奖励：计算文本中 <reasoning> 和 <answer> 标签的出现次数，并根据它们的位置和频率分配奖励
def count_xml(text) -> float:
    count = 0.0
    if text.count("<reasoning>\n") == 1:
        count += 0.125
    if text.count("\n</reasoning>\n") == 1:
        count += 0.125
    if text.count("\n<answer>\n") == 1:
        count += 0.125
        count -= len(text.split("\n</answer>\n")[-1])*0.001
    if text.count("\n</answer>") == 1:
        count += 0.125
        count -= (len(text.split("\n</answer>")[-1]) - 1)*0.001  # 如果存在多余的文本在 </answer> 标签之后，扣除一些奖励。
    return count

def xmlcount_reward_func(completions, **kwargs) -> list[float]:
    contents = [completion[0]["content"] for completion in completions]
    return [count_xml(c) for c in contents]

# 模型名和训练输出目录
model_name = "model/Qwen2.5-0.5B-Instruct"
output_dir="outputs/Qwen-0.5B-GRPO"
run_name="Qwen-0.5B-GRPO-gsm8k"

# GRPO训练参数配置
training_args = GRPOConfig(
    output_dir=output_dir,
    run_name=run_name,
    learning_rate=5e-6,
    adam_beta1 = 0.9,
    adam_beta2 = 0.99,
    weight_decay = 0.1,
    warmup_ratio = 0.1,
    lr_scheduler_type='cosine',
    logging_steps=1,
    bf16=True,
    per_device_train_batch_size=1,  # 每个设备上进行的训练批次大小，即每次计算时使用的样本数。此处设置为 1，表示每个 GPU 或设备上处理 1 个样本。根据显存大小调整。
    gradient_accumulation_steps=4,
    num_generations=16, # 每个 prompt 生成 16 个样本，用于组内相对排名。GRPO 核心参数之一。
    max_prompt_length=256,
    max_completion_length=200,
    num_train_epochs=1,
    save_steps=100,
    max_grad_norm=0.1,
    log_on_each_node=False,
    use_vllm=False,
    vllm_gpu_memory_utilization=.3,
    #vllm_device="cuda:0",
    # report_to="wandb",
    generation_batch_size=16   # 控制推理阶段一次生成多少样本（非训练 batch）。
)

# 模型加载：GPU
model = AutoModelForCausalLM.from_pretrained(
    model_name,
    torch_dtype=torch.bfloat16,
    device_map=None
).to("cuda")

# 加载分词器
tokenizer = AutoTokenizer.from_pretrained(model_name)
tokenizer.pad_token = tokenizer.eos_token

# 开始训练
trainer = GRPOTrainer(
    model=model,
    processing_class=tokenizer,
    reward_funcs=[
        xmlcount_reward_func,
        soft_format_reward_func,
        strict_format_reward_func,
        int_reward_func,
        correctness_reward_func],
    args=training_args,
    train_dataset=dataset,
)

trainer.train()
trainer.save_model(output_dir)

```

输出：

![image](./7837ce24-259a-43c6-851a-22dc3860c1cb.png)

开悟时刻：

![image](./c2a5c044-e516-4423-8df2-00b36605cc25.png)

最终生成的文件：
![image](./1b36dc85-79e4-4a8d-ac47-8e588ae2b3b3.png)


