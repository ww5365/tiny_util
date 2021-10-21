[TOC]

# ES相关知识总结

## ES基本命令

### 1 批量更新ES POST _bulk命令

1.1 更新或创建

{ "index" : { "_index" : "test", "_id" : "1" } }

{ "field1" : "value1" }

其中 “test” 是索引名 “1” 是 id, “value1”是 要更新或创建的对象

1.2 删除

{ "delete" : { "_index" : "test", "_id" : "2" } }

1.3 创建

{ "create" : { "_index" : "test", "_id" : "3" } }

{ "field1" : "value3" }

1.4 更新

{ "update" : {"_id" : "1", "_index" : "test"} }

{ "doc" : {"field2" : "value2"} }

### 2 Elasticsearch的查询

2.1查询（query）

查询（query）默认会计算每个返回文档的得分，然后根据得分排序

bool：可以组合多个查询条件，bool查询也是采用more_matches_is_better的机制，因此满足must和should子句的文档将会合并起来计算分值。

1. must：必须满足

   query 必须出现在匹配的文档中，并将有助于得分。

2. filter：过滤器 不计算相关度分数，cache☆

   query 必须出现在匹配的文档中。但是不像 must查询的分数将被忽略。Filter子句在filter上下文中执行，这意味着计分被忽略，并且子句被考虑用于缓存。

3. should：可能满足 or

   query 应出现在匹配的文档中。

4. must_not：必须不满足 不计算相关度分数 not

   query 不得出现在匹配的文档中。子句在过滤器上下文中执行，这意味着计分被忽略，并且子句被视为用于缓存。由于忽略计分，0因此将返回所有文档的分数。

   

例如：

``` json

{
    "query": {
        "bool": {
            "must": [{
                "match": {
                    "ids": {
                        "values": ["634C043DFE19DF5E3D17ACCE9F9D97A9"]
                    }
                }
            }]
        }
    }
}

```



2.2过滤（filter）

只会筛选出符合的文档，并不计算得分，且可以缓存文档

term精确值查询，示例1：

``` json

{
    "query" : {
      "constant_score" : { 
          "filter" : {
              "term" : { 
                  "price" : 20
              }
          }
      }
  }
}
```


terms多个精确值查询

```json
{
    "query" : {
        "constant_score" : { 
            "filter" : {
                "terms" : { 
                    "price" : [20,30]
                }
            }
        }
    }
}
```


Terms主分区精确值查询 primary 代表查询主分区的数据


``` json
{
    "query": {
        "bool": {
            "filter": [{
                "terms": {
                    "primary.id": ["634C043DFE19DF5E3D17ACCE9F9D97A9"]
                }
            }]
        }
    }
}

```