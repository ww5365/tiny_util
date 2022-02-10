/*
 * sales_data.h
 *
 *  Created on: Mar 25, 2019
 *      Author: wangwei69
 */

#ifndef SALES_DATA_H_
#define SALES_DATA_H_

#include <string>
using namespace std;


class  Sales_data{

public:
/*topic 友元函数：
 * 1、非成员函数；类的友元函数的声明;
 * 2、为什么要有友元？这些函数可以访问类对象的私有成员变量
 */

friend Sales_data add(const Sales_data&, const Sales_data&);
friend std::ostream& print(std::ostream& os, const Sales_data&);
friend std::istream& read(std::istream& is, const Sales_data&);

/*
 * 第14章
 * 1、把输入输出等动作，抽取出来，重载成运算符，来方便使用
 *
 */

//输入，输出 运算符
friend Sales_data operator<< (std::ostream &os, const Sales_data& data);
friend Sales_data operator>> (std::istream &is, Sales_data& data);


//相等 运算符

friend bool operator==(const Sales_data &l, const Sales_data &r);


private:
    /*
     * 成员变量的说明：
     * 1、初始化的顺序，和定义顺序相同；和初始化列表的顺序无关；
     * 2、常量成员变量，初始化只能通过初始化列表；也就是说，初始化列表是在其获取const属性前赋值；
     */
    std::string isbn; //书的唯一标号
    unsigned int units_sold = 0; //销售量
    double revenue = 0.0 ;  //类内默认值，销售额

public:

    /* topic：默认构造函数：
     * 1、没有参数；没定的话，编译器会自动合成默认构造函数
     * 2、使用=default，编译器会自动合成的构造函数；没有实现？=default就是实现；
     * 3、为什么需要=default？因为当定义了其它版本的构造函数，类就不会再生成默认构造函数了；
     * 但类可能又是需要默认构造函数的，这时=default一下。。
     * 4、不能定义，默认参数的const类型的对象
     */

    //Sales_data() = default;

    //默认构造函数；使用默认值和初始化列表,进行初始化；
    Sales_data():isbn(""),revenue(0.0),units_sold(0){

        /* topic：初始化列表和赋值的区别？
        * 定义const对象时，必须得用初始化列表；也就是说，类的对象获取const属性，是在初始化列表之后的。
        */

        //isbn = "";
        //revenue = 0.0;
        //units_sold = 0;
    }

    Sales_data(std::istream &is);

    /*
     * topic：类内const成员函数说明：
     * 1、非常量函数，不能通过常量对象或指针来访问这个函数；因为要改变对象成员变量的值；
     * 2、根本原因是：隐含的使用了this指针，这个指针是：TYPE *const this这种类型的；
     *
     */
    void addCount(){
        units_sold ++;
    }
    /* topic: this指针
     * const常量函数： 把this指针置为：const TYPE *const this；
     * 所以此类定义的常量对象或指针，不可用访问非const的成员函数，只能访问const成员函数；
     * tips：
     * 不改变类成员变量的函数，尽量都定义成const成员函数，保证类定义的const对象和非const对象都可以访问此函数；
     */
    unsigned int getCount() const{
        return units_sold;
    }


};














#endif /* SALES_DATA_H_ */
