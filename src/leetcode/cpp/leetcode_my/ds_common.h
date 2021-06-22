/*
 * ds_common.h
 *
 *  Created on: Jan 15, 2018
 *      Author: wangwei69
 */

#ifndef DS_COMMON_H_
#define DS_COMMON_H_




//常用数据结构节点的定义

//链表节点

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

//二叉树节点
struct TreeNode{
    int val;
    struct TreeNode *left,*right;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};

#endif /* DS_COMMON_H_ */
