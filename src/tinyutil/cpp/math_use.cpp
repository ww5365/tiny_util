/*
 * math_use.cpp
 *
 *  Created on: Aug 10, 2018
 *      Author: wangwei69
 *  @breif
 *  数学计算相关的函数实现
 *
 */

#include "com_use.h"
#include <vector>
#include <iostream>

#include <cmath>

using namespace std;

float sum_square(vector<float> &);

void math_use_test(){

    //平方和
    cout << "begin to cal square of vec " << endl;
    vector<float> vec = {-0.68, -0.54, -0.33, 0.16, 0.56, 0.81, -0.01, -0.21, 0.09, 0.14};
    cout << "square of vec: " << sum_square(vec) << endl;

    vector<float> vec1 = {-0.16, -0.02,0.19,-0.06,0.34,0.59,-0.23,-0.43,-0.13,-0.08};
    cout << "square of vec1: " << sum_square(vec1) << endl;

    // 向上取整 ceil(x) : >= x 的最小整数
    cout << "ceil(7/3) result: " << ceil((float)7/3) << endl;
    
    // 向上取整 floor(x) : <= x 的最大整数
    cout << "floor(7/3) result: " << floor(7/3) << endl;
    
    // 向上取整 round(x) : 四舍五入
    cout << "round(7/3) result: " << round(7/3) << endl;


}



/*
 * 计算向量各个元素的平方和：vec ={x1，x2,...}
 *
 * sum = x1^2 + x2^2 + ...
 *
 */


float sum_square(vector<float> &vec){

    float res = 0;

    for(auto e : vec){
        res += e * e;
    }
    return res;
}



