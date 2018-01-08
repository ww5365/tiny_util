/*
 * algorithm_use.cpp
 *
 *  Created on: Jul 31, 2017
 *      Author: wangwei69
 */

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


/*
 * @date:20170731
 * @desc: ����ӿڵ�ʹ�ã�sort��stable_sort
 *
 *
 */

/*
 * �ȽϺ�����ע������ǣ�const ���͵�����
 * �ȽϺ�����������Ƴ�
 */

template <class Type>
bool cmp_fun(const Type&t1,const Type &t2){
    return (t1.size() < t2.size());
}



void sort_algorithm_use(){

    //�����ַ����ĳ���,��С��������
    vector<std::string> test;

    test.push_back("wang");
    test.push_back("wei");
    test.push_back("test");
    test.push_back("ni");
    test.push_back("hao");
    test.push_back("hello");

    //�ȶ����򣺳�����ͬ���ַ���������ԭ����λ�ò���
    std::stable_sort(test.begin(),test.end(),cmp_fun<string>);
    vector<string>::iterator it = test.begin();
    for (;it != test.end();it++){
        std::cout << *it << "  ";
    }

    std::cout << std::endl;
    /*
     * Ԥ�ڽ����ni  wei  hao  wang  test  hello
     */


    test.clear();
    test.push_back("wang");
    test.push_back("niooo");
    test.push_back("weii");
    test.push_back("test");
    test.push_back("haoo");
    test.push_back("hello");

    //���ȶ����򣺳�����ͬ���ַ�����λ�ÿ��ܱ�
    std::sort(test.begin(),test.end(),cmp_fun<string>);
    it = test.begin();
    for (;it != test.end();it++){
        std::cout << *it << "  ";
    }

    std::cout << std::endl;


}


void algorithm_use(){

    sort_algorithm_use();
}