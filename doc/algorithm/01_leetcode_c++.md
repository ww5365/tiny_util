# note for leetcode c++


## 一、考核环境搭建

1. [vscode](/km/blogs/details/7840371) 使用*trust*插件来搭建环境 编译、调试、以及静态检查，并且该插件已经安装了安全库函数。
  * 新建工程：F1 -> create c++ project for mingw -> 可以选择不生成gtest框架
  * 编译运行：
    terminal -> run -> configure this project
    ctrl + shift + p -> run -> run task -> build / clean build / build & run
  * 调试: F5
  * 安全头文件：securec.h
    main.cpp中打开头文件的注释及cmakelist.txt中进行安全库libsecurec.a的链接即可用
  * cleancode： 右键-> cleancode  进行检查

2. 规范： 参考编程规范5.0版本
3. [考核时问题说明](/km/groups/3803117/blogs/details/7887463?l=zh-cn)




## 二、算法分类学习


### 2.1 004 栈、单调栈：
https://leetcode-cn.com/problems/decode-string/
https://leetcode-cn.com/problems/daily-temperatures/solution/  
https://leetcode-cn.com/problems/smallest-subsequence-of-distinct-characters/
https://leetcode-cn.com/problems/number-of-islands/
https://leetcode-cn.com/problems/redundant-connection/
https://leetcode-cn.com/problems/minimum-size-subarray-sum/




### 001 字符串、排序
https://leetcode-cn.com/problems/bianry-number-to-string-lcci/1
https://leetcode-cn.com/problems/longest-palindromic-substring/
https://leetcode-cn.com/problems/restore-ip-addresses/
https://leetcode-cn.com/problems/basic-calculator-ii/

### 002 链表、队列、哈希
https://leetcode-cn.com/problems/fu-za-lian-biao-de-fu-zhi-lcof/
https://leetcode-cn.com/problems/top-k-frequent-words/
https://leetcode-cn.com/problems/find-the-most-competitive-subsequence/ 
https://leetcode-cn.com/problems/swapping-nodes-in-a-linked-list/

### 003 滑动窗口、双指针
https://leetcode-cn.com/problems/interval-list-intersections/
https://leetcode-cn.com/problems/max-consecutive-ones-iii/
https://leetcode-cn.com/problems/can-you-eat-your-favorite-candy-on-your-favorite-day/
https://leetcode-cn.com/problems/container-with-most-water/




### 005 递归
https://leetcode-cn.com/problems/swap-nodes-in-pairs/
https://leetcode-cn.com/problems/binary-tree-preorder-traversal/
https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/
https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/
https://leetcode-cn.com/problems/longest-substring-with-at-least-k-repeating-characters/
https://leetcode-cn.com/problems/partition-to-k-equal-sum-subsets/

### 006 树、二叉树
https://leetcode-cn.com/problems/maximum-width-of-binary-tree/ 
https://leetcode-cn.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/
https://leetcode-cn.com/problems/binary-tree-level-order-traversal/
https://leetcode-cn.com/problems/maximum-difference-between-node-and-ancestor/


### 007 搜索算法 BFS、DFS：
https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/solution/
https://leetcode-cn.com/problems/course-schedule/solution/
https://leetcode-cn.com/problems/perfect-squares/
https://leetcode-cn.com/problems/course-schedule/


### 008 贪心和动态规划：

https://leetcode-cn.com/problems/task-scheduler/
https://leetcode-cn.com/problems/house-robber/
https://leetcode-cn.com/problems/boats-to-save-people/
https://leetcode-cn.com/problems/house-robber-iii/

### 009 打家劫舍专题，大家先做1，再做2，如果有兴趣，可以再做3
https://leetcode-cn.com/problems/house-robber/
https://leetcode-cn.com/problems/house-robber-ii/
https://leetcode-cn.com/problems/house-robber-iii/




## 代码实现
具体实现参考：src/leetcode/cpp/leetcode_my   使用前面的编号辨识
