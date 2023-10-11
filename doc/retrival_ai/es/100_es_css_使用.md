
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


## python访问ES

## 创建mapping

```json

{
  "settings": {
    "refresh_interval": "120s",
    "number_of_shards": "3",
	  "routing.allocation.total_shards_per_node": 2,
    "number_of_replicas": "1"
  },
  "mappings": {
    "_source": {
      "enabled": "false"    ## 关闭store，不存原始数据字段，但能查询也就是只存储索引情况
    },
    "properties": {
      "title": {
        "type": "text",
        "store": "false",   ## 不存原始字段
        "index": "true",
        "similarity": "Payload",
        "analyzer": "whitespace",
        "search_analyzer": "whitespace"
      },
      "real_title_analyzer": {
        "type": "text",
        "store": "true",  ## 会存原始字段
        "index": "true",
        "similarity": "Payload",
        "analyzer": "whitespace",
        "search_analyzer": "whitespace"
	  }
    }
  }
}
```

1).关注store使用

``` json
GET my_index1/_search
{
  "stored_fields": [
    "real_title_analyzer"   # 指明了要显示的存储的原始字段值
  ],
  "query": {
    "match": {
      "title": "query for search"
    }
  }
}
```
2) REST High Level Client 接口来创建索引
参考：https://www.cnblogs.com/xiaoyh/p/16061594.html
可以把mapping写在配置中，读入后，指定映射1的方式，整体创建

4) REST High Level Client 接口来判断索引是否已经创建过了

## 写入es中数据

参考：https://cloud.tencent.com/developer/article/1643818

直接用json写入










