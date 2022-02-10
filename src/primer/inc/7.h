
#ifndef _7_H_
#define _7_H_

#include <iostream>
#include <vector>
#include <string>

#include <bitset>

#include "sales_data.h"

class Screen; //声明类，非定义实现
class Window_mgr;

extern std::ostream& storeOn(std::ostream &, Screen &);
extern std::bitset<32>& storeOn(std::bitset<32> &, Screen &);


class Window_mgr {

public:
//定义类型
using ScreenIndex = std::vector<Screen>::size_type;

public:

    Window_mgr() = default;
    //清空某个Screen
    void clear(ScreenIndex i); //仅声明；这个函数是Screen类的友元，要访问类Screen的私有成员变量，实现放在Screen类定义之后；

    Screen& get(ScreenIndex i);//仅声明

    ScreenIndex set(Screen &); //往window中添加screen;注意，类体外定义时，类作用域

private:
    std::vector<Screen> screens;
    //std::vector<Screen> screens{Screen(3, 3, '#')}; //仅声明，还不能调用Screen的构造函数

};



class Screen{

public:

    /*
     * 定义一个类型成员，如下：
     * 1、等价于：using pos = std::string::size_type
     * 2、可以使用这个: 类型成员来定义其它变量
     *
     */
    typedef std::string::size_type pos;

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;

    mutable size_t access_ctr = 0;//mutable：可变数据成员；

public:
    //构造函数
    Screen(){};   //默认构造函数
    Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(ht*wd, c){}

    /*
     * topic: inline 函数
     * 好处： 效率，编译器要直接替换代码；函数短小精悍
     *
     *
     * 1、类内成员函数，定义并实现的，默认是inline的
     * 2、类外实现的成员函数，可以显式的定义为inline
     *
     */

    char get() const{
        return contents[cursor];//默认inline
    }

    char get(pos ht, pos wd) const;

    /*
     * topic: mutable
     *
     */
    void some_memeber() const{
        ++access_ctr; //mutable成员变量:即使是类的常量对象，也可以改变
        std::cout << "access_ctr: " << access_ctr << std::endl;
    }

    /*
     * topic: 返回对象自身？*this
     */

    Screen &set(char ch){

        //contents[cursor] = ch;
        contents.insert(cursor, 1, ch);
        return *this; //返回类对象本身
    }

    Screen &set(pos row, pos col, char ch){

        //contents[row * width + col] = ch;  //string 直接某个位置赋值，有点问题。不知道什么原因？
        contents.insert(row * width + col, 1, ch);
        return *this;
    }



    /*
     * topic: 非常量对象：const函数返回自身常量对象，如何再次调用对象中的非const函数？
     * 怎么设计实现？
     * 考虑把const函数进行重载，自动调用const或非const的函数。
     * 这个函数里面再设计小函数，设计成const,保证最小化的访问对象成员变量；
     *
     *  比如： Screen sce;
     *
     *  sce.display(os).set("#");
     *  一般display都是const函数，怎么设计才能即可const也可非const实现？
     *  重载、使用const小函数
     *
     */

private:
    //小而精的内联函数，同时提供给const和非const来调用
    void do_display(std::ostream &os) const{
        os << contents;
    }

public:
    /*
     * 说明:
     * 1、非const成员函数可以调用const成员函数；
     * 2、
     */
    Screen &display(std::ostream &os){
        do_display(os);
        return *this;

    }
    /* 说明：
     * 1、重载display, 这个函数主要给const对象来用;
     * 2、const 成员函数能调用非const成员函数吗？ 否
     * 3、调用：常量对象调用display时，自动调用const函数
     *
     *
     */

    const Screen &display(std::ostream &os) const{
        do_display(os);
        return *this;//这个对象是常量对象

    }

    /*
     *  topic: 友元  再探索
     *  1、为什么需要友元？ 可以访问其它类对象的私有成员变量。
     *  2、友元的形式？可以声明某个类的，
     *     友元函数
     *     友元类
     *     友元类的成员函数
     *
     *     example 如下
     *
     *  3、友元类，友元函数，需要在类内声明友元类型；友元函数可以在声明时，直接定义实现；但在类外还需要函数的声明；
     *  4、友元不具备传递性
     *
     *
     */


//friend class Window_mgr;  //友元类，类中成员函数都可以访问类Screen对象的私有成员变量

friend std::ostream& stroeOn(std::ostream &, Screen &); //友元函数声明；函数本身已提前声明；虽然有同名重载，但只有这个版本有权限访问类Screen对象的私有成员

