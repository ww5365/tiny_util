/*
 * str_vec.h
 *
 *  Created on: Mar 25, 2019
 *      Author: wangwei69
 */

#ifndef STR_VEC_H_
#define STR_VEC_H_

#include <memory>
#include <string>

using namespace std;


/*
 * 定义实现strvec类: 类似 vector<string> 功能，存储任意多个string字符串
 *
 *
 */


class StrVec{


private:

    string *element;
    string *first_free; //第一个空闲位置
    string *cap;   //容量

    static allocator<string> alloc;  //为什么要设计成static?

public:

    StrVec(const string &s){
        alloc.allocate(1);
        //alloc.construct()
    }



    /*
     * 在14章：运算符这章节，新增的运算
     *
     * 1. operator=
     * 2. operator[]
     *
     * 3.
     *
     *
     */


    //赋值运算，支持初始化列表的形式：StrVec test = {"ab", "cde"}

    StrVec& operator= (std::initializer_list<string> li);


    //下标运算， StrVec test[0]  为什么有两个版本？

    StrVec& operator[] (std::size_t n);
    const StrVec& operator[] (std::size_t n) const;






};






#endif /* STR_VEC_H_ */
