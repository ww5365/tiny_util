## Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0.0)

# Name of the project，可以任意指定
project(tinyUtil VERSION 0.1.0)
message(STATUS, "project name:${PROJECT_NAME}, source_dir:${PROJECT_SOURCE_DIR}, binary_dir: ${tinyUtil_BINARY_DIR}")

message(STATUS, "project current source dir:${CMAKE_CURRENT_SOURCE_DIR}")  #这个是和CMakeList.txt同层的目录

include(CTest)
enable_testing()

##支持c++11  c++17
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=gnu++17")
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)  #设置了c++的标准

message(STATUS "cxx_flags: " ${CMAKE_CXX_FLAGS})
message(STATUS "cxx_standard: " ${CMAKE_CXX_STANDARD})

set(JSON_BuildTests OFF CACHE INTERNAL "")
# add_subdirectory(${PROJECT_SOURCE_DIR}/third-party/json) ##这个库直接下载就可以使用


##特定目录头文件
include_directories(${PROJECT_SOURCE_DIR}/src/tinyutil/inc)
include_directories(${PROJECT_SOURCE_DIR}/src/leetcode/inc)

## 只需要下载git上下载nlohmann库,把头文件加载cmakelist就可以使用
include_directories(${PROJECT_SOURCE_DIR}/third-party/json/single_include)

## 扫描 ./src/cpp 下的所有源文件，并将文件名存入DIR_SRCS中
aux_source_directory(./src/tinyUtil/cpp DIR_SRCS)

#aux_source_directory(./src/leetcode/cpp LEETCODE_DIR_SRCS)
###############
# add_subdirectory(./src/leetcode)   # 会在当前目录下面生成libLeetCode.a静态库文件

add_executable(${PROJECT_NAME} ./src/tinyUtil.cpp ${DIR_SRCS})

#add_executable(${PROJECT_NAME} ./src/tinyUtil.cpp ${DIR_SRCS} ${LEETCODE_DIR_SRCS})
# add_executable(${PROJECT_NAME} ./src/tinyUtil.cpp)
# add_library("tiny_util" STATIC ${DIR_SRCS})

#target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/third-party/json/single_include)

# 配置了子目录，子目录中的文件打成了库文件 子目录leetcode中代码都打包到库：libLeetCode.a 中

##############
# target_link_libraries(${PROJECT_NAME} LeetCode)


message(STATUS "STD_LIBRARY: ${STD_LIBRARY}")

## cpack生成安装包?
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
