/*
 * 14_stack_use_queue_imp.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: wangwei69
 */

/*
 * 问题：
 *
 * Implement the following operations of a stack using queues.
 * push(x) -- Push element x onto stack.
 * pop() -- Removes the element on top of the stack.
 * top() -- Get the top element.
 * empty() -- Return whether the stack is empty.
 *
 *思路：
 * 使用两个queue，que 和 tmp 实现
 * 入栈：push(x)操作，将元素x入队到tmp；将que中所有元素出队，放到tmp中，同时交换tmp和que；这样保持最新的元素在que的对头；
 * 出栈：将que中对头元素出队；
 * top：获取que的队头元素；
 * empty：que是否为空
 *
 * 类StackUsingQue:
 *
 * 使用两个队列，模拟实现stack的功能；
 */

#include <queue>
#include <iostream>
using namespace std;

template<typename T>
class StackUsingQue{

private:
    queue<T>* que; //queue是容器适配器，底层默认使用deque实现
    queue<T>* tmp;
    int size;

public:
    StackUsingQue(){
        que = new queue<T>();
        tmp = new queue<T>();
        size = 0;
    }
    ~ StackUsingQue(){
        delete que;
        delete tmp;
    }
    void push (T x);
    void pop();
    T top();
    bool empty(){
        return (size <= 0);
    }
};



template<typename T>
void StackUsingQue<T>::push(T x){

    while(!tmp->empty()){
        tmp->pop();//清空tmp队列
    }
    tmp->push(x); //最新元素入队tmp，保持最新元素的对头

    while (!que->empty()){
        tmp->push(que->front());
        que->pop();//将que中的所有元素，出队，并进入到tmp中；
    }

    //交换tmp和que，始终保持que是真实队列的指针
    swap<queue<T>* >(que,tmp);
    size++;
    return;
}

template<typename T>
void StackUsingQue<T>::pop(){

    //队列不为空，出队
    if(!que->empty()){
        que -> pop();
        size--;
    }
    return;
}

template<typename T>
T StackUsingQue<T>::top(){

    //队列不为空
    if(!que->empty()){
        return que -> front();
    }
    return 0;
}


void stack_use_queue_imp_test(){

    StackUsingQue<int> test;

    test.push(1);
    test.push(2);
    test.push(3);
    test.push(4);

    while(!test.empty()){
        cout << "stackUsingQue: " << test.top() << endl;
        test.pop();
    }

    cout << "StackUsingQue test over!" <<endl;

}




