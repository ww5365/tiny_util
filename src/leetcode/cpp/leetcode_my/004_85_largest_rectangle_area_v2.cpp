/*
 * Copyright (c) Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: 文件功能描述
 * 单调栈的性质
 * 1.单调栈里的元素具有单调性，栈中元素只能是单调递增或者单调递减
 * 2.元素加入栈前，会在栈顶端把破坏栈单调性的元素都删除；
 * 3.使用单调栈可以找到元素向左遍历第一个比它小的元素，也可以找到元素向左遍历第一个比它大的元素。
 * （原文链接：https://blog.csdn.net/liujian20150808/article/details/50752861）
 * leetcode 85
 * 题目：给定一个仅包含 0 和 1 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积。
 * 示例:
 * 输入:
 * [
 *   ["1","0","1","0","0"],
 *   ["1","0","1","1","1"],
 *   ["1","1","1","1","1"],
 *   ["1","0","0","1","0"]
 * ]
 * 输出: 6

 * 解法：
 * 1、每行遍历：形成当前行的高度值，遇到1，列维度高度增加1；遇到0，列维度的高度重置为0
 * 2、问题转化为：求由数组中数字代表高度的矩形的最大面积
 * 3、利用dp的思想，记录由某行构成矩形的最大面积
 *
 */

#include "01_all.h"
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

class Solution {

public:
    int MaximalRectangle(std::vector<std::vector<char>>& matrix)
    {   
        int result = 0;
        if (matrix.size() <= 0) {
            return result;
        }

        int len = matrix[0].size();
        int *tmp = new int[len](); //分配内存，并初始化

        for (std::size_t row = 0; row < matrix.size(); ++row) {
            std::cout << "test for ---" << row << std::endl;  
            for (std::size_t col = 0; col < len; ++col) {
                if (matrix[row][col] == '1') {
                    tmp[col] += 1;
                } else {
                    tmp[col] = 0;
                }
                std::cout << "test for --- col:" << col << std::endl;  
            }

            //对于每一行的高度数据，可能形成的最大面积
            std::vector<int> heights(tmp, (tmp + len));

            for (auto e : heights) {
                cout << e << " ";
            }
            cout << std::endl;
            result = std::max(result, MaxRectangle(heights));
            cout << "current max rectangle: " << result << std::endl; 
        }

        delete []tmp;
        return result;
    }

private:

    int MaxRectangle(std::vector<int> &heights)
    {
        //计算由某一数组构成的高度的矩形，可以形成的最大面积;维护单调递增的栈来实现;
        //关键是出栈是出栈时，当前栈顶元素 < 原栈顶元素 > 当前元素; 原栈顶元素的形成的面积area = 高度 * 宽度
        //宽度 = i - st.top() - 1  上下限
        int result = 0;
        if (heights.size() <= 0) {
            return result; 
        }
        std::stack<int> st; //保存数组的下标
        st.push(-1); //首位置之前的位置，哨兵
        for (std::size_t i = 0; i < heights.size(); ++i) {

            while (st.top() != -1 && heights[i] < heights[st.top()]) {
                //当前元素小于栈顶元素了，单调性破坏，出栈
                int idx = st.top();
                st.pop();
                int area = heights[idx] * (i - st.top() - 1);
                result = std::max(result, area);
            }
            st.push(i);//每个元素都需要入栈
        }
        std::size_t len = heights.size();
        while (st.top() != -1) {
            //栈不为空，栈内还保存了单调递增的矩形高度； 这时宽度： len - st.pop() - 1
            int idx = st.top();
            st.pop();
            int area = heights[idx] * (len - st.top() - 1);
            result = std::max(result, area);
        }
        return result;
    }
};


void testLargestRectangleArea2()
{
    std::vector<std::vector<char>> matrix  = {
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    };
    Solution s;
    std::cout <<"largest rectangle area v2: " << s.MaximalRectangle(matrix) << std::endl;

}
