/*
 * new_feature_c11_use.cpp
 *
 *  Created on: Sep 10, 2018
 *      Author: wangwei69
 */

#include "com_use.h"
#include <vector>

#include <iostream>


/*
 * 右值引用？
 * T &&
 * 作用：？解决c++效率问题。深拷贝构造生成临时变量；
 * https://juejin.cn/post/6844903497075294216   这篇文章参考下，看起来比较深入
 */

struct A{
    char *x;
    int len;
    A(char *str, int b): len(b){
        x = new char[len];
        snprintf(x, 10, "%s", str);
        std::cout << "constructor!" << std::endl;
    }

    A(const A &other){
        if(this != &other){
            len = other.len;
            this->x = new char[len];
            snprintf(x, 10, "%s", other.x);
        }

        std::cout << "copy constructor!" << std::endl;
    }

    A(A &&o){
        this->x = o.x;
        len = o.len;

        std::cout << "move copy constructor"  << std::endl;

        //delete []o.x;
        //o.x = nullptr;
        //o.len = 0;
    }

};

void rvalue_referenct_use(){

    A a("wangwei", 30);

    std::vector<A> vec;
    vec.reserve(10);//预先分配合适大小的vector，也能提高效率；
    vec.push_back(a);
    std::cout << "-----" << std::endl;
    vec.push_back(a);

    std::cout << "-----" << std::endl;
    vec.push_back(a);

    std::cout << "-----" << std::endl;
    vec.emplace_back(a);//a不是右值，所以这个效果和push_back类似

    std::cout << "a.x: " << a.x << " size: " << vec.size()<<std::endl;

    std::cout << "-----" << std::endl;
    vec.emplace_back(std::move(a));

    std::cout << "a.x: " << a.x << " size: " << vec.size() << std::endl;

    std::cout << "-----" << std::endl;


}




void new_feature_c11_use_test(){
    rvalue_referenct_use();

}
