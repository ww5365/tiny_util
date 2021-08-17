
/*
 * Copyright (c) Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: 文件功能描述 

 * 单调栈的性质
 * 1.单调栈里的元素具有单调性，栈中元素只能是单调递增或者单调递减
 * 2.元素加入栈前，会在栈顶端把破坏栈单调性的元素都删除；
 * 3.使用单调栈可以找到元素向左遍历第一个比它小的元素，也可以找到元素向左遍历第一个比它大的元素。 
 * （原文链接：https://blog.csdn.net/liujian20150808/article/details/50752861）

 
 * leetcode 363
 * 题目描述：
 * 给你一个 m x n 的矩阵 matrix 和一个整数 k ，找出并返回矩阵内部矩形区域的不超过 k 的最大数值和。
 * 题目数据保证总会存在一个数值和不超过 k 的矩形区域。

 * 示例1：
 * 输入：matrix = [[1,0,1],[0,-2,3]], k = 2
 * 输出：2
 * 解释：蓝色边框圈出来的矩形区域 [[0, 1], [-2, 3]] 的数值和是 2，且 2 是不超过 k 的最大数字（k = 2）。


 * 解法：
 * 
 *
 */

#include "01_all.h"
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

class Solution {

public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k)
    {
        return 0;
    }
};


void testMaxSumSubmatrix()
{
    std::vector<vector<int>> vec = {{1, 0, 1},{0, -2, 3}};
    Solution s;

    std::cout <<"largest rectangle area: " << s.maxSumSubmatrix(vec, 2) << std::endl;

}
