/*
 * 5.cpp
 *
 *  Created on: 2016��7��22��
 *      Author: wangwei69
 */



/*
 * �����£� ���
 */

#include <iostream>
#include <vector>

#include <stdexcept>

using namespace std;

void test_5(){


    /*
     * swicth: ʹ��
     * var����֧�����ͳ���
     */
    int var = -1;
    switch(var){//֧��int char
        case 1:
            cout << "var is one" <<endl;
            break;
        case -1:
            cout << "var is negtive one" <<endl;
            break;
        default:
            break;
    }

    /*
     * for: c++ 11 �������ķ�Χfor���
     */
    std::string str_for = "wangwei nihao ,come on every day!";
    for(auto &ch:str_for){
        //str_for ���������飬string��vector�����͵Ķ��󣬹�ͬ���ǵ������ܷ��أ�begin,end��Ա
        cout << ch <<": " ;
    }
    cout << endl;
    std::vector<int> vec_for = {12,2,3,35,45,0,455};

    for (int r:vec_for){
        cout << r <<": " ;
    }

    /*
     *��ת��䣺֪����ʲô�����ʹ�ã�
     * break ��ѭ����switch
     * continue ��ѭ��
     * goto �� ��ǩ
     *
     */


    /*
     * �쳣�����׳���throw
     * �쳣����
     *  try{
     *  }catch(){
     *  }..
     *
     * �����쳣������ࣺ<stdexcept>
     * exception
     * runtime_error
     * bad_alloc
     * bad_cast
     */

    try{
        std::cout << "this is test exception " <<std::endl;

        if (true){
            throw std::runtime_error("wangei test runtime error");
        }

    }catch(std::runtime_error e){
        cout << e.what() <<endl;
    }catch(std::exception e2){
        cout << e2.what() <<endl;
    }catch(std::bad_cast e3){
        cout << e3.what() << endl;
    }catch(std::bad_alloc e4){
        cout << e4.what() << endl;
    }catch(...){
        cout <<"no name exception" <<std::endl;
    }


}

