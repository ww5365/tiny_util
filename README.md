# 项目开发小工具


可以直接在命令行运行如下命令产出makefile文件
D:\tools\cmake-3.20.1\bin\cmake.EXE --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=D:\tools\mingw64\bin\gcc.exe -DCMAKE_CXX_COMPILER:FILEPATH=D:\tools\mingw64\bin\g++.exe -Hd:/workspace/gitlab/tiny_util -Bd:/workspace/gitlab/tiny_util/build -G "MinGW Makefiles"

```
-H定义home目录也就是主CMakeLists.txt所在目录
-B定义build编译生成目录
-G定义generator-name生成的编译规则文件类型
```
