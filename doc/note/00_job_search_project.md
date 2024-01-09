# job search project


## project 准备进展


## 2023.1.4
1. hadoop/spark 使用，indexfeature项目中处理代码，整理
2. nebulagrahp 使用
3. 深挖知识图谱构建项目...

4. 走通bert + llm技术栈
   Pytorch => 向量化模型：all-MiniLM-L6-v2 => bert => 大模型：langchain ? =》 模型加速  实际工程化

5. 看看别人写的blog，他山之石
   https://www.cnblogs.com/pinard/



## 2023.9.8


再次启程


LTR：

D:\workfiles\20220906_大搜搜索\20220920_精排资料\LTR

 
   \level2model\catboost_rongz ： rongzhe 的 level2model 二层精排模型
   
    D:\workspace\tanxin2\20230128_catboost_rz\catboost ： 这里存了代码
	
	D:\workspace\tanxin2\20221206_catboost   这是网上 + 官网的关于catboost的实例代码
	

这是排序思路整理参考资料：

https://github.com/ww5365/tiny_util/blob/master/doc/retrival_ai/retrival_algorithm/02_%E6%8E%92%E5%BA%8F%E6%A8%A1%E5%9E%8B.md	
 

xgboost专题：

D:\myfiles\技术文档\xgboost： 原理参考   
   D:\workspace\tanxin2\20201012_xgboost ： 代码参考
   

word2vec专题：

  deep_learning/20200620_word_vec/skip-gram/word2vec中的数学.pdf  ：  这个github的仓(tanxin)可以合并到python的仓中，进行整理整合
   

leetcode:

  http://3ms.xxx.com/km/blogs/details/14249309?l=zh-cn  大家有空就看看练练。
  https://labuladong.gitee.io/algo/home/
  
  高频即可: 算法通关手册66页.pdf 后面git上提交下这个文件

面经：
1. 字节跳动广告搜索面试：
https://maimai.cn/web/gossip_detail/33038722?egid=cd781662ab1b473cbab7325e2cd8a979&gid=33038722&operation_id=f54954f7-45c0-467f-8830-b767d2bd2bfc&share_channel=2&share_euid=uOT1tw07Tx7QzfY9xV4GtUrQANFlsVE04jOqLU6YQniVr_I9jdTFZhd_c5NR-lKs
  
  

  
## 2023.9.1

一定要形成积累，材料及相关的参考(博客，视频，文档，一定要记录)

### leetcode

参考：00_leetcode_c++.md

### 项目

#### transformer专题

1. https://mp.weixin.qq.com/s/VrzkxEVBAO6abJcUsYGr0Q ： 这篇是比较好的，也是参考了jalammer这篇博客
https://blog.csdn.net/longxinchen_ml/article/details/86533005
原作者：Jay Alammar  https://jalammar.github.io/illustrated-transformer

2. tanxin的视频及记录的笔记

3. transfomer 原理和实现

4. 面试常见的类型：
   https://www.bilibili.com/video/BV1Di4y1c7Zm?p=2&spm_id_from=pageDriver&vd_source=ff1d5f0f1a1b50dc5fc0b20e64d1bba6
   这个视频中会涉及些面试相关的，其中qoute到作者写的知乎上面试汇总文章
   
语义召回：

transformer专题，语义相关项目，已汇总到这里：
https://github.com/ww5365/tiny_util/blob/master/doc/retrival_ai/retrival_algorithm/03_%E6%B7%B1%E5%BA%A6%E6%A8%A1%E5%9E%8B_%E8%AF%AD%E4%B9%89%E5%8F%AC%E5%9B%9E.md
   

#### pytorch 专题

1. 重点学习了视频： 非常好
   https://www.bilibili.com/video/BV1zS4y1n7Eq/?spm_id_from=333.999.0.0&vd_source=ff1d5f0f1a1b50dc5fc0b20e64d1bba6

   形成了学习笔记及github的代码：https://github.com/ww5365/python/tree/master/deepshare
   

   




### 2022.5.31  回溯：

leetcode : 基本刷了一遍，持续性的

技术深度准备：transformer, bert 一半 ， 还差ltr

project 回顾和准备： 未准备

### 2022.6.10  进展

1.todolist ？


2. zijie 面的情况

* 一面：
  暴露两个问题：
  1. 项目准备的不充分，介绍项目思路稍有混乱，重点突出什么能力(技术)？ 或者 你想聊什么，突出你的能力？
  2. ES相关知识，忘了。


  leetcode：考察:最小子数组和




## todolist

resume准备 -> leetcode -> jingdong 项目为依托：召回和排序深入 (LTR,Transformer, BERT)  -> 项目 

1. resume
  
  作为准备的基版，涉及的点，都要准备下

  可能需要补充，项目的更新点


2. leetcode
  1. 依托trust考试，形成这块的算法体系。题目要实现，代码写一遍。
  2. 笔记本上题目要手写一遍


3. jingdong项目 - ml dl retrival rank

  * 指标

  ROC
  NDCG
  混淆矩阵

  * 排序特征
  
  文本：
  BM25
  CQR
  OFFSET

  点击：
  CTR
  用户需求分布

  *  ML DL
  
  树模型：
  CART -> GBDT  XGBOOST  -> Gbrank, lambdaMart (xgboost  lightGBM) -> deepFM (pytorch)
  
  深度模型:
  DSSM
  LSTM
  Transformer

  多目标
  模型压缩和蒸馏
  spark
  pytorch

  
  1) 召回：
     语义召回： 03_深度模型_语义召回.md

  
  
  2) 排序：




4. 项目

  项目难点？
  最好的项目？
  GC项目： 
  引入KG的空间召回能力
  检索评价体系： 产品问了一个问题，按下葫芦浮起瓢，质疑？ 怎会回事？ 怎么解决？

  开发diff工具
  引入人工评测和开发自评机制，关注diff率，GSB
  调研ABtest情况

  思路要同步到产品，测试(为什么要搞diff工具，为什么搭建diff环境)


  项目和领域深度思考 ？

  技术规划？  工程落地能力？思考


5. 目标职位

sp - one
岗位描述：
1. 负责公司核心地图搜索引擎的算法研发，不断探索业界前沿方法和技术，提升搜索系统效果。
2. 负责搜索系统相关性计算（语义、文本、点击等）及召回算法等技术方向的深入研究，探索模型设计和结构，探索学习目标和任务，优化解决方案。
3. 负责将算法成果应用到实际业务场景中，提升用户的搜索体验。

岗位要求：
1. 计算机、数学相关专业背景本科及以上学历，5年以上应用 ML/DL 技术和驱动 AI 产品（搜索、推荐等）方面的经验。
2. 扎实的算法理论基础，对最新的深度学习模型有深入的了解，如 DSSM、LSTM、Transforms 等。
3. 丰富的端到端机器学习任务、case 分析、数据增强、超参数调优、模型优化等方面经验。
4. 熟悉常见的机器学习框架，如 Pytorch 或 Tensorflow。
5. 具备良好的编程能力和数据结构算法基础，能熟练使用 Python/Java/C++ 等任一语言进行算法策略的落地部署，具备用 Hadoop/Hive/Spark/Flink 等大数据工具分析海量数据的能力。
6. 具备强烈的责任感，逻辑思维严谨清晰，具有优秀的分析问题和解决问题的能力，易于沟通协作。
7. 有 Dense Retrieval、多目标建模、模型压缩/蒸馏等经验者优先。






     



   



