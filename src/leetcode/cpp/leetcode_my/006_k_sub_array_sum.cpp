
/*
 * 402 lintcode / leetcode: 
 */

#include "01_all.h"
#include <deque>
#include <queue>
#include <iostream>
#include <limits>
#include <vector>

#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
560. 和为 K 的子数组
给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的连续子数组的个数 。
子数组是数组中元素的连续非空序列
https://leetcode.cn/problems/subarray-sum-equals-k/?show=1

输入：nums = [1,1,1], k = 2
输出：2

*/
class Solution {
public:
    int subarraySum2(vector<int>& nums, int k) {
        
        unordered_set<int> hash;

        int preSum = 0;
        hash.emplace(0);
        int  result = 0;

        for (int i = 0; i < nums.size(); ++i) {

            // [1,-1,0] 这个case没过，说明不能使用set,需要使用map记录某个key出现的次数
            preSum += nums[i];
            if (preSum == k) {
                result += 1;
            }
            int key = preSum - k;
            if (hash.find(key) != hash.end()) {
                result += 1;
            }

            hash.emplace(preSum);
        }
        return result;
    }

    int subarraySum(vector<int>& nums, int k) {
        
        unordered_map<int, int> hash;

        int preSum = 0;
        hash[0] = 1;  // 想明白点： map使用 和 初始值为0 presum - 0 代表了：[0,i] 之间的和
        int  result = 0;

        for (int i = 0; i < nums.size(); ++i) {

            // [1,-1,0] 这个case没过，说明不能使用set,需要使用map记录某个key出现的次数
            preSum += nums[i];
            int key = preSum - k;
            
            if (hash.find(key) != hash.end()) {
                result += hash[key];
            }

            if (hash.find(preSum) != hash.end()) {
                hash[preSum] = 0;
            }
            hash[preSum] ++;
        }
        return result;
    }

};


/*

1844 · 子数组和为K II
https://www.lintcode.com/problem/1844/?showListFe=true&page=1&problemTypeId=2&tagIds=390&pageSize=50

给定一个整数数组和一个整数k，你需要找到和为k的最短非空子数组，并返回它的长度。
如果没有这样的子数组，返回-1.

输入: 
nums = [2,1,-1,4,2,-3] and k = 3
输出: 
2
*/

class Solution2 {
public:
    /**
     * @param nums: a list of integer
     * @param k: an integer
     * @return: return an integer, denote the minimum length of continuous subarrays whose sum equals to k
     */
    int subarraySumEqualsKII(vector<int> &nums, int k) {
        // write your code here

        if (nums.size() <= 0) return -1;

        unordered_map<int, int> hash; //记录达到这个前缀和时，最后元素的位置索引
        
        int sum = 0;
        hash[0] = -1;  // 这个初始化理解很重要，保证有索引位置[0， i]之间的和
        int result = std::numeric_limits<int>::max();

        for (int i = 0; i < nums.size(); ++i) {

            sum += nums[i];
            int preSum = sum - k;

            if (hash.find(preSum) != hash.end()) {
                result = std::min(result, i - hash[preSum]);
            }

            hash[sum] = i;
        }
        if (result == std::numeric_limits<int>::max()) {
            result = -1;
        }

        return result;
    }
};


/*
406 · 和大于S的最小子数组
https://www.lintcode.com/problem/406
给定一个由 n 个正整数组成的数组和一个正整数 s ，请找出该数组中满足其和 ≥ s 的最小长度子数组。如果无解，则返回 -1。

输入: [2,3,1,2,4,3], s = 7
输出: 2
解释: 子数组 [4,3] 是该条件下的最小长度子数组。

*/

class Solution3 {
public:
    /**
     * @param nums: an array of integers
     * @param s: An integer
     * @return: an integer representing the minimum size of subarray
     */
    int minimumSize(vector<int> &nums, int s) {
        // write your code here
    }
};

void testKSubArraySum()
{
    // rest;
    return ;
}
