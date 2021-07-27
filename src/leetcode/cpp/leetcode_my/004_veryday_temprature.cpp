
/*
 * Copyright (c) Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: 文件功能描述 
 
 * leetcode 739
 * 题目描述：
 * 请根据每日气温列表，重新生成一个列表。对应位置的输出为：要想观测到更高的气温，至少需要等待的天数。如果气温在这之后都不会升高，请在该位置用0来代替。

 * 示例1：
 * 输入：temperatures = [73, 74, 75, 71, 69, 72, 76, 73]
 * 输出：arr = [1, 1, 4, 2, 1, 1, 0, 0]

 * ref: https://mp.weixin.qq.com/s/Y2QZZ-coEYZ6ItDRyrdwVw

 * 解法：o(n)
 * 
 * 数组中的每个元素，按序遍历，利用栈，形成从上到下的单调递增的栈； 
 * 每个元素val和栈顶元素比较，val小于等于栈顶元素，直接入栈，保持单调性；val大于栈顶元素，栈顶元素出栈，并计算相差天数，循环判断可能多个元素出栈。
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
