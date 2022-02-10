/*
 * 10_test_bind.cpp
 *
 *  Created on: Mar 8, 2019
 *      Author: wangwei69
 */
#include "all.hpp"
#include <iostream>
#include <string>
#include <functional>

using namespace std;



/*
 * 练习使用bind
 *
 *  1、绑定普通函数
 *  2、绑定类中成员函数
 *
 *
 */

int fun(const string &str , int num){

    cout << "----------" << endl;
    cout << "hello " << str << endl;
    cout << "invoke time: " << num << endl;

    return 0;
}



class Object{

private:

    string name;

public:

    explicit Object(const string& s = ""):name(s){}

    void printObject(const string &s){
        //this->name = s;
        cout << "object function name: " << this->name << endl;
        cout << "object function str: " << s << endl;
    }

};




void test_10_bind(){

    int number = 0;

    /*
     * 绑定普通的函数:
     *
     * auto useFuc = bind(realFunc,_1,r, _2, s)
     *
     * 使用： useFuc(p1,p2) => realFunc(p1,r,p2,s)
     *
     * bind的返回值类型： function<void (p1, p2)> useFunc;
     *
     * 引用传值： cref ref
     *
     */

    typedef function<int(const string &str)> FunType; //函数类型指针

    FunType newf = std::bind(fun, std::placeholders::_1, number);
    ++number;
    newf("world"); // 等价与调用： fun("world", number)  使用新函数名，可以少传一个参数，另一个参数默认绑定:值是绑定时的值，不是调用时的值


    FunType newf2 = std::bind(fun, std::placeholders::_1, cref(number));
    ++number;
    newf2("world2"); //默认绑定的参数number，是传引用；所以这里是调用时的真实值

    /*
     * 绑定一个对象的成员函数
     *
     * bind(&类中成员函数, &类对象, 参数列表...)
     *
     */

    Object obj("wang");
    typedef function<void(const string &s)> FunType2;
    FunType2 newf3 = std::bind(&Object::printObject, &obj, std::placeholders::_1);
    newf3("wangwei"); //等价调用: obj.printObject("wangwei");

    /*
     * 离线建库代码中，有使用 bind
     */


}


