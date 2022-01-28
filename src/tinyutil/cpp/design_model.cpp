/*
 * design_pattern.cpp
 *
 *  Created on: Mar 10, 2019
 *      Author: wangwei69
 */

#include <iostream>

#include "../inc/design_model.h"

// 类中静态成员(private)，必须要初始化; 放在cpp中定义，.h中声明;
// 不能在.h中定义初始化，因为别的文件include头文件时，会造成重复定义，链接报错

bool Singlton::s_create = false;
Singlton* Singlton::s_instance = nullptr;

class TestClass {
public:

    TestClass() 
    { 
        std::cout << "create TestClass object by CLASS_REGISTER" << std::endl;
    }
    ~TestClass(){}

    void print(){
        std::cout << "this is Test class create by CLASS_REGISTER" << std::endl;
    }

};

CLASS_REGISTER(TestClass);


void test_design_pattern(){

    //Singlton::instance().printTest();
    //Singlton::instance().printTest();
    //Singlton::instance().printTest();

    //重新写了一个singlton

    Singlton &sgl1 = Singlton::get_instance();
    Singlton &sgl2 = Singlton::get_instance2();

    //_Singlton ss("sss");
    ClassFactory::GetInstance().GetClassObj("TestClass");


}




