/*
 * ml_use.cpp
 *
 *  Created on: Sep 19, 2018
 *      Author: wangwei69
 */

#include <vector>
#include <iostream>
#include <cmath>
#include "com_use.h"
using namespace std;


/*
 * 获取向量的L2范数
 */
double get_norma(vector<double> &vec){

    double l2_norma = 0.0;
    if (vec.size() < 0){
        return l2_norma;
    }
    for (std::size_t i = 0; i < vec.size(); ++i){
        l2_norma  += pow(vec[i], 2);
    }
    return sqrt(l2_norma);
}


void vector_use_test(){

    //通过swap交换数据，保持

    vector<int *> data;
    vector<int *> tmp;

    int *array1 = new int[10];
    int *array2 = new int[5];
    int *array3 = new int[2];

    data.push_back(array1);
    data.push_back(array2);
    data.push_back(array3);

    tmp.swap(data);
    data.clear();
    cout << "vector size: " << tmp.size() << " :  " << data.size() << endl;

    //在循环访问过程中实现对某些元素的删除？

    vector<int> test = {1,2, 3, 4, 5};
    auto it = test.begin();
    while (it != test.end()){
        if (*it == 3){
            it = test.erase(it);  //返回下一个迭代器的位置
        } else {
            ++it;
        }
    }

    cout << "test vector size: " << test.size() << endl;
    cout << "test vector elem: " ;
    for (auto e : test){
        cout << "  " << e;
    }
    cout << endl;

    //插入特定位置元素

    auto itor = test.begin();

    itor += 2;
    test.insert(itor, 7);

    cout << "test vector elem2: " ;
    for (auto e : test){
        cout << "  " << e;
    }
    cout << endl;


    /*
     * vector作为向量时，初始化固定个大小的数据值；并进行更新
     * resize
     */

    vector<int> test2;
    test2.resize(4, 1);  //初始化为1，空间大小为4
    test2[2] = 10;

    for (auto elem : test2){
        cout << "test vector2: "  << elem << endl;
    }

    vector<double> test3 = {0.3, 0.4};
    double l2 = get_norma(test3);
    cout << "L2 norma: " << l2 << endl;

    //插入特定位置的元素




}
