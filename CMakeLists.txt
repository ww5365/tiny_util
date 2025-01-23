## Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0.0)

# set( CMAKE_CXX_COMPILER "/pathto/g++" )
# set( CMAKE_C_COMPILER "/pathto/gcc" )

project(mytest)


# Name of the project，可以任意指定
project(tinyUtil VERSION 0.1.0)
message(STATUS, "project name:${PROJECT_NAME}, source_dir:${PROJECT_SOURCE_DIR}, binary_dir: ${tinyUtil_BINARY_DIR}")

message(STATUS, "project current source dir:${CMAKE_CURRENT_SOURCE_DIR}")  #这个是和CMakeList.txt同层的目录, 进入到子目录的cmakeList后，这个值更新为子目录的路径

include(CTest)
enable_testing()

##支持c++11  c++17
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=gnu++17")
# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)  #设置了c++的标准

message(STATUS "cxx_flags: " ${CMAKE_CXX_FLAGS})
message(STATUS "cxx_standard: " ${CMAKE_CXX_STANDARD})

set(JSON_BuildTests OFF CACHE INTERNAL "")
# add_subdirectory(${PROJECT_SOURCE_DIR}/third-party/json) ##这个库直接下载就可以使用


##特定目录头文件
include_directories(${PROJECT_SOURCE_DIR}/src/tinyutil/inc)
include_directories(${PROJECT_SOURCE_DIR}/src/leetcode/inc)
include_directories(${PROJECT_SOURCE_DIR}/src/primer/inc)

## 只需要下载git上下载nlohmann库,把头文件加载cmakelist就可以使用
include(FetchContent)  
FetchContent_Declare(json  
        URL https://cmc-hgh-artifactory.cmc.tools.huawei.com/artifactory/opensource_general/JSON-for-Modern-C++/3.10.1/package/json-3.10.1.zip)
FetchContent_MakeAvailable(json)  

message(STATUS "nlohmann_json path2: " ${nlohmann_json_SOURCE_DIR})
  
# include_directories(${nlohmann_json_SOURCE_DIR}/include)  # 通过target_link_libraries来保证头文件库的路径正确

## 扫描 ./src/cpp 下的所有源文件，并将文件名存入DIR_SRCS中, 不会递归包含子目录下的源文件
## aux_source_directory用于搜集在指定目录下所有的源文件的文件名（不包括头文件），将输出结果列表储存在指定的变量中。
aux_source_directory(./src/tinyUtil/cpp DIR_SRCS)

#aux_source_directory(./src/leetcode/cpp LEETCODE_DIR_SRCS)
###############
add_subdirectory(./src/leetcode)   # 会在当前目录下面生成libLeetCode.a静态库文件

add_subdirectory(./src/primer)   # 会在当前目录下面生成libLeetCode.a静态库文件

add_executable(${PROJECT_NAME} ./src/tinyUtil.cpp ${DIR_SRCS})

    #add_executable(${PROJECT_NAME} ./src/tinyUtil.cpp ${DIR_SRCS} ${LEETCODE_DIR_SRCS})
    # add_executable(${PROJECT_NAME} ./src/tinyUtil.cpp)
    # add_library("tiny_util" STATIC ${DIR_SRCS})

    #target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/third-party/json/single_include)

# 配置了子目录，子目录中的文件打成了库文件 子目录leetcode中代码都打包到库：libLeetCode.a 中

##############
target_link_libraries(${PROJECT_NAME} LeetCode Primer nlohmann_json::nlohmann_json) # nlohmann_json仅是个头文件库不会有so或.a，这里实际上只是确保头文件路径正确


message(STATUS "STD_LIBRARY: ${STD_LIBRARY}")

## cpack生成安装包?
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
