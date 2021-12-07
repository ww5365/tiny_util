﻿﻿﻿﻿﻿# ElasticSearch DSL详解和召回场景解决方案

## 前言

本文主要关注ElasticSearch 7.x 中文档搜索和DSL查询部分。本文参照的知识来源于官方ElasticSearch 7.9英文文档。鉴于ElasticSearch相比之前的版本有较大改动，更多信息补充不建议参考中文翻译版《ElasticSearch权威指南》，建议参考官方7.x英文文档和ElasticSearch 7.x相关博客。



## DSL核心概念：过滤&打分

详情参见[Query and filter context | Elasticsearch Guide 7.14 | Elastic](https://www.elastic.co/guide/en/elasticsearch/reference/7.14/query-filter-context.html)。

文档搜索和DSL查询的核心逻辑是查找满足最多条件的文档，实现这个的途径是相关度打分，每个最基础的打分语句从最细的Query语句开始，如下以match语句为例。

```
    "match": {
      "message": {
        "query": "this is a test"
      }
    }
```

每个最小的Query语句都会对要匹配的字段（e.g. message）进行匹配度打分。

复合语句通过组合上面最细的Query语句从而集合分数（一般将所有语句的分数加和起来）。

```
    "bool" : {
      "must" : {
        "term" : { "user.id" : "kimchy" }
      },
      "filter": {
        "term" : { "tags" : "production" }
      },
      "must_not" : {
        "range" : {
          "age" : { "gte" : 10, "lte" : 20 }
        }
      },
      "should" : [
        { "term" : { "tags" : "env1" } },
        { "term" : { "tags" : "deployed" } }
      ]
    }
```



### Query

Query语句注重于在一个查询的句子中有多少能够匹配字段，并对匹配的程度进行打分。match、term等语句都具有Query属性。

### Filter

Filter语句只关注查询的句子中与字段是否完全匹配并给出二值判断。

1. 无打分情况下，使用Filter会过滤掉不合要求的文档，之后的语句处理的文档会减少，同时过滤的文档会缓存，加快查询速度（e.g. 上面bool语句中的filter）

2. 有打分情况下，除了上一点的效果外，需要外层特定语句的支持，如下对于constant_score，如果filter返回的结果为true，constant_score就会打固定的分数，由boost指定。

   ```
   "constant_score": {
     "filter": {
       "term": { "user.id": "kimchy" }
     },
     "boost": 1.2
   }
   ```

### 一般形式

一般的DSL由query语句进入，内容由复合查询连接独立查询语句，形成query-复合-子语句的结构。

```
{
  "query"（query）: { 
    "bool"（复合语句）: { 
      "must"（复合语句参数）: [
        { "match"（子查询）: { "title":   "Search"        }},
        { "match"（子查询）: { "content": "Elasticsearch" }}
      ],
      "filter"（复合语句参数）: [ 
        { "term"（子查询）:  { "status": "published" }},
        { "range"（子查询）: { "publish_date": { "gte": "2015-01-01" }}}
      ]
    }
  }
}
```

## ES打分公式：Okapi BM25

对于一个标准的子语句，衡量匹配程度的语句（match语句系列）：

    "match": {
      "message": {
        "query": "this is a test"
      }
    }
    
    目标字段message内容：this is a quiz
通过比较两个内容匹配程度（这里match比较有多少个单词匹配），ElasticSearch可以打出分数来衡量匹配程度。

旧版本ES使用的默认打分公式为标准TF-IDF公式结合协调因子等其它参数，目前已经废弃。ElasticSearch 7.x默认使用Okapi BM25打分公式。

BM25分数由Query中每个单词$q_i$的TF和IDF之积的总和计算：

$$
\sum_{i=1}^{n} IDF(q_i)\times TF(q_i)
$$

其中
$$
IDF(q_i)=ln(\frac{N-n(q_i)+0.5}{n(q_i)+0.5}+1)
$$
$N$为所有查询的文档数量，$n(q_i)$为含有$q_i$的文档数量
$$
TF(q_i)=\frac{f(q_i,D)\cdot2.2}{f(q_i,D)+k_1\cdot(1-b+b\cdot\frac{|D|}{avgdl})}
$$

其中$f(q_i,D)$为$q_i$在文档出现的次数，$|D|$为查询的字段的单词长度，$avgdl$为所有查询文档中该字段的平均长度，默认$k_1=1.2,b=0.75$。

ElasticSearch相比标准Okapi BM25，不同的地方在于$TF(q_i)$中$k_1+1$被修改为定值$2.2$。

进一步，大多数语句具有boost参数：

    "match": {
      "query": {
        "term": { "user.id": "kimchy" }
      },
      "boost": 1.2
    }

boost参数乘以BM25打分为子查询语句的最终得分，可以提升查询的重要程度：
$$
boost\times\sum_{i=1}^{n} IDF(q_i)\times TF(q_i)
$$

### 功能

- ES查询打分可以调整的参数有$k_1,b$，前者可以调整词频的影响，$k_1$越小词频的影响越低（$f(q_i,D)$增大得分上升的程度越低），$b$越大让目标字段越短的文档相对得分越高。在召回POI的名字或者地址时调低$k_1$可以防止一个单词重复出现导致得分无意义升高而其它$q_i$完全没有匹配的情况发生，调高$b$可以防止匹配Qeury但与Query无关的内容很多的长文档字段被召回。

- ES查询具有explain功能，可以详细显示对某文档Query中各语句的打分和加总情况，在最外层与query并列使用：

  ```
  {
    "query"（query）: { 
      "bool"（复合语句）: { 
        "must"（复合语句参数）: [
          { "match"（子查询）: { "title":   "Search"        }},
          { "match"（子查询）: { "content": "Elasticsearch" }}
        ],
        "filter"（复合语句参数）: [ 
          { "term"（子查询）:  { "status": "published" }},
          { "range"（子查询）: { "publish_date": { "gte": "2015-01-01" }}}
        ]
      }
    },
    "explain":true
  }
  
  返回的结果如下：
  "_explanation":{
  	......
  }
  ```

  详细的解读请参考[es 仅返回单个字段 查询_ES系列13：彻底掌握相关度：从TF-IDF、BM25到对相关度的控制..._李诗旸的博客-CSDN博客](https://blog.csdn.net/weixin_35782943/article/details/112331093)。



## DSL语句功能大纲

- BM25：对match等语句返回理想的简洁只含有不重复的精准召回结果重要，在ES生成索引（mapping）中调整$k_1,b$的值。

- 复合查询（[Compound queries | Elasticsearch Guide 7.14 | Elastic](https://www.elastic.co/guide/en/elasticsearch/reference/7.14/compound-queries.html)）

  - bool：组合查询语句和加和打分（[Boolean query | Elasticsearch Guide 7.14 | Elastic](https://www.elastic.co/guide/en/elasticsearch/reference/7.14/query-dsl-bool-query.html)）
    - should：条件任意满足，返回满足的条件的分数之和
    - must：既要求文档满足所有的条件，又要返回完全匹配情况下的匹配度得分
    - filter：不满足条件的文档完全不再考虑打分，加快查询速度
    - must_not：filter的反面，满足条件的文档完全不再考虑打分
  - constant_score：不考虑Query和目标字段匹配单词数越多越好，只考虑是否满足最低匹配条件（[Constant score query | Elasticsearch Guide 7.14 | Elastic](https://www.elastic.co/guide/en/elasticsearch/reference/7.14/query-dsl-constant-score-query.html)）
  - boosting：有特定匹配会产生负向影响，想减少负向匹配出现程度时使用（[Boosting query | Elasticsearch Guide 7.14 | Elastic](https://www.elastic.co/guide/en/elasticsearch/reference/7.14/query-dsl-boosting-query.html)）
  - dis_max：文档满足多个语句的要求而只关心最匹配字段的匹配情况（[Disjunction max query | Elasticsearch Guide 7.14 | Elastic](https://www.elastic.co/guide/en/elasticsearch/reference/7.14/query-dsl-dis-max-query.html)）
  - function_score：对不同Query的打分组合或者对文档中某些字段的Query语句打分有复杂的自定义要求（[Function score query | Elasticsearch Guide 7.14 | Elastic](https://www.elastic.co/guide/en/elasticsearch/reference/7.14/query-dsl-function-score-query.html)）

- 子语句

  - 匹配查询（切词，根据匹配的词数衡量匹配得分）
    - match & match_phrase（匹配&完整匹配）
    - multi_match（匹配多个字段）
  - 整词查询（不切词，boolean判断整个Query是否匹配）
    - term & terms & terms_set（完整匹配&多字段匹配）
  - 子文档列表查询（针对以列表形式储存多个子文档的字段搜索）
    - nested（以子文档为单位查询）
  - 地理查询（针对坐标字段的位置搜索）
  - 特殊查询
    - distance_feature（根据距离计算得分）

- minimum_should_match（限定match中至少要匹配的词语数量）

- rescore（对最外层query返回的粗排在前列的文档再进行细化的打分再排序）

- 索引相关（建立索引在Query查询之前）

  - copy_to（多个字段预先合并内容）
  - similarity_module（自定义match打分模型）

  

## 召回场景解决方案

- 加快查询速度：由于给文档匹配度打分是查询中耗时的核心内容，我们有两种解决方案：
  - 减少需要打分的文档数：使用bool中的filter可以减少打分的文档数量，使用打分语句constant_score等的filter可以缓存
    - 灵活使用minimum_should_match：我们对召回目标匹配的最低词数有一个基础的判断，可以过滤掉匹配词数较少的文档
  - 减少需要打分的查询语句数量：减少Query语句的数量（复合语句和子语句），减少条件判断数量
  - 减少需要搜索的字段数：在mapping时使用copy_to合并多个字段以便统一搜索（逻辑与multi_match中的cross_fields相同，使用请参照该场景）
  - 对单个条件选择更快的语句：
    - 用term替代match，因为term不分词整体搜索，match分词且逐个按词搜索
    - 减少使用function_score、script_score等自定义打分语句，避免使用其它语言驱动的函数计算分数
  - 特定搜索预先索引化：例如搜索numeric范围对经常搜索的范围建立boolean新字段，避免使用range
  - 改变数据类型：；例如将numeric改为keyword，可以使用term进行更快的完全匹配  
- 调整匹配度打分，要回理想的简洁只含有不重复的精准召回结果：
  - 在ES生成索引（mapping）中调整$k_1,b$的值
  - 细化召回条件，Query越短越容易满足，POI和地址分开搜索
  - 改变ES匹配打分公式
    - 创建索引时改变相似度计算公式，改变$TF$、$IDF$的计算方法（[Similarity module | Elasticsearch Guide 7.9 | Elastic](https://www.elastic.co/guide/en/elasticsearch/reference/7.9/index-modules-similarity.html)）
    - 召回时使用function_score/script_score设计打分公式，但是速度上劣于创建索引时改写公式
- 针对坐标的限制
  - 地理位置搜索相关语句geo_bounding_box，geo_polygon，geo_distance验证坐标点是否在范围内
  - function_score支持对坐标使用多种形式的打分函数，根据文档坐标与目标坐标间的距离打分
  - distance_feature提供另一种距离打分公式
- 针对语句查询的字段场景调试查询的boost权重，例如查询地址和POI名称，哪一个具有更高的权重需要考虑，意味着Query会优先满足权重高的字段的匹配程度
- 对查询多个字段的多个语句的打分组合有自定义计算公式，使用multi_match、dis_max或function_score
- 在有合并排序的情况下，Query查询召回应针对多种情况细化拆分，每个Query尽量缩短，功能和查询的Query参数尽量互相独立
- 查询使用的参数要与查询字段的含义对齐，详情参见模板参数与结构分析文档
- 过滤Filter和打分Query应互相独立，先过滤后打分，对打分后的前排文档有再精排的需求，在后面使用rescore语句



## 复合查询



### bool

bool语句保证了不同的Query能以逻辑判断形式组合使返回的文档满足逻辑要求，所有满足的条件得到的打分加起来代表文档和Query的整体匹配程度。

```console
{
  "query": { 
    "bool": { 
      "must": [
        { "match": { "title":   "Search"        }},
        { "match": { "content": "Elasticsearch" }}
      ],
      "should" : [
        { "term" : { "tags" : "env1" } },
        { "term" : { "tags" : "deployed" } }
      ],
      "filter": [ 
        { "term":  { "status": "published" }},
        { "range": { "publish_date": { "gte": "2015-01-01" }}}
      ]
    }
  }
}
```

- should：满足任一条件的文档被返回，返回满足的条件的分数之和
- must：要求文档满足所有的条件才返回，返回完全匹配情况下的匹配度得分之和
- filter：不满足条件的文档完全不再考虑打分，满足条件的文档被缓存
- must_not：filter的反面，满足条件的文档完全不再考虑打分，不满足条件的文档被缓存

### constant_score

constant_score只关注条件是否满足，满足条件即返回固定的打分，值等于boost：

```console
{
  "query": {
    "constant_score": {
      "filter": {
        "term": { "user.id": "kimchy" }
      },
      "boost": 1.2
    }
  }
}
```

### boosting

请参见[9.1.1-elasticsearch复合查询之bool/boosting查询_红笺小字-CSDN博客](https://blog.csdn.net/weixin_28906733/article/details/106726932)。

对于有些条件希望召回结果尽量不满足，不用must_not完全排除，可以使用boosting对这些条件设置负向加权：

```console
{
  "query": {
    "boosting": {
      "positive": {
        "term": {
          "text": "apple"
        }
      },
      "negative": {
        "term": {
          "text": "pie tart fruit crumble tree"
        }
      },
      "negative_boost": 0.5
    }
  }
}
```

positive和negative分别包裹要正向加权和负向加权的子语句，用negative_boost设定negative中子语句的负向权重。

### dis_max

请参见[Elasticsearch复合查询—dis_max查询_Chdaring的博客-CSDN博客](https://blog.csdn.net/co_zjw/article/details/109811572)。

与bool语句在组合文档满足多个语句的要求上相同，但是在打分上如果只关心其中任意一个字段能达到最大匹配的情况则使用该语句。

```console
{
  "query": {
    "dis_max": {
      "queries": [
        { "term": { "title": "Quick pets" } },
        { "term": { "body": "Quick pets" } }
      ],
      "tie_breaker": 0.7
    }
  }
}
```

结合tie_breaker，dis_max对所有匹配子语句的分数加和算法为：
$$
Score_{最匹配打分最高语句}+tie\_breaker\times \sum Score_{其它匹配语句}
$$

### function_score

请参照[ElasticSearch - function_score 简介_kucw的博客-CSDN博客](https://blog.csdn.net/weixin_40341116/article/details/80913045)。

function_score作为可以对子语句自定义打分的语句，使用方式灵活，有多种打分语句可以选择：

- [`script_score`](https://www.elastic.co/guide/en/elasticsearch/reference/7.9/query-dsl-function-score-query.html#function-script-score)
- [`weight`](https://www.elastic.co/guide/en/elasticsearch/reference/7.9/query-dsl-function-score-query.html#function-weight)
- [`random_score`](https://www.elastic.co/guide/en/elasticsearch/reference/7.9/query-dsl-function-score-query.html#function-random)
- [`field_value_factor`](https://www.elastic.co/guide/en/elasticsearch/reference/7.9/query-dsl-function-score-query.html#function-field-value-factor)
- [decay functions](https://www.elastic.co/guide/en/elasticsearch/reference/7.9/query-dsl-function-score-query.html#function-decay)（衰减函数）: `gauss`, `linear`, `exp`

对上面的语句和，function_score可以再组合自定义打分：

```console
{
  "query": {
    "function_score": {
      "query": { "match_all": {} },
      "boost": "5", 
      "functions"（组合打分语句）: [
        {
          "filter": （满足条件的按照本语句规则打分）{ "match": { "test": "bar" } },
          "random_score": {}, 
          "weight": 23
        },
        {
          "filter"（满足条件的按照本语句规则打分）: { "match": { "test": "cat" } },
          "weight": 42
        }
      ],
      "max_boost": 42,
      "score_mode": "max"（满足多个函数的总分的计算规则）,
      "boost_mode": "multiply",
      "min_score": 42
    }
  }
}
```

#### script_score

在获得满足Query的文档后，script_score能通过取到文档字段内容等多种参数和写函数式语句自定义打分：

```console
{
  "query": {
    "function_score": {
      "query": {
        "match": { "message": "elasticsearch" }
      },
      "script_score": {
        "script": {
          "source": （自定义函数）"Math.log(2 + doc['my-int'].value（取到'my_int'字段的值）)"
        }
      }
    }
  }
}
```

#### decay_function

decay_function针对数字字段值和目标值的距离计算随距离增大逐渐减小的分数，对geo_point地理点格式同样成立。gauss（高斯函数）、exp（指数函数）、linear（线性函数）都涉及四种用户定义参数：

- origin：目标点，函数中心点，也即最高值
- offset：从目标点延伸的一段平台距离，在offset之类打分维持中心点一样
- decay & scale：从offest开始，分数衰减到decay的时候延伸的距离为scale

四个参数和三种decay_function的分数计算可视化如下：

![decay 2d](https://www.elastic.co/guide/en/elasticsearch/reference/7.9/images/decay_2d.png)

关于decay_function具体函数的详细公式与使用，参见[Function score query | Elasticsearch Guide 7.9 | Elastic](https://www.elastic.co/guide/en/elasticsearch/reference/7.9/query-dsl-function-score-query.html#function-decay)

## 子语句

### 匹配查询

匹配查询的核心在于切词后检验单词匹配的数量频率总的程度，根据匹配的词数衡量匹配得分。根据单词匹配形式、单词之间的距离、多字段匹配等有多种专有语句使用，我们的关注点如下：

- match & match_phrase（匹配&完整匹配）
- multi_match（匹配多个字段）

#### match & match_phrase

match对单Query，对单字段进行词语匹配打分，应用默认的BM25打分。

- operator：控制单词之间的逻辑关系，or允许匹配一个及以上单词，and要求所有分词都要匹配
- analyzer：设置将Query切割成分词的分析器
- minimum_should_match：限定至少要匹配的分词数量

更多参数请参见[Match query | Elasticsearch Guide 7.9 | Elastic](https://www.elastic.co/guide/en/elasticsearch/reference/7.9/query-dsl-match-query.html)

match_phrase 则限定了对所有单词看成一个整体phrase进行搜索，单词间的距离可以通过slop进行调节。

- slop：单词间允许出现的间隔长度，例如slop=1，quick fox之间可以匹配出现一个单词的情况quick red fox。

更多参数请参见[Elasticsearch - 短语匹配(match_phrase)以及slop参数_何成俭的博客-CSDN博客_match_phrase](https://blog.csdn.net/sinat_29581293/article/details/81486761)

#### multi_match

multi_match是针对使用多个match语句，用同一个Query搜索多个字段设置的合并和打分策略设置的检索。

```console
{
  "query": {
    "multi_match" : {
      "query":    "this is a test", 
      "fields"（搜索的字段列表）: [ "subject^3（通过^可以给指定字段加上权重）", "message" ] 
    }
  }
}
```

multi_match参数的搜索和打分联合策略的核心在参数type上：

- best_fields：分词在任一字段上面匹配均可，打分时取最匹配的字段的分数为返回分数，也即关注最匹配情况，与dis_max相同
- most_fields：分词在任一字段上面匹配均可，打分时取所有匹配的字段的分数和为返回分数，关注所有字段的整体匹配情况
- cross_fields：将所有字段视为一个字段，计算匹配度在融合字段上进行，针对单词散落在多个字段中但是组合成完整Query

详情参见[elasticsearch优化之多字段搜索multi_match查询_bugSeeking的博客-CSDN博客](https://blog.csdn.net/danger0629/article/details/102695894)

### 整体查询

整体查询以term为核心，不对Query切词，将Query整体投入搜索，要求完全匹配，返回boolean判断整个Query是否匹配。所以与不要求完全匹配。靠匹配度进行区分的match系列语句，term适合搜索没有切词的keyword语句，避免对要分词的text类型文本搜索。

#### term & terms & terms_set

一个基本的terms形式如下。

```console
{
  "query": {
    "term": {
      "user.id"（字段）: {
        "value": "kimchy",
        "boost"（权重）: 1.0
      }
    }
  }
}
```

terms针对多个Query搜索一个字段进行整合：

```console
{
  "query": {
    "terms": {
      "user.id": [ "kimchy", "elkbee" ]（所以Query形成列表）,
      "boost": 1.0
    }
  }
}
```

terms_set针对包含多个keyword的列表格式的字段，用多个Query的列表搜索并保证匹配的Query数量：

```console
对列表形式的字段：
{
  "name": "Jason Response",
  "programming_languages": [ "java", "php" ]（keyword组成的列表）,
  "required_matches": 2
}

{
  "query": {
    "terms_set": {
      "programming_languages"（搜索字段）: {
        "terms"（Query列表）: [ "c++", "java", "php" ],
        "minimum_should_match_field"（至少匹配的Query数量）: "required_matches"
      }
    }
  }
}
```

### 子文档列表查询

nested针对以列表形式储存多个子文档的字段进行搜索，这些字段的type类型就是nested：

```console
{
  "driver" : {
        "last_name" : "Hudson",
        "vehicle" : （以列表形式存储的子文档）[
            {
                "make" : "Mifune",
                "model" : "Mach Five"
            }（子文档）,
            {
                "make" : "Miller-Meteor",
                "model" : "Ecto-1"
            }（子文档）
        ]
    }
}
```

如果不使用nested进行搜索，上面搜索vehicle.make/model时就会融合子文档，变成:

```
"vehicle.make":["Mifune","Miller-Meteor"]
"vehicle.model":["Mach Five","Ecto-1"]
```

如果我们要搜索满足条件的子文档，返回的结果就不一定满足时同一个子文档，所以需要nested保证子文档的完整性。（[ElasticSearch - 嵌套对象 nested_kucw的博客-CSDN博客_es nested](https://blog.csdn.net/weixin_40341116/article/details/80778599)）

#### nested

nested保证了对nested字段以子文档为单位查询，只有列表中的任意文档中的字段内容完整满足Query才返回结果：

```console
{
  "query": {
    "nested": {
      "path": "obj1"（指定子文档列表字段）,
      "query"（搜索语句）: {
        "bool": {
          "must": [
            { "match": { "obj1.name"（子文档中的字段）: "blue" } },
            { "range": { "obj1.count"（子文档中的字段）: { "gt": 5 } } }
          ]
        }
      },
      "score_mode"（多个子文档匹配时的打分策略）: "avg"
    }
  }
}
```

多个子文档匹配时的打分策略在score_mode中设定：

- max：所有匹配子文档得分的最大值
- min：所有匹配子文档得分的最小值
- avg：所有匹配子文档得分的平均值
- sum：所有匹配子文档得分的和
- none：只匹配，不打分

详情参见[Nested query | Elasticsearch Guide 7.9 | Elastic](https://www.elastic.co/guide/en/elasticsearch/reference/7.9/query-dsl-nested-query.html)

### 地理查询

ElasticSearch可以将地理信息以Geo形式储存，有针对坐标字段的位置进行搜索的语句。

- geo_point：有坐标的地理点
- geo_shape：表示一块区域的形状、坐标等信息

相关语句如下：

- geo_bounding_box：左上和右下坐标形成方形，验证字段坐标是否在内：

```console
        "geo_bounding_box": {
          "pin.location"（坐标字段）: {
            "top_left"（左上）: {
              "lat": 40.73,
              "lon": -74.1
            },
            "bottom_right"（右下）:{ 
              "lat": 40.01,
              "lon": -71.12
            }
          }
        }
```

- geo_distance：以设定坐标为圆心，验证字段坐标是否在圆内：

```console
        "geo_distance": {
          "distance"（半径）: "200km",
          "pin.location"（坐标字段）: {
          	（设定圆心）
            "lat": 40,
            "lon": -70
          }
        }
```

- geo_polygon：验证字段坐标是否在设定的多边形内：

```console
        "geo_polygon": {
          "person.location"（坐标字段）: {
            "points"（多边形顶点）: [
              { "lat": 40, "lon": -70 },
              { "lat": 30, "lon": -80 },
              { "lat": 20, "lon": -90 }
            ]
          }
        }
```

- geo_shape：针对geo_shape和geo_point，支持更多地理搜索形状，支持相交、包含等字段&搜索形状关系

详情参见[Geo queries | Elasticsearch Guide 7.9 | Elastic](https://www.elastic.co/guide/en/elasticsearch/reference/7.9/geo-queries.html)

### 特殊查询

#### distance_feature

distance_feature为数字、时间、距离等计算得分，与decay_function相似，计算公式如下：
$$
Score=boost\times \frac{pivot}{pivot+distance},boost\&pivot为设置参数
$$


### minimum_should_match

minimum_should_match针对match等分词匹配度语句，限定至少要匹配的词语数量：

| 类型     | 例子        | 解释                                                         |
| -------- | ----------- | ------------------------------------------------------------ |
| 整数     | 3           | 至少满足整数个词数（例子：满足至少3个）                      |
| 负整数   | -2          | 最多不满足整数个词数（例子：最多不满足2个）                  |
| 百分比   | 75%         | 满足百分比比例词数，向下取整（例子：满足75%个词数）          |
| 负百分比 | -25%        | 不满足百分比比例词数，向下取整（例子：最多不满足25%个词数）  |
| 区间结合 | 3<90%       | 左侧整数表示整数总长度整数及以下的Query要全部匹配，以上的Query满足右侧百分比要求（例子：3个和以下全部匹配，3个以上整体匹配90%） |
| 多区间   | 2<70% 4<50% | 多区间叠加以左侧整数为分割，按照Query词数长度，超过某个区间按照该区间右侧条件执行（例子：小于等于2词全部匹配，大于2词按70%比例匹配，大于4词按50%比例匹配） |

详情参见[elasticsearch中minimum_should_match的一些理解_xiao_jun_0820的专栏-CSDN博客](https://blog.csdn.net/xiao_jun_0820/article/details/51095521)

### rescore

rescore与最外层的query并列，对最外层query返回的粗排在前列的文档再进行细化的打分再排序：

```console
{
   "query" : {
      "match" : {
         "message" : {
            "operator" : "or",
            "query" : "the quick brown"
         }
      }
   },
   "rescore"（与query并列） : {
      "window_size" : 50,
      "query" : {
      	 "score_mode"（与前面传递的打分结合方式）:"total"
         "rescore_query" : {
            "match_phrase" : {
               "message" : {
                  "query" : "the quick brown",
                  "slop" : 2
               }
            }
         },
         "query_weight" : 0.7,
         "rescore_query_weight" : 1.2
      }
   }
}
```

- window_size：取前面的query传递下来的文档的前window_size位进行再打分，默认取前10个文档
- score_mode：与前面传递下来的分数结合的算法
  - total：与前面的分数相加
  - multiply：与前面的分数相乘
  - avg：取二者平均数
  - max/min：取二者最大/最小值
- query_weight：与前面传递下来的分数结合计算时前面的分数的加权
- rescore_query_weight：与前面传递下来的分数结合计算时rescore分数的加权

可以以列表形式使用多个rescore_query，层层选择层层计算：

```console
{
   "query" : {
      "match" : {
         "message" : {
            "operator" : "or",
            "query" : "the quick brown"
         }
      }
   },
   "rescore" : （列表形式包括多个rescore_query）[ {
      "window_size" : 100,（第一层选择100个重打分）
      "query" : {
         "rescore_query" : {
            "match_phrase" : {
               "message" : {
                  "query" : "the quick brown",
                  "slop" : 2
               }
            }
         },
         "query_weight" : 0.7,
         "rescore_query_weight" : 1.2
      }
   }, {
      "window_size" : 10,（第二层选择10个重打分）
      "query" : {
         "score_mode": "multiply",
         "rescore_query" : {
            "function_score" : {
               "script_score": {
                  "script": {
                    "source": "Math.log10(doc.count.value + 2)"
                  }
               }
            }
         }
      }
   } ]
}
```

## 索引创建

在DSL查询之外，索引创建时的一些因素也跟提高查询速度和准确度相关，建立索引在Query查询之前，所以需要预先规划。

### copy_to

对于经常被同一个Query使用multi_match等同时搜索的多个字段，multi_match的跨字段搜索耗费时间，字段越多效率越低。可以通过在建立索引时预先合并多个字段的内容，达到在一个字段中搜索的目的。融合字段搜索的概念与multi_match中cross_fields相同，建议经常搜索cross_fields时用copy_to预先建好索引。

```console
PUT my-index-000001
{
  "mappings": {
    "properties": {
      "first_name": {
        "type": "text",
        "copy_to"（指定合并到新字段名）: "full_name" 
      },
      "last_name": {
        "type": "text",
        "copy_to"（指定合并到新字段名）: "full_name" 
      },
      "full_name": {
        "type": "text"
      }
    }
  }
}

PUT my-index-000001/_doc/1
{
  "first_name": "John",
  "last_name": "Smith"
}

GET my-index-000001/_search
{
  "query": {
    "match": {
      "full_name"（可以使用新字段检索）: { 
        "query": "John Smith",
        "operator": "and"
      }
    }
  }
}
```

### similarity_module

建立索引时可以自定义ElasticSearch的匹配打分公式：

```console
PUT /index/_mapping
{
  "properties" : {
    "title" : { "type" : "text", "similarity"（选择打分公式） : "my_similarity" }
  }
}
```

ElasticSearch自带的打分公式如下：

- BM25
- DFR
- DFI
- IB
- LMDirichlet
- LMJelinekMercer

公式和各参数通过建立自定义公式名完成（各参数请参照[Similarity module | Elasticsearch Guide 7.9 | Elastic](https://www.elastic.co/guide/en/elasticsearch/reference/7.9/index-modules-similarity.html)）：

```console
PUT /index
{
  "settings": {
    "index": {
      "similarity": {
        "my_similarity"（自定义名）: {
          "type": "DFR",（选择公式）
          （公式参数）
          "basic_model": "g",
          "after_effect": "l",
          "normalization": "h2",
          "normalization.h2.c": "3.0"
        }
      }
    }
  }
}
```

进一步，用户可以通过script写函数的形式直接定义打分函数：

```console
PUT /index
{
  "settings": {
    "number_of_shards": 1,
    "similarity": {
      "scripted_tfidf": {
        "type": "scripted"（表明类型为自定义函数）,
        "script": {（通过使用painless语言取得文档频率、词频等数值计算返回自定义打分结果）
          "source": "double tf = Math.sqrt(doc.freq); double idf = Math.log((field.docCount+1.0)/(term.docFreq+1.0)) + 1.0; double norm = 1/Math.sqrt(doc.length); return query.boost * tf * idf * norm;"
        }
      }
    }
  },
  "mappings": {
    "properties": {
      "field": {
        "type": "text",
        "similarity": "scripted_tfidf"（mapping选择自定义scripted_tfidf）
      }
    }
  }
}
```

## 参考

1.极客时间[Elasticsearch核心技术与实战](https://time.geekbang.org/course/detail/197-142584), 已下载视频。 另外看到一门课：[检索技术核心20讲](https://time.geekbang.org/column/intro/100048401)  
2.《ElasticSearch实战》 作者: Radu Gheorghe 出版社: 人民邮电出版社
3.《相关性搜索：利用Solr与Elasticsearch创建智能应用》 作者: [美]Doug Turnbull (道格·特恩布尔) 出版社: 电子工业出版社 [书评](https://book.douban.com/subject/27157298/)




---



