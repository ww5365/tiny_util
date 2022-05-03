#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>

#include <iterator>

#include <set>

using namespace std;

/*
https://leetcode.cn/problems/contains-duplicate-iii/
220. 存在重复元素 III

给你一个整数数组 nums 和两个整数 k 和 t 。请你判断是否存在 两个不同下标 i 和 j，使得 abs(nums[i] - nums[j]) <= t ，同时又满足 abs(i - j) <= k 。

如果存在则返回 true，不存在返回 false。

输入：nums = [1,2,3,1], k = 3, t = 0
输出：true




思路：

1. k + 1 个元素大小的窗口内：两个元素的差值 <= t
2. 当前元素：x 前面的K个元素窗口内，是否有元素满足：  x - t <= 之前的k个元素 <= x + t 如果有的话，说明窗口K内，是有元素满足: |x - prex| <= t

3. 关键是如何实现? 每次都遍历查找前k个元素是否满足条件，要超时； 选择数据结构，二分查找o(logn)，只要找到大于等于x-t的元素，同时再判断一下这个元素是否<=x+t 就可以。

*/

class Solution {
public:
bool ContainsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {

    if (nums.size() <= 1 || k == 0) {
        return false;
    }

    set<long> setK;  // 防止溢出使用long
    for (size_t right = 0; right < nums.size(); ++right) {
        long x  = static_cast<long>(nums[right]);
        auto it = setK.lower_bound(x - t);  // 关键，查找时间复杂度：logn
        if (it != setK.end() && *it <= (x + t)) {
            return true;
        }
        setK.insert(x); // 
        if (right >= k ) {
            setK.erase(nums[right - k]); // 当right>=k时，每轮一删; erease(值/iter)
        }
    }
    return false;
    }
};

void TestContainsNearbyAlmostDuplicate()
{
    Solution s;
    cout << "-----------TestContainsNearbyAlmostDuplicate----------------" << endl;
    vector<int> nums = {1,2,3,1};
    bool result = s.ContainsNearbyAlmostDuplicate(nums, 3, 0);
    cout << "result is : " << result << endl;
    cout << "-----------TestContainsNearbyAlmostDuplicate finished-------------" << endl;
}

