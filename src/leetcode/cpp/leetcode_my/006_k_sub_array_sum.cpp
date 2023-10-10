
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
        hash[0] = 1;
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


void testKSubArraySum()
{
    // rest;
    return ;
}
