/*
 * text_query.cpp
 *
 * 功能： 在某个文件中查找key，返回如下值：
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


//在文件中ifs查找key值
void text_query(ifstream &ifs){

    TextQuery2 tq(ifs); //构造查询对象
    string key;
    cout << "enter a key to find: " << endl;
    while (true){

        if (!(cin >> key) || key == "q"){
            cout << "finished query operator!"  << endl;
            break;
        }

        TextQuery2Res res = tq.query(key); //实施查询操作
        print(cout, res); //打印结果

        cout << "please enter next word: " << endl;

    }

    return ;

}






