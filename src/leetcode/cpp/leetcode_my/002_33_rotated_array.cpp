
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

void TestRotatedArray()
{
    std::vector<int> vec = {4,5,6,7,0,1,2};
    Solution s;
    int result = s.search(vec, 6);
    std::cout << "TestRotatedArray result:  " << result << std::endl;


}
