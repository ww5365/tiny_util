
/*
 * Copyright (c) Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: 文件功能描述
 * leetcode 239
 * 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。
 * 你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
 * 返回滑动窗口中的最大值。
 * 示例：
 * 输入：nums = [1,3,-1,-3,5,3,6,7], k = 3 输出：[3,3,5,5,6,7]

 * ref: https://mp.weixin.qq.com/s/Y1QZZ-coEYZ6ItDRyrdwVw

 * 解法：单调队列
 * 如何保持一个队列的队头是最大值且是单调的？是解决这个问题的关键
 */

#include "01_all.h"
#include <vector>
#include <deque>
#include <iostream>

class MaxSlideWindow {

public:
    std::vector<int> maxSlideWindow(std::vector<int> &vec, unsigned int k)
    {
        std::vector<int> res;
        if (vec.size() <= 0) {
            return res;
        }
        std::deque<int> deq;
        std::size_t win_len = vec.size() - k + 1; // 滑动窗口的滑动次数

        // 前k个数进队deq,保持单调队列特性: 从大到小 ： 从front到back， 也知道front一定在当前窗口中的最大值
        for (std::size_t i = 0; i < k; ++i) {
            while (!deq.empty() && vec[i] > deq.back()) {
                deq.pop_back();
            }
            deq.push_back(vec[i]);
        }
        res.push_back(deq.front()); // 前k个元素入队后，取队头最大元素，保存第1个窗口内的最大元素

        for (std::size_t j = k; j < vec.size(); ++j) {

            if (vec[j - k] == deq.front()) {
                deq.pop_front(); // ***这步难理解，重要*** 保持单调队列更新，淘汰超出窗口的可能的最大值
                //出队： 窗口K内，要淘汰的首元素，一定是最大的情况下，才有可能在队头；否则，已经被单调栈规则淘汰了
            }
            // 保持单调队列 和上面一样
            while (!deq.empty() && vec[j] > deq.back()) {
                deq.pop_back();
            }
            deq.push_back(vec[j]);
            res.push_back(deq.front());
        }
        return res;
    }
};

void testMaxSlideWindow()
{
    MaxSlideWindow msw;
    std::vector<int> vec = {1, 3, -1, -3, 5, 3, 6, 7} ;
    std::vector<int> res = msw.maxSlideWindow(vec, 3); // 窗口大小为3
    for (auto e : res) {
        std::cout << "max slide window: " << e << std::endl;
    }
}
