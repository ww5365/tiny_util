/*
 * design_model.h
 *
 * Created on: May 28, 2019
 * Author: wangwei69
 */

#ifndef SRC_INC_DESIGN_MODEL_H_
#define SRC_INC_DESIGN_MODEL_H_

#include "thread_use_demo.h"
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
using namespace std;

class DataProcess {
private:
    vector<int> data;

public:
    void process();
};

class Singlton {
private:
    static bool s_create;
    static Singlton *s_instance;
    string str;
    unique_ptr<DataProcess> dp; // 单例中真正进行数据处理的类(智能指针);独占方式；

    // copy构造函数是私有的，类用户（类定义这）可用；普通用户（类使用者）不可用;
    explicit Singlton(string s = "") : str(s), dp(new DataProcess)
    {
        cout << "constructor: " << str << endl;
    }

    // 拷贝和赋值
    Singlton(const Singlton &cp) = delete;
    Singlton &operator = (const Singlton &cp) = delete;


public:
    /*
     * 懒汉方式实现单例模式: 使用的时候才创建实例
     */

    // 方式1: c++11 最简洁实现方式，static是线程安全的
    static Singlton &get_instance()
    {
        static Singlton obj("Singlton test"); // 类内部：私有构造函数可见
        return obj;
    }

    // 方式2： 常用: 多线程 + double chcek
    static Singlton &get_instance2()
    {
        if (!s_create) {
            Lock lock; // 保证多线程的情况下线程安全
            if (!s_create) {
                static Singlton obj("Singlton test2");
                s_instance = &obj;
            }
        }

        return *s_instance;
    }

    void data_process()
    {
        dp->process();
    }
};




/*
* 单例 + 工厂 + 反射机制 ？
* 通过类名自动化创建类的对象, 也就是定义一堆类自动注册: 对象创建者函数。
* 
*/

typedef void* (*PtrFun)();
class ClassFactory {

private:
    std::unordered_map<string, PtrFun> mClassMap;

    // 构造单例, 把构造和析构函数屏蔽掉
    ClassFactory(){}
    ~ClassFactory(){}
    ClassFactory(const ClassFactory &) = delete;
    ClassFactory & operator==(const ClassFactory &) = delete;
public:
    static ClassFactory & GetInstance() {
        static ClassFactory singltonClassFactory;
        return singltonClassFactory;
    }

    void RegisterClass(const std::string &name, PtrFun fun) {
        mClassMap[name] = fun;
    }

    void* GetClassObj(const std::string &name) {
        std::unordered_map<string, PtrFun>::const_iterator it = mClassMap.find(name);
        if (it == mClassMap.end()) {
            return nullptr;
        }
        return (it -> second)(); // 直接返回这种类创建的对象
    }
};

class RegisterAction {
public:
    RegisterAction(){}
    explicit RegisterAction(const string name, PtrFun fun)
    {
        std::cout <<"RegisterAction called register class: " << name << std::endl;
        ClassFactory::GetInstance().RegisterClass(name, fun);
    }
    ~RegisterAction(){}
};

typedef  void* (*PtrFun)(void);

#define CLASS_REGISTER(className)       \
    className* Create##className() {    \
            return new className();     \
    }                                   \
    RegisterAction g_register##className(#className, (PtrFun)Create##className)

// 注意全局变量，文件域和类中静态变量，初始化时机？ main函数执行之前。 所以定义了全局变量，自动进行了类名的注册。

#endif /* SRC_INC_DESIGN_MODEL_H_ */
