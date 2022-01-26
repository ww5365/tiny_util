# 使用





## protoc

### 生成的文件存放路径

```
protoc --proto_path=src --cpp_out=build/gen src/foo.proto src/bar/baz.proto

```

生成：
build/gen/foo.pb.h
build/gen/foo.pb.h
build/gen/bar/baz.pb.h   #  自动创建gen文件夹
build/gen/bar/baz.pb.h

其中：
build/gen/bar文件夹会自动创建
build/ build/gen不会自动创建


说明：
–proto_path=src 或-I 指定了项目路径，其实他主要是为了和后面的.proto文件路径结合，proto文件会把src去掉，并把剩下的路径/bar/baz.proto 生成相应的头文件和源文件并放到–cpp_out=build/gen路径下。