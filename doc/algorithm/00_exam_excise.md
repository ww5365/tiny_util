
# 练习 2022.4.4


序号	题目名称	考察知识点	难度
1	科目一展厅最多人数限制	二分查找	中等
2	中秋礼物挑选	排序	简单
3	文件树	树，字典树	中等
4	船票预定系统	设计	困难

参考：http://3ms.huawei.com/km/groups/3803117/blogs/details/10964225?l=zh-cn


5	机器人道路行走	二叉树，递归，DFS，栈	中等
6	最长空闲内存	数组，双指针，滑动窗口	中等
7	基站穿行	队列，BFS	困难
8	座位管理系统	hashMap，设计	简单
9	最长回文子串	字符串	中等
10	前K个高频单词	topk，排序	中等


http://3ms.huawei.com/km/groups/3475657/blogs/details/12031931




## 题目1： 展厅最多人数限制


MWCS 展共有 N 个展厅，每个展厅的报名人数记于数组 nums。因疫情原因，所有展厅参展总人数上限为 cnt。若报名人数之和大于 cnt，则需限制参展人数。请计算单个展厅的 最大 参展人数 limit，使得参展总人数不超过 cnt，参展限制规则为：

对于报名人数不超过 limit 的展厅，凡报名即参展；

对于报名人数超过 limit 的展厅，则均要求 limit 名人员参展。

若报名人数之和小于等于 cnt，此时不需要限制参展人数，请返回 -1。

请返回 limit 的最大值或 -1。

样例1：

输入：nums = [1,4,2,5,5,1,6]，cnt = 13

输出：2

解释：报名总人数为24，大于cnt，需要限制参展人数。当 limit = 2 时，展厅报名人数大于 2 的，均有 2 人参加，参展人数总和为 1+2+2+2+2+1+2 = 12，不超过 13；若limit = 3 时，参展人数总和为 1+3+2+3+3+1+3 = 16，则超过 13。因此返回 2。

样例2

输入：nums = [1,3,2,1]，cnt = 197

输出：-1

解释：所有报名人数之和为 7，小于等于 197，此时不需要限制参展人数，因此返回 -1。

样例3

输入：nums = [1,1]，cnt = 1

输出：0

解释：limit = 0 时，无人参展即满足规则；若 limit = 1，则参展人数为 1 + 1 = 2，超过 cnt。


2022.5.3 五一期间的练习题目

序号	题目名称	url	考察知识点	难度
1	矩阵搜索	https://leetcode.com/problems/search-a-2d-matrix/
二分查找	中等
2	包含重复III	https://leetcode.com/problems/contains-duplicate-iii/
排序，滑动窗口	中等
3	N皇后问题I	https://leetcode.com/problems/n-queens/
回溯	困难
4	二叉树Z字形遍历	https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
队列，二叉树	中等
5	设计Twitter	https://leetcode.com/problems/design-twitter/
设计，模拟	中等
6	融合K个有序链表	https://leetcode.com/problems/merge-k-sorted-lists/
链表，归并排序	中等
7	最短回文子串	https://leetcode.com/problems/shortest-palindrome/
字符串，哈希，KMP，回溯	困难
8	课程规划II	https://leetcode.com/problems/course-schedule-ii/
图，BFS，DFS，拓扑排序	中等
9	滑动窗口最大值	https://leetcode.com/problems/sliding-window-maximum/
队列，滑动窗口，堆	困难
10	汽油站	https://leetcode.com/problems/gas-station/
数组，贪心算法	中等
