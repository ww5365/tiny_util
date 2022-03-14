/*
 * 6.cpp
 *
 *  Created on: 2016年8月20日
 *      Author: wangwei69
 *
 *  通过编程学语言：c++
 *
 *  相当于反过来的一种思路，去学习编程语言。
 *
 *  工欲善其事，必先利其器。
 *
 *  chapter 6: 函数
 *  行文脉络：
 *  函数参数(传值，实参、形参)->
 *
 *
 */

#include "all.hpp"
#include <initializer_list>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>

#include <stdarg.h>

void error_msg(int err_code, std::initializer_list<std::string> para);

void sum_int(const int len,...);
void print_msg(char *buf,const char *format,...);

int (*fun_ret_2(int arr[][4],int))[4];//返回指向有4个列的数组指针
auto fun3(int len) ->int (*)[10]; //c++11 尾置的返回数据类型


constexpr int fun_test(){return 42;} //返回常量表达式，编译阶段就能确定这个式子的值；
int &get(int *arr, int idx);

int calc(char *,char*){return 1;}  // int calc(char* const,char* const );  重复定义
int calc(const char* ,const char* ){return 2;}


//函数类型

bool str_cmp_test(const std::string &s1, const std::string &s2){
    std::cout << "test function pointer use!" << std::endl;
    return false;
}

//定义函数类型别名
typedef bool str_cmp(const std::string &, const std::string &); //定义了str_cmp为此类函数的类型别名
using str_cmp2 = bool (const std::string &, const std::string&);//使用using定义了函数类型的别名，效果同上；上面的定义更常见；

//定义函数类型指针
typedef bool (*str_cmp_ptr) (const std::string &s1, const std::string &s2);//str_cmp_ptr函数类型指针
str_cmp2 *str_cmp_ptr2; //使用函数类型别名，来定义函数类型指针

//函数类型指针作为形参来使用

void my_sort(std::vector<int>&,  bool (*str_cmp_ptr)(std::string &, std::string &)); //函数类型指针作为形参，能否简化定义？

void my_sort(std::vector<int>& vec,  str_cmp_ptr fun){ //简化定义，直接使用函数类型指针

    std::cout << "test function pointer as parameters!" << std::endl;

    std::string s1,s2;
    fun(s1, s2);
}

//函数指针作为函数返回值来使用
auto get_fun_ptr() -> bool (*)(const std::string &, const std::string &){
    str_cmp2 *fun = str_cmp_test;
    return fun;
}

decltype(str_cmp_test)* get_fun_ptr2(){
    //第二种定义方式，使用decltype
    str_cmp_ptr fun = str_cmp_test;
    return fun;
}

void get_fun_ptr_use(){

    std::string s1,s2;
    std::cout << "test function pointer as return value!" << std::endl;
    //函数指针作为返回值，并实现调用此函数
    get_fun_ptr()(s1, s2);

}



void test_6(){


    std::cout << "-------------test chapter6----------------" << std::endl;

    //函数指针

    std::vector<int> test_vec(2, 0);
    test_vec.reserve(10);
    my_sort(test_vec, str_cmp_test);
    get_fun_ptr_use();


    /*
     * 函数参数
     */

    //尽量使用常量引用
    //数组作为形参

    ///可变参数的函数
    ///省略号参数:可变参数

     //error_msg(0, {"this", "error", "msg1"}); //mac eclipse中没有链接成功
    //error_msg(1, {"this", "error", "msg1", "msg2"});

    sum_int(4,344,4,5,6);

    char buf[256];
    buf[0]='\0';

    print_msg(buf,"this is %s test and result is %d","wangwei",1);

    printf("the buf content: %s",buf);

    /*
     * 函数的返回值
     */

    //返回数组指针,针对二维数组有用

    int array_test[][4] ={
            {1,2,3,4},
            {4,3,2,1},
            {5,6,7,8}
    };

    int (*ptr) [4] ;
    int size_test = sizeof(array_test)/sizeof(array_test[0]);
    ptr = fun_ret_2(array_test,size_test);

    int *ptr2 = array_test[1];

    for(auto i =0 ;i<4;i++){
        std::cout << std::endl
        <<"two dimension:" << (ptr2)[i] <<" ";
    }

    std::cout << std::endl;

    int (*ptr3)[10];
    ptr3 = fun3(1);

    std::cout << "ptr3 content: " << std::endl;
    for(auto i = 0;i< 10 ; i++){
        std::cout << i << " " << *ptr3[i] << std::endl;
    }

    std::cout <<std::endl;

    int *arr = *ptr3;
    //返回左值
    get(arr, 1) = 11;

    std::cout << "after change ptr3 content: " << std::endl;
    for(auto i = 0; i< 10; i++){
        std::cout << i << " " << arr[i] << std::endl;
    }



    //函数里面的特殊用途的语言特性  ？？


    //constexpr 函数   用途？    比如： constexpr int fun_test(){return 42;} ，返回是常量，定义数组

    int array[fun_test()]; //constexpr: 是内联，编译时把constexpr函数调用替换成结果值

    const int val2 = 10;

    int array2[val2];

    //函数的调试技术： 思想：调试时使用，上线后要屏蔽调调试代码

    ///assert 预处理宏，头文件cassert;断言，在什么场景下使用？
    // 调试的时候？因为使用NDEBUG可以使其失效。同时，断定条件是否成立。不成立，程序立马死掉了。
    assert(1 < 3); //条件为真，继续执行下面的代码；条件为假0，输出信息并终止程序；

    ///NDEBUG :
    ////1. gcc -D NDEBUG main.c  : 从编译器传入NDEBUG，不执行调试程序；相当于在main开始插入了 #define NDEBUG。同时assert也不在生效；
    ////2. #ifndef NDEBUG ...#endif  : 没有定义不进行调试标识，也就是进行调试，执行调试代码

    #ifndef NDEBUG

    std::cout <<"function:" << __func__  //编译器为每个函数定义的，存放函数名称
         <<" at file:"  << __FILE__   //预处理器定义，很有用的下面4个信息
         <<" at line:"  << __LINE__
         <<" on date:"  << __DATE__
         <<" at time:"  << __TIME__
         <<std::endl;

    #endif




    std::cout <<"this is programmer end"<<std::endl;


}

