/*
 * 4.cpp
 *
 *  Created on: 2016年6月28日
 *      Author: wangwei69
 */

#include <all.hpp>
#include <string>
#include <iostream>
using namespace std;

/*
 * 第四章  表达式
 */


/*
 * const_cast 使用场景：例子
 */

const string& fun(const string& str1, const string& str2){

    return str1.size() < str2.size() ? str1: str2;
    //返回长度小的字符串；但如果传入参数是两个非const的string，返回的是const的引用
    //这种情况，如何返回非const的引用? 如下重载函数
}

string& fun(string&str1, string& str2){

    const string &result = fun(const_cast<const string&>(str1), const_cast<const string&>(str2));
    //这样用是安全的，string& -> const string&

    return const_cast<string&>(result);
}



void test_4(){

    //求模运算结果？ 负数的

    std::cout << "-17 mod 10 : " << (-17%10) << std::endl;

    //前置后置，自增，自减 运算： 建议使用前置版本，提高性能

   //三元条件运算符: 嵌套， 简洁
    int score = 80 ;
    std::string str1 = (score >90)? "high score" :(score < 60)? "not pass" :"usual pass";
    std::cout << "socre: " <<str1 <<std::endl;

    //位运算： >> , <<, ~, & ,| ,^,

    unsigned char bits = 0227;
    std::cout <<"bits: " <<bits <<"reverse bit: " <<~bits <<std::endl; //取反：过程是：先提升char（8bit）为int（32），再反转
    unsigned long quiz = 17; //检测该无符号长整型，第5 bit是否为0？
    bool res = quiz & (1UL << 4); //先获取无符号字面值常量：1UL<<4 再进行与运算
    std::cout << "the res: " <<res <<std::endl;

    //交换两个整数数，不允许中间变量？如何实现
    //位运算：swap(a,b) ?
    uint16_t a = 3;
    uint16_t b = 2;
    a = a^b;
    b = a^b;//(a^b)^b ->a 赋给 b ；把a交换到b上
    a = b^a; // a ^(a^b) ->b 赋给a；把b交换到a上
    std::cout << "swap a b res:" << a << " " <<b << std::endl;



    //sizeof 运算符号

    int x[10];
    int *ptr = x;
    int len = sizeof(x)/sizeof(*x); //数组名，计算数组的总长度；*x第一个元素占用的字节数；
    std::cout << "compute the len of array: " << len <<std::endl;
    int len2 = sizeof(ptr)/sizeof(*ptr);//指针名，计算指针的大小；64bit
    std::cout << "compute the len of array2: "<<sizeof(ptr) <<":" <<sizeof(*ptr) <<":"<<len2 <<std::endl;

    decltype(x) xx;

    int len3 = sizeof(xx)/sizeof(*xx);// xx 为int[10] 数据类型
    std::cout << "compute the len of array3: "<<sizeof(xx) <<":" <<sizeof(*xx) <<":"<<len3 <<std::endl;

    //隐式数据类型转换

       //数组名，大多数情况，转成指针； 但sizeof，decltype,&,typeid 运算，还是看成数据，上面的例子能看出来；

       // 指针， 指向任意非常量的指针转成void *; 指向任意对象的指针转换成const void*;


    //显示类型转换   cast_name<type>(expression)

    int i = 2,j = 3;
    double k = static_cast<double> (i)/j; //static_cast : 底层不含const，类型明确


    /*
     * 显示类型转换:
     * static_case<TYPE>(EXP) : 最常用
     * const_cast : 只改变表达式（取消或增加）const属性；不能改变类型； 取消const属性后，对于常量，有背写的风险；使用场景：？ 函数重载的上下文中
     * dynamic_cast:
     * reinterpret_cast :
     *
     */

    int test = 10;
    const void *ptr1 = &test;

    const int *ptr_exact = static_cast<const int *>(ptr1); //将void * 类型的指针转成int *

    //int *ptr_exact2 = const_cast<int *>(ptr1);  //错误，不能改变类型

    void *ptr_exact3 = const_cast<void *>(ptr1); //正确，仅仅去掉了const属性；不改变类型；

















}



