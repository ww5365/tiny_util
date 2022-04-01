# 滑动窗口

## 滑动窗口介绍
出处：（https://zhuanlan.zhihu.com/p/61564531）
滑动窗口法，也叫尺取法（可能也不一定相等，大概就是这样），可以用来解决一些查找满足一定条件的连续区间的性质（长度等）的问题。
由于区间连续，因此当区间发生变化时，可以通过旧有的计算结果对搜索空间进行剪枝，这样便减少了重复计算，降低了时间复杂度。
往往类似于“请找到满足xx的最x的区间（子串、子数组）的xx”这类问题都可以使用该方法进行解决。

## 代码模板

``` java

/* 滑动窗口算法框架 */
void slidingWindow(string s, string t) {
    unordered_map<char, int> need, window;
    for (char c : t) need[c]++;
    
    int left = 0, right = 0;
    int valid = 0; 
    while (right < s.size()) {
        // c 是将移入窗口的字符
        char c = s[right];
        // 右移窗口
        right++;
        // 进行窗口内数据的一系列更新
        ...

        /*** debug 输出的位置 ***/
        printf("window: [%d, %d)\n", left, right);
        /********************/
        
        // 判断左侧窗口是否要收缩
        while (window needs shrink) {
            // d 是将移出窗口的字符
            char d = s[left];
            // 左移窗口
            left++;
            // 进行窗口内数据的一系列更新
            ...
        }
    }
}

```

## 典型题

### 1 长度最小的子数组(#[209](https://leetcode-cn.com/problems/minimum-size-subarray-sum/))

给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的连续子数组。如果不存在符合条件的连续子数组，返回 0。示例: 
输入: s = 7, nums = [2,3,1,2,4,3]
输出: 2
解释: 子数组 [4,3] 是该条件下的长度最小的连续子数组。

``` c++
// 暴力算法 o(n^3)  leetcode 超时
    int minSubArrayLen(int target, vector<int>& nums) {
       int len = nums.size();
       int result = std::numeric_limits<int>::max();
        for (int i = 0; i < len; ++i) {
            for (int j = i; j < len; ++j) {
                int sum = std::accumulate(nums.begin() + i, nums.begin() + j + 1, 0);
                cout << "sum: " << sum << endl;
                if (sum >= target) {
                    result = std::min(result, j - i + 1);
                    break;
                }
            }
        }
        if (result == std::numeric_limits<int>::max()) {
            result = 0;
        }
        return result;
    }
```

优化思路：







### 2 无重复字符的最长子串([#3](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/))

给定一个字符串，请你找出其中不含有重复字符的 最长子串的长度。
示例 1:
输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。


### 3 最大连续1的个数 III（#1004）
给定一个由若干 0 和 1 组成的数组 A，我们最多可以将 K 个值从 0 变成 1 。
返回仅包含 1 的最长（连续）子数组的长度。

示例 1：
输入：A = [1,1,1,0,0,0,1,1,1,1,0], K = 2
输出：6
解释： 
[1,1,1,0,0,1,1,1,1,1,1]
粗体数字从 0 翻转到 1，最长的子数组长度为 6。
示例 2：
输入：A = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], K = 3
输出：10
解释：
[0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
粗体数字从 0 翻转到 1，最长的子数组长度为 10


## 触类旁通

### 1 尽可能使字符串相等（#1208）

### 2 至多包含 K 个不同字符的最长子串

### 3 最少交换次数来组合所有的 1（#1151会员）

### 4 长度为 K 的无重复字符子串（#1100会员）


## 真题练习

### 







​     

