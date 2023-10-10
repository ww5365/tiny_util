
/*
 * Copyright (c) Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: 文件功能描述 
 
 * leetcode 42
 https://leetcode.cn/problems/trapping-rain-water/
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

// 2023.10.10

class Solution {
public:
    int trap2(vector<int>& height) {

        // 单调栈：单调递减，从栈底到栈顶 
        stack<int> st;
        int sum = 0;

        for (int i = 0; i < height.size(); ++i) {
            while(!st.empty() && height[st.top()] < height[i]) {
                // 当前元素要大于栈顶，出栈处理
                int curTop = st.top();
                st.pop(); // 出栈

                if (!st.empty()) {
                    
                    int minVal = std::min(height[i], height[st.top()]);
                    int h = minVal - height[curTop];
                    int steps = i - st.top() - 1;
                    sum += (h * steps);
                }
            }
            st.push(i); // 每个元素都入栈，要么空，要么height[i]<=栈顶元素
        }
        return sum;
    }

    int trap(vector<int>& height) {

        // 参考： https://labuladong.github.io/algo/di-san-zha-24031/jing-dian--a94a0/ru-he-gao--0d5eb/

        // 双指针

        if (height.size() <= 2)
            return 0; 

        // 4个指针        
        int left = 0; 
        int right = height.size() - 1;
        int lmax = height[0]; // 从0到left的最高柱子
        int rmax = height[height.size() - 1]; //从right到end的最高柱子
        
        int result = 0;

        while (left < right) {

            lmax = std::max(lmax, height[left]);
            rmax = std::max(rmax, height[right]);

            if (lmax < rmax) {
                result += (lmax  - height[left]);
                left ++;
            } else {
                result += (rmax - height[right]);
                right --;
            }
        }
        return result;
    }

};

/*
11. 盛最多水的容器

给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
返回容器可以储存的最大水量。

输入：[1,8,6,2,5,4,8,3,7]
输出：49 
解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。

*/

class Solution2 {
public:
    int maxArea(vector<int>& height) {

        if (height.size() <= 1) 
            return 0;

        int left = 0;
        int right = height.size() - 1;
        int result = 0;
     
        while (left < right) {
                int steps = right - left;
                if(height[left] < height[right]) {
                    result = std::max(result, height[left] * steps);
                    left ++;
                } else {
                    result = std::max(result, height[right] * steps);
                    right --;
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
