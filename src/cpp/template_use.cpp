/*
 * template_use.cpp
 *
 *  Created on: Aug 31, 2018
 *      Author: wangwei69
 */

#include "com_use.h"

#include <string>
#include <iostream>

using namespace std;

/*
 * 1、普通的类，其成员函数是否可以为模板函数？ok
 *
 */
class Frame{

public:
    Frame():str(""){
    }
    //模板成员函数
    template<typename Type>
    void get_type_len(){
        Type test;
        cout << "sizeof Type: " << sizeof(test) << endl;
    }
private:
    string str;
};


void template_use_test(){

    Frame fr;

    //调用模板成员函数
    fr.get_type_len<int>();

}



