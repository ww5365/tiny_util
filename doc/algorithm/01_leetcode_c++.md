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

| **小类**       | **内容**                                                     |
| -------------- | ------------------------------------------------------------ |
|进制与位运算   | •位运算  •进制转换  •进位计算                                |
|基础数据结构   | •字符串（字典树等）  •线性表（字符数组、静态数组动态数组）  •栈（单调栈）  •队列  •链表  •哈希/Map |
|高级数据结构   | •树  •堆和优先队列  •图（并查集）                            |
|常用算法及应用 | •排序及查找  •枚举（遍历、排列、组合）  •滑窗、双指针、前缀和  •迭代、递归、回溯、分治（归并、二分等）  •搜索（深搜、广搜)  •贪心  •动归 •模拟 |

* 004 栈、单调栈
详见：04_monotonous_stack.md

* 009 归并集 DSU
详见：09_disjoint_set_union.md



001 字符串、排序

002 链表、队列、哈希

003 滑动窗口、双指针

005 递归

006 树、二叉树

007 搜索算法 BFS、DFS：

008 贪心和动态规划：

009 打家劫舍专题，大家先做1，再做2，如果有兴趣，可以再做3


## 代码实现
具体实现参考：src/leetcode/cpp/leetcode_my   使用前面的编号辨识



![算法学习思路](../img/算法学习思路-16416401495941.png)







