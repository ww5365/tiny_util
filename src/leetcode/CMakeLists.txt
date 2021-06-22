cmake_minimum_required(VERSION 3.0.0)
project(leetcode VERSION 0.1.0)

include(CTest)
enable_testing()

##支持c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")

##特定目录头文件
include_directories(${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/chapater_nine/*.h ${PROJECT_SOURCE_DIR}/src/leetcode_my/*.h)

## 扫描 ./src/cpp 下的所有源文件，并将文件名存入DIR_SRCS中
##aux_source_directory(./src/test_main.cpp DIR_SRCS)
aux_source_directory(./src/leetcode_my DIR_SRCS_3)
aux_source_directory(./src/chapater_nine DIR_SRCS_2)


add_executable(${PROJECT_NAME}  ${DIR_SRCS_2} ${DIR_SRCS_3})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)