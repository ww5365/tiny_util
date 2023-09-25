
# es hw cloud 


## 快速使用es

使用Kibana的dev tools 的 console来进行可视化的数据的写入，索引创建等

参考：
https://support.huaweicloud.com/qs-css/index.html#index__zh-cn_topic_0000001223434400_fig1830133281516

另外，es7.9版本的官方的guide说明：
https://www.elastic.co/guide/en/elasticsearch/reference/7.9/search-search.html


```
创建索引: my_store

PUT /my_store
{
  "settings": {
    "number_of_shards": 1
  },
  "mappings": {
          "properties": {
        "productName": {
          "type": "text",
          "analyzer": "ik_smart"
        },
        "size": {
          "type": "keyword"
        }
      }
    }
  }
```

```
批量向索引中写入数据：

POST /my_store/_doc/_bulk
{"index":{}}
{"productName":"2017秋装新款文艺衬衫女装","size":"L"}
{"index":{}}
{"productName":"2017秋装新款文艺衬衫女装","size":"M"}
{"index":{}}
{"productName":"2017秋装新款文艺衬衫女装","size":"S"}
{"index":{}}
{"productName":"2018春装新款牛仔裤女装","size":"M"}
{"index":{}}
{"productName":"2018春装新款牛仔裤女装","size":"S"}
{"index":{}}
{"productName":"2017春装新款休闲裤女装","size":"L"}
{"index":{}}
{"productName":"2017春装新款休闲裤女装","size":"S"}

```

```
query的查询：

GET /my_store/_search
{
    "query":{
        "match":{
            "productName":"春装牛仔裤"
        }
    }
}


```


```
查询并按照某个字段进行聚合
GET /my_store/_search
{
    "query":{
        "match":{
            "productName":"春装"
        }
    },
    "size":0,   ## 这里size为0，不显示匹配doc
    "aggs":{
        "sizes":{  ## 聚合显示用的新字段
            "terms":{
                "field":"size"
            }
        }
    }
}
```






