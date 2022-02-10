#ifndef _TINY_UTIL_SRC_INCLUDE_PREDICATE_USE
#define _TINY_UTIL_SRC_INCLUDE_PREDICATE_USE 

#include <iostream>


/* 
* 定义个类；类中成员函数定义lamda表达式，使用类成员变量和成员函数局部变量；调用后看值的变化
* [] () -> TYPE {}  lambda表达式
* [] : 捕获
* 显式 和 隐式 [=] [&]
* 值捕获 和 引用捕获
* 
* 类的成员函数中，定义了lambda表达式，内部想使用类成员变量的值，并改变, 该怎么办？
* [&] : 隐式的引用捕获
* [this] : 显式的捕获this对象指针，之后可以使用类中成员变量
*/

class Predicate{
public:
    Predicate() = default;
    Predicate(int a = 0):_a(a){}
    virtual ~Predicate(){}

    inline void test_predicate(){
        int b = 3;
        
        // auto f = [&](int c) -> int  // 等价于下面的写法: 隐式引用捕获， 传入的变量的值可以改变, 内外部都变
        // auto f = [this, &b](int c)  -> int

        // _a 值被改变,相当于显式引用捕获类成员变量; b 显式值捕获 因为有mutable修饰，可以在表达式内部改变，但不影响外部传入的
        auto f = [this, b] (int c) mutable -> int
        {
            
            ++_a; //类成员变量自加 : _a 初始化为1
            ++b; //成员函数变量 
            ++c; //参数自加 
            std::cout << "test value list in lambda: " << _a << ":" << b << ":" << c << std::endl; // 2:4:5
            return (_a + b + c);
        };

        int sum = f(4);
        std::cout << "test value list2 out lambda " << _a << ":" << b << ":" << sum << std::endl; // 2 : 3 : 11

    } 

private:
    int _a;
};

#endif

