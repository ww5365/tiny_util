# cmake 使用介绍

## 1.1 cmake介绍
CMake主要是编写CMakeLists.txt文件，然后用cmake命令将CMakeLists.txt文件转化为make所需要的makefile文件，最后用make命令编译源码生成可执行程序或共享库（so(shared object)）。

cmake  指向CMakeLists.txt所在的目录，例如cmake .. 表示CMakeLists.txt在当前目录的上一级目录。
cmake后会生成很多编译的中间文件以及makefile文件，所以一般建议新建一个新的目录，专门用来编译，例如

```
mkdir build
cd build
cmake ..
make  //根据生成makefile文件，编译程序。
```

## 1.2 cmake的配置及编译

* 设置Makefile类型：
  文件>首选项>设置>搜索cmake: generator
  设置为”MinGw Makefiles”或者” Unix Makefiles”，这相当于运行cmake –G “MinGw Makefiles” .

* vs中cmake全部配置：
  ctrl + shift + p -> cmake -> edit cmake cache 也可以修改cmake配置,运行环境

* cmake 命令：


``` shell

# configure the project and generate a native build system: 
cmake    "-GNinja" \   # 配置使用Ninja来进行构建和编译；指定构建系统生成器
        -DCMAKE_BUILD_TYPE=$BUILD_TYPE \  #  指定生成的Makefile的编译模式：Debug /Release
        -DENABLE_COVERAGE=OFF \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \  # 其生成的文件compile_commands.json，包含所有编译单元所执行的指令; 同：cmakelist.txt中set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
        -DSERVICE_VERSION=$SERVICE_VERSION \
        -DPROJECT_VERSION=$PROJECT_VERSION \
        -DOUTPUT_DIR=$BUILD_RELEASE_DIR \
        -DCMAKE_C_FLAGS="${SAFE_FLAGS}" \
        -DCMAKE_CXX_FLAGS="${SAFE_FLAGS}" \  #指定编译参数;同set(CMAKE_CXX_FLAGS   "${SAFE_FLAGS}")
        -DNATIVE_EXECUTABLES_DIR=$BUILD_EXECUTABLES_DIR \
        -DCOMPILIE_PREBUILD=$COMPILIE_PREBUILD \
        -DBUILD_COMMON_DIR=$BUILD_OBJ_COMMON \
        -DCMAKE_TOOLCHAIN_FILE=$CMAKE_TOOL_CHAIN_FILE ${SOURCE_DIR} 2>&1 | tee -a $LOG_FILE

# Then call that build system to actually compile/link the project
cmake --build . --target  rankengine_all  
# --build是指定CMakeCache.txt（或CMakeFiles文件夹）所在的路径;在此目录中构建二进制树


cmake --no-warn-unused-cli \
-DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
-DCMAKE_BUILD_TYPE:STRING=Debug \
-DCMAKE_C_COMPILER:FILEPATH=C:\msys64\mingw64\bin\x86_64-w64-mingw32-gcc.exe \
-DCMAKE_CXX_COMPILER:FILEPATH=C:\msys64\mingw64\bin\x86_64-w64-mingw32-g++.exe \
-Hg:i1Protocol \
-Bg:i1Protocol/build \
-G Ninja
#-H定义home目录也就是主CMakeLists.txt所在目录
#-B定义build编译生成目录
#-G定义generator-name生成的编译规则文件类型
  -S <path-to-source>          = Explicitly specify a source directory.
  -B <path-to-build>           = Explicitly specify a build directory.
  -C <initial-cache>           = Pre-load a script to populate the cache.
  -D <var>[:<type>]=<value>    = Create or update a cmake cache entry.
  -U <globbing_expr>           = Remove matching entries from CMake cache.
  -G <generator-name>          = Specify a build system generator.
  -T <toolset-name>            = Specify toolset name if supported by

```


