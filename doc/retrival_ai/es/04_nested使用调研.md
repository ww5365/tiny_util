#### nested

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

如果我们要搜索满足条件的子文档，返回的结果就不一定同时满足同一个子文档，所以需要nested保证子文档的完整性。（[ElasticSearch - 嵌套对象 nested_kucw的博客-CSDN博客_es nested](https://blog.csdn.net/weixin_40341116/article/details/80778599)）

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





参考：



[干货 | Elasticsearch Nested类型深入详解](https://cloud.tencent.com/developer/article/1357697)

[Elasticsearch Nested 选型，先看这一篇](https://www.modb.pro/db/102685)



```json
{
    "id":1,
    "name":"联想ThinkPad P1(01CD)",
    "price":29999,
    "brand":"Lenovo",
    "attributes":[
        {
            "attribute_name":"cpu",
            "attribute_value":"Intel Core i9-10885H"
        },
        {
            "attribute_name":"memory",
            "attribute_value":"32GB"
        },
        {
            "attribute_name":"storage",
            "attribute_value":"2TB"
        }
    ]
}


{
    "query":{
        "bool":{
            "must":[
                {
                    "match":{
                        "attributes.attribute_name":"cpu"
                    }
                },
                {
                    "match":{
                        "attributes.attribute_value":"32GB"
                    }
                }
            ]
        }
    }
}


{ "id": 1,"name": "联想ThinkPad P1(01CD)","price": 29999,"brand": "Lenovo","attributes.attribute_name": ["cpu", "memory", "storage"], "attributes.attribute_value": [“Intel Core i910885H”, “32GB”, “2TB”] }




{
    "mappings":{
        "properties":{
            "id":{
                "type":"long"
            },
            "name":{
                "type":"text",
                "analyzer":"ik_max_word"
            },
            "price":{
                "type":"long"
            },
            "brand":{
                "type":"keyword"
            },
            "attributes":{
                "type":"nested",
                "properties":{
                    "attribute_name":{
                        "type":"keyword"
                    },
                    "attribute_value":{
                        "type":"keyword"
                    }
                }
            }
        }
    }
}


{
    "query":{
        "nested":{
            "path":"attributes",
            "query":{
                "bool":{
                    "must":[
                        {
                            "match":{
                                "attributes.attribute_name":"cpu"
                            }
                        },
                        {
                            "match":{
                                "attributes.attribute_value":"8GB"
                            }
                        }
                    ]
                }
            }
        }
    }
}
```

