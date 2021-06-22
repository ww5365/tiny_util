/*
 * basic_8_hash_heap.cpp
 *
 *  Created on: 2019年11月4日
 *      Author: wangwei69
 */

#include "chapater_nine.h"

using namespace std;



/*
 * ugly number: 求第 Kth 个丑数
 *
 * 只有质因子：2，3，5的数字，1比较特殊直接定义为丑数；比如：1，2，3，4，5，6，8，9，10(=2*5)，12(=2*2*3),15(=3*5)
 * 第7个丑数是：8
 *
 * 算法思想：？ 利用计算机的迭代能力。。
 *
 * 如果一个数字是丑数，那么它已定是{2，3，5}不断累乘的结果； 2*2*2*3*5 。。。
 *
 * 用一个优先级对队列(每次可以取到最小值),不断出队，乘以{2,3,5}向量；得到的结果去重后再次入队，重复以上步骤，直到计算出第k个丑数；
 *
 */
class Solution{

public:
    int ugly_number(int k){

        if (k == 1) return 1;

        int prime_factor[] = {2,3,5};
        unordered_set<int> uset {std::begin(prime_factor), std::end(prime_factor)};
        std::priority_queue<int, vector<int>, greater<int>> qu{std::begin(prime_factor), std::end(prime_factor)};  //模拟 heap 实现

        std::sort(std::begin(prime_factor), std::end(prime_factor), greater<int>());
//        while (!qu.empty()){
//            int elem = qu.top();
//            qu.pop();
//            cout << "priority queue: " << elem << endl;
//        }

        for (int i = 2; i < k; ++i){

            int elem = qu.top();
            qu.pop();

            for (auto factor: prime_factor){

                int new_ugly_number = factor * elem;

                if (uset.find(new_ugly_number) == uset.end()){
                    qu.push(new_ugly_number);
                    uset.insert(new_ugly_number);
                }
            }
        }

        //循环结束后，优先级队列的最小的元素，就是第K个丑数

        return qu.top();

    }
};


/*
 * TOPK sorted list merge:
 * Merge k sorted linked lists and return it as one sorted list.Analyze and describe its complexity.
 *
 * Example 1:
    Input:   [2->4->null,null,-1->null]
    Output:  -1->2->4->nul

 * 算法: 实现多个有序 list 的归并成一个有序list
 *
 * 1、实现思路一：
 *    利用heap结构，存储 K 个 list 的元素，每次选取最小的元素，相应的对应的指针后移一位，并将最新指向元素加入到heap；
 *    如果为空，说明这个list 已经处理完，就不再加入； 直到 heap 的大小为空时，所有list 都处理完毕；
 *
 * 2、实现思路二： 分治法
 *
 *   首先实现两个有序链表的合并，返回最新有序链表的头指针；
 *
 *   分：所有k个有序链表，前k/2个合并成一个有序链表left，后k/2个合并成一个有序链表 right；
 *
 *   治：合并 left 和 right
 *
 *
 *
 */

struct ListNode{
    int val;
    struct ListNode *next;
    ListNode(int v = 0): val(v), next(nullptr){}
};


class Solution2{

private:
    //比较类中重载()运算符, 小顶堆创建时使用
    struct ListNodeCompare{
        bool operator()(const ListNode *left, const ListNode *right){
            return left->val > right->val;
        }
    };

public:
    /**
     * @param lists: a list of ListNode
     * @return: The head of one sorted list.
     *
     * 使用分治算法实现
     *
     */
    ListNode *mergeKLists_v1(vector<ListNode *> &lists) {

        return helper(lists, 0, lists.size() - 1);

    }

    //使用 heap 实现
    ListNode *mergeKlists_v2(vector<ListNode *> &lists) {

        if (lists.empty()) return nullptr;
        if (lists.size() == 1) return lists[0];

        ListNode dummy(0);
        ListNode *cur = &dummy;

        priority_queue<ListNode *, vector<ListNode *>, ListNodeCompare> qu;

        //初始化优先级队列，使用K个链表的头指针
        for (int i = 0; i < lists.size(); ++i){
            if (lists[i] != nullptr)
                qu.push(lists[i]);
        }

        while (!qu.empty()){
            ListNode *tmp = qu.top();
            cur->next = tmp;
            cur = tmp;
            tmp = tmp->next;
            qu.pop();

            //被选中链表，下一个节点入队
            if (tmp != nullptr){
                qu.push(tmp);
            }
        }

        return dummy.next;
    }

private:
    //实现两个有序链表的合并
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2){
        if (!l1 && !l2) return nullptr;
        ListNode dummy(0);
        ListNode* cur = &dummy; //利用头结点，简化代码判断
        while (l1 && l2){
            if (l1->val <= l2->val){
                cur->next = l1;
                cur = l1;
                l1 = l1->next;
            } else {
                cur->next = l2;
                cur = l2;
                l2 = l2->next;
            }
        }
        if (l1) cur->next = l1;
        if (l2) cur->next = l2;
        return dummy.next;
    }

    //将 start-》end 之间的有序链表合并成一个有序的链表
    ListNode*  helper(vector<ListNode *> &lists, int start, int end){

        if (start > end) return nullptr;
        if (start == end) return lists[start];
        int mid = start + (end - start)/2;
        ListNode *left = helper(lists, start, mid);
        ListNode *right = helper(lists, mid + 1, end);

        return mergeTwoLists(left, right);
    }
};


void test_base_8_hash(){

}



void test_base_8_heap(){


    Solution sl;
    cout << "the 7th ugly number: " << sl.ugly_number(7) << endl;
    cout << "the 7th ugly number: " << sl.ugly_number(10) << endl;
    cout << "the 17th ugly number: " << sl.ugly_number(17) << endl;


}


