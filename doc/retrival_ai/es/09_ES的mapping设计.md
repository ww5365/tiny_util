# ES的mapping设计


## 

``` json

"mappings": {
  "properties": {
     "index_tag": {
       "type": "keyword", //数据类型
       "store": true  //仅仅存储，创建索引
      },
     "primary": { //属性字段名称
          "properties": { //可以嵌套定义属性字段，访问时使用： primary.address
            "address": {
              "type": "text",
              "analyzer": " index_analyzer", //索引构建使用分词器
              "search_analyzer": " search_analyzer" //在线搜索时使用的分词器
            },
            "alias_checked": {
              "type": "nested",
              "properties": {
                "lang": {
                  "type": "keyword",
                  "store": true
                },
                "name": {
                  "type": "text",
                  "store": true,
                  "analyzer": " index_analyzer",
                  "search_analyzer": " search_analyzer"
                }
              }
            },
            "esDocId": {
              "type": "keyword"
            },
            "id": {
              "type": "keyword"
            },
            "info": {
              "type": "nested",  //nested类型， 子文档类型
              "properties": {
                "address": {
                  "type": "text",
                  "analyzer": " index_analyzer",
                  "search_analyzer": " search_analyzer"
                },
                "name": {
                  "type": "text",
                  "analyzer": " index_analyzer",
                  "search_analyzer": " search_analyzer"
                }
              }
            },
            "lat_lng": {
              "type": "geo_point"
            },
            "type": {
              "properties": {
                "level_1": {
                  "type": "keyword"
                },
                "level_2": {
                  "type": "keyword"
                },
                "level_3": {
                  "type": "keyword"
                },
                "level_4": {
                  "type": "keyword"
                }
              }
            }
          }
        }
  }

```

```json

      {
        "_index": "indexName",
        "_type": "_doc",
        "_id": "10000000000000",
        "_score": 16.656557,
        "_source": {
          "final_score": 0.0,
          "src_id": "3c9fd",
          "quality_score": 0.0,
          "details": {
            "country_code": "MY",
            "city_site_id": "11222",
            "contact": {}
          },
          "primary": {
            "esDocId": "106",
            "address": "Mukim 13,Mukim 13,Daerah Tengah,Pulau Pinang,Malaysia",
            "lat_lng": [
              100.4,
              5.2
            ],
            "id": "106",
            "type": {
              "level_3": [
                "110001"
              ],
              "level_1": [
                "11"
              ],
              "level_2": [
                "1100"
              ]
            },
            "info": [  // 这是nested类型，子文档
              {
                "address": "Mukim 13,Mukim 13,Daerah Tengah,Pulau Pinang,Malaysia",
                "name": "Jalan Perindustrian Bukit Minyak 8"
              }
            ]
          }
        }
      }

```





## mapping中的参数 - fields



fields 它可以使同一个字段通过不同的方式实现不同的目的

```json
PUT my-index-000001
{
  "mappings": {
    "properties": {
      "city": {
        "type": "text",  // 全文搜索 分词
        "fields": {
          "raw": {
            "type":  "keyword", // 同时可以利用fields设置为keyword类型，用于排序和聚合。
            "normalizer": "my_lowercase"
          }
        }
      }
    }
  }
}
```



查询时我们就可以使用`city`进行全文检索，使用`city.raw`进行排序和聚合。

```json

GET my-index-000001/_search
{
  "query": {
    "match": {
      "city": "york" 
    }
  },
  "sort": {
    "city.raw": "asc" 
  },
  "aggs": {
    "Cities": {
      "terms": {
        "field": "city.raw" 
      }
    }
  }
}
```



