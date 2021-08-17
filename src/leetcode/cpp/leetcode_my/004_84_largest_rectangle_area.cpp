
/*
 * Copyright (c) Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: 文件功能描述 

 * 单调栈的性质
 * 1.单调栈里的元素具有单调性，栈中元素只能是单调递增或者单调递减
 * 2.元素加入栈前，会在栈顶端把破坏栈单调性的元素都删除；
 * 3.使用单调栈可以找到元素向左遍历第一个比它小的元素，也可以找到元素向左遍历第一个比它大的元素。 
 * （原文链接：https://blog.csdn.net/liujian20150808/article/details/50752861）

 
 * leetcode 84
 * 题目描述：
 * 给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
 * 求在该柱状图中，能够勾勒出来的矩形的最大面积。
 

 * 示例1：
 * 输入：heights = [2,1,5,6,2,3]
 * 输出：10
 * 解释：最大的矩形为图中红色区域，面积为 10

 * ref: https://leetcode-cn.com/problems/largest-rectangle-in-histogram/
 * 解法参考：https://leetcode-cn.com/problems/largest-rectangle-in-histogram/solution/bao-li-jie-fa-zhan-by-liweiwei1419/

 * 解法：
 * 1、单调栈： 单调递增栈    第一个右边小于栈顶元素的值； 栈顶倒数第2个元素，是第一个左边小于栈顶元素的值；
 * 2、入栈： 都入栈  从左向右
 *    出栈： 栈顶 大于 当前元素，出栈； 从右向左，计算出栈元素下标到上限(当前元素下标，不包含当前元素)和下限（栈中紧邻元素）宽度，面积 = 宽度 * 出栈元素的高度;
 * 3、最终栈处理： 遍历结束，栈不为空
 *    假设最后一个元素为高度0，
 *    
 *
 */

#include "01_all.h"
#include <stack>
#include <vector>
#include <iostream>

class Solution {

public:
    int largestRectangleArea(std::vector<int> &heights)
    {
        int result = 0;
        std::size_t len = heights.size();
        if (len <= 0) {
            return result;
        }
        std::stack<int> st;
        st.push(-1); //下限，哨兵

        for (std::size_t i = 0; i < len; ++i) {

            while (st.top() != -1 && heights[i] < heights[st.top()]){
                // 保持单调递增的栈
                int top_elem = heights[st.top()];
                st.pop();
                // 计算面积
                int width = i - st.top() - 1;  // 上限i 下限紧邻元素
                result = std::max(result , width * top_elem);
            }
            st.push(i); //所有元素入栈
        }

        // 处理栈内剩余元素, 上限是len
        while (st.top() != -1) {

            int top_elem = heights[st.top()];
            st.pop();
            int width = len - st.top() - 1;
            result = std::max(result, top_elem * width);
        }
        return result;
    }
};


void testLargestRectangleArea()
{
    std::vector<int> vec = {2, 1, 5, 6, 2, 3};
    Solution s;

    std::cout <<"largest rectangle area: " << s.largestRectangleArea(vec) << std::endl;

}
