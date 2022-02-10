/*
 * 13.h
 *
 *  Created on: Feb 26, 2019
 *      Author: wangwei69
 */

#include <string>

using namespace std;

/*
 * 定义：行为像值的类
 *
 *    每个对象，都有自己数据的一份拷贝;
 *
 *    必须有析构函数时，必须考虑拷贝控制：拷贝构造、拷贝赋值
 *
 *    关键是：operator= 实现: 拷贝 + 析构
 *
 *
 *
 */

class hasPtr1 {

    friend void swap(hasPtr1 &l, hasPtr1 &r);

public:

    hasPtr1(const string &s = string()) :
            ps(new string(s)), i(0) {
        //默认构造函数，每个对象都有自己一份拷贝值
    }

    hasPtr1(const hasPtr1 &hp) :
            ps(new string(*hp.ps)), i(hp.i) {
        //拷贝构造，每个ps都有自己一份拷贝
    }

    hasPtr1& operator=(const hasPtr1&); //常规版本
    hasPtr1& operator=(hasPtr1); //基于swap的拷贝交换技术的，异常安全的版本

    ~hasPtr1() {
        delete ps;
    }

private:
    string *ps; //每个对象的ps都是不同的，都有一份拷贝
    int i;

};

hasPtr1& hasPtr1::operator=(const hasPtr1& hp) {

    string *tmp = new string(*hp.ps); //先分配新空间

    delete ps; //释放原来指向空间

    ps = tmp;
    i = hp.i;
    return *this;
}



/*
 * 定义 : 行为像指针的类   有点类似智能指针的功能实现
 *
 *   1、初始化构造对象时，需要创建一个引用计数器
 *   2、拷贝构造： 拷贝数据成员，递增引用计数器
 *   3、拷贝赋值： 递增右侧引用计数器，递减左侧计数器，若减为0，则释放
 *   4、析构函数： 引用计数器递减，为0释放资源；
 *
 *   如何设计这个『引用计数器』 ？ 类对象之间需要共享这个数据
 *
 *   ？ 设计成 static 成员变量 ：不行，所有类对象，都共享这个数据；这个场景只有部分类对象之间共享数据；
 *   ？ 不能是值类型成员，只能是：动态分配的空间，实现共享；
 *
 *
 *
 *
 *
 */



class hasPtr2{

private:
    string *ps;
    int i;
    std::size_t *cntPtr;

public:

    hasPtr2(const string &s = string()):ps(new string(s)), i(0),cntPtr(new size_t(1)){
    }

    hasPtr2(const hasPtr2& other): ps(other.ps),i(other.i),cntPtr(other.cntPtr){
        (*cntPtr)++;
    }


    //包含析构和拷贝构造思路
    hasPtr2& operator=(const hasPtr2& other){

        if ((--*cntPtr) == 0){ //左边ref递减
            delete ps;
            delete cntPtr; //原来内容和ref计数，都得清空；
        }
        ps = other.ps;
        ++(*other.cntPtr); //右边ref递增
        cntPtr = other.cntPtr;
        i = other.i;

        return *this;
    }

    //析构函数
    ~hasPtr2(){

        if (--(*cntPtr) == 0){
            delete ps;
            delete cntPtr;
        }
    }

};


/*
 * topic : swap
 *
 *    swap虽然不必要，但拷贝控制需要考虑，是一种重要的优化手段；对于分配资源的类；
 *
 *    使用注意：  using std::swap;
 *              swap(obj1, obj2); //交换对象，但如果对象有自己的重载的swap，则优先使用对象重载的swap
 *
 *
 *              使用swap，可以实现：operator= 的 ，拷贝并交换的技术，异常安全的实现拷贝赋值；
 *
 *
 */

//重新实现：hasPtr1使用的swap函数
inline void swap(hasPtr1 &l, hasPtr1 &r){
    using std::swap;
    swap(l.ps, r.ps);
    swap(l.i, r.i); //内置类型，没有swap使用std::swap; 如果重载swap的类，即使using std::swap,也优先使用对象内部自己的swap；
}


hasPtr1& hasPtr1::operator=(hasPtr1 other){ //参数是值拷贝构造

    swap(*this, other); //优先使用，类hasPtr1中swap版本
    return *this; //这步会自动销毁,other中保存的内容

}















