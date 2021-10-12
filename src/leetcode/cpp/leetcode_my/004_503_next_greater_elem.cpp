
/*
 * Copyright (c) Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: 文件功能描述 
 
 * leetcode 503
 * 题目描述：
 * 给定一个循环数组（最后一个元素的下一个元素是数组的第一个元素），输出每个元素的下一个更大元素。数字 x 的下一个更大的元素是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 -1

 
 * 示例:
 * 输入: [1,2,1]
 * 输出: [2,-1,2]
 * ref: https://leetcode-cn.com/problems/next-greater-element-ii/
 
 * 解决：
 * （1）第一轮循环数组： 使用小顶栈（自下而上变小），按照下一个最大元素I的思路，可以定位数组中部分元素下一个更大元素。
 * （2）栈内剩余元素的是一个自下而上的单调递减的队列，其中整个数组中的最大元素是栈底元素。
 * （3）第二轮循环数组：主要的目的是把栈内的元素，出栈，并找到下一个最大元素；这个过程中，不再进行入栈操作；如果当前元素小于等于栈顶元素，直接忽略；如果大于栈顶元素，出栈，同时指向数组位置的指针保持不变，有可能栈内下一个元素也小于当前元素；
 * （4）最后，栈内只剩最大元素，对应的输出下一个最大值为-1。
 */

#include "01_all.h"
#include <stack>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> NextGreaterElements(vector<int>& nums)
    {
        if (nums.size() <= 0) {
            return std::vector<int> (); 
        }
        std::vector<int> res (nums.size(), 0); 
        std::stack<int> st;
        for (int i = 0; i < nums.size(); ++i) {
            while (!st.empty() && nums[i] > nums[st.top()]) {
                // 破坏了小顶栈的规则，出栈，计算栈顶元素与当前元素距离
                int top_idx = st.top();
                st.pop();
                res[top_idx] = nums[i];
            }
            st.push(i);
        } // 第一轮计算可以确定的元素的下一个最大元素
        int idx = 0;
        while (!st.empty()) {  //以栈的维度去理解
            int idx_elem = st.top();
            while (idx < nums.size() && nums[idx] <= nums[idx_elem]) {
                ++idx; //当前元素<= 栈顶元素, 那么肯定也是<=栈下面的元素；放心的到数组后面去找；
            }
            if (idx >= nums.size()) {
                // 没有找到下一个更大元素了
                while (!st.empty()) {
                    res[st.top()] = -1;
                    st.pop();
                }
                break;
            } else {
                res[idx_elem] = nums[idx]; //第二轮搜索找到下一个最大元素
                st.pop();
            }
        }
        return res;
    }
    vector<int> NextGreaterElements2(vector<int>& nums)
    {
        if (nums.size() <= 0) {
            return std::vector<int> (); 
        }
        std::vector<int> res (nums.size(), -1); 
        std::stack<int> st;
        for (int i = 0; i < nums.size(); ++i) {
            while (!st.empty() && nums[i] > nums[st.top()]) {
                // 破坏了小顶栈的规则，出栈，计算栈顶元素与当前元素距离
                int top_idx = st.top();
                st.pop();
                res[top_idx] = nums[i];
            }
            st.push(i);
        } // 第一轮计算可以确定的元素的下一个最大元素

        for (int i = 0; i < nums.size(); ++i) { // 以数组为维度
            while (!st.empty() && nums[st.top()] < nums[i]) {
                res[st.top()] = nums[i];
                st.pop();
            } 
            // 不再入栈了，栈内剩余元素的下一个最大元素都是-1， 初始化的时，已经搞定
        } 
        return res;

    }

    vector<int> NextGreaterElements3(vector<int>& nums)
    {
        if (nums.size() <= 0) {
            return std::vector<int> (); 
        }
        std::vector<int> res (nums.size(), -1); 
        std::stack<int> st;
        for (int i = 0; i < 2 * nums.size(); ++i) {
            int num = nums[i % nums.size()];
            while (!st.empty() && num > nums[st.top()]) {
                // 使用另外一种思路: 更加简练
                int top_idx = st.top();
                st.pop();
               res[top_idx] = num;
            }
            if (i < nums.size()) st.push(i);
        } 
        return res;
    }

};

void TestNextGreaterElements()
{

    std::vector<int> vec = {1, 1, 1};
    Solution s;
    std::vector<int> result (vec.size(), -1);
    result = s.NextGreaterElements3(vec);
    std::cout <<"test next greater elements: " << std::endl;
    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i] << " "; 
    }
    std::cout << std::endl;
}