## 1.3 CMakeList.txt使用

  ``` makefile
  
  # 常用的变量
  
  ## 预定义变量
  PROJECT_SOURCE_DIR：工程的根目录
  PROJECT_BINARY_DIR：运行 cmake 命令的目录，通常是 ${PROJECT_SOURCE_DIR}/build
  PROJECT_NAME：返回通过 project 命令定义的项目名称
  CMAKE_CURRENT_SOURCE_DIR：当前处理的 CMakeLists.txt 所在的路径
  CMAKE_CURRENT_BINARY_DIR：target 编译目录
  CMAKE_CURRENT_LIST_DIR：CMakeLists.txt 的完整路径
  CMAKE_CURRENT_LIST_LINE：当前所在的行
  CMAKE_MODULE_PATH：定义自己的 cmake 模块所在的路径，SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)，然后可以用INCLUDE命令来调用自己的模块
  EXECUTABLE_OUTPUT_PATH：重新定义目标二进制可执行文件的存放位置
  LIBRARY_OUTPUT_PATH：重新定义目标链接库文件的存放位置
  
  ## 开关变量
  BUILD_SHARED_LIBS：这个开关用来控制默认的库编译方式，如果不进行设置，使用 add_library 又没有指定库类型的情况下，默认编译生成的库都是静态库。如果 set(BUILD_SHARED_LIBS ON) 后，默认生成的为动态库
  CMAKE_C_FLAGS：设置 C 编译选项，也可以通过指令 add_definitions() 添加
  CMAKE_CXX_FLAGS：设置 C++ 编译选项，也可以通过指令 add_definitions() 添加
  add_definitions(-DENABLE_DEBUG -DABC) # 参数之间用空格分隔
  
  ## 自定义变量
  set(A B) # 定义变量A内容为B
  ${A} # ${A}使用变量A,如上面${PROJECT_NAME}
  message(STATUS ${A}) #输出消息 内容为变量A的值
  
  # 常用命令
  
  ## Minimum version of CMake required to build this project
  cmake_minimum_required(VERSION 3.0.0)
  
  ## 设置项目名称 Name of the project，可以任意指定
  project(demo VERSION 0.1.0)  
  ###它会引入两个变量 demo_BINARY_DIR 和 demo_SOURCE_DIR
  ###同时，cmake 自动定义了两个等价的变量 PROJECT_BINARY_DIR 和 PROJECT_SOURCE_DIR
  project(Helloworld VERSION 1.0.0 LANGUAGES C CXX) #设置项目名称、版本及项目使用的语言等

  ## 设置编译选项
  cmake -DTEST_DEBUG=ON .   #设置选项参数开关;
  cmake --build .  #生成makefile . 是cmakelist.txt所在路径
  option(TEST_DEBUG "option for debug" OFF) #默认关上
  if (TEST_DEBUG)
     add_definitions(-DTEST_DEBUG)  #加到gcc的编译选项中
  endif()
  #include "test.h"
  #ifdef TEST_DEBUG  #源码中使用此编译选项
  ...
  #endif

  ## 设置编译类型
  add_executable(demo demo.cpp) # demo为要生成的可执行文件名字，demo.cpp是要编译的文件
  add_library(hello SHARED ${SOURCE_1}) #生成一个动态链接库libhello.so, 使用#{SOURCE_1}知识的代码
  add_library(common STATIC util.cpp) # 生成静态库，libcommon.a为名字
  
  ## 设置源码文件搜索规则
  aux_source_directory(src/ DIR_SRCS) ## 扫描 src/ 下的所有源文件，并将文件名存入DIR_SRCS中
  add_executable(main ${DIR_SRCS}) ## ${DIR_SRCS}所有源文件 main将生成的可执行文件名
  FILE(GLOB SOURCE_1 "${CMAKE_SOURCE_DIR}/src/*.cpp")  ##自定义的文件搜索规则
  
  ## 设置构建的子目录
  add_subdirectory(sub output) ## 在父目录下调用cmake .构建之后，在output目录下会出现libsub.a库
  
  ## 设置包含的目录
  include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/include") ## Linux 下还可以通过如下方式设置包含的目录
  
  ## 设置链接库搜索目录
  
  link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_CURRENT_SOURCE_DIR}/libs") ## 也可通过如下方式设置包含的目录
  
  
  ## 设置链接库
  link_libraries("/opt/MATLAB/R2012a/bin/glnxa64/libeng.so" "/opt/MATLAB/R2012a/bin/glnxa64/libmx.so") ##链接库文件的路径
  target_link_libraries(demo ${CMAKE_CURRENT_SOURCE_DIR}/libs/libface.a boost_system.a pthread) ##链接多个库文件的名称
  add_dependencies(rankserver boost) ##add_dependencies一般来说用不到。用到的情况就是两个targets有依赖关系（通过target_link_libraries解决）并且依赖库也是通过编译源码产生的。这时候一句add_dependencies可以在直接编译上层target时，自动检查下层依赖库是否已经生成。没有的话先编译下层依赖库，然后再编译上层target，最后link depend target。

  ## 查找共享so库
  find_library(STD_LIBRARY libstdc++.so.6 PATHS /usr/local/lib64 /usr/lib64 /lib64)
  ###当不同的系统，相同的库文件被安装在不同路径下时，就需要使用这个命令
  ###只需要库的base name，即不需要libtiff，libtiff2，或者tiff.so，tiff.so.2
  ###find命令，会去${PATH}里面找文件，命令会默认创建CACHE

  ## 几个target命令

  target_include_directories()：指定目标包含的头文件路径target_link_libraries()：指定目标链接的库
  target_compile_options()：指定目标的编译选项 目标由 add_library() 或 add_executable() 生成

  target_link_libraries(hello-world PRIVATE/INTERFACE/PUBLIC hello)
  target_include_directories(hello-world PRIVATE/INTERFACE/PUBLIC hello)

  可执行文件依赖 libhello-world.so， libhello-world.so 依赖 libhello.so 和 libworld.so。
  main.c 不使用 libhello.so 的任何功能，因此 libhello-world.so 不需要将其依赖—— libhello.so 传递给 main.c，hello-world/CMakeLists.txt 中使用 PRIVATE 关键字；
  main.c 使用 libhello.so 的功能，但是libhello-world.so 不使用，hello-world/CMakeLists.txt 中使用 INTERFACE 关键字；
  main.c 和 libhello-world.so 都使用 libhello.so 的功能，hello-world/CMakeLists.txt 中使用 PUBLIC 关键字；
  
  cmake-test/                 工程主目录，main.c 调用 libhello-world.so
  ├── CMakeLists.txt
  ├── hello-world             生成 libhello-world.so，调用 libhello.so 和 libworld.so
  │   ├── CMakeLists.txt
  │   ├── hello               生成 libhello.so 
  │   │   ├── CMakeLists.txt
  │   │   ├── hello.c
  │   │   └── hello.h         libhello.so 对外的头文件
  │   ├── hello_world.c
  │   ├── hello_world.h       libhello-world.so 对外的头文件
  │   └── world               生成 libworld.so
  │       ├── CMakeLists.txt
  │       ├── world.c
  │       └── world.h         libworld.so 对外的头文件
  └── main.c

  ## install 安装命令
  
  install(TARGETS rankserver DESTINATION sbin COMPONENT rankengine) ## 安装目标文件

  参数中的TARGET可以是很多种目标文件，最常见的是通过ADD_EXECUTABLE或者ADD_LIBRARY定义的目标文件，即可执行二进制、动态库、静态库：

  目标文件	内容	安装目录变量	默认安装文件夹
  ARCHIVE	静态库	${CMAKE_INSTALL_LIBDIR}	lib
  LIBRARY	动态库	${CMAKE_INSTALL_LIBDIR}	lib
  RUNTIME	可执行二进制文件	${CMAKE_INSTALL_BINDIR}	bin
  PUBLIC_HEADER	与库关联的PUBLIC头文件	${CMAKE_INSTALL_INCLUDEDIR}	include
  PRIVATE_HEADER	与库关联的PRIVATE头文件	${CMAKE_INSTALL_INCLUDEDIR}	include

  DESTINATION: 指定磁盘上要安装文件的目录;建议安装目录变量下的文件夹；
  COMPONENT：指定了该安装规则相关的一个安装部件的名字，如“runtime”

  install(DIRECTORY "${PROJECT_SOURCE_DIR}/resource" DESTINATION . COMPONENT rankengine) ##安装目录,把目录./resource及下面的内容，拷贝到安装目录(.)中

  install(DIRECTORY "${OUTPUT_DIR}/lib" DESTINATION . COMPONENT rankengine REGEX libboost_unit_test_framework* EXCLUDE) ##支持正则表达式拷贝




  ## CTest是测试工具?
  include(CTest)
  enable_testing()
  
  ## cpack生成安装包?
  set(CPACK_PROJECT_NAME ${PROJECT_NAME})
  set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
  include(CPack)
  
  ## 示例1： 生成一个动态库并链接到main的可执行文件
  FILE(GLOB SOURCE_1 "${CMAKE_SOURCE_DIR}/src/*.cpp")
  FILE(GLOB SOURCE_2 "${CMAKE_SOURCE_DIR}/main/*.cpp")
  INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/include/")
  LINK_LIBRARIES(hello)  ##链接libhello.so
  ADD_LIBRARY(hello SHARED ${SOURCE_1}) ##告诉cmake生成一个动态链接库libhello.so
  ADD_EXECUTABLE(sayhello ${SOURCE_2})  ##根据main.cpp生成可执行文件 sayhello
  TARGET_LINK_LIBRARIES(sayhello ${hello}) ##将libhello.so链接到可执行文件
  
  ```
  