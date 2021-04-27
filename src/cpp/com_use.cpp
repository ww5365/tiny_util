/*
 * array_use.cpp
 *
 *  Created on: Jul 4, 2018
 *      Author: wangwei69
 */

#include "../inc/com_use.h"
#include <cstddef>
#include <iterator>
#include <bitset>

extern int *g_int_ptr; //别的文件定义的；在本文件声明即可用；

/*
 * @brief
 * 1.不同的类型的数组的定义
 * 2.多维数组的动态内存分配和回收
 */

void array_use_test(){
    const size_t LEN = 10;
    int arr1[LEN] = {1,2,3,4,5};
    int *arr2[LEN];    //定义指针数组：数组中的元素都是指向整型指针；
    int (*ptr)[LEN];  //定义数组指针：ptr是指针；指向一个有LEN个整型元素的数组；
    int (&ref)[LEN] = arr1;  //定义数组的引用： ref是一个引用；引用了有LEN个整型元素的数组；
    //ref = arr1;
    int *(&ref2)[LEN] = arr2; //引用需要初始化
    int *ptr_end = &arr1[LEN];   //尾后指针，这样不太安全，c++11提供了函数
    int *ptr_head = std::begin(arr1); //数组头指针
    int *ptr_post_tail = std::end(arr1); //数组尾后指针

    ptrdiff_t len = ptr_post_tail - ptr_head; //类型：ptrdiff_t; 两个位置长度；


    //多维数组的内存的动态分配和回收
    constexpr size_t ROW = 3;
    constexpr size_t COL = 4;

    //分配
    int **arr3 = nullptr;
    arr3 = new int*[ROW];
    for (size_t i = 0;i < ROW; i++){
        arr3[i] = new int[COL];
    }
    for (size_t i = 0;i < ROW; i++){
        for(size_t j = 0;j < COL; j++){
            arr3[i][j] = i + j;

            std::cout << arr3[i][j] << " ";
        }
        std::cout << std::endl;
    }

    //回收
    for (size_t i = 0;i < ROW; i++){
        delete []arr3[i];//每行指向的多列回收
    }

    delete []arr3; //回收保存行数组


    //全局变量

    g_int_ptr = arr1;

    std::cout << "global int ptr: " << std::endl;
    for (size_t i = 0; i < sizeof(arr1)/sizeof(int); i++){

        std::cout << g_int_ptr[i] << " ";
    }

    std::cout << std::endl;



}


/*
 * @brief
 * const constexpr  区别
 * constexpr 什么使用比较合?
 * 数组长度，枚举初始化
 */

struct A{
    int x,y;
    constexpr A(int xx, int yy):x(xx),y(xx){}//需要为空，也就是必须在初始化列表中初始化；
};

constexpr A a(1,2); //常量表达式对象

enum Test{
  XX = a.x, //直接使用常量表达式
  YY = a.y
};

constexpr int LEN = 32; //这点类似：const int LEN = 32..

void const_use_test(){

    std::bitset<LEN> bs; //bitset的长度是编译期间必须要知道的
    bs.flip(9); //第10bit的数据取反: bs.set(9,~bs[9]);
    std::cout << "the value of pos 10: " << bs[9] << std::endl;










}




void com_use_test(){


    std::cout << "begin to test com use--const use test !" << std::endl;
    const_use_test();

    std::cout << "begin to test com use--array use test !" << std::endl;

    array_use_test();


}