 friend void Window_mgr::clear(Window_mgr::ScreenIndex i);
 /*
 * 友元类成员函数， 存在一个问题？
 * Window_mgr::clear访问Screen，但Window_mgr::clear还没有定义，怎么办？
 *把Window_mgr定义放在Screen之前？window_mgr又要使用Screen的构造函数和私有变量； 放之后，这里又找不到clear，如何处理？？？
 * 出现问题： 环形依赖。。
 *
 * 解决方案：
 * 1、window_mgr类，先于Screen声明，但成员函数先不要定义；需要Screen类的话，先把Screen声明了；
 *
 * 2、定义实现类Screen
 *
 * 3、实现window_mgr类中成员函数
 *
 *
 */


};

//显式的内联定义
inline char Screen::get(pos ht, pos wd) const{
    return contents[ht * wd];
}

void Window_mgr::clear(ScreenIndex i){

    Screen &s = screens[i];
    s.contents = std::string(s.height * s.width, ' '); //因为是类Screen的友元类，所以可以访问Screen类对象的私有成员

    if (s.contents.empty()){
        std::cout << "screen : " << i << " clear!" << std::endl;
    }
}


Screen& Window_mgr::get(ScreenIndex i){
    return screens[i];
}

Window_mgr::ScreenIndex Window_mgr::set(Screen &s){
    screens.emplace_back(s); //思考：放入容器的s，是重新构造？还是原来的？
    //screens.push_back(s);
    //std::cout << "make use of s construct screens in window_mgr" << std::endl;
    //screens[0].some_memeber();
    return screens.size() - 1;
}


/*
 * topic: 构造函数再探
 *
 * 1、构造函数对成员变量初始化的时机？
 *   在函数体刚开始执行时，成员变量的初始化就已经完成； 所以，对于const成员和引用类型的成员，就不能使用赋值方式进行初始化；必须使用初始化列表；
 *
 * 2、类的数据成员的初始化的顺序？
 *    按照类内定义的顺序来进行初始化；
 *
 * 3、代理构造函数：delegating constructor   ??
 *
 *    构造函数调用别的构造函数来进行成员变量的初始化；
 *
 *    执行顺序：初始化列表中调用的构造函数 -》 函数体内代码
 *
 * 4、默认构造函数
 *
 *    4.1 仅有一个带参数的构造函数，这个类T在定义对象时， T test, 这样是不行的。没有默认构造函数，编译器也不会生成：合成的默认构造函数;
 *    4.2 什么时机可能使用默认构造函数？ 类内成员变量，也是某个类的对象；
 *
 *
 *  5、关键字：explicit
 *
 *    防止类的构造对象时，进行隐式数据类型转换；
 *    针对：一个参数的构造函数，会发生隐式类型转换的情况；而且是直接构造，不是赋值=操作
 *
 *  6、字面值常量类
 *
 *    constexpr 构造函数： 来构造字面值常量类
 *
 *    没有理解透：字面值常量类？为什么要有constexpr ？ 字面值常量其实都理解的不是很透？
 *
 *    后续再深入了解吧。。
 *
 */


class Test_class {

private:
    std::string isdn;
    double price;
    unsigned int units_sold;
    double revenue;

public:

    Test_class(std::string s, unsigned int cnt, double p): isdn(s), price(p),units_sold(cnt){
        revenue = price * units_sold;
    }

    //代理函数
    //一个参数的构造函数,使用上面三个参数的构造函数，来实现一个参数的构造函数
    Test_class(double pr):Test_class("", 0, pr){}

    //默认构造函数
    Test_class():Test_class("", 0, 0){}

    //explict 只允许显示构造;使用Test_class对象，只能显示的构造，不能进行隐式转换了；
    //比如：test.add(Test_class(std::string("999-999"))); 正确
    //     test.add(std::string("999-999")); //不正确 string不能隐式转成Test_class类临时对象

     explicit Test_class(std::string s):Test_class(s, 0, 0){}
     void add(Test_class t){}

};


/*
 * topic: 类的静态变量
 *
 *  1、为什么需要static成员？
 *     独立于类的所有对象
 *     程序运行空间：静态数据区
 *
 *  2、声明及定义：
 *  static 类成员(变量，函数)，声明在类内，定义赋值在类体外；同时，类外定义赋值时不用再加static关键字;
 *  static成员变量，有时可以类内初始化，但也需要类外进行不赋值的定义;
 *
 *  类静态数据成员可以是自己类型的对象； 牛逼； 突然想到，resource加载资源单例模式的实现，就使用了static自身类成员变量实现；
 *
 *  3、使用：
 *
 *
 *
 *
 *
 */


class Account {

private:
    static constexpr int period = 30; //静态，常量表达式；类内初始化

    double daily_tbl[period];  //period实际是静态常量

    static Account other_acc;  //这个类成员变量：是自己类型的。。这种场景好像再那里用过？ 单例模式。resource加载实现

    std::string owner;
    double amount;
    static double interestRate;
    static double initRate();

public:
    static double rate(){ return interestRate; }

    static void rate(double);
    void calculate(){
        amount += amount * interestRate;
    }

};







#endif /* 7_H_ */
