cmake_minimum_required(VERSION 3.0.0)
project(tinyUtil VERSION 0.1.0)

include(CTest)
enable_testing()

##支持c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")

##特定目录头文件
include_directories(${PROJECT_SOURCE_DIR}/src/inc)

## 扫描 ./src/cpp 下的所有源文件，并将文件名存入DIR_SRCS中
aux_source_directory(./src/cpp DIR_SRCS)


add_executable(${PROJECT_NAME} ./src/tinyUtil.cpp ${DIR_SRCS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
