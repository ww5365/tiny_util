
/*
 * Copyright (c) Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: 文件功能描述 
 
 * leetcode 42
 * 题目描述：
 * 整数数组 nums 按升序排列，数组中的值 互不相同 。
 * 在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，
 * 使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。
 * 例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。
 * 
 * 给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。


 * 解决：

 * 
 */

#include "01_all.h"
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int search(vector<int>& vec, int target) {

        if (vec.size() <= 0) return -1;

        int start = 0;
        int end = vec.size() - 1;

        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (vec[mid] == target) {
                return mid;
            }
            if (vec[start] <= vec[mid]) {
                // start -> mid 这半边是单调递增的

                if (vec[start] <= target && vec[mid] > target) {
                    // 目标在单调区间内
                    end = mid;
                } else {
                    start = mid;
                }
            } else {
                // mid -> end 单调递增的
                if (vec[mid] < target && vec[end] >= target) {
                    start = mid;
                } else {
                    end = mid;
                }
            }
        }

        if (vec[start] == target)
            return start;
        if (vec[end] == target)
            return end;

        return -1;

    }
};

//2023.11.7

/*
搜索旋转排序数组 II
81.  https://leetcode.cn/problems/search-in-rotated-sorted-array-ii/
63. https://www.lintcode.com/problem/63
已知存在一个按非降序排列的整数数组 nums ，数组中的值不必互不相同。
在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转 ，使数组变为 
[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。
例如， [0,1,2,4,4,4,5,6,6,7] 在下标 5 处经旋转后可能变为 [4,5,6,6,7,0,1,2,4,4] 。
给你 旋转后 的数组 nums 和一个整数 target ，请你编写一个函数来判断给定的目标值是否存在于数组中。
如果 nums 中存在这个目标值 target ，则返回 true ，否则返回 false 。
你必须尽可能减少整个操作步骤。

注意：这里面是可以有重复的数字的

思路：
mid = start + (end - start)/2   
1. mid命中， 返回
2. nums[start] == nums[mid] && nums[mid] == nums[end] 
   判断不出单调性，先过去
3. nums[start] <= nums[mid]   [start, mid] 单调
   nums[mid] ? target
   nums[start] <= target < nums[mid] : end = mid
   否则：start = mid
4. nums[start] > nums[mid]  [mid, end] 单调
   nums[mid] < target <= nums[end]: start = mid
   否则：end = mid

*/

class Solution3 {
public:
    bool search(vector<int>& nums, int target) {

         if (nums.empty()) {
            return false;
        }
        int start = 0;
        int end = nums.size() - 1;
        while(start < end) {
            int mid = start + (end - start)/2;
            if (nums[mid] == target) {
                return true;
            }
            if (nums[start] == nums[mid] && nums[mid] == nums[end]) {
                // 区分不了单调性,把这个重复的数字过去
                start ++;
                end --;
            } else if (nums[start] <= nums[mid]) {
                // [start, mid]单调
                if (nums[start] <= target && target < nums[mid]) {
                    end = mid - 1;
                } else {
                    start = mid + 1;
                }

            } else {
                // [mid, end]单调
                if (nums[mid] < target && target <= nums[end]) {
                    start = mid + 1;                    
                } else {
                    end = mid - 1;
                }
            }
        }

        if (nums[start] == target){
            return true;
        }
        return false;
};

void TestRotatedArray()
{
    std::vector<int> vec = {4,5,6,7,0,1,2};
    Solution s;
    int result = s.search(vec, 6);
    std::cout << "TestRotatedArray result:  " << result << std::endl;


}
