#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>

#include <unordered_map>


using namespace std;

/*

23. 合并K个升序链表  https://leetcode.cn/problems/merge-k-sorted-lists/
给你一个链表数组，每个链表都已经按升序排列。
请你将所有链表合并到一个升序链表中，返回合并后的链表。

输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6


思路：

1、 使用优先级队列，保存k个链表的指针，并按照从小到大进行出队
2、 将出队的最小元素依次形成新的链表，同时对于出队的节点所在的链表的下一个元素需要进行入队

*/


/**
 * Definition for singly-linked list.
 */

struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {

        if (lists.size() <= 0) {
            return nullptr;
        }

        ListNode dummy(0); // 哨兵
        ListNode *cur = &dummy;
        auto cmpFun = [](const ListNode *left, const ListNode *right){
            return (left->val > right->val); //构建小顶堆
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmpFun)> qu(cmpFun); //使用匿名函数类型，需要传参

        for (size_t i = 0; i < lists.size(); ++i) {
            if (lists[i]) {
                qu.push(lists[i]); // k个链表的头结点入队 非空
            }
        }

        while (!qu.empty()) {
            ListNode *tmp = qu.top();
            qu.pop();
            cur->next = tmp;
            
            if (tmp->next) {
                qu.push(tmp->next);
            }
            cur = tmp;
        }
    return dummy.next;
    }
};



void TestMergeKLists()
{
    Solution s;
    cout << "-----------TestMergeKLists----------------" << endl;

}

