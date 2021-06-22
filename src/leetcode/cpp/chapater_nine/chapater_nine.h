/*
 * chapater_nine.h
 *
 *  Created on: Jul 15, 2019
 *      Author: wangwei69
 */

#ifndef CHAPATER_NINE_CHAPATER_NINE_H_
#define CHAPATER_NINE_CHAPATER_NINE_H_

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_set>
#include <queue>

using namespace std;

//链表节点定义
struct LNode{
    int val;
    LNode *next; //链表节点，指向下一个节点
    LNode(int x = 0) : val(x), next(nullptr){}
};



void  nine_test();

void base_2_binary_search();

void base_2_rotated_array();

void test_basic_3_binary_tree_divide_conquer();

void test_base_4_bfs();

void test_base_5_dfs();

void test_base_6_list();

void test_base_6_array();

void test_base_8_heap();

void test_base_9_dp();



#endif /* CHAPATER_NINE_CHAPATER_NINE_H_ */
