/*
 * design_pattern.h
 *
 *  Created on: Mar 10, 2019
 *      Author: wangwei69
 */

#ifndef SRC_INC_DESIGN_PATTERN_H_
#define SRC_INC_DESIGN_PATTERN_H_

#include <iostream>
using namespace std;



//验证一下单例设计中的疑问点



class SingltonMgr{
public:
    SingltonMgr(){}
    ~SingltonMgr(){}
private:
    int num = 0;
};


class Singlton{

private:
    SingltonMgr mgr;
    static int objNum;
    Singlton(){cout << "objNum: " << objNum << endl; objNum++;};
    ~Singlton(){};
    Singlton(const Singlton&) = delete;
    Singlton& operator= (const Singlton&) = delete;

public:

    static void printTest(){
        cout << "class Singlton function: " << objNum<< endl;
    }

    static Singlton& instance(){
        static Singlton sgl;
        return sgl;
        //这种设计方式，会不会每次调用instance,都会生成一个sgl的对象？
        // 结论:不会，每次调用instance都是同一个静态局部变量sgl,不会再生成一个对象；
    }

};









#endif /* SRC_INC_DESIGN_PATTERN_H_ */
