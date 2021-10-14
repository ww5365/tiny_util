
/*
 * Copyright (c) Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: 文件功能描述 

 * 单调栈的性质
 * 1.单调栈里的元素具有单调性，栈中元素只能是单调递增或者单调递减
 * 2.元素加入栈前，会在栈顶端把破坏栈单调性的元素都删除；
 * 3.使用单调栈可以找到元素向左遍历第一个比它小的元素，也可以找到元素向左遍历第一个比它大的元素。 
 * （原文链接：https://blog.csdn.net/liujian20150808/article/details/50752861）


 * 901 股票价格跨度
 * 编写一个 StockSpanner 类，它收集某些股票的每日报价，并返回该股票当日价格的跨度。
 * 今天股票价格的跨度被定义为股票价格小于或等于今天价格的最大连续日数（从今天开始往回数，包括今天）。
 * 例如，如果未来7天股票的价格是 [100, 80, 60, 70, 60, 75, 85]，那么股票跨度将是 [1, 1, 1, 2, 1, 4, 6]。

 * 输入：["StockSpanner","next","next","next","next","next","next","next"], [[],[100],[80],[60],[70],[60],[75],[85]]
 * 输出：[null,1,1,1,2,1,4,6]

 * 输入：[100, 80, 60, 70, 60, 75, 85]
 * 输出：[1, 1, 1, 2, 1, 4, 6]
 * 解释：
 * 首先，初始化 S = StockSpanner()，然后：
 * S.next(100) 被调用并返回 1，
 * S.next(80) 被调用并返回 1，
 * S.next(60) 被调用并返回 1，
 * S.next(70) 被调用并返回 2，
 * S.next(60) 被调用并返回 1，
 * S.next(75) 被调用并返回 4，
 * S.next(85) 被调用并返回 6* 
 * 注意 (例如) S.next(75) 返回 4，因为截至今天的最后4个连续价格(包括今天的价格 75) 小于或等于今天的价格。
 * 
 * 核心算法的解决思路：
 * 使用小顶栈，并且哨兵-1作为栈底；
 * 如果栈顶元素大于当前元素，那么当前元素的跨度为1； 否则，出栈并记录首位出栈元素的idx，最终跨度为：idx - st.top() + 1
 * 难点：
 * 具体工程化落地，如何实现StockSpanner类，并能进行初始化？
 *    
 *
 */

#include "01_all.h"
#include <stack>
#include <vector>
#include <iostream>

class StockSpanner {
public:
    StockSpanner() {

    }
    
    int next(int price) {

    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */



void TestStockSpanner()
{
    std::vector<int> vec = {2, 1, 5, 6, 2, 3};
    std::vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
    // Solution s;
    // std::cout <<"largest rectangle area: " << s.largestRectangleArea(vec) << std::endl;



}
