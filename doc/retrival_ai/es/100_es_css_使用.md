
# es hw cloud 


## 快速使用es

使用Kibana的dev tools 的 console来进行可视化的数据的写入，索引创建等

``` 创建索引

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



