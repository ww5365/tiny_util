
/*
 * Copyright (c) Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: 文件功能描述 
 
 * leetcode 84
 * 题目描述：
 * 给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
 * 求在该柱状图中，能够勾勒出来的矩形的最大面积。
 

 * 示例1：
 * 输入：heights = [2,1,5,6,2,3]
 * 输出：10
 * 解释：最大的矩形为图中红色区域，面积为 10

 * ref: https://leetcode-cn.com/problems/largest-rectangle-in-histogram/

 * 解法：
 * 
 * 
 *  
 */

#include "01_all.h"
#include <stack>
#include <vector>
#include <iostream>

class Solution {

public:
    int largestRectangleArea(std::vector<int> &data)
    {
        int result = 0;
        return result;
    }

};

void testLargestRectangleArea()
{
    std::vector<int> vec = {2, 1, 5, 6, 2, 3};
    Solution s;

    std::cout <<"largest rectangle area: " << s.largestRectangleArea(vec) << std::endl;

}
