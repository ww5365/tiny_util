/*
 * string_using.cpp
 *
 *  Created on: Apr 28, 2017
 *      Author: wangwei69
 */

#include <vector>
#include <string>
#include <iostream>
#include "./com_use.h"

using namespace std;

int string_using_test(){

    //测试如何消除，臃肿的容器？capcity 很大，但size很小的情况。

    vector<string> vec1;
    for (int i =0 ;i< 1000 ;i++){
        vec1.push_back("wan");
    }//添加1000个字符串
    cout << "origin capacity:size: " <<vec1.capacity() <<" :" <<vec1.size()<<endl;
    vec1.clear();
    vec1.push_back("wangwei");//1024 capacity : 1 size
    cout << "clear capacity:size: " <<vec1.capacity() <<" :" <<vec1.size()<<endl;

    //消除臃肿技巧
   vector<string>(vec1).swap(vec1);
   cout << "swap capacity:size: " <<vec1.capacity() <<" :" <<vec1.size()<<endl;


}


