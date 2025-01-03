

/*
* 将函数的声明和实现都放在 .h 头文件中，并在多个 .cpp 文件中包含这个头文件，可能会导致 duplicate symbol（重复符号）链接错误。
* 原因：头文件中的非 inline 函数定义会被多个 .cpp 文件编译，从而在链接阶段出现重复定义;
       头文件中的函数定义会被复制到每个包含该头文件的 .cpp 文件中。这意味着多个目标文件（.o 文件）中会包含相同的函数符号。

*/

/*
example.h：
#ifndef EXAMPLE_H
#define EXAMPLE_H

// 函数声明和实现都在头文件中
void myFunction() {
    // 函数定义
}
#endif

file1.cpp：
#include "example.h"
void test() {
    myFunction();
}


file2.cpp：
#include "example.h"
void test2() {
    myFunction();
}

g++ file1.cpp file2.cpp -o output

链接报错： duplicate symbol: myFunction

*/
