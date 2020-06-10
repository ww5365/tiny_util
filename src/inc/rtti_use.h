
#pragma once

#include <string>
#include <iostream>
#include <typeinfo>
#include <sstream> 

class ClassBase{
public:
    ClassBase():_name(""){}
    virtual ~ClassBase(){}
    virtual void set_name(std::string str){
        _name = str;
    }
    virtual std::string get_name(){

        //实际调用这个函数的是基类？继承类？
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