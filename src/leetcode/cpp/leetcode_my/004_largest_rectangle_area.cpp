
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

struct Element {
    int data;
    std::size_t pos;
};
class Solution {

public:
    std::vector<int> dailyTemprature(std::vector<int> &data)
    {
        std::size_t len = data.size();
        std::vector<int> result(len, 0);
        // std::stack<Element> st;
        std::stack<std::size_t> st;

        for (std::size_t i = 0; i < len; ++i) {
            // 出栈，计算栈内元素的相隔当前val的间隔天数
            while (!st.empty() && data[i] > data[st.top()]) {
                result[st.top()] = (i - st.top());
                st.pop();
            }
            st.push(i);
        }

        return result;
    }

};

void testEveryDayTemprature()
{
    std::vector<int> vec = {73, 74, 75, 71, 69, 72, 76, 73};
    Solution s;
    std::vector<int> result =  s.dailyTemprature(vec);
    for (auto e : result) {
        std::cout << "daily temprature: " << e << std::endl;
    }

}
