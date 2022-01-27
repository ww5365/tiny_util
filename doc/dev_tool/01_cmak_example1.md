#  cmake 示例分析

 





```cmake

cmake_minimum_required(VERSION 3.14)
project(server)

# 使用c++17标准
set(CMAKE_CXX_STANDARD 17)


message("current source path: ${CMAKE_CURRENT_SOURCE_DIR}")
message("current binary path: ${CMAKE_CURRENT_BINARY_DIR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/output/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/output/lib) # 静态库输出路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)  # 动态库输出路
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # 设置输出compile_commands.json 文件

SET(PROJECT_THIRDPARTY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/third_party)  # 使用set 定义初始化
SET(PROJECT_PROTOC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/tool)

# 设置g++编译的flags， 参考示例1

set(CFLAGS "${CFLAGS} -fstack-protector-all -fPIE  -fPIC"):
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CFLAGS} -g -pthread -DBOOST_SYSTEM_NO_DEPRECATED  -L${CMAKE_CURRENT_SOURCE_DIR}/lib -ldl -lrt -o3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CFLAGS} -Wreturn-type -Wmissing-noreturn -Wunreachable-code -Wreturn-local-addr -Wunused-variable -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(notdir $(abspath $<))\"'")


set(CMAKE_SHARED_LINKER_FLAGS "${LDFLAGS} -z noexecstack -z relro -z now -pie")
set(CMAKE_EXE_LINKER_FLAGS "${LDFLAGS} -z noexecstack -z relro -z now -pie")

# cmake中执行shell命令
execute_process(COMMAND bash -c "mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/lib")
execute_process(COMMAND bash -c "mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/proto")
execute_process(COMMAND bash -c "tar -zxf ${CMAKE_CURRENT_SOURCE_DIR}/lib/libbrpc.tar.gz -C ${CMAKE_CURRENT_SOURCE_DIR}/lib/")
message("cd ${CMAKE_CURRENT_SOURCE_DIR}/lib; xz -k -d -f libtensorflow_cc.so.2.5.0.xz; cd -")
execute_process(COMMAND bash -c "cd ${CMAKE_CURRENT_SOURCE_DIR}/lib; xz -k -d -f libtensorflow_cc.so.2.5.0.xz; cd -") # 用这种直接解压的方式引入第三方的依赖库



# 编译proto文件，生成相关的代码到./build/proto
execute_process(COMMAND bash -c "LD_LIBRARY_PATH=./tool:${CMAKE_CURRENT_SOURCE_DIR}/lib ${CMAKE_CURRENT_SOURCE_DIR}/tool/protoc  --cpp_out=${CMAKE_CURRENT_BINARY_DIR}/proto -I=${CMAKE_CURRENT_SOURCE_DIR}/proto:${CMAKE_CURRENT_SOURCE_DIR}/third_party  ${CMAKE_CURRENT_SOURCE_DIR}/proto/http.proto")
message("LD_LIBRARY_PATH=./tool:${CMAKE_CURRENT_SOURCE_DIR}/lib ${CMAKE_CURRENT_SOURCE_DIR}/tool/protoc  --cpp_out=${CMAKE_CURRENT_BINARY_DIR}/proto -I=${CMAKE_CURRENT_SOURCE_DIR}/proto:${CMAKE_CURRENT_SOURCE_DIR}/third_party  ${CMAKE_CURRENT_SOURCE_DIR}/proto/http.proto")


# 将指定目录添加到编译器的头文件搜索路径下
 
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/ad")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/shopping")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/src/shopping")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/proto")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/third_party/brpc")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/third_party/libevent")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/third_party/prometheus")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/third_party/eigen3")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/third_party")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/third_party/nebula/common/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/third_party/nebula/interface/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/third_party/nebula/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/third_party/flatbuffers/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/third_party/hiredis-1.0.2")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/third_party/librdkafka-1.4.2/output/include/librdkafka")

# 增加/proto//http.pb.cc 到源文件
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/proto/" PROTO_SRCS)
message(STATUS ${PROTO_SRCS})

# 增加头文件搜索路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/)

# 设置链接库的搜索路径
# 等价方式： set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_CURRENT_SOURCE_DIR}/libs")

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/lib)
include_directories("${CMAKE_CURRENT_BINARY_DIR}/proto")
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

#file 自定义的文件搜索规则：GLOB 会产生一个由所有匹配globbing表达式的文件组成的列表，并将其保存到变量中。Globbing 表达式与正则表达式类似，但更简单。

file(GLOB SERVER_SOURCE "src/server/*.cpp")
file(GLOB SERVICE_SOURCE "src/service/*.cpp")
file(GLOB KAFKA_SOURCE "src/kafka/*.cpp")
file(GLOB KAFKA_CLIENT_SOURCE "src/kafka_client/*.cpp")
file(GLOB QUERY_EMB_SOURCE "src/query_emb")

# 链接多个库文件的名称， 最后的库等价于：libbrpc.so -lbrpc
set(COMMON_LIBRARIES   brpc log4cplus leveldb  snappy z zstd bz2 lzma lz4 wangle m protobuf securec crypto ssl gflags curl hiredis event double-conversion tensorflow_framework tensorflow_cc utf8proc jsoncpp sasl2 rdkafka rdkafka++ dl)
set(ADSENSE_LIBRARIES  ad_auth ad_util shopping adsense ad_nebula)
set(BOOST_LIRBRARIES boost_context boost_system boost_serialization boost_regex)
set(QUERY_EMB_LIRBRARIES onnxruntime utf8proc pcrecpp)
set(PROMETHEUS_BOOST_LIRBRARIES prometheus-cpp-core prometheus-cpp-pull prometheus-cpp-push)

# 子目录下面有CMakeList.txt 构建子项目
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/shopping)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/util)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/auth)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/ad)

# 构建可执行文件的目标
add_executable(adsense_server  ${AD_SOURCE}  ${PROTO_SRCS} ${SERVER_SOURCE} ${SERVICE_SOURCE} ${QUERY_EMB_SOURCE} ${KAFKA_SOURCE} ${KAFKA_CLIENT_SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

# 目标
TARGET_LINK_LIBRARIES(adsense_server ${COMMON_LIBRARIES} folly ${ADSENSE_LIBRARIES} ${BOOST_LIRBRARIES}  ${PROMETHEUS_BOOST_LIRBRARIES} shopping_esfeature_attr)

add_executable(adsense_enc ${CMAKE_CURRENT_SOURCE_DIR}/src/reranker_encrypt.cpp)

TARGET_LINK_LIBRARIES(adsense_enc ad_auth)


```



## 示例1：

![image-20220125144825766](../img/image-20220125144825766.png)
