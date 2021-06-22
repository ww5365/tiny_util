/*
 * basic_6_list.cpp
 *
 *  Created on: Oct 9, 2019
 *      Author: wangwei69
 */

#include "chapater_nine.h"

//公用打印链表函数
void print_list(LNode *head){
    LNode *cur = head;
    cout << "list value: "  << endl;
    while(cur != nullptr){
        if (cur->next){
            cout<< cur->val << " -> ";
        } else {
            cout<< cur->val << endl;
        }
        cur = cur->next;
    }

}

/*
 * problem:
 * Given a list, rotate the list to the right by k places, where k is non-negative.
 *
 * 比如：[1,2,3,4] k=2  => 3 4 1 2
 *
 * 算法实现：
 * 1、先计算链表长度 len
 * 2、规范化k取值： k = k%len
 *   因为k值可能大于链表长度
 * 3、双指针，差k步，同向移动，结束时：cur指向最后一个元素，pre指向cur之前第k个元素；
 *   借助dummy node， 将后面k个元素整体剪切到合适位置
 *
 */


LNode* rotate_list(LNode *head,  int k){

    //先计算链表长度
    int len = 0;
    LNode *cur = head;
    while(cur){
        len ++;
        cur = cur->next;
    }

    //规范化k取值
    k = k%len;
    if (k == 0) return head;

    LNode dummy(0);
    dummy.next = head;
    cur = head;
    LNode *pre = &dummy;
    for (int i = 1; i < k; ++i){
        //先把cur后移k步，保持和pre之间有k的gap
        cur = cur->next;
    }

    //pre 和 cur 同步移动; 结束时,cur指向最后一个元素，pre指向之前k位置元素
    while(cur->next){
        pre = pre->next;
        cur = cur->next;
    }

    //整体剪切pre后的k个元素，进行rotate

    dummy.next = pre->next;
    cur->next = head;
    pre->next = nullptr;

    return dummy.next;
}

/*
 * problem:
 * 给出一个链表，每个节点包含一个额外增加的随机指针可以指向链表中的任何节点或空的节点。
 * 返回一个深拷贝的链表。
 *
 * 算法：
 * 
 * 
 * 问题和参考：https://www.jiuzhang.com/solutions/copy-list-with-random-pointer/#tag-highlight-lang-cpp
 * 
 * 正常思路：
 * 1. 先把list拷贝出来，形成一个新的list', 同时用map记录新->旧节点的映射关系
 * 2. 再循环遍历一遍list'，将list'的random节点赋
 *
 */






void test_base_6_list(){

    //构造一个链表

    LNode *head = nullptr;
    LNode *last = nullptr;
    for (int i = 1; i <= 5; ++i){

        LNode *node = new LNode(i);
        node->next = nullptr;

        if (!head){
            head = node;
        }else{
            last->next = node;
        }
        last = node;
    }


    head = rotate_list(head, 1);

    print_list(head);



}



