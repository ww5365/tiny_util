/*
 * text_query.cpp
 *
 * ���ܣ� ��ĳ���ļ��в���key����������ֵ��
 *
 *  element occurs 12 times
 *     (line 35) a set element contains only a key;
 *     (line 160) regardless of element whether the element
 *     ....
 *
 *  Created on: Feb 25, 2019
 *      Author: wangwei69
 */
#include "all.hpp"
#include "text_query.h"
#include <fstream>
#include <iostream>

using namespace std;



void text_query(ifstream &ifs);

void test_text_query(){

    ifstream ifs("./test");

    if (!ifs.good()){
        cout << "open file failed!" << endl;
        return;
    }

    text_query(ifs);

}


//���ļ���ifs����keyֵ
void text_query(ifstream &ifs){

    TextQuery tq(ifs); //�����ѯ����
    string key;
    cout << "enter a key to find: " << endl;
    while (true){

        if (!(cin >> key) || key == "q"){
            cout << "finished query operator!"  << endl;
            break;
        }

        TextQueryRes res = tq.query(key); //ʵʩ��ѯ����
        print(cout, res); //��ӡ���

        cout << "please enter next word: " << endl;

    }

    return ;

}






