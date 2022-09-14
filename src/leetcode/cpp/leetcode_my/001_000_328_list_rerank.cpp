#include "01_all.h"
#include <iostream>
using namespace std;

/*
一个链表，奇数位升序偶数位降序，让链表变成升序的。比如：1 8 3 6 5 4 7 2 9，最后输出1 2 3 4 5 6 7 8 9

分析思路:
1、将原始链表按奇偶分开（leetcode原题：奇偶链表 : 328. 奇偶链表 https://leetcode.cn/problems/odd-even-linked-list/)
2、偶链表是降序的，所以将其逆序（leetcode原题：翻转链表 : 206. 反转链表 https://leetcode.cn/problems/reverse-linked-list/）
3、合并两个有序链表（leetcode原题：合并两个有序链表 : https://leetcode.cn/problems/merge-two-sorted-lists/）

时复杂度为O(n),空间复杂度为O（1）
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

void PrintList(ListNode *head)
{
    if (!head) {
        cout << "the list is empty!" << endl;
    }
    ListNode *cur = head;
    while (cur) {
        cout << " " << cur->val << " ";
        cur = cur->next;
    }
    cout << endl;
}

ListNode *ListRerank(ListNode *head)
{
    ListNode *odd = nullptr;
    ListNode *even = nullptr;
    SplitList(head, odd, even);
    ReversList(even);
    return MergeList(odd, even);
}

// private:

// 链表拆分成奇偶位的两个链表
void SplitList(ListNode *head, ListNode *&odd, ListNode *&even)
{   
    odd = head;
    if (!head || !head->next) {
        return;
    }
    even = head->next;

    ListNode *oddCur = odd;
    ListNode *evenCur = even;
    ListNode *cur = head->next->next;
    while(cur) {
        cout <<"cur val: " << cur->val << endl;
        // 可以不用奇偶标识，直接走两步
        oddCur->next = cur;
        oddCur = cur;
        cur = cur->next;
        if (cur){
            evenCur->next = cur;
            evenCur = cur;
            cur = cur->next;
        }
    }
    evenCur->next = nullptr;
    oddCur->next = nullptr;
    return;
}

// 链表逆置
ListNode *ReversList(ListNode *head)
{
    if (!head || !head->next) {
        return head;
    }

    ListNode *pre = nullptr;
    ListNode *cur = head;
    // 就地逆置方法
    while (cur) {
        ListNode *tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }
    head = pre;
    return head;
}

// 有序链表合并

ListNode* MergeList(ListNode *odd, ListNode *even)
{
    ListNode dummy;
    ListNode *cur = &dummy;
    ListNode *curOdd = odd;
    ListNode *curEven = even;
    while (curOdd && curEven) {
        if (curOdd->val <= curEven->val) {
            cur->next = curOdd;
            cur = curOdd;
            curOdd = curOdd->next;
        } else {
            cur->next = curEven;
            cur = curEven;
            curEven = curEven->next;
        }
    }

    if (curOdd) {
        cur->next = curOdd;
    }

    if (curEven) {
        cur->next = curEven;
    }
    return dummy.next;
}

};

void TestRerankList()
{
    Solution s;
    
    // 创建链表
    ListNode *head = nullptr;
    ListNode *cur = nullptr;
    vector<int> vec = {1, 8, 3, 6, 5};
    head = new ListNode(vec[0]);
    cur = head;
    for (size_t i = 1; i < vec.size(); ++i) {
        cur -> next = new  ListNode(vec[i]);
        cur = cur -> next; 
    }

    // 打印初始链表
    s.PrintList(head);

    // 拆分链表
    ListNode *odd = nullptr;
    ListNode *even = nullptr;
    s.SplitList(head, odd, even);
    
    cout << "-----------TestRerankList  split odd ----------------" << endl;
    s.PrintList(odd);

    cout << "-----------TestRerankList split even ----------------" << endl;
    s.PrintList(even);
    
    cout << "-----------TestRerankList reverse list ----------------" << endl;
    even = s.ReversList(even);
    s.PrintList(even);
    
    cout << "-----------TestRerankList merge list ----------------" << endl;
    head = s.MergeList(odd, even);
    s.PrintList(head);

    cout << "-----------TestRerankList----------------" << endl;

}

