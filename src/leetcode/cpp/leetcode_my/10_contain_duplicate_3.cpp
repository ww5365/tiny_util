/*
 * 10_contain_duplicate_3.cpp
 *
 *  Created on: Dec 16, 2017
 *      Author: wangwei69
 */

/* 问题：
 * Given an array of integers, find out whether there are two distinct indices i and j
 * in the array such that the difference between nums[i] and nums[j] is at most t
 * and the difference between i and j is at most k .
 *
 * 分析：
 *
 * 1、从0开始，对每个元素下标i，搜索i+k个之内的元素，是否有|num[i]-num[i+k']|<=t
 *    时间复杂度：o(nk)
 *
 * 2、
 *
 */

#include <set>
#include <vector>
#include <cstdlib>

using namespace std;

 bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    set<int> window; // set is ordered automatically
    for (int i = 0; i < nums.size(); i++) {
        if (i > k) window.erase(nums[i-k-1]); // keep the set contains nums i j at most k
        // |x - nums[i]| <= t  ==> -t <= x - nums[i] <= t; => x-t <= num[i] <= x+t
        auto pos1 = window.lower_bound(nums[i] - t ); // x-nums[i] >= -t ==> x >= nums[i]-t
        //auto pos2 = window.upper_bound(nums[i]);
        // x - nums[i] <= t ==> |x - nums[i]| <= t
        if (pos1 != window.end() && abs(*pos1 - nums[i]) <= t) return true;
        window.insert(nums[i]);
    }
    return false;
}

