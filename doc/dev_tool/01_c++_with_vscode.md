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

## 2. cmake编译项目

### 2.1 cmake介绍
cmake命令将CMakeLists.txt文件转化为make所需要的makefile文件，最后用make命令编译源码生成可执行程序或共享库（so(shared object)）。

cmake  指向CMakeLists.txt所在的目录，例如cmake .. 表示CMakeLists.txt在当前目录的上一级目录。
cmake后会生成很多编译的中间文件以及makefile文件，所以一般建议新建一个新的目录，专门用来编译，例如

``` shell
mkdir build
cd build
cmake ..
make  //根据生成makefile文件，编译程序。
```

### 2.2 cmake的配置及编译

* VsCode设置Makefile类型：
  文件>首选项>设置>搜索cmake: generator
  设置为”MinGw Makefiles”或者” Unix Makefiles”，这相当于运行cmake –G “MinGw Makefiles” .

* VsCode中cmake全部配置：
  ctrl + shift + p -> cmake -> edit cmake cache 也可以修改cmake配置,运行环境

* cmake 命令：关键编译时生成complie_commands.json文件，用来进行代码的跳转

  > 修改项目路径下：./scripts/build.sh
  >
  > 产出文件目录：


``` shell
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

本地不跳转,不提示的解决方案：

导入本地头文件：
    设置→用户→拓展→WeCode C/C++→Codebase › Generator: Search Paths 包含头文件路径列表，可以是src根目录
包含头文件找到include路径：
    Ctrl + Shift + P执行命令→wecode c++: generate compile_commands.json file→弹窗让选择文件夹
