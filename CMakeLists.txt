## Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0.0)

# Name of the project，可以任意指定
project(tinyUtil VERSION 0.1.0)

include(CTest)
enable_testing()

##支持c++11 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=gnu++17")

message(STATUS "cxx_flags: " ${CMAKE_CXX_FLAGS})

set(JSON_BuildTests OFF CACHE INTERNAL "")
# add_subdirectory(${PROJECT_SOURCE_DIR}/third-party/json) ##这个库直接下载就可以使用


##特定目录头文件
include_directories(${PROJECT_SOURCE_DIR}/src/tinyutil/inc)
include_directories(${PROJECT_SOURCE_DIR}/src/leetcode/inc)

## 只需要下载git上下载nlohmann库,把头文件加载cmakelist就可以使用
include_directories(${PROJECT_SOURCE_DIR}/third-party/json/single_include)

## 扫描 ./src/cpp 下的所有源文件，并将文件名存入DIR_SRCS中
aux_source_directory(.tinyutil/src/cpp DIR_SRCS)

#aux_source_directory(./src/leetcode/cpp LEETCODE_DIR_SRCS)
add_subdirectory(./src/leetcode)

add_executable(${PROJECT_NAME} ./src/tinyUtil.cpp ${DIR_SRCS})
#add_executable(${PROJECT_NAME} ./src/tinyUtil.cpp ${DIR_SRCS} ${LEETCODE_DIR_SRCS})
# add_executable(${PROJECT_NAME} ./src/tinyUtil.cpp)
# add_library("tiny_util" STATIC ${DIR_SRCS})

#target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/third-party/json/single_include)

target_link_libraries(${PROJECT_NAME} LeetCode)

## cpack生成安装包?
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
