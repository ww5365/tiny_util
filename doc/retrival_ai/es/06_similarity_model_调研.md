# similarity model

## 一 similarity 相似度作用理解

相似度（评分/排名模型）定义了匹配文档的评分方式。每个字段具有相似性，这意味着可以通过映射为每个字段定义不同的相似性。


## 配置similarity

创建索引或更新索引设置时可以提供索引选项。

``` json
PUT /index
{
  "settings": {
    "index": {
      "similarity": {
        "my_similarity": {
          "type": "DFR",
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
配置 DFR 相似度，以便在映射中将其称为my_similarity，具体使用如下：

``` json
PUT /index/_mapping
{
  "properties" : {
    "title" : { "type" : "text", "similarity" : "my_similarity" }
  }
}
```

## available similarity

### BM25

参考es bm25的介绍：
https://www.cnblogs.com/novwind/p/15177871.html


### DFR


### DFI

### IB

### LM Dirichlet similarity


### LM Jelinek Mercer similarity

### Scripted similarity


下面给出了一个更高效的tf-idf分数计算：

``` json

PUT /index
{
  "settings": {
    "number_of_shards": 1,
    "similarity": {
      "scripted_tfidf": {
        "type": "scripted",
        "weight_script": {
          "source": "double idf = Math.log((field.docCount+1.0)/(term.docFreq+1.0)) + 1.0; return query.boost * idf;"    # idf = 1+log((N+1)/(tf +1))
        },
        "script": {
          "source": "double tf = Math.sqrt(doc.freq); double norm = 1/Math.sqrt(doc.length); return weight * tf * norm;" # tf= sqrt(tf)  doc.freq: 该term在该doc的该field中出现的次数 doc.length:doc中该字段的token数量 weight:如果没有weight_script则为1,The weight as calculated by a weight script.
        }
      }
    }
  },
  "mappings": {
    "properties": {
      "field": {
        "type": "text",
        "similarity": "scripted_tfidf"
      }
    }
  }
}

```

文档创建和打分情况：

``` json

PUT /index/_doc/1   # 创建文档1
{
  "field": "foo bar foo"
}

PUT /index/_doc/2  # 创建文档2
{
  "field": "bar baz"
}

POST /index/_refresh

GET /index/_search?explain=true #使用query进行搜索
{
  "query": {
    "query_string": {
      "query": "foo^1.7",   # 命中foo这个term，权重boost倍数：1.7
      "default_field": "field"
    }
  }
}

```

打分情况的结果：

```json

{
  "took": 12,
  "timed_out": false,
  "_shards": {
    "total": 1,
    "successful": 1,
    "skipped": 0,
    "failed": 0
  },
  "hits": {
    "total": {
        "value": 1,
        "relation": "eq"
    },
    "max_score": 1.9508477,
    "hits": [
      {
        "_shard": "[index][0]",
        "_node": "OzrdjxNtQGaqs4DmioFw9A",
        "_index": "index",
        "_type": "_doc",
        "_id": "1",
        "_score": 1.9508477,
        "_source": {
          "field": "foo bar foo"
        },
        "_explanation": {
          "value": 1.9508477,
          "description": "weight(field:foo in 0) [PerFieldSimilarity], result of:",
          "details": [
            {
              "value": 1.9508477,
              "description": "score from ScriptedSimilarity(weightScript=[null], script=[Script{type=inline, lang='painless', idOrCode='double tf = Math.sqrt(doc.freq); double idf = Math.log((field.docCount+1.0)/(term.docFreq+1.0)) + 1.0; double norm = 1/Math.sqrt(doc.length); return query.boost * tf * idf * norm;', options={}, params={}}]) computed from:",
              "details": [
                {
                  "value": 1.0,
                  "description": "weight",
                  "details": []
                },
                {
                  "value": 1.7,
                  "description": "query.boost",
                  "details": []
                },
                {
                  "value": 2,
                  "description": "field.docCount",  # 分片shard中该字段有值的文档数量
                  "details": []
                },
                {
                  "value": 4,
                  "description": "field.sumDocFreq", #The sum of all terms that exist for the current field. If this is not available the value is -1.这个字段，所有文档的terms数量，本例：foo, bar; bar baz
                  "details": []
                },
                {
                  "value": 5,
                  "description": "field.sumTotalTermFreq", ## The sum of occurrences in the index for all the terms that exist in the current field. If this is not available the value is -1. 出现在这个索引中的，这个字段上，所有的term的总数量，本例：foo,bar, foo; bar,baz
                  "details": []
                },
                {
                  "value": 1,
                  "description": "term.docFreq", # 分片shard中包含该term的文档数量，本例仅在doc1中包含foo这个term
                  "details": []
                },
                {
                  "value": 2,
                  "description": "term.totalTermFreq", #index中该term的总出现次数， 在doc1中出现2个
                  "details": []
                },
                {
                  "value": 2.0,
                  "description": "doc.freq", #该term在该doc的该field中出现的次数
                  "details": []
                },
                {
                  "value": 3,
                  "description": "doc.length", # 该字段的token数量，The number of tokens the current document has in the current field
                  "details": []
                }
              ]
            }
          ]
        }
      }
    ]
  }
}
```






## 更全的es的打分机制


https://cloud.tencent.com/developer/article/1747352






## 参考：

1、[es官方说明](https://www.elastic.co/guide/en/elasticsearch/reference/current/index-modules-similarity.html#configuration)

2、[Elasticsearch 7.10 之 Similarity module](https://blog.csdn.net/wang7075202/article/details/111193681)

