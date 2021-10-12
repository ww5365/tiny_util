
/*
 * Copyright (c) Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: 文件功能描述 
 
 * leetcode 42
 * 题目描述：
 * 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
 
 * 示例:
 * 输入：height = [4,2,0,3,2,5]
 * 输出：9
 * ref: https://mp.weixin.qq.com/s/Y2QZZ-coEYZ6ItDRyrdwV
 
 * 解决：
 * 利用单调栈的解决思路
 * 1 入栈规则：保持栈，从栈顶到栈底的单调递增；建模了，可能盛水的碗的左半边；
 * 2 出栈规则：当前的元素大于等于栈顶元素，将栈顶元素出栈；并在大于栈顶元素且栈中有至少2个元素的情况下，计算可以盛水的量
 * 
 * 
 */

#include "01_all.h"
#include <stack>
#include <vector>
#include <iostream>

class Solution {

public:
    // 单调栈解法:  时间 o(n) 空间 o(n)
    int rainTrap(std::vector<int> &data)
    {
        std::size_t len = data.size();
        int result = 0;

        if (len < 3) {
            return result;
        }
        // std::vector<int> result(len, 0);
        // std::stack<Element> st;
        std::stack<std::size_t> st; //只需要保存元素的下标的位置
        for (std::size_t i = 0; i < len; ++i) {
            // if ( !st.empty() && data[i] == data[st.top()]) {
                // 当前元素和栈顶元素相等
            //     continue;
            // }
            while (!st.empty() && data[i] > data[st.top()]) {
                std::size_t minPos = st.top();
                st.pop();
                if (!st.empty()) {
                    // 至少有1个元素才可以形成盛水的凹形
                    int height = std::min(data[st.top()] - data[minPos], data[i] - data[minPos]);
                    int width = i - st.top() - 1;
                    result += (height * width);
                }
            }
            st.push(i);
        }
        return result;
    }

    // 双向指针的解法
    int rainTrap2(std::vector<int> &data) 
    {
        int maxLeft = 0;
        int maxRight = 0; // 当前为止，左边 或 右边 墙，最高的那个墙
        int result = 0;
        std::size_t i = 0, j = data.size() - 1; // 下标
        while (i <= j) {
            if (maxLeft <= maxRight) {
                // 左边的最高墙，小于 右边的最高墙  盛水由短板决定,左边的更短些
                maxLeft = std::max(maxLeft, data[i]);
                result += (maxLeft - data[i++]);
            } else {
                // 右边墙更短些; 左边最高墙已经保证；
                maxRight = std::max(maxRight, data[j]);
                result += (maxRight - data[j--]);
            }
        }
        return result;
    }

};

void TestRainTrap()
{
    std::vector<int> vec = {4, 2, 0, 3, 2, 5};
    Solution s;
    int result = s.rainTrap(vec);
    std::cout << "rain trap1: " << result << std::endl;
    std::cout << "rain trap11: " << s.rainTrap(vec) << std::endl;

    // 双向指针解法
    std::vector<int> vec2{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    std::cout << "rain trap2: " << s.rainTrap2(vec2) << std::endl;

}
