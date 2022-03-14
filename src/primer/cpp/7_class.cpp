/*
 * 7.cpp
 *
 *  Created on: Dec 14, 2018
 *      Author: wangwei69
 */


#include "all.hpp"
#include "7.h"



/*
 * this指针
 * 常量对象或常量对象的指针，只能访问常量成员函数，为什么？
 *
 * 1、常规理解：因为是常量对象或常量对象的指针，那么常量对象本身内容是不能被改变的；如果访问非const的成员函数，是有可能改变对象本身内容的；
 *
 * 2、深入理解：每个对象有隐含的指向自身的this指针，对象隐式的通过this来访问数据成员，类型：TYPE *const this：这是指向非常常量的常量指针；
 *            如果对象自身是const的，这个隐含的指针还是指向非常量对象的，会造成类型不匹配了。
 *            所以怎么把this变成：const TYPE *const this这种类型？
 *            通过成员函数最后加上const，把this申明为指向const对象的指针，对象就可以通过this来访问数据成员了；
 *            没有申明为const的成员函数，是不能被常量对象调用的；
 *
 *            const函数如果返回：*this 则是常量对象的引用；
 *
 *            总结：为了保持类的兼容性，能申明为const成员函数的，就尽量声明为const；保证类的const对象，尽可能多的访问成员函数；
 *
 */



void test_7(){

    const Sales_data sa;

    //sa.addCount(); //不能访问非const的成员函数

    sa.getCount();

    const Screen screen;
    screen.some_memeber(); //获取mutable成员变量数据

    Screen screen2;

    screen2.display(std::cout).set('w'); //自动调用重载的非const的display函数
    screen2.display(std::cout); //调用const的display函数
    std::cout << std::endl << "screen2 some member: " << std::endl;
    screen2.some_memeber();

    std::cout << std::endl;

    //测试友元类

    Window_mgr wm;
    wm.set(screen2);

    std::cout << std::endl << "in wm screen's some member: " << std::endl;

    Screen &s = wm.get(0);
    s.display(std::cout);

    std::cout << std::endl;
    screen2.display(std::cout);
    std::cout << std::endl;
    wm.clear(0);

    s.display(std::cout);

    std::cout << std::endl << "test finished!" << std::endl;

    //默认构造函数
    Test_class test; //调用默认构造函数
    //test.add(std::string("999-999")); // 因为接受一个string参数的构造函数是exlicit的，不能进行隐式类型转换；
    test.add(Test_class(std::string("999-999"))); //"999-999" 隐式类型转换成string，并调用一个参数的构造函数，隐式构造了一个临时Test_class变量;





}




