
/*
 * Copyright (c) Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: 文件功能描述 
 
 * leetcode 155

 * 设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈
 * push(x) —— 将元素 x 推入栈中
 * pop() —— 删除栈顶的元素
 * top() —— 获取栈顶元素
 * getMin() —— 检索栈中的最小元素。
 * 
 * 示例：
 * 输入：
 * ["MinStack","push","push","push","getMin","pop","top","getMin"]
 * [[],[-2],[0],[-3],[],[],[],[]]
 * 输出：
 * [null,null,null,null,-3,null,0,-2]

 * ref: https://mp.weixin.qq.com/s/Y2QZZ-coEYZ6ItDRyrdwVw

 * 解法：
 * 最难点：如何实现getMin函数，使用普通的栈，比较难实现。需要使用辅助栈，这个栈是单调递增的，栈头保持最小；
 * 
 */

#include "01_all.h"
#include <stack>
#include <iostream>

class MinStack {

public:
    MinStack(){}
    ~MinStack(){}
    // 入栈
    void push(int val)
    {
        data.push(val);
        // 栈头保存当前为止最小的元素入栈；从头到尾部，从小到大单调栈；
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }

    // 出栈 : 这里是保持单调性的关键点
    void pop()
    {
        // 单调栈出栈规则： 如果单调栈的头元素 == 出栈元素的值, 单调栈才出栈；否则不出栈
        if (minStack.top() == data.top()) {
            minStack.pop();
        }
       // 出栈
        data.pop();
    }

    int top() const 
    {
        return data.top();

    }

    // 获取栈的最小值
    int getMin()
    {
        return minStack.top();
    }

private:
    std::stack<int> data;
    std::stack<int> minStack;
};

void testMinStack()
{
    MinStack mst;
    mst.push(-1);
    mst.push(0);
    mst.push(-2);
    mst.push(-1);
    // minStack: -1,-2 
    std::cout << "minStack: " << mst.getMin() << std::endl;

    mst.pop();
    mst.pop();
    // minStack: -1
    std::cout << "minStack: " << mst.getMin() << std::endl;

}
