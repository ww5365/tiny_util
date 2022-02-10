/*
 * 14.cpp
 *
 *  Created on: Mar 24, 2019
 *      Author: wangwei69
 */

#include <iostream>
#include <vector>
#include <string>
#include <functional>


using namespace std;



void test_14(){

    /* 表14.1中疑问：什么运算符？ ^ , .* , ->*
     *
     * ^ : 异或？是的，异或运算
     *
     * .* : ? 啥运算符
     *
     * ->* :?
     *
     *
     */


    bool test1 = true, test2 = false, test3 = true;

    cout << " test operator ^: " << (test1^test2) << " : "  << (test1^test3) << endl;

    /*
     * 输入输出运算符:  <<  >>
     *
     * 1、非类成员函数
     * 2、注意输入运算符的错误的检查:  不合法的输入，要重置
     *
     */


    /*
     * 最终的一个需要了解的运算符：函数调用运算符 -》 函数对象
     *
     * greater<TYPE> less<TYPE> ... 标准库提供的：函数对象类 （也就是重载了()运算的类）,主要应用点：泛型算法
     *
     * plus  minus multiplies divides modules negate
     *
     * greater less  greater_equal less_equal equal_to not_equal_to
     *
     * logical_and logical_or logical_not
     *
     *   应用的泛型算法：
     *
     *   for_each
     *   sort
     *   stable_sort
     *
     * lamda表达式的本质：临时函数对象类
     *
     *
     */


    vector<string> vec_str = {"wang", "wei", "ni", "hao"};

    stable_sort(vec_str.begin(), vec_str.end(), greater<string>());

    for_each(vec_str.begin(), vec_str.end(), [](string &s){cout << s << " ";});

    cout << endl;

    //上面的lamda表达式，等价的函数对象类  : TMP();

    class TMP{

    public:
        TMP(){};
        void operator()(string &s){
            cout << s << " ";
        }
    };



    /*
     * 类型转换运算符：first time to understand
     *
     * operator TYPE() const; //无返，无参，是const  隐式的对类进行数据类型转换：转换成的结果，还是要用return返回；
     * explicit operator TYPE() const; //显示的对类进行数据类型转换：static_cast<TYPE>(..)
     *
     * 明白：while(cin >> str) 发生了什么？cin对象自动进行了：数据类型转换，转成bool； 调用就是类中operator bool() const函数；
     *
     *  cin << value ; 又会发生什么？ value进行位运算，左移1或0位
     *
     */


    class Test {
    private:
        string s;
    public:
        explicit operator bool()const{
            return (s.size() != 0 ? true : false);
        }
        Test(string str = ""):s(str){}
        string& content(){
            //非const情况下，是可以对象的私有成员s引用出来的；并且可以修改它的值；
            return s;
        }
    };

    Test t1;
    if(!t1){//发生了什么？对象t1,进行了类型转换，转成了bool型；虽然是explicit的类型转换运算符，但在if，while条件中，可以隐形的进行；
            // 也就是说： 隐形的进行了显式的数据类型转换。。

        cout << "t1 is an empty object!" << endl;
    }else{
        cout << "t1 is : " << t1.content() << endl;
    }

    Test t2("wangwei");
    if(!t2){
        cout << "t2 is an empty object!" << endl;
     }else{
         t2.content() += "nihao";
         cout << "t2 is : " << t2.content() << endl;
     }








}
