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


## 算法学习思维导图

截止2022.4.22 已经系统整理知识点

单调栈:
归并集:

DFS(回溯)： 
BFS:

树 + 分治 ：

两根指针： 滑动窗口

前缀和

3篇工作级的真题：

系统设计：

## 再次起航

### 重拾资料
#### 2023.9.25
1. jiuzhang
   * 形成的纸质笔记， 知识体系
   * doc/algorithm 基于知识体系的实现代码
   * leetcode： https://leetcode.cn/problemset/all/      主要用来运行新写的代码，是否AC；有错误case提示；
   * lintcode： https://www.lintcode.com/problem/?typeId=2  主要来参考解决方法，leetcode上找不到原题的，用它来AC代码；
   * https://www.jiuzhang.com/problem/search?tags=microsoft  这里也可以参考答案
    
2. 九阳神功 : 现在doc/algorithm中md文档基于这个材料形成,  培养知识体系
   
3. labuladong  
   * chrome 插件，在leetcode上刷题时参考解题思路 ： 这个插件已装，整体来说有参考价值
4. 打榜活动

#### 2023.10

数组前缀和：  这个为起点： 纸质笔记
* 连续子数组最大和I II ： lintcode：41/402  前缀和
* 和为k的连续子数组 ：560 前缀和 + hash

* 股票最大收益 ： 差分 + 前缀和  **双指针**  动态规划
* 股票最大收益：121,122,123,309,714 团灭，动态规划建模
* 乘积最大的子数组：152  双指针  最大 + 最小
* 接雨水：42 左右双指针，最大 + 最大
* 盛最多水的容器：11  左右双指针
* 下一个大的排列 ： 31 双指针

#### 2023.11.28   MS

* LC 236. 二叉树最近公共祖先的题
* LC 82. 删除排序链表中的重复元素 II
* LC 76. 最小覆盖子串

边界
Codeshare 上写代码
https://codetop.cc/home  题目分类
参考：https://zhuanlan.zhihu.com/p/394958018


ms job describe:
https://jobs.careers.microsoft.com/global/en/job/1664067/Senior-Software-Development-Engineer




## 算法中常用的函数


### 头文件 algorithm


#### std::all_of  

all_of(itor_begin, itor_end, predit); // 判断[itor_begin, itor_end)中的元素是否都满足谓词条件

``` c++

#include <algorithm> 

// 声明
template< class InputIt, class UnaryPredicate >
bool all_of( InputIt first, InputIt last, UnaryPredicate p );


1) Checks if unary predicate p returns true for all elements in the range [first, last).

template< class InputIt, class UnaryPredicate >
bool any_of( InputIt first, InputIt last, UnaryPredicate p );

3) Checks if unary predicate p returns true for at least one element in the range [first, last).

template< class InputIt, class UnaryPredicate >
bool none_of( InputIt first, InputIt last, UnaryPredicate p );

5) Checks if unary predicate p returns true for no elements in the range [first, last).

// 代码示例1：
std::all_of(keys.begin(), keys.end(), [hash](const char &c) { return hash[c - 'A'] > 0; });  // keys中值，全部满足lambda表达式,lambda表达式传递外部变量到内部使用

// 代码示例2：

#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
 
int main()
{
    std::vector<int> v(10, 2);
    std::partial_sum(v.cbegin(), v.cend(), v.begin()); // 部分和累加函数，并把结果放到v.begin起始位置；{1,2,3}->{1,1+2,1+2+3},以覆盖的方式写;
    std::cout << "Among the numbers: ";
    std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " ")); // 输出vector中的值，并用空格分割
    std::cout << '\n';
 
    if (std::all_of(v.cbegin(), v.cend(), [](int i){ return i % 2 == 0; })) {
        std::cout << "All numbers are even\n";
    }
    if (std::none_of(v.cbegin(), v.cend(), std::bind(std::modulus<>(), 
                                                     std::placeholders::_1, 2))) {
        // 使用ff = bind(f,_1, 2) => ff(1) 实际f(1, 2)
        std::cout << "None of them are odd\n";
    }
    struct DivisibleBy
    {
        const int d;
        DivisibleBy(int n) : d(n) {}
        bool operator()(int n) const { return n % d == 0; } // 重载()运算符
    };
 
    if (std::any_of(v.cbegin(), v.cend(), DivisibleBy(7))) {
        std::cout << "At least one number is divisible by 7\n";
    }
}
```


### 头文件 string

字符串处理的常用函数

#### find

size_t find (const string& sbustr, size_t pos = 0) ：从字符串pos位置开始，寻找匹配的substr。
返回值：
The position of the first character of the first match.
If no matches were found, the function returns string::npos.

#### substr

substr(pos, len) : 从pos位置截取，len个字符。pos默认起始是0。返回子串。

pos
Position of the first character to be copied as a substring.
If this is equal to the string length, the function returns an empty string.
If this is greater than the string length, it throws out_of_range. // pos超出长度时，会抛异常
Note: The first character is denoted by a value of 0 (not 1).
len
Number of characters to include in the substring (if the string is shorter, as many characters as possible are used).
A value of string::npos indicates all characters until the end of the string.

当len大于实际的长度时，怎么样？不会抛异常，直接截取到最后，相当于substr(pos);


``` c++

// 分隔符切出所有字符串，比如：ab/cd/e  => [ab, cd, e]  ab/cd/ef/  => [ab, cd, ef, ""] 

size_t split_string(const std::string& src,
                    const std::string& delimiter,
                    std::vector<std::string>& fields){

    fields.clear();
    size_t previous_pos = 0;
    size_t current_pos = 0;
    while ((current_pos = src.find(delimiter, previous_pos)) != std::string::npos) {
        fields.push_back(src.substr(previous_pos, current_pos - previous_pos));
        previous_pos = current_pos + delimiter.length();
    }

    // Add the last string
    // If the last string is delimiter, add emyty string to fields too.
    if (previous_pos <= src.length()) {
        fields.push_back(src.substr(previous_pos));
    }

    return fields.size();
}
```


``` c++

// copy式输出
std::copy(nums.begin(), nums.end(), std::ostream_iterator<int>(std::cout, ","))

// 逆转
reverse(nums.begin(), nums.end());   // reverse 使用iterator进行操
std::reverse(nums.begin() + index + 1, nums.end()); // 从index + 1 到尾部，逆转, 得到比原排序大的最小的排序数

// 交换
 std::swap(nums[index], nums[changeIdx]);

// 



```