/*
 *  参数
 */

//数组作为形参

///下面三个函数等价；
void print1(const int *); //形参都作为const int* 来看待
void print2(const int[]);  //形参作用于一个数组，意图明显
void print3(const int[10]); // 忽略形参大小10的；防止越界，如何管理指针形参？

///管理数组指针长度的技术
void print(const int[],const int size); //常用，直接指明长度
void print(const int [],const int *beg,const int *end);//数组，开始元素指针，和尾元素后一个指针

///数组引用作为形参？ 能达到改变数组内部元素的目的，如何定义,下面那个是？

//void print(int &arr[10]);  //arr是一个有10个整形引用的数组
void print(int (&arr)[10]);//yes,not lose parathesis

///多维数组作为参数；多维实际在C++没有实现，其实是数组的数组

void print(int arr[][10]);
void print(int (*arr)[10]);//arr是指针，指向有10个元素的数组

//可变参数

///initializer_list形参

void error_msg(int &err_code, std::initializer_list<std::string> para){

    //initializer_list 是模板类
    for(auto it = para.begin(); it != para.end(); it++){
        std::cout << "para: " << *it << std::endl;
    }

    //这个类支持迭代器，所以也可以用范围for
    for(auto &e: para){
        std::cout << "para2: " << e << std::endl;
    }
    err_code = 0;
}

///省略号形参：参数通常用于c和c++通用类型，类对象通常难正确拷贝传递

/// <stdarg.h> va_list,va_start(),va_arg(),va_end()
/// 本质是一系列的宏定义；根据进程运行空间，参数的分布情况，计算出各个参数的地址；
/// 参数从右向左入栈，所以高地址->低地址：第n个->第1个参数；

void sum_int(const int len,...){ //计算整型参数的和,长度可变

    va_list para;
    va_start(para,len); //len是最后一个固定参数名称; para 指向第一可变参数的起始位置
    int para_value = va_arg(para,int);  //获取第一个int类型参数的值； 注意va_arg的第二个参数是数据类型：int

    std::cout << "param:" << 1 << ": "<<para_value <<std::endl;

    for (int i = 1 ;i < len;i++){
        para_value = va_arg(para,int);
        std::cout << "param:" << i+1 << ": "<<para_value <<std::endl;
    }
    va_end(para);
}

///vsnprintf打印va_list变量，进而能打印出可变参数,结果放在buf;

void print_msg(char *buf,const char *format,...){
    va_list va_par;
    va_start(va_par,format);
    vsnprintf(buf,256,format,va_par);  //专门格式化打印va_list变量
    va_end(va_par);
}


/*
 * 函数的返回值
 */

//有值返回

///如何被返回？将返回值返回到调用点

///不能返回局部变量的指针或引用

const std::string &fun_p(){
    std::string ret;
    if (!ret.empty())
        return ret;  // 错误：局部变量
    else
        return "empty"; //错误：局部变量
}

///返回非常量引用，作为左值； 开开眼

char &get_first_char(std::string str){
    if(!str.empty())
        return str[0];
}
void test(){
    std::string tt = "hangwei";
    get_first_char(tt) = 'w'; //第一个字符改为w
    std::cout << tt <<std::endl;
}

int &get(int *arr, int idx){
    return arr[idx];
}


//函数返回值：返回数组指针

typedef int arr1[10];  //arr1是int[10]类型别名
using arr2 = int [10]; //同上，c++11

arr1 *fun1(int len);//函数返回值：指向int[10]的一个指针

int (*fun2(int len))[10]; //同上，完整的定义方式

//int *fun2_1(int len)[10]; //返回值是一个，有10个指针元素的数组

auto fun3(int len) ->int (*)[10]{
    //分配二维数组内存空间
    int **ptr2 = new int*[3];
    for(int i = 0; i < 3; i++){
        ptr2[i] = new int[10];
    }
    //强制类型转换，不做的话，编译要报错
    int (*ptr)[10] = reinterpret_cast<int(*)[10]>(ptr2[1]);

    for (int i = 0; i< 10;i++){
        *ptr[i] = i + 1;
    }
    return ptr;
}


int (*fun_ret_2(int arr[][4] ,int size))[4]{
    //返回二维数组中第二行的首指针
    if(size>=2){
        int (*ptr)[4] ;
        ptr = &arr[1];
        return ptr;
    }
    return 0;
}


//函数里面的特殊用途的语言特性

///默认实参，从第一个默认开始，后面参数都需有默认
std::string screen(size_t h = 24, size_t w = 80, char back_grd = 'a'){return NULL;}

///内联函数 inline  注意内联和宏定义的区别？  阶段：编译，预处理；  参数检查：有，无  ；

inline int fun_test(int a, int b){
    return a > b ? a : b; //编译器会根据情况，在调用点直接展开该表达式
}














