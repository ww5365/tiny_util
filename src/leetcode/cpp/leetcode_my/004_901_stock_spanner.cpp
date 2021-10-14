
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
 */

#include "01_all.h"
#include <stack>
#include <vector>
#include <iostream>

class StockSpanner {
public:
    StockSpanner() 
    {
        st = new std::stack<Elem>();
    }
    
    int next(int price) 
    {   
        Elem elem;
        elem.result = 1;
        while (!st->empty() && st->top().price <= price) {
            Elem tmp = st->top();
            st->pop();
            elem.result += tmp.result;  //单调栈最关键的变形点：怎么计算连续的天数？已经初始化为1了
        }
        elem.price = price;
        st->push(elem);
        return elem.result;

    }

private:
    struct Elem {
        int price; //记录输入元素的数值
        int result; //记录小于等于该元素连续天数
    };
    std::stack<Elem> *st;
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */


void TestStockSpanner()
{
    std::vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
    StockSpanner *sp = new StockSpanner();
    std::cout << "stock spanner test1: " << std::endl;
    
    for (auto e : prices) {
        std::cout << sp->next(e) << " ";
    }
    std::cout << std::endl;
    
    // 直接
    StockSpanner sp2;
    std::cout << "stock spanner test2: " << std::endl;
    for (auto e : prices) {
        std::cout << sp2.next(e) << " ";
    }
    std::cout << std::endl;
}
