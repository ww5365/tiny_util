/*
 * study_case.cpp
 *
 *  Created on: 2016年3月23日
 *      Author: wangwei69
 */


#include "macro_study.h"
#include <cmath>
#include <cstdint>
#include <iostream>
using namespace std;


extern "C" __attribute__((constructor)) void RegisterProxyModule(void)
{
    // napi_module_register(&g_proxyModule);
}

/*
 上面这段代码的解读：

 extern "C" 告诉 C++ 编译器使用 C 语言的链接方式来处理函数。这通常用于与 C 语言的代码进行链接，避免 C++ 名字修饰（name mangling）、
 原因：C++ 编译器会对函数名进行修饰以支持函数重载等特性，但 C 编译器不支持函数重载。使用 extern "C" 可以让函数的名字保持不变，确保可以与 C 代码进行链接。

 __attribute__((constructor))
作用：这是 GCC 特定的扩展，用于标记函数为构造函数，指示该函数在程序启动时自动执行，类似于 main 函数之前运行的初始化代码。
用途：当程序运行时，编译器会自动调用被标记为 constructor 的函数。在库加载时，如果这个标记的函数存在，它会在主程序执行前自动被调用。

*/

void macro_study(){

    //可变参数的宏定义
//    LOG("this is a test macro\n");
    int t = 10 ;

    // LOG("this is another test macro:%d\n",t);
    // LOG("this is another test macro:%d,%d\n",t, 30)
// 
    FACTORY(te, st);
// 
// 
    // uint32_t prefix = (1 << 10);
// 
    // if (BIT_TST(prefix, 10) == 1){
        // cout << "bit_tst res: " << prefix << " : " << BIT_TST(prefix, 10) << endl;
    // }
// 


}


