/*
 * 15.cpp
 *
 *  Created on: Apr 17, 2019
 *      Author: wangwei69
 */

#include "all.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <set>


using namespace std;

void test_15(){

    /*
     * oop: 面向对象核心思想：
     *      数据封装： Data abstract
     *      继承：    Inheritance
     *      多态，动态绑定： Dynamic binding  virtual函数在runtime时，确定指针或引用调用基类还是派生类的函数。
     *
     *
     */


    /*
     * c++11: 新增了两个修饰说明符，放在函数行参列表之后
     *
     * override: 虚函数可以被子类继承。但不小心把子类中继承的虚函数参数列表写错了一点点（基，子类函数同名）？如果不加override，
     *           那么被认为是子类特有的新的函数；如果加上override，编译器会给基子类同名虚函数做检查，参数列表变化了，会报错；
     *
     * final:  虚函数定义成final，其子类就不能再继承，不能重新实现了；此虚函数就到此为止；
     *
     */

    class Derived;
    void print_obj(Derived obj);

    class Base{
    public:
        Base() = default;
        Base(string s = "bookname", double p = 0) : price(p), name(s){}
        virtual ~Base(){}
//        virtual double get_price( ) const{
//            return price;
//        }
        virtual double get_price(std::size_t n) const{
            return price * n;
        }
        virtual string get_name() final{return name;}

        //clone  对象自身,左值调用时，调用此函数
        virtual Base* clone() const &{
            return new Base(*this); //new一个对象，使用自身对象进行初始化；
        }
        //clone 对象作为右值时，调用此函数
        virtual Base* clone() const &&{
            return new Base(std::move(*this)); //右值拷贝构造函数；空间没有额外增加，更高效；前提*this对象是heap区数据；
        }

    protected:
        double price;
    private:
        string name;
    };

    class Derived : public Base{
    public:
        Derived(string s ="", double p = 0): Base(s, p){}
        ~Derived(){}
//        double get_price( ) const override{ //既然是override，基类中必然有相同形式的虚函数；如果这里参数不同，编译器会报错的；
//            return price * 2;
//        }
        //virtual string get_name(){} //编译报错，Base中此虚函数就已经final了 不能再重新实现了。

    //friend void print_obj(Base obj); //思考一下，这个友元函数中，能否访问基类对象：obj中的受保护的成员price？ 不能，这个函数不是Base的友元。
    friend void print_obj(Derived obj);//如果想访问，通过这个派生类对象来访问；

    };


    Derived obj("testbookname", 2);
    //基类指针，指向派生类对象；
    //如果是proteced或private的方式继承，这种转换是非法的；为什么？因为派生类对象的所有成员，对外都是不可访问的；
    //如果转了，部分基类成员变成可访问的；违反了protect/private规则；
    Base *b_ptr = &obj;

    b_ptr->get_name();
    //int price = b_ptr->get_price(); //多态性；dynamic-binding, 会调用派生类的函数；
    //cout <<"what is price ? " << price << endl;



    /*
     * 抽象基类 ： abstract base class
     *
     * 有纯虚函数的类（包括继承而来）是抽象基类；也就是所谓的接口；
     * 它是不能定义对象的；
     * 纯虚函数 ： fun() = 0
     *
     * 为什么要设计抽象基类(接口)？
     * 可扩展性；
     * 抽象基类数据可定，但纯虚函数的动作不定；
     * 继承它的类，可以自定义的实现不同动作策略；
     *
     */

    class Abstract_Base:public Base{
    protected:
        std::size_t quantity = 0; //买书量
        double discount = 0.0; //折扣
    public:

        Abstract_Base(string &s, double p, std::size_t cnt, double discnt):
            Base(s, p),
            quantity(cnt),
            discount(discnt){}

        //virtual double get_price(std::size_t cnt)  = 0; // 继承这个父类的子类，将实现不同的价格策略
    };


    class Bulk_quote: public Abstract_Base{

    public:
        Bulk_quote() = default;
        Bulk_quote(string s, double p, std::size_t cnt, double discnt = 1):
            Abstract_Base(s, p, cnt, discnt){}

        double get_price(std::size_t cnt) const{
            if (cnt >= this->quantity){
               // >=限定数量，执行打折策略；
                return (discount * price * cnt);
            }else{
                return price * cnt;
            }

        }

        //clone 对象自身
        virtual Bulk_quote* clone() const &{
            return new Bulk_quote(*this);
        }
        //clone 对象自身，对象是右值时，调用此函数clone; 减小开销；
        virtual Bulk_quote* clone() const &&{
            return new Bulk_quote(std::move(*this));
        }

    };


    string book = "nihao";
    Bulk_quote bulk_quo(book, 30, 5, 1);

    double cnt_price = bulk_quo.get_price(6);


    cout << "test bulk_quote price : " << cnt_price << endl;



    /*
     * 1、派生类向基类转换
     *
     * 常用场景： 派生类对象 赋值给基类指针(引用)， 目的是实现多态的访问；
     *
     * 但是这种赋值，也不是时时都可以进行的。
     *  思考，如果是protected 或 private 的方式来继承，还可以进行这种赋值吗？
     *
     *  不可以，类的普通用户而言，这两种继承方式，类中内容都不可见。
     *
     * 2、改变派生类中，继承自基类的变量或函数的访问权限？
     *
     *    基类：名称（变量，函数） 是protected 或 public
     *    继承方式： protected 或 private
     *
     *    继承类： 名称  访问权限 对普通用户而言，改成public的
     */

    class Base1{
    public:

        Base1(std::size_t number = 1): n(number){}

        std::size_t get_size(){
            return n;
        }

        std::size_t get_size(int x){
            return n * x;
        }
    protected:
        std::size_t  n;
    };

    class Pri_Base : private Base1{
    public:
        using Base1::get_size; //普通用户而言，虽然是private继承，但也可以访问; 直接使用名字，不需要加括号；这样两个重载版本的get_size对普通用户都可见；
        using Base1::n;   // 基类中是protected元素，在子类中都可以放开到public。
    };

   Pri_Base obj1;
   // Base1 *p1 = &obj1;  //错误，不能做这种转换; 私有继承，不能将子类对象赋值给基类指针。
   //p1->get_size();

   cout << "inherit class access privilege: " <<obj1.n << " "  <<obj1.get_size() << " " << obj1.get_size(3) << std::endl;


   /*
    * 名字查找与继承   p-> mem() 这个函数名字查找过程。
    *
    * 1、确定p的静态类型。 p 必须是类类型
    *
    * 2、先在静态类型中查找，找不到，继续到其基类中查；直到继承链的顶端。找不到报错；
    *
    *    p是最基层的基类，继承类对象赋值给它，同时继承类对象的中又函数mem；此时先从基类查，所以查不到，报错。
    *
    *    Derived d ; Base *p;
    *    p = &d;
    *    p->mem(); //基类中没有函数mem，报错；
    *
    * 3、查到名字后，再做函数的类型检查；
    *
    *    不合法： 报错；
    *    合法：
    *    （1） 虚函数，且通过引用或指针调用，发生动态绑定
    *    （2） 常规调用
    *
    */





   /*
    * 构造函数与拷贝控制
    *
    *
    * 1、为什么默认合成的析构函数是virtual的？ 虚析构函数
    *
    *   常用的场景：继承类对象赋值给基类指针或引用，使用动态绑定的功能； Base *ptr = new Derived();
    *   当我们使用 delete ptr；释放heap区内存时；会调用析构函数；如果不是virtual的，直接从Base的析构函数释放，造成未定义的行为；
    *
    *
    * 2、什么情况下，派生类中的拷贝控制函数是被删除的？
    *
    *   基类： 构造，拷贝构造，赋值，析构 是删除或不可访问  -》 继承类：对应都是被删除的；
    *
    *   基类： 析构函数是删除或不可访问  -》 继承类： 合成的默认构造和拷贝构造是delete的；
    *
    *
    *  总结：最终导致的结果是，继承类，无法进行构造或拷贝构造。
    *
    *
    * 3、 派生类的拷贝控制？
    *
    *    构造函数 ： 负责构造：自身和基类；不过可以调用基类的相应函数进行构造；
    *    拷贝构造
    *    移动构造
    *    赋值运算
    *    移动赋值
    *    析构函数： 只负责释放派生类自身的资源就可以。
    *
    *
    *
    */

   class Derived3;
   void print(Derived3&); //定义一个友元函数没有实现

   class Base3{
   public:

       explicit Base3(std::size_t num): n(num){}
       virtual ~Base3(){}  //基类的构造函数一定是virtual的。
       Base3(const Base3 &b){
           //拷贝构造
           this->n = b.n;
       }

       Base3& operator=(const Base3& b) noexcept{
          this->n = 0; //先释放，后构造
          this->n = b.n;
          return *this;
       }

   protected:
       std::size_t n;
   };

   class Derived3: public Base3{

   public:
       explicit Derived3(size_t n1, size_t n2): Base3(n1), nn(n2){} //利用基类构造函数，构造自身和基类

       Derived3(const Derived3 &d): Base3(d){  //基类部分，使用初始化列表
           this->nn = d.nn; //拷贝构造派生类部分
       }

       Derived3& operator=(const Derived3 &d){
           Base3::operator =(d);
           this->nn = d.nn;
           return *this;
       }

       friend void print(Derived3&);

       void get_element(){
           cout << "base element: " << this->n << endl;
           cout  << "inherit element: " << this->nn << endl;
       }
   private:
       std::size_t nn;

   };



   Derived3 d31(1, 2);
   Derived3 d32 = d31; //赋值运算
   Derived3 d33(d31); //拷贝构造

   d32.get_element();
   d33.get_element();


   /*
    * 容器与继承
    *
    * 1、场景：想要在容器中，同时保存基类和派生类对象, 改怎么办？
    *
    *    直接定义： vector<Base> 或 vector<Derived> 来同时保存两种类型的对象，都是有问题的。
    *
    *    通过间接方式，保存指针(智能指针)
    *
    *    顺便再回顾一下智能指针的使用：
    *    定义：    shared_ptr<T> p
    *             shared_ptr<T> p(new T());
    *    初始赋值： p = make_shared<T>(T的构造参数列表)；  //这种赋初值更优的一种方式
    *    使用：    *p
    *             p=q; //q引用计数加1, p的引用计数减1；p的引用计数为0时，释放p原来所指资源
    *
    *
    *
    */


   vector<shared_ptr<Base3>> vec;
   vec.push_back(shared_ptr<Base3>(new Base3(3)));
   vec.push_back(make_shared<Derived3>(1,2));//把一个派生类对象赋值给基类指针


   //设计一个购物篮类：购买Base或Bulk_quote类定义的书籍；


   class Basket{


   private:
       //自定义比较函数
       static bool compare(const std::shared_ptr<Base> &l, const std::shared_ptr<Base> &r){
           return l->get_name() < r->get_name();
       }
       //预订可能是Bulk_quote，也可能是Base对象单本书预订，所以set中存放基类指针，指向两种可能的对象；
       //同时，相同的书名(key)对象,可以同时出现，所以使用mulitset;
       //因为元素使用了对象的指针（这也出现自定义的compare常见场景），没有operator<的运算，所以自定义了compare;
       std::multiset<std::shared_ptr<Base>, decltype(compare)*> item{compare};

   public:

       //正常左值引用加入购物项
       void add_item(const Base& b){
           //参数：普通的Base或Bulk_quote对象，如何添加到multiset中？因为不知道是哪种类，所以不能直接重新new
           // item.insert(std::shared_ptr<Base>(new Base(b)));
           // 怎么办？ 想办法把b给clone出来？而且clone时是动态的，基类使用基类clone方法；派生类使用派生类clone方法；
           //clone返回new出来的新对象的指针。之后构造set中的智能指针

           item.insert(std::shared_ptr<Base>(b.clone()));  //clone是虚函数，动态调用Base或Bulk_quote类中clone函数；

       }

       //对象是右值，加入购物项时，可以使用右值的clone版本。也就是原来内存基础上clone，减小开销；
       void add_item(Base&& b){

           item.insert(std::shared_ptr<Base>(std::move(b).clone())); //虽然b是右值引用，但b本身还是左值；？？难以理解。。。

       }

       //每本书的总价和所有书总价，返回所有书总价
       double total_receipt(std::ostream& os) const{

           double sum = 0;

           for(auto it = item.cbegin(); it != item.cend(); it = item.upper_bound(*it)){

               string name = (*it)->get_name();
               std::size_t num = item.count(*it);
               os << "book name: " << (*it)->get_name() << endl;

               os << "book num: " << item.count(*it) << endl;

               double single_sum = (*it)->get_price(num);

               sum += (*it)->get_price(num);

               os << "book price: " << single_sum << endl;;

           }


           os << "book sum: " << sum << endl;


       }


   };


   Base test5("test5", 5);

   Bulk_quote test55("test55", 5.0, 3, 0.7);

   Basket b5;

   b5.add_item(test5);
   b5.add_item(test55);
   b5.add_item(test55);
   b5.add_item(test55);
   b5.add_item(test55); //四本书，大于限定3；执行打折策略；

   b5.total_receipt(cout);




} //end test_15()



