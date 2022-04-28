
#pragma once

#include <string>
#include <iostream>
#include <typeinfo>
#include <sstream> 

/*

typeid : c++ 的关键字,类似sizeof，返回：  标准库中类型：type_info对象的引用；

typeid(表达式/数据类型):  最为关键得到对象或类型的名称

如果表达式的类型是类类型且至少包含有一个虚函数，则typeid操作符返回表达式的动态类型，需要在运行时计算；否则，typeid操作符返回表达式的静态类型，在编译时就可以计算

type_info数据类型支持操作： 
t1 == t2 
t1 != t2
t1.name(); // 返回cstr类型的类型名称，这个类型名称不一定是真实的类名;由编译器决定

*/

class ClassBase{
public:
    ClassBase():_name(""){}
    virtual ~ClassBase(){}
    virtual void set_name(std::string str){
        _name = str;
    }
    virtual std::string get_name(){

        //实际调用这个函数的是基类？继承类？
        // 根据运行状态来决定，因为是virtual函数： 如果是Derived派生类指针，调用了get_name，之后又调用了基类的get_name, 此时typeid获取到的是派生类的类型名；
        const std::type_info &typeinf = typeid(*this);
        std::cout <<"typeid get typename: " << typeinf.name() << std::endl;
        _name.assign(typeinf.name());
        return _name;
    }
private:
    std::string _name;
};


class ClassDerived : public ClassBase{
public:
    ClassDerived(int a = 0):ClassBase::ClassBase(), _no(a){}
    virtual ~ClassDerived(){}

    virtual std::string get_name(){
        std::stringstream ss;
        ss << ClassBase::get_name() << _no;
        return ss.str();
    }

private:
    int _no;
};


class BaseA {};
class DeriveA: public BaseA {};
 
class BaseB 
{
	virtual void f(){}  // 基类中有虚函数，运行性可能有多态
};
class DeriveB: public BaseB {};

