#cmake_minimum_required(VERSION 3.0.0)
#project(leetcode VERSION 0.1.0)
#
#include(CTest)
#enable_testing()
#
###支持c++17
##set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=gnu++17")

##特定目录头文件
message("test for ww primer source dir: " ${PROJECT_SOURCE_DIR})

#include_directories(${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/chapater_nine/*.h ${PROJECT_SOURCE_DIR}/src/leetcode_my/*.h)

## 扫描 ./src/cpp 下的所有源文件，并将文件名存入DIR_SRCS中
##aux_source_directory(./src/test_main.cpp DIR_SRCS)

include_directories(./inc)
aux_source_directory(. DIR_SRCS_0)
aux_source_directory(./cpp DIR_SRCS_1)


#add_executable(${PROJECT_NAME}  ${DIR_SRCS_2} ${DIR_SRCS_3})
add_library(Primer  ${DIR_SRCS_0} ${DIR_SRCS_1})



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)