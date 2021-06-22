#ifndef _TINY_UTIL_SRC_INCLUDE_PREDICATE_USE
#define _TINY_UTIL_SRC_INCLUDE_PREDICATE_USE 

#include <iostream>


//定义个类；类中成员函数再定义lamda表达式，使用类成员变量和成员函数局部变量；调用后看值的变化
class Predicate{
public:
    Predicate(int a = 0):_a(a){}
    virtual ~Predicate(){}

    inline void test_predicate(){
        int b = 3;

        auto f = [&](int c)->int{
            
            ++_a; //类成员变量自加
            ++b; //成员函数变量
            ++c; //参数自加
            std::cout << "test value list: " << _a << ":" << b << ":" << c << std::endl;
            return (_a + b + c);
        };

        int sum = f(4);
        std::cout << "test value list2: " << _a << ":" << b << ":" << sum << std::endl;

    } 

private:
    int _a;




};













#endif

