# 使用





## protoc

 - protoc
用法: protoc [OPTION] PROTO_FILES
解析proto文件并根据给定的选项生成输出:
  -IPATH, --proto_path=PATH   指定搜索目录，可多次指定，默认为当前工作目录。
  --version                   显示版本信息并退出
  -h, --help                  显示帮助文档并退出
  --encode=MESSAGE_TYPE       从标准输入读取给定类型的文本格式消息，从标准输出写入二进制文件。消息类型必须在原始文件或导入中定义。
  --decode=MESSAGE_TYPE       从标准输入中读取给定类型的二进制消息，向标准输出中写入文本格式。消息类型必须定义在proto文件或其导入的文件中。
  --decode_raw                从标准输入读取任意协议消息，向标准输出写入原始标记或文本格式的值。
  --descriptor_set_in=FILES   指定文件分隔符列表，每个都包含了一个文件描述符集合。
  -oFILE,                     写入FileDescriptorSet
  --include_imports           当使用--descriptor_set_out时, 同时包含输入文件的依赖项
  --include_source_info       当使用--descriptor_set_out时无需剥离FileDescriptorProto中的SourceCodeInfo
  --dependency_out=FILE       指定依赖输出文件
  --error_format=FORMAT       设置打印错误格式，默认gcc，可选msvs。
  --print_free_field_numbers  打印给定proto文件中消息定义的可用字段号
  --plugin=EXECUTABLE         指定使用插件的可执行文件
  --cpp_out=OUT_DIR           产生C++头文件和源文件
  --csharp_out=OUT_DIR        产生C#源文件
  --java_out=OUT_DIR          产生Java源文件
  --javanano_out=OUT_DIR      产生Java Nano源文件
  --js_out=OUT_DIR            产生JavaScript源文件
  --objc_out=OUT_DIR          产生Objective C头文件和源文件
  --php_out=OUT_DIR           产生PHP源文件
  --python_out=OUT_DIR        产生Python源文件
  --ruby_out=OUT_DIR          产生Ruby源文件
  @<filename>                 从文件中读取选项和文件名


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

// 结合cmake使用

```cmake
execute_process(COMMAND bash -c "LD_LIBRARY_PATH=./tool ./tool/protoc --cpp_out=./proto -I=../query-rewriter/projects/server/src/main/proto  queryrewriter.proto" WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

```