/*
 * 10_test_bind.cpp
 *
 *  Created on: Mar 8, 2019
 *      Author: wangwei69
 */
#include "all.hpp"
#include <iostream>
#include <string>
#include <functional>

using namespace std;



/*
 * ��ϰʹ��bind
 *
 *  1������ͨ����
 *  2�������г�Ա����
 *
 *
 */

int fun(const string &str , int num){

    cout << "----------" << endl;
    cout << "hello " << str << endl;
    cout << "invoke time: " << num << endl;

    return 0;
}



class Object{

private:

    string name;

public:

    explicit Object(const string& s = ""):name(s){}

    void printObject(const string &s){
        //this->name = s;
        cout << "object function name: " << this->name << endl;
        cout << "object function str: " << s << endl;
    }

};




void test_10_bind(){

    int number = 0;

    /*
     * ����ͨ�ĺ���:
     *
     * auto useFuc = bind(realFunc,_1,r, _2, s)
     *
     * ʹ�ã� useFuc(p1,p2) => realFunc(p1,r,p2,s)
     *
     * bind�ķ���ֵ���ͣ� function<void (p1, p2)> useFunc;
     *
     * ���ô�ֵ�� cref ref
     *
     */

    typedef function<int(const string &str)> FunType; //��������ָ��

    FunType newf = std::bind(fun, std::placeholders::_1, number);
    ++number;
    newf("world"); // �ȼ�����ã� fun("world", number)  ʹ���º������������ٴ�һ����������һ������Ĭ�ϰ�:ֵ�ǰ�ʱ��ֵ�����ǵ���ʱ��ֵ


    FunType newf2 = std::bind(fun, std::placeholders::_1, cref(number));
    ++number;
    newf2("world2"); //Ĭ�ϰ󶨵Ĳ���number���Ǵ����ã����������ǵ���ʱ����ʵֵ

    /*
     * ��һ������ĳ�Ա����
     *
     * bind(&���г�Ա����, &�����, �����б�...)
     *
     */

    Object obj("wang");
    typedef function<void(const string &s)> FunType2;
    FunType2 newf3 = std::bind(&Object::printObject, &obj, std::placeholders::_1);
    newf3("wangwei"); //�ȼ۵���: obj.printObject("wangwei");

    /*
     * ���߽�������У���ʹ�� bind
     */


}


