/*
 * @lc app=leetcode.cn id=142 lang=cpp
 *
 * [142] 环形链表 II
 *
 * https://leetcode-cn.com/problems/linked-list-cycle-ii/description/
 *
 * algorithms
 * Medium (49.57%)
 * Likes:    450
 * Dislikes: 0
 * Total Accepted:    70.2K
 * Total Submissions: 140.8K
 * Testcase Example:  '[3,2,0,-4]\n1'
 *
 * 给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
 * 
 * 为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。
 * 
 * 说明：不允许修改给定的链表。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：head = [3,2,0,-4], pos = 1
 * 输出：tail connects to node index 1
 * 解释：链表中有一个环，其尾部连接到第二个节点。
 * 
 * 
 * 
 * 
 * 示例 2：
 * 
 * 输入：head = [1,2], pos = 0
 * 输出：tail connects to node index 0
 * 解释：链表中有一个环，其尾部连接到第一个节点。
 * 
 * 
 * 
 * 
 * 示例 3：
 * 
 * 输入：head = [1], pos = -1
 * 输出：no cycle
 * 解释：链表中没有环。
 * 
 * 
 * 
 * 
 * 
 * 
 * 进阶：
 * 你是否可以不用额外空间解决此题？
 * 
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include "ds_common.h"

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {

        if (!head || !head->next) return nullptr;

        //先找到相遇点
        ListNode *slow = head;
        ListNode *fast = head;
        bool is_circle = false;
        ListNode *node = nullptr;
        while (fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast){
                is_circle = true;
                node = slow;
                break;
            }
        }
        //再从头和相遇点开始找链表交点
        if (!is_circle) return nullptr;
        slow = head;
        while (slow != node){
            slow = slow->next;
            node = node->next;
        } //链表交点时的入口

        return node;
        
    }
};
// @lc code=end

