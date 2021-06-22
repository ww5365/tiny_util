[TOC]

# C/C++开发配置指南

## 1. 环境准备

如要安装的软件如下：

- [wecode](http://wecode.huawei.com/Home)，直接下载安装
- [mingw64](https://sourceforge.net/projects/mingw-w64/files/mingw-w64/)，下载`x86_64-posix-seh`，解压到`C:\mingw64`下，并在环境变量PATH配置`C:\mingw64\bin`。同时把`bin`目录下`mingw32-make.exe`重新copy，重命名为`make.exe`。使用命令`gcc -v`和`g++ -v`，检验安装是否成功
- [cmake](https://cmake.org/download/)，下载完解压，并将`bin`配置到环境变量PATH下。使用`cmake --version`检验安装是否成功
- [plink](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html)，用于远程编译和调试

需要安装插件：
- cmake , cmake tools
- c/c++
- 

wecode配置： ctrl+shift+p -> 首选项：打开设置(json)，新增如下配置，涉及**字体**、**编码**、**目录树缩进**、**ctrl+鼠标滚轮调整字体大小**，**markdown配置**

``` json
{
    "editor.fontFamily": "Cascadia Code, Microsoft YaHei Mono, Consolas, 'Courier New', monospace",
    "editor.fontSize": 12,
    "files.encoding": "utf8",
    "workbench.tree.indent": 16,
    "editor.tabSize": 4,
    "editor.mouseWheelZoom": true,
    "editor.wordWrap": "on",
    "markdownlint.config": {
        "MD025": {
            "front_matter_title": ""
        },
        "MD013": false,
        "MD041": false,
        "MD033": false
    },
    "markdown-preview-enhanced.previewTheme": "one-light.css",
    "files.eol": "\n"
}
```

注意`"files.eol": "\n"`表示换行符是LF，同时建议git config设置`core.autocrlf=false`，方便windows与linux文件同步

## 2. 使用cmake编译项目

### 2.1 cmake介绍
CMake主要是编写CMakeLists.txt文件，然后用cmake命令将CMakeLists.txt文件转化为make所需要的makefile文件，最后用make命令编译源码生成可执行程序或共享库（so(shared object)）。

cmake  指向CMakeLists.txt所在的目录，例如cmake .. 表示CMakeLists.txt在当前目录的上一级目录。
cmake后会生成很多编译的中间文件以及makefile文件，所以一般建议新建一个新的目录，专门用来编译，例如

```
mkdir build
cd build
cmake ..
make  //根据生成makefile文件，编译程序。
```

### 2.2 cmake的配置及编译

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


* CMakeList.txt：

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
  
  

### 2.3 task.json配置及运行

* 生成默认task.json
  ctrl + shift + p -> tasks: configure default task  生成task.json
* task.json使用：
  workspaceFolder: [vs预定义变量全部](https://code.visualstudio.com/docs/editor/variables-reference)

  ``` json
  {
    // See https://go.microsoft.com/fwlink/?LinkId=733558
    // for the documentation about the tasks.json format
    "version": "2.0.0",
    "isShellCommand": true,
    "options": {
        "cwd": "${workspaceFolder}/build"  //${workspaceFolder} - the path of the folder opened in VS Code
    },
    "tasks": [
        {
            "label": "echo",
            "type": "shell",
            "command": "echo ${workspaceFolder}", //显示vs预定义变量

        },
        {
            "label": "Build-all",
            "type": "shell",
            "command": "${command:cmake.launchTargetPath}",
            "args": [],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": []
        },
        {
            "label": "Cmake",
            "command": "cmake -G 'MinGW Makefiles' -DCMAKE_BUILD_TYPE=Debug ..",  //通过这命令产出makefile，调用了cmake命令
            "type": "shell", //任务类型，一般指定为shell或process。当设置为shell时会将命令看作终端操作，包括bash、cmd或PowerShell。当指定为process时会将命令看作是一个进程。这里选择shell。
            "presentation": {
                "echo": true, //是否将执行的命令输出到终端中。默认值为true。
                "reveal": "always", //在执行任务时是否显示内置的终端面板
                "panel": "shared" // panel：控制是否在各任务间共享终端输出
            },
            "group": {//指定任务输出的分组，同一个分组的任务会共享终端而非开启新终端
                "kind": "build", //指定任务的分组归属。例如指定group为test，那么可以通过命令面板的Run Test Task运行该任务。
                "isDefault": true
            }
        },
        {
            "label": "Make",
            "command": "make -j 2", 
            "type": "shell",
            "presentation": {
                "echo": true,
                "reveal": "always",
                "panel": "shared"
            },
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "isBuildCommand": true 
        },
        {
            "label": "Run",
            "type": "shell",
            "dependsOn": "cmake_code", //这个命令执行之前，先执行cmake_code
            "command": "${workspaceFolder}/build/tinyUtil.exe",
            "args": [],
            "presentation": {
                "reveal": "always",
                "focus": true,  //终端是否在输入时激活
                "panel": "shared"
            },
            "problemMatcher": [],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
     ]
    }

  ```

ctrl + shift + b : 选择不同的task任务执行
shift + f5 : run without debug

### 2.4 launch.json 配置debug








### 问题及解决：
``` 
报错：
 from D:\workspace\tiny_util\src\tinyUtil.cpp:9:
[build] C:/Users/w00590050/.wecode/extensions/spb-wecode.wecode-cpp-0.7.0/sdk/RTOS/compiler_cpu-v200r005c00spc030/hcc_arm32le/arm-linux-gnueabi/include/c++/7.3.0/cwchar:146:11: error: '::fwide' has not been declared
[build]    using ::fwide

解决方案：

 This question is not the same question, but has the same solution, namely to replace std=c++11 with std=gnu++11 in the call to g++.

```








## 2. 创建项目

使用如下命令打开一个项目

``` shell
mkdir tutorial
cd tutorial
```

新建一个文件main.cpp，粘贴内容如下

```C++
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
}
```

右键目录tutorial，`Open With WeCode`，wecode会在目录下面自动生成.vscode文件夹，并自动创建一系列配置

可以看到如下效果

- .vscode文件夹自动生成
- 代码编辑框无报错，ctrl+鼠标左键标准库支持跳转

![view](./img/wecode_view.png)

## 3. 编译调试

两个概念

1. **task**：多用于编译/构建，使用文件`tasks.json`描述。可以从菜单栏的**终端**中配置和运行任务。
2. **launch**：用于debug，使用文件`launch.json`描述。可以从菜单栏的**运行**中配置和启动调试。

建议直接把本Tutorial的`.vscode/tasks.json`和`.vscode/launch.json`直接拷贝到自己项目.vscode目录下，并按需修改。下面简单解释下编译和debug流程以及相关配置的含义。更详细的请参考[Wecode代码调试](http://wecode.huawei.com/Docs/77)和[VsCode Debugging](https://code.visualstudio.com/docs/cpp/cpp-debug)

### 3.1 本地编译/调试

#### 3.1.1 编译

编译需要配置`tasks.json`，新增`local-build`任务

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "type": "shell",
            "label": "local-build",
            "command": "C:\\mingw64\\bin\\g++.exe",
            "args": [
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe"
            ],
            "windows": {
                "options": {
                    "shell": {
                        "executable": "cmd.exe",
                        "args": [
                            "/d",
                            "/c"
                        ]
                    }
                }
            },
            "options": {
                "cwd": "${workspaceFolder}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```

配置好后，**选择main.cpp**（这步很重要，影响配置中的中`${file}`, `${fileDirname}`和`${fileBasenameNoExtension}`），菜单栏->终端->运行任务->local-build，可以看到能够生成main.exe
![local-build](./img/local-build.gif)

关键参数解释如下（可能需要修改的字段已加粗）：

1. **label** ：任务名（task之间依赖，或者launch依赖task会用到这个名字）
2. **command** ：命令，我们是编译cpp文件，因此是`g++.exe`
3. **args** ：也就是command的参数，和command一起组成编译的完整命令。这里用到了变量引用，大概了解即可，深入研究可参考[Variables Reference](https://code.visualstudio.com/docs/editor/variables-reference)。
    - `${file}`表示当前打开的文件
    - `${fileDirname}`表示当前打开文件的目录名
    - `${fileBasenameNoExtension}`表示当前打开文件去掉扩展的basename

4. windows：表示运行command的环境，可以是`cmd`、`PowerShll`、`git bash`。经实测，最好用`cmd`，另外两个都存在兼容性问题
5. options、problemMatcher、group这三个没深入研究，配就好

PS:
上述配置本质上等同于如下命令，如果发现任务运行失败，可以手动执行进行定位

``` powershell
cmd.exe /d /c "C:\\mingw64\\bin\\g++.exe -g D:\\Wecode-Tutorial\\tutorial\\main.cpp -o D:\\Wecode-Tutorial\\tutorial\\main.exe"
```

手动模拟结果如下，可以看到也能能生成`main.exe`
![local-build](./img/local-build.png)

#### 3.1.2 调试

调试需要编辑`launch.json`，新增`local-debug`启动器

```json
{
    "version": "0.2.0",
    "configurations": [

        {
            "name": "local-debug",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "C:\\mingw64\\bin",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "C:\\mingw64\\bin\\gdb.exe",
            "setupCommands": [
                {
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "local-build"
        }
    ]
}
```

配置好后，选择**main.cpp**，点击左侧运行标签，在下拉框中选中`local-debug`启动器，可以看到会生成`main.exe`，并运行它
![local-launch](./img/local-launch.gif)

关键参数解释如下（可能需要修改的字段已加粗）：

1. **name** ：启动器名称，会更新到调试视图的下拉菜单中
2. type ：配置类型，C/C++都用cppdbg
3. request ：请求配置类型，有两个launch和attach，前者会起一个新进程来加载bin文件，后者会关联到已有的进程上
4. **program** ：gdb要加载的bin文件路径
5. **args** ：bin文件启动参数
6. stopAtEntry ：是否停在main函数入口
7. MIMode ：调试器类型，gdb或者lldb
8. **miDebuggerPath** ：调试器路径
9. setupCommands： gdb的命令行参数
10. **preLaunchTask**：启动器依赖的编译task，启动器启动前，会先运行该任务。可以不设置，但那样需要先手动运行编译任务

### 3.2 远程编译/调试

远程编译调试的方法，大致与本地相同，核心是通过plink在远程服务器上执行命令。另外在执行命令前，需要配置Sftp插件将本地代码同步到远端环境。

#### 3.2.1 代码同步

（确保wecode已安装Sftp插件）
在.vscode下新增`sftp.json`或者`ctrl+shift+p`选择`SFTP:Config`，内容如下

```json
{
    "name": "71 Server",
    "host": "10.136.211.71",
    "protocol": "sftp",
    "port": 22,
    "username": "root",
    "password": "rootOs_123",
    "remotePath": "/home/workspace/tutorial",
    "uploadOnSave": true,
    "ignore": [
        "**\\.vscode",
        "**\\.git",
        "**\\.gitattributes",
        "**\\.gitignore",
        "**\\.DS_Store"
    ]
}
```

`ctrl+shift+p`打开命令面板，选择命令`SFTP: Sync Local -> Remote`，可以把本地目录同步到远程服务器上
![sftp](./img/sftp.gif)
由于我们配置了`"uploadOnSave": true`，在首次同步完整个项目后，只需要在wecode中保存文件，wecode会自动把文件同步到服务器

#### 3.2.2 编译

编辑tasks.json新增`remote-build`配置，基本与本地编译相同，核心参数是`command`，使用plink命令执行远程命令，可以根据自己的需要修改`command`，其他参数无需变化。

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "remote-build",
            "type": "shell",
            "command": "D:/tools/bin/plink.exe -ssh root@10.136.211.71 -pw rootOs_123 \"cd /home/workspace/tutorial;chmod +x build.sh;./build.sh;\"",
            "windows": {
                "options": {
                    "shell": {
                        "executable": "cmd.exe",
                        "args": [
                            "/d",
                            "/c"
                        ]
                    }
                }
            },
            "problemMatcher": {
                "base": "$gcc",
                "source": "gcc",
                "fileLocation": [
                    "relative",
                    "${workspaceFolder}"
                ],
                "pattern": {
                    "regexp": "^/usr1/base/product/(.*):(\\d+):(\\d+):\\s+(warning|error):\\s+(.*)$",
                    "file": 1,
                    "line": 2,
                    "column": 3,
                    "severity": 4,
                    "message": 5
                }
            }
        }
    ]
}

```

运行任务结果如下
![remote-build](./img/remote-build.gif)

#### 3.2.3 调试

编辑launch.json，增加`remote-debug`，核心是通过配置[pipeTransport](https://code.visualstudio.com/docs/cpp/pipe-transport)，并使用plink来进行远程debug。
另外注意这里使用的是

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "remote-debug", // 会更新到调试视图的下拉菜单中
            "type": "cppdbg", // 配置类型，C也用cppdbg
            "request": "launch", // 请求配置类型，有两个launch和attach，前者会起一个新进程来加载bin文件，后者会关联到已有的进程上
            "program": "./hello", // gdb要加载的bin文件路径
            "args": [], // bin文件启动参数
            "stopAtEntry": true, // 是否停在main函数入口
            "cwd": "/home/workspace/hello", // bin运行的工作路径
            "environment": [], // bin文件运行时的环境变量
            "MIMode": "gdb", // 调试器类型，gdb或者lldb
            "pipeTransport": {
                // 远程服务器的链接设置
                "pipeCwd": "",
                "pipeProgram": "D:\\tools\\bin\\plink.exe",
                "pipeArgs": ["-ssh", "root@10.136.211.71", "-pw", "rootOs_123"],
                "debuggerPath": "/usr/bin/gdb" // 远程服务器上调试器的路径
            },
            "setupCommands": [
                // gdb的命令行参数
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "sourceFileMap": {
                // 远程服务器的文件路径和本地文件映射
                "/home/workspace/tutorial": "D:\\Wecode-Tutorial\\tutorial"
            },
            "logging": {
                     "trace": true,
                     "traceResponse": true,
                     "engineLogging": true
            },
            "preLaunchTask": "remote-build"
        }
    ]
}
```

运行结果如下
![remote-debug](./img/remote-debug.gif)

## 4. 静态检查与fixbot修复

在代码编辑界面右键，会有很多有用的功能，包括，**格式化文档**、**静态检查**、**fixbot修复**，下面以静态检查和fixbot修复为例做一个展示
![check_and_fix](./img/check_and_fix.gif)

## 5. 其他

### 5.1 最常用的快捷键（持续补充）

ctrl+shift+p：命令面板，所有的操作都列在里面
ctrl+p： 全局查找文件
ctrl+t： 全局查找符号，包括函数等

### 5.2 建议的其他插件

- **CMake Tools**： cmake构建
- **Markdown Preview Enhanced**： markdown预览
- **Markdown Shortcuts**： markdown快捷键
- **markdownlint**： markdown格式化

### 5.3 关于远程编译和调试

本文介绍了进行远程编译和调试的根本原理和方法。vscode中还有很多其他的插件可以协助完成这项任务，大家可以按需选取。

- [Remote Build](https://marketplace.rnd.huawei.com/detail?identifier=RemoteBuildPro)，在wecode中远程执行远端服务器中的命令行进行构建。
- [it-remote-build-debug](http://isource.huawei.com/vscode_plugins/it-remote-ssh/wikis)，支持远程代码同步、构建和debug。但存在2个问题，与插件开发者沟通后，无果，遂弃用。
- [Remote - SSH](https://code.visualstudio.com/docs/remote/ssh), vscode原生插件，wecode上搜不到，代码、编译、调试全部在远端工作，就连gcc/gdb都是直接用远端的进行十分好用。

其中，Remote-SSH和gdbserver进行调试可以参考[我的博客](http://3ms.huawei.com/km/blogs/details/9674131?l=zh-cn)

### 5.4 关于跳转

Wecode的跳转完全是基于Clangd的，我们用wecode打开项目时，会自动在.vscode下面生成`compile_commands.json`文件，这个文件也被称作编译数据库，是编译整个项目所需编译信息的集合。其格式如下，每个command对象记录了一个编译单元在项目编译过程中是如何被编译的，包括编译参数、工作目录和源文件等

```json
[
    {
        "arguments": [
            "g++",
            "-c",
     "-DDOUBLE_PATH_ENABLE=1",
            "-I/home/zhenghang/cc/Codebin_Linux/update/../inireader",
            "-o",
  "CMakeFiles/fnbuildm.dir/home/zhenghang/cc/Codebin_Linux/inireader/inireader.cpp.o",
            "../inireader/inireader.cpp"
        ],
        "directory": "/home/zhenghang/cc/Codebin_Linux/update",
        "file": "../inireader/inireader.cpp"
    }
]
```

如果生成的compile_commands.json不能满足我们的要求，可以人工编辑该文件，修复好编译命令后，重启wecode，代码就可以正常的跳转.另外CMake也支持直接生成`compile_commands.json`文件
具体参考[http://wecode.huawei.com/Docs/74](http://wecode.huawei.com/Docs/74)
