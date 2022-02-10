/*
 * 5.cpp
 *
 *  Created on: 2016年7月22日
 *      Author: wangwei69
 */



/*
 * 第五章： 语句
 */

#include <iostream>
#include <vector>

#include <stdexcept>

using namespace std;

void test_5(){


    /*
     * swicth: 使用
     * var：仅支持整型常量
     */
    int var = -1;
    switch(var){//支持int char
        case 1:
            cout << "var is one" <<endl;
            break;
        case -1:
            cout << "var is negtive one" <<endl;
            break;
        default:
            break;
    }

    /*
     * for: c++ 11 新引进的范围for语句
     */
    std::string str_for = "wangwei nihao ,come on every day!";
    for(auto &ch:str_for){
        //str_for 必须是数组，string，vector等类型的对象，共同点是迭代器能返回：begin,end成员
        cout << ch <<": " ;
    }
    cout << endl;
    std::vector<int> vec_for = {12,2,3,35,45,0,455};

    for (int r:vec_for){
        cout << r <<": " ;
    }

    /*
     *跳转语句：知道在什么情况下使用？
     * break ：循环，switch
     * continue ：循环
     * goto ： 标签
     *
     */


    /*
     * 异常主动抛出：throw
     * 异常处理：
     *  try{
     *  }catch(){
     *  }..
     *
     * 常用异常处理的类：<stdexcept>
     * exception
     * runtime_error
     * bad_alloc
     * bad_cast
     */

    try{
        std::cout << "this is test exception " <<std::endl;

        if (true){
            throw std::runtime_error("wangei test runtime error");
        }

    }catch(std::runtime_error e){
        cout << e.what() <<endl;
    }catch(std::exception e2){
        cout << e2.what() <<endl;
    }catch(std::bad_cast e3){
        cout << e3.what() << endl;
    }catch(std::bad_alloc e4){
        cout << e4.what() << endl;
    }catch(...){
        cout <<"no name exception" <<std::endl;
    }


}

