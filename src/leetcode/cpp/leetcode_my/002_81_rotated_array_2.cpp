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
    }
};
