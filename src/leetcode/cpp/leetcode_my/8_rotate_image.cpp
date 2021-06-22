/*
 *  Created on: Dec 6, 2017
 *      Author: wangwei69
 *
 *  1、问题：
 *   You are given an n × n 2D matrix representing an image.
 *   Rotate the image by 90 degrees (clockwise).
 *   Follow up: Could you do this in-place?
 *
 *  2、分析：？
 *
 *  这个运算，变成：1. 对角线对称->2.轴对称运算 ，完成90度的顺时针旋转操作
 *
 */

#include "test_main.h"
#include <vector>

#include <iostream>

using namespace std;


class Solution{

public:

    void rotate(vector<vector<int> >&martrix){

        int n = martrix.size(); //矩阵的纬数

        //矩阵，副对角线对称；(y = -x ＋ (n-1) 对称)
        for (int i = 0;i < martrix.size();i++){
            for (int j = 0;j < (martrix[i].size() - i);j++){
                swap(martrix[i][j],martrix[-j + n - 1][-i + n -1]);
            }
        }

        //矩阵，关于x轴对称；（y=n/2对称）
        for (int i = 0;i < martrix.size()/2;i++){
            for (int j = 0;j < (martrix[i].size() - i);j++){
                swap(martrix[i][j],martrix[n - 1 - i][j]);
            }
        }
    } //end rotate
};



void rotate_test(){

    vector<vector<int> > image = {{1,2,3},{4,5,6},{7,8,9}};
    cout << "--- before rotate ---" << endl;

    for (int i = 0;i < image.size();i++){
        for (int j =0;j < image[i].size();j++){
            cout << image[i][j] << " ";
        }
        cout << endl;
    }

    Solution s;
    s.rotate(image);

    cout << "--- after rotate ---" << endl;

    for (int i = 0;i < image.size();i++){
        for (int j =0;j < image[i].size();j++){
            cout << image[i][j] << " ";
        }
        cout << endl;
    }



}








