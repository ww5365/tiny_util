# 基本数据结构 - 链表相关


## 链表奇偶位重排

描述：一个链表，奇数位升序偶数位降序，让链表变成升序的。比如：1 8 3 6 5 4 7 2 9，最后输出1 2 3 4 5 6 7 8 9
### 思路

分析思路:
1、将原始链表按奇偶分开（leetcode原题：奇偶链表 : 328. 奇偶链表 https://leetcode.cn/problems/odd-even-linked-list/)
2、偶链表是降序的，所以将其逆序（leetcode原题：翻转链表 : 206. 反转链表 https://leetcode.cn/problems/reverse-linked-list/）
3、合并两个有序链表（leetcode原题：合并两个有序链表 : https://leetcode.cn/problems/merge-two-sorted-lists/）

### 代码

001_000_328_list_rerank.cpp