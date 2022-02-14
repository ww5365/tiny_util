
/*
 * Copyright (c) Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: 文件功能描述 
 
 * leetcode 34  lintcode 38

 34. 在排序数组中查找元素的第一个和最后一个位置
给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。
如果数组中不存在目标值 target，返回 [-1, -1]。
 
 * 
 */

#include "01_all.h"
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    
    vector<int> searchRange(vector<int>& nums, int target) {

        vector<int> result(2, -1);
        if (nums.size() <= 0) return result;
        // 二分搜索： target出现第一次位置
        result.clear();
        sort(nums.begin(), nums.end(), less<int>());
        int leftPos = FindLeftPos(nums, target); 
        int rightPos = FindRightPos(nums, target); 
        result.emplace_back(leftPos);
        result.emplace_back(rightPos);
        return  result;
    }

private:
    int FindLeftPos(vector<int> nums, int target) {
        int start = 0;
        int end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] >= target) {
                end = mid;
            } else {
                start = mid + 1;
            }
        }
        if (nums[start] == target) return start;
        if (nums[end] == target) return end;
        return -1;
    }

    int FindRightPos(vector<int> nums, int target) {
        
        int start = 0;
        int end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] <= target) {
                start = mid;
            } else {
                end = mid - 1;
            }
        }
        if (nums[end] == target) return end;
        if (nums[start] == target) return start;
        return -1;
    }
};

void TestSearchRange()
{
    std::vector<int> vec = {1, 2, 3, 3, 9, 15, 16};
    Solution s;

    vector<int> result = s.searchRange(vec, 4);

    std::cout << "-------TestSearchRange result -----" << std::endl;
    for_each(result.begin(), result.end(), [](const int &elem){std::cout << elem <<" ";});

    std::cout << std::endl;

}
