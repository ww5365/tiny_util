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
     * oop: ����������˼�룺
     *      ���ݷ�װ�� Data abstract
     *      �̳У�    Inheritance
     *      ��̬����̬�󶨣� Dynamic binding  virtual������runtimeʱ��ȷ��ָ������õ��û��໹��������ĺ�����
     *
     *
     */


    /*
     * c++11: ��������������˵���������ں����в��б�֮��
     *
     * override: �麯�����Ա�����̳С�����С�İ������м̳е��麯�������б�д����һ��㣨�������ຯ��ͬ�������������override��
     *           ��ô����Ϊ���������е��µĺ������������override�����������������ͬ���麯������飬�����б�仯�ˣ��ᱨ��
     *
     * final:  �麯�������final��������Ͳ����ټ̳У���������ʵ���ˣ����麯���͵���Ϊֹ��
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

        //clone  ��������,��ֵ����ʱ�����ô˺���
        virtual Base* clone() const &{
            return new Base(*this); //newһ������ʹ�����������г�ʼ����
        }
        //clone ������Ϊ��ֵʱ�����ô˺���
        virtual Base* clone() const &&{
            return new Base(std::move(*this)); //��ֵ�������캯�����ռ�û�ж������ӣ�����Ч��ǰ��*this������heap�����ݣ�
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
//        double get_price( ) const override{ //��Ȼ��override�������б�Ȼ����ͬ��ʽ���麯����������������ͬ���������ᱨ��ģ�
//            return price * 2;
//        }
        //virtual string get_name(){} //���뱨��Base�д��麯�����Ѿ�final�� ����������ʵ���ˡ�

    //friend void print_obj(Base obj); //˼��һ�£������Ԫ�����У��ܷ���ʻ������obj�е��ܱ����ĳ�Աprice�� ���ܣ������������Base����Ԫ��
    friend void print_obj(Derived obj);//�������ʣ�ͨ�������������������ʣ�

    };


    Derived obj("testbookname", 2);
    //����ָ�룬ָ�����������
    //�����proteced��private�ķ�ʽ�̳У�����ת���ǷǷ��ģ�Ϊʲô����Ϊ�������������г�Ա�����ⶼ�ǲ��ɷ��ʵģ�
    //���ת�ˣ����ֻ����Ա��ɿɷ��ʵģ�Υ����protect/private����
    Base *b_ptr = &obj;

    b_ptr->get_name();
    //int price = b_ptr->get_price(); //��̬�ԣ�dynamic-binding, �����������ĺ�����
    //cout <<"what is price ? " << price << endl;



    /*
     * ������� �� abstract base class
     *
     * �д��麯�����ࣨ�����̳ж������ǳ�����ࣻҲ������ν�Ľӿڣ�
     * ���ǲ��ܶ������ģ�
     * ���麯�� �� fun() = 0
     *
     * ΪʲôҪ��Ƴ������(�ӿ�)��
     * ����չ�ԣ�
     * ����������ݿɶ��������麯���Ķ���������
     * �̳������࣬�����Զ����ʵ�ֲ�ͬ�������ԣ�
     *
     */

    class Abstract_Base:public Base{
    protected:
        std::size_t quantity = 0; //������
        double discount = 0.0; //�ۿ�
    public:

        Abstract_Base(string &s, double p, std::size_t cnt, double discnt):
            Base(s, p),
            quantity(cnt),
            discount(discnt){}

        //virtual double get_price(std::size_t cnt)  = 0; // �̳������������࣬��ʵ�ֲ�ͬ�ļ۸����
    };


    class Bulk_quote: public Abstract_Base{

    public:
        Bulk_quote() = default;
        Bulk_quote(string s, double p, std::size_t cnt, double discnt = 1):
            Abstract_Base(s, p, cnt, discnt){}

        double get_price(std::size_t cnt) const{
            if (cnt >= this->quantity){
               // >=�޶�������ִ�д��۲��ԣ�
                return (discount * price * cnt);
            }else{
                return price * cnt;
            }

        }

        //clone ��������
        virtual Bulk_quote* clone() const &{
            return new Bulk_quote(*this);
        }
        //clone ����������������ֵʱ�����ô˺���clone; ��С������
        virtual Bulk_quote* clone() const &&{
            return new Bulk_quote(std::move(*this));
        }

    };


    string book = "nihao";
    Bulk_quote bulk_quo(book, 30, 5, 1);

    double cnt_price = bulk_quo.get_price(6);


    cout << "test bulk_quote price : " << cnt_price << endl;



    /*
     * 1�������������ת��
     *
     * ���ó����� ��������� ��ֵ������ָ��(����)�� Ŀ����ʵ�ֶ�̬�ķ��ʣ�
     *
     * �������ָ�ֵ��Ҳ����ʱʱ�����Խ��еġ�
     *  ˼���������protected �� private �ķ�ʽ���̳У������Խ������ָ�ֵ��
     *
     *  �����ԣ������ͨ�û����ԣ������ּ̳з�ʽ���������ݶ����ɼ���
     *
     * 2���ı��������У��̳��Ի���ı��������ķ���Ȩ�ޣ�
     *
     *    ���ࣺ���ƣ������������� ��protected �� public
     *    �̳з�ʽ�� protected �� private
     *
     *    �̳��ࣺ ����  ����Ȩ�� ����ͨ�û����ԣ��ĳ�public��
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
        using Base1::get_size; //��ͨ�û����ԣ���Ȼ��private�̳У���Ҳ���Է���; ֱ��ʹ�����֣�����Ҫ�����ţ������������ذ汾��get_size����ͨ�û����ɼ���
        using Base1::n;   // ��������protectedԪ�أ��������ж����Էſ���public��
    };

   Pri_Base obj1;
   // Base1 *p1 = &obj1;  //���󣬲���������ת��; ˽�м̳У����ܽ��������ֵ������ָ�롣
   //p1->get_size();

   cout << "inherit class access privilege: " <<obj1.n << " "  <<obj1.get_size() << " " << obj1.get_size(3) << std::endl;


   /*
    * ���ֲ�����̳�   p-> mem() ����������ֲ��ҹ��̡�
    *
    * 1��ȷ��p�ľ�̬���͡� p ������������
    *
    * 2�����ھ�̬�����в��ң��Ҳ�����������������в飻ֱ���̳����Ķ��ˡ��Ҳ�������
    *
    *    p�������Ļ��࣬�̳������ֵ������ͬʱ�̳����������ֺ���mem����ʱ�ȴӻ���飬���Բ鲻��������
    *
    *    Derived d ; Base *p;
    *    p = &d;
    *    p->mem(); //������û�к���mem������
    *
    * 3���鵽���ֺ��������������ͼ�飻
    *
    *    ���Ϸ��� ����
    *    �Ϸ���
    *    ��1�� �麯������ͨ�����û�ָ����ã�������̬��
    *    ��2�� �������
    *
    */





   /*
    * ���캯���뿽������
    *
    *
    * 1��ΪʲôĬ�Ϻϳɵ�����������virtual�ģ� ����������
    *
    *   ���õĳ������̳������ֵ������ָ������ã�ʹ�ö�̬�󶨵Ĺ��ܣ� Base *ptr = new Derived();
    *   ������ʹ�� delete ptr���ͷ�heap���ڴ�ʱ������������������������virtual�ģ�ֱ�Ӵ�Base�����������ͷţ����δ�������Ϊ��
    *
    *
    * 2��ʲô����£��������еĿ������ƺ����Ǳ�ɾ���ģ�
    *
    *   ���ࣺ ���죬�������죬��ֵ������ ��ɾ���򲻿ɷ���  -�� �̳��ࣺ��Ӧ���Ǳ�ɾ���ģ�
    *
    *   ���ࣺ ����������ɾ���򲻿ɷ���  -�� �̳��ࣺ �ϳɵ�Ĭ�Ϲ���Ϳ���������delete�ģ�
    *
    *
    *  �ܽ᣺���յ��µĽ���ǣ��̳��࣬�޷����й���򿽱����졣
    *
    *
    * 3�� ������Ŀ������ƣ�
    *
    *    ���캯�� �� �����죺����ͻ��ࣻ�������Ե��û������Ӧ�������й��죻
    *    ��������
    *    �ƶ�����
    *    ��ֵ����
    *    �ƶ���ֵ
    *    ���������� ֻ�����ͷ��������������Դ�Ϳ��ԡ�
    *
    *
    *
    */

   class Derived3;
   void print(Derived3&); //����һ����Ԫ����û��ʵ��

   class Base3{
   public:

       explicit Base3(std::size_t num): n(num){}
       virtual ~Base3(){}  //����Ĺ��캯��һ����virtual�ġ�
       Base3(const Base3 &b){
           //��������
           this->n = b.n;
       }

       Base3& operator=(const Base3& b) noexcept{
          this->n = 0; //���ͷţ�����
          this->n = b.n;
          return *this;
       }

   protected:
       std::size_t n;
   };

   class Derived3: public Base3{

   public:
       explicit Derived3(size_t n1, size_t n2): Base3(n1), nn(n2){} //���û��๹�캯������������ͻ���

       Derived3(const Derived3 &d): Base3(d){  //���ಿ�֣�ʹ�ó�ʼ���б�
           this->nn = d.nn; //�������������ಿ��
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
   Derived3 d32 = d31; //��ֵ����
   Derived3 d33(d31); //��������

   d32.get_element();
   d33.get_element();


   /*
    * ������̳�
    *
    * 1����������Ҫ�������У�ͬʱ�����������������, ����ô�죿
    *
    *    ֱ�Ӷ��壺 vector<Base> �� vector<Derived> ��ͬʱ�����������͵Ķ��󣬶���������ġ�
    *
    *    ͨ����ӷ�ʽ������ָ��(����ָ��)
    *
    *    ˳���ٻع�һ������ָ���ʹ�ã�
    *    ���壺    shared_ptr<T> p
    *             shared_ptr<T> p(new T());
    *    ��ʼ��ֵ�� p = make_shared<T>(T�Ĺ�������б�)��  //���ָ���ֵ���ŵ�һ�ַ�ʽ
    *    ʹ�ã�    *p
    *             p=q; //q���ü�����1, p�����ü�����1��p�����ü���Ϊ0ʱ���ͷ�pԭ����ָ��Դ
    *
    *
    *
    */


   vector<shared_ptr<Base3>> vec;
   vec.push_back(shared_ptr<Base3>(new Base3(3)));
   vec.push_back(make_shared<Derived3>(1,2));//��һ�����������ֵ������ָ��


   //���һ���������ࣺ����Base��Bulk_quote�ඨ����鼮��


   class Basket{


   private:
       //�Զ���ȽϺ���
       static bool compare(const std::shared_ptr<Base> &l, const std::shared_ptr<Base> &r){
           return l->get_name() < r->get_name();
       }
       //Ԥ��������Bulk_quote��Ҳ������Base���󵥱���Ԥ��������set�д�Ż���ָ�룬ָ�����ֿ��ܵĶ���
       //ͬʱ����ͬ������(key)����,����ͬʱ���֣�����ʹ��mulitset;
       //��ΪԪ��ʹ���˶����ָ�루��Ҳ�����Զ����compare������������û��operator<�����㣬�����Զ�����compare;
       std::multiset<std::shared_ptr<Base>, decltype(compare)*> item{compare};

   public:

       //������ֵ���ü��빺����
       void add_item(const Base& b){
           //��������ͨ��Base��Bulk_quote���������ӵ�multiset�У���Ϊ��֪���������࣬���Բ���ֱ������new
           // item.insert(std::shared_ptr<Base>(new Base(b)));
           // ��ô�죿 ��취��b��clone����������cloneʱ�Ƕ�̬�ģ�����ʹ�û���clone������������ʹ��������clone������
           //clone����new�������¶����ָ�롣֮����set�е�����ָ��

           item.insert(std::shared_ptr<Base>(b.clone()));  //clone���麯������̬����Base��Bulk_quote����clone������

       }

       //��������ֵ�����빺����ʱ������ʹ����ֵ��clone�汾��Ҳ����ԭ���ڴ������clone����С������
       void add_item(Base&& b){

           item.insert(std::shared_ptr<Base>(std::move(b).clone())); //��Ȼb����ֵ���ã���b��������ֵ������������⡣����

       }

       //ÿ������ܼۺ��������ܼۣ������������ܼ�
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
   b5.add_item(test55); //�ı��飬�����޶�3��ִ�д��۲��ԣ�

   b5.total_receipt(cout);




} //end test_15()



