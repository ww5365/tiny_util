# 项目开发小工具

## 使用本project

1. 先配置task.json, 参考01_c++_with_vscode.md中task.json配置
2. 其它设置小改动：解决exe文件不能执行，显示有问题
   ```
    "terminal.integrated.defaultProfile.windows": "Command Prompt",
    "terminal.integrated.shell.windows": "C:/WINDOWS/System32/cmd.exe",
    "terminal.integrated.persistentSessionScrollback": 1000000,
    "terminal.integrated.scrollback": 1000000
   ```

## 使用cmake进行编译

1. config + 编译 + 运行

* 通过cmake插件进行config

  ctrl + shift + f7  =》 config   相当于执行如下命令产出makefile文件

  ``` shell
  D:\tools\cmake-3.20.1\bin\cmake.EXE 
  --no-warn-unused-cli 
  -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE 
  -DCMAKE_BUILD_TYPE:STRING=Debug 
  -DCMAKE_C_COMPILER:FILEPATH=D:\tools\mingw64\bin\gcc.exe 
  -DCMAKE_CXX_COMPILER:FILEPATH=D:\tools\mingw64\bin\g++.exe 
  -Hd:/workspace/gitlab/tiny_util 
  -Bd:/workspace/gitlab/tiny_util/build 
  -G "MinGW Makefiles"
  
  -H定义home目录也就是主CMakeLists.txt所在目录
  -B定义build编译生成目录
  -G定义generator-name生成的编译规则文件类型
  ```
* 编译
  使用快捷键F7， 这也是设置了cmake插件的得到

* 运行：
  ctrl + shift + p => tasks: run 
