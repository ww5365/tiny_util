
/*
 * Copyright (c) Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: 文件功能描述
 * 请定义一个队列并实现函数 max_value 得到队列里的最大值
 * 若队列为空，pop_front 和 max_value 需要返回 -1
 * 示例：
 * 输入: ["MaxQueue","push_back","push_back","max_value","pop_front","max_value"]
 * [[],[1],[2],[],[],[]]
 * 输出: [null,null,null,2,1,2]
 * ref: https://mp.weixin.qq.com/s/Y2QZZ-coEYZ6ItDRyrdwVw
 */

#include "01_all.h"
#include <deque>
#include <queue>
#include <iostream>

class MaxQueue {

public:
    MaxQueue(){}
    ~MaxQueue(){}
    // 获取最大值动作:max_value
    int maxValue()
    {
        return deq.empty() ? -1 : deq.front();
    }

    void pushBack(int value)
    {
        qu.push(value); // 入队
        // 如何使用双端队列保持：单调递减的队列
        while (!deq.empty() && deq.back() < value) {
            deq.pop_back(); // 队尾出队
        }
        deq.push_back(value); // 保留单调的队列
    }

    int popFront()
    {
        if (qu.empty()) return -1;
        int val = qu.front(); // 队头
        if (val == deq.front()) {
            deq.pop_front(); // 单调队列队头出队，同样保持单调性
        }
        qu.pop();
        return val;
    }

private:
    std::queue<int, std::deque<int>> qu;
    std::deque<int> deq;
};

void testMaxQueue()
{
    MaxQueue mq;
    mq.pushBack(3); // qu：3 deq：3
    mq.pushBack(1); // qu：3 1 deq：3 1
    mq.pushBack(2); // qu: 3 1 2 deq: 3 2
    std::cout << "queue max value: " << mq.maxValue() << std::endl;
    mq.popFront();
    std::cout << "queue max value2: " << mq.maxValue() << std::endl;
}
