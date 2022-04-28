#include "../inc/com_use.h"

#include <tuple>

using namespace std;

/*
头文件：#include  <tuple>

元组容器：tuple 是一个固定大小的不同类型值的集合，是泛化的std::pair。类似：结构体  但不需要创建结构体，程序更简洁直观。

参考：

1. https://www.cnblogs.com/pandamohist/p/13630613.html


*/

void tuple_recurse();


void tuple_use_test()
{

    std::cout << "------ tuple_use_test ------- " << std::endl;
    
    /* 
    * 定义并初始化
    */
    std::tuple<int, string> tp1;

    std::tuple<int, string, bool> tp2(1, string("ww"), true); //定义并初始化
    std::tuple<int, string, bool> tp22 = {1, "ww", false}; //定义并初始化
    string name ("wang");
    std::tuple<int ,string &> tp3(2, name); // 类型可以是引用，指向name,通过元祖修改了1号元素的数值，name也会跟着改变
    std::cout <<"before name : " << name << std::endl;
    std::get<1>(tp3) = "wei"; 
    std::cout <<"after name : " << name << std::endl;

    std::tuple<int ,string, bool> tp4 = std::make_tuple(4, "ni", true);
    auto tp5 = std::make_tuple(5, "hao", true);

    /*
    * 访问元素: 
    * 1、使用索引方式，必须get<N>() N是编译时确定的，不能是变量
    * 2、使用std::tie进行解包操作
    */
    int idx = std::get<0>(tp5);
    string myName = std::get<1>(tp5);
    bool sex = std::get<2>(tp5);
    
    std::cout <<" idx: " << idx  << " name: " << myName << " sex: " << sex << std::endl;

    
    std::tie(idx, myName, sex) = tp4; 
    
    std::cout <<" idx: " << idx  << " name: " << myName << " sex: " << sex << std::endl;

    std::cout << "------ tuple_use_test ------- " << std::endl;

}
