#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>


using namespace std;

/*

长度最小的子数组

# 209 https://leetcode-cn.com/problems/minimum-size-subarray-sum/
给定一个含有 n 个正整数的数组和一个正整数 target 。

找出该数组中满足其和 ≥ target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr]
，并返回其长度。如果不存在符合条件的子数组，返回 0 。

 
输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。


*/


class Solution {
public:

    // 暴力算法 o(n^3)
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int len = nums.size();
        int result = std::numeric_limits<int>::max();
        for (int i = 0; i < len; ++i) {
            for (int j = i; j < len; ++j) {
                int sum = std::accumulate(nums.begin() + i, nums.begin() + j + 1, 0);
                // cout << "sum: " << sum << endl;
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

    // 两根指针：滑动窗口的思路
    int minSubArrayLen2(int target, vector<int> &nums)
    {

        int result = std::numeric_limits<int>::max();
        int sum = 0;

        for (int right = 0, left = 0; right < nums.size(); ++right) {
            sum += nums[right];

            while (sum >= target) {
                result = std::min(result, right - left + 1);
                sum -= nums[left];
                ++left;
            }
        }
        return (result == std::numeric_limits<int>::max() ? 0 : result);
    }
};

void TestMinLenSubArray()
{
    // vector<int> nums = {1, 2, 3};
    vector<int> nums = { 2, 3, 1, 2, 4, 3 };
    Solution s;

    cout << "-----------TestMinLenSubArray----------------" << endl;

    int result = s.minSubArrayLen2(7, nums);

    cout << "TestMinLenSubArray result = " << result << endl;
    cout << "-----------TestMinLenSubArray finished-------------" << endl;
}