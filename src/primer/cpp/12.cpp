/*
 * 12.cpp
 *
 *  Created on: Feb 20, 2019
 *      Author: wangwei69
 */

#include "all.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <memory>

using namespace std;

/*
 * chapter 12 : 智能指针
 *
 *
 * 目的： 使用智能指针，可以自动进行内存的释放；主要是是heep区的；
 * 头文件：<memory>
 *
 * 共享： shared_ptr
 *

 *
 * 弱指针： weak_ptr

 *
 *
 * 独占：unique_ptr
 *

 *
 *
 *
 *
 *
 *思考：
 * 1、为什么需要动态生存期的资源的类？
 *
 *   不知道需要用多少个对象？
 *   多个对象间共享数据？
 *      自定义某个类，此类定义的多个对象之间，可以共享数据成员中的数据；
 *   不知道对象的准确类型？
 *
 * 2、内存泄露？空悬指针？
 *
 *   memeory leak :  未释放动态分配的内存。一般就是忘记:delete 了
 *   dangling pointer:  delete ptr指向内存区域后，ptr其实还保存地址数据；此时为避免空悬，可以在delete之后赋值nullptr；
 *
 *
 */



/*
 * 希望这个类的多个对象，通过shared_ptr可以共享底层data数据？但什么场景下会用？
 *
 * 开眼： 看看伴随指针类，怎么设计实现？
 *
 */


class strBlob{

friend class strBlobPtr;

public:

    using size_type = vector<string>::size_type;
    strBlob();
    strBlob(initializer_list<string> li);

    size_type get_size(){
        return data->size();
    }

    long get_point_cnt(){
        return data.use_count();
    }


private:
    shared_ptr<vector<string>> data;

};

strBlob::strBlob():data(make_shared<vector<string>>()){}
strBlob::strBlob(initializer_list<string> li):data(make_shared<vector<string>>(li)){}


/*
 * 伴随指针类
 * 目的: ?   伴随指针类对象和被伴随对象，使用相同的底层数据。
 *          伴随指针类对象，使用cur来管理访问元素
 *
 */


class strBlobPtr{

public:

    strBlobPtr():cur(0){};
    strBlobPtr(strBlob &a, size_t idx = 0): wptr(a.data),cur(idx){}; //这里用到strBlob类对象的私有数据a，来初始化成员变量；怎么办？ friend

    string& deref() const;  //通过这个伴随指针，解引用原对象中数据；
    strBlobPtr& incr();  //递增这个指针


private:
    weak_ptr<vector<string>> wptr;
    size_t cur;
    shared_ptr<vector<string>> check(size_t idx, const string &str)const;

};


//检查合法性
shared_ptr<vector<string>> strBlobPtr::check(size_t idx, const string& msg) const{

    shared_ptr<vector<string>> it = wptr.lock();  //通过weak_ptr来访问shared_ptr....

    if (!it){ //shared_ptr引用计数已经为0了
        throw std::runtime_error("unbound shared ptr!"); //抛出运行时异常
    }
    if (idx >= it->size()){ //下标超限了
        throw std::out_of_range(msg);  //抛出越界异常
    }
    return it;
}

//解引用操作
string& strBlobPtr::deref() const{
    auto sptr = check(cur, "dereference failed!");
    return (*sptr)[cur]; //
}

strBlobPtr& strBlobPtr::incr(){

    check(cur, "out of range");
    ++cur; //若果cur是最后一个，++cur就超限了啊？
    return *this;

}



