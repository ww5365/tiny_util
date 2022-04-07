#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>


using namespace std;

/*

最大连续1的个数 III

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

思路：

滑动窗口中，最多可以有K个0的情况下，最长的连续1的个数;

1、循环遍历数组， 同时计数窗口内，0的个数 cnt
2、如果：cnt > k ，左边移动指针
3、每轮计算窗口内最长的连续1的个数（包括<=K个0的长度）

*/


class Solution {
public:
    int longestOnes(vector<int> &nums, int k)
    {
        int cnt = 0;
        int left = 0;
        int result = 0;
        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] == 0) {
                cnt++;
            }
            while (cnt > k && left < nums.size()) {
                if (nums[left++] == 0) {
                    cnt--;
                }
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};

void TestLongestOnes()
{
    vector<int> nums = { 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0 };
    Solution s;
    cout << "-----------TestLongestOnes----------------" << endl;
    int result = s.longestOnes(nums, 3);
    cout << "TestLongestOnes result = " << result << endl;
    cout << "-----------TestLongestOnes finished-------------" << endl;
}