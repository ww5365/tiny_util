[TOC]

# C/C++开发配置指南

## 1. 环境准备

如要安装的软件如下：

- [vscode](https://code.visualstudio.com/DownloadF)，直接下载安装
- [mingw64](https://sourceforge.net/projects/mingw-w64/files/mingw-w64/)，下载`x86_64-posix-seh`，[结构化异常处理:SEH Structured Exception Handling Windows使用自己的异常处理机制]; 解压到`C:\mingw64`下，并在环境变量PATH配置`C:\mingw64\bin`。同时把`bin`目录下`mingw32-make.exe`重新copy，重命名为`make.exe`。使用命令`gcc -v`和`g++ -v`，检验安装是否成功
- [cmake](https://cmake.org/download/)，下载完解压，并将`bin`配置到环境变量PATH下。使用`cmake --version`检验安装是否成功
- [plink](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html)，用于远程编译和调试

## 2. vscode插件

需要安装插件：
- cmake , cmake tools
- c/c++
  搜索 c/c++，选择第一个安装即可
- sftp
- Visual Studio IntelliCode
  是一组AI辅助功能，可通过上下文智能感知，参数完成，代码格式和样式规则推断等功能提高开发人员的工作效率。
- code runer
  
  
## 3.vscode 配置

### 3.1 vscoe基本配置
ctrl+shift+p -> 首选项：打开设置(json)  preferences : open user settings
新增如下配置，涉及**字体**、**编码**、**目录树缩进**、**ctrl+鼠标滚轮调整字体大小**，**markdown配置**

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


### 3.2 task.json配置及运行

* 生成默认task.json
  ctrl + shift + p -> tasks: configure default task  生成task.json

* 快捷键
  - ctrl + shift + b : 选择不同的task任务执行  
  使用下面配置task.json的Cmake，报错:CMAKE_MAKE_PROGRAM is not set  ctrl + shift + p -> cmake:edit cmake cache 设置make路径 `D:\Tools\mingw64\bin`
  - shift + f5 : run without debug


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


### 3.3 cmake 配置

#### 3.3.1  cmake介绍
cmake命令将CMakeLists.txt文件转化为make所需要的makefile文件，最后用make命令编译源码生成可执行程序或共享库（so(shared object)）。

cmake  指向CMakeLists.txt所在的目录，例如cmake .. 表示CMakeLists.txt在当前目录的上一级目录。
cmake后会生成很多编译的中间文件以及makefile文件，所以一般建议新建一个新的目录，专门用来编译，例如

``` shell
mkdir build
cd build
cmake .. //CMakeLists.txt文件放在上一层
make  //根据生成makefile文件，编译程序。
```

### 3.3.2 cmake的配置及编译

* VsCode设置Makefile类型：
  文件>首选项>设置>搜索cmake: generator
  设置为”MinGw Makefiles”或者” Unix Makefiles”，这相当于运行cmake –G “MinGw Makefiles” .

* VsCode中cmake全部配置：
  ctrl + shift + p -> cmake -> edit cmake cache 也可以修改cmake配置,运行环境

* cmake 命令：关键编译时生成complie_commands.json文件，用来进行代码的跳转

  > -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE 
  > 或 set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  
* cmake 简单示例
``` shell
# 使用示例 
# configure the project and generate a native build system: 
cmake    "-GNinja" \   # 配置使用Ninja来进行构建和编译；指定构建系统生成器,生成build.ninja文件
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
cmake --build . --target  rankengine_all   # --build是指定CMakeCache.txt（或CMakeFiles文件夹）所在的路径;在此目录中构建二进制树

# 另一个示例
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


### 3.4 launch.json 配置debug

参考下面的实际项目例子来看吧


## 4. 创建项目使用配置跑通流程

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



### 4.1 编译配置

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

### 4.2 调试debug配置

调试快捷键：F5 需要编辑`launch.json`，新增`local-debug`启动器

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


## 5. 其他

### 5.1 最常用的快捷键（持续补充）

ctrl+shift+p：命令面板，所有的操作都列在里面
ctrl+p： 全局查找文件
ctrl+t： 全局查找符号，包括函数等

### 5.2 关于跳转

#### compile_commands.json

Wecode的跳转完全是基于Clangd的，我们用wecode打开项目时，会自动在.vscode下面生成`compile_commands.json`文件，这个文件也被称作编译数据库，是编译整个项目所需编译信息的集合。

人工编辑该文件，修复好编译命令后，重启wecode，代码就可以正常的跳转.另外CMake也支持直接生成`compile_commands.json`文件.

``` json
-DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE 

或者

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
```

#### 导入文件

先替换compile_commands.json 中路径为windows本机路径

```shell
1,$s#/usr/local/bin/g++#g++#g
1,$s#/opt/huawei/wangwei/GeoCodingRankEngine_dev#D:/workspace/my_codehub/MapGeoCodingRankEngine_dev#g

```

将上面处理的compile_commands.json 放在.vscode 下，导入：F1 -> import compile_commands.json 文件


#### 本地不跳转,不提示的解决方案：

导入本地头文件：
    设置→用户→拓展→WeCode C/C++→Codebase › Generator: Search Paths 包含头文件路径列表，可以是src根目录
包含头文件找到include路径：
    Ctrl + Shift + P执行命令→wecode c++: generate compile_commands.json file→弹窗让选择文件夹
