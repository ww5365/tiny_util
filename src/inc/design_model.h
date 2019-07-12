/*
 * design_model.h
 *
 *  Created on: May 28, 2019
 *      Author: wangwei69
 */

#ifndef SRC_INC_DESIGN_MODEL_H_
#define SRC_INC_DESIGN_MODEL_H_

#include "thread_use_demo.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class DataProcess{
private:
    vector<int> data;
public:
    void process();
};

class _Singlton{

private:
    static bool s_create;
    static _Singlton *s_instance;
    string str;
    unique_ptr<DataProcess> dp; //单例中真正进行数据处理的类(智能指针);独占方式；

    //copy构造函数是私有的，类用户（类定义这）可用；普通用户（类使用者）不可用;
    explicit _Singlton(string s = ""):str(s), dp(new DataProcess){ cout << "constructor: " << str << endl;}

    //拷贝和赋值
    _Singlton(const _Singlton &cp) = delete;
    _Singlton& operator=(const _Singlton &cp) = delete;


public:

    //c++11 最简洁实现方式，static是线程安全的
    static _Singlton& get_instance(){
        static _Singlton obj("_Singlton test"); //类内部：私有构造函数可见
        return obj;
    }

    //常用: 多线程 + double chcek
    static _Singlton& get_instance2(){
        if (!s_create){
            Lock lock;
            if (!s_create){
                static _Singlton obj("_Singlton test2");
                s_instance = &obj;
            }
        }

        return *s_instance;
    }


    void data_process(){
        dp->process();
    }

};


bool _Singlton::s_create = false;
_Singlton* _Singlton::s_instance = nullptr;





#endif /* SRC_INC_DESIGN_MODEL_H_ */