void test_12(){

    /*
     * shared_ptr
     *  模板类： shared_ptr<OBJ_TYPE> p;
     *          p : p是否指向一个对象；是的话，返回true；否则返回false；
     *
     *          *p :
     *          p->mem:
     *
     *          p.get() : 返回p保存的指针；
     *
     *          swap(p,q) : 两个智能指针进行交换
     *
     *  特有的操作：
     *
     *        make_shared<OBJ_TYPE>(args) :
     *        使用args构造OBJ_TYPE类型对象(这个参数需要符合类构造函数的要求)，并返回指向该对象的shared_ptr指针；
     *
     *        动态分配内存并初始化；异常安全；
     *
     *        shared_ptr<OBJ_TYPE> p(q) : q 赋给 p，指向同一个对象；q指针计数器增加1；
     *
     *        p = q ： p的计数器递减；q的引用计数器递增；如果p指向的原来的部分，计数器变成0了，需要释放内存；
     *
     *        p.unique(): 判断p指向的对象，引用计数是否为1；
     *
     *        p.use_count():
     *
     */

    strBlob str1;

    //限定str2可见范围
    {
        strBlob str2({"wang","wei","ni","hao"});
        str1 = str2;
        //正常话的str2将被释放；但str2中创建的数据还是有的；因为==后，里面的data： str2 引用计算器++，str1中data释放原来指向内容，指向str2中data；
    }

    //str2中数据是否还存在？str1种data的引用计数器的个数？

    cout << "str1 can remain str2 data ? size:  " << str1.get_size() << " pointer cnt: "  << str1.get_point_cnt()<< endl;

    strBlob &str3 = str1;
    cout << " pointer cnt: "  << str3.get_point_cnt()<< endl; //shared_ptr 如果是引用，不增加引用计数器的值；

    strBlob str4 = str1;
    cout << " pointer cnt: " << str4.get_point_cnt() << endl;


    strBlobPtr str1_ptr(str1, 1);

    cout << "strBlobPtr deref: " << str1_ptr.deref() << endl;
    str1_ptr.incr();
    cout << "strBlobPtr after incr deref : " << str1_ptr.deref() << endl;

    /*
     * weak_ptr
     *       使用场景： 指向由shared_ptr管理的对象；不增加shared_ptr的引用计数器的值；即使有weak_ptr指向，shared_ptr也可能被销毁
     *
     *       w.expired() : shared_ptr的数量为0了；就超期了，返回true;否则返回false;
     *
     *       w.lock() :  没expired的情况下，返回指向wd的对象的shared_ptr;否则返回，空的shared_ptr；
     *
     *       w = p :  p是shared_ptr或weak_ptr,不增加引用计数器值；w,p指向相同的对象；
     *
     */

    shared_ptr<vector<string>> s_str_ptr(new vector<string>(10, "wang"));

    cout << "shared_ptr : " << (*s_str_ptr)[1] << " shared count: "<< s_str_ptr.use_count()<<endl;

    weak_ptr<vector<string>> w_str_ptr;
    w_str_ptr = s_str_ptr;

    //cout << "weak_ptr : " << (*w_str_ptr)[1] << endl;
    cout << "weak_ptr : " << (*w_str_ptr.lock())[1] << endl;  //weak_ptr不能直接引用；需要通过lock获取shared_ptr才能用；



    /*
     * unique_ptr
     *
     *  不能赋值和拷贝，可以发生转移；
     *      unique_ptr<OBJ_TYPE> ptr (new OBJ_TYPE(args)) : 独占指针一般用new返回直接初始化；
     *      p.release() : 释放p控制权，p置空；并返回对应指针； 但原来的内存还在。
     *      p.reset(): 释放p指向对象，内存也释放了。
     *      p.reset(q.realease()) :  转移控制权：q置空，释放控制权；并将原来内存指针重指到p上；发生控制权的转移；
     *      设计单例模式时: 可以使用独占指针，指向统一的数据处理类
     *
     */

    /*
    初始化方式
　　1. 直接初始化：unique<T> myPtr(new T);  //ok。但不能通过隐式转换来构造，如unique<T> myPtr = new T()。因为unique_ptr构造函数被声明为explicit。
　　2. 移动构造：unique<T> myOtherPtr = std::move(myPtr);但不允许复制构造，如unique<T> myOther = myPtr; 因为unique是个只移动类型。
　　3. 通过make_unique构造：unique<T> myPtr = std::make_unique<T>(); //C++14支持的语法。但是make_都不支持添加删除器，或者初始化列表。
　　4. 通过reset重置：如std::unique_ptr up; up.reset(new T());
   */

    unique_ptr<vector<string>> str_ptr(new vector<string>(10, "test"));

    unique_ptr<vector<string>> str_ptr_other;
    str_ptr_other.reset(str_ptr.release());  //unique_ptr 发生控制权的转移

    cout << "unique_ptr use: " << (*str_ptr_other)[2] << endl;



    /*
     * topic  动态数组
     *
     *
     *
     *
     */


    size_t len = 10;
    int *ptr = new int[len]; //未初始化
    int *ptr2 = new int[10](); //元素值被初始化为0

    int *ptr3 = new int[len]{1,2,3,4,5}; //可以直接用{}赋初始值

    //int *ptr4 = new int[3]{1,2,3,4}; //元素个数，超出分配空间大小；抛出异常：bad_array_new_length 头文件<new>

    delete []ptr; //new后必须要delete，数组要带[];
    delete []ptr2;
    delete []ptr3;



    /*
     * topic  allocator  <memory>
     *
     *    内存的分配 和 构造 分开； new 是连在一起，可能造成不必要的计算浪费；多赋值一次；
     *
     *    allocator<T> a  : 定义一个分配器的对象
     *
     *    p = a.allocate(n) : 分配n个未用的内存空间; 返回 T* p？
     *
     *    a.deallocate(n) : 回收n个分配的内存空间；注意，在回收内存之前，需要destroy内存中对象，也就是析构操作；
     *
     *    a.construct(p, args) : 在指针p所指位置上，构造类型T的对象，args匹配相应的构造函数
     *
     *    a.destory(p) :  指针p所指对象，进行析构操作。
     *
     *
     *
     *
     */


    allocator<string> alloc;
    string *str_ptr_al = alloc.allocate(10); //分配10个装string对象的原生内存空间；

    auto p = str_ptr_al;
    alloc.construct(p, "wang");
    alloc.construct(++p, "wei");

    cout << "allocator str: " << str_ptr_al[0] << endl;
    cout << "allocator str: " << str_ptr_al[1] << endl;





}



