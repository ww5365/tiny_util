/*
 * @lc app=leetcode.cn id=88 lang=cpp
 *
 * [88] 合并两个有序数组
 *
 * https://leetcode-cn.com/problems/merge-sorted-array/description/
 *
 * algorithms
 * Easy (47.20%)
 * Likes:    477
 * Dislikes: 0
 * Total Accepted:    135.7K
 * Total Submissions: 286.7K
 * Testcase Example:  '[1,2,3,0,0,0]\n3\n[2,5,6]\n3'
 *
 * 给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。
 * 
 * 
 * 
 * 说明:
 * 
 * 
 * 初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。
 * 你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
 * 
 * 
 * 
 * 
 * 示例:
 * 
 * 输入:
 * nums1 = [1,2,3,0,0,0], m = 3
 * nums2 = [2,5,6],       n = 3
 * 
 * 输出: [1,2,2,3,5,6]
 * 
 */

#include <vector>
using namespace std;

// @lc code=start
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {

        if (n <= 0) return;
        //因为nums1的空间足够大，可以同时保留m+n个元素
        nums1.resize(m + n);
        
        //从后往前进行寻找，当前最大的填充到nums1的最后
        int i = m - 1;
        int j = n - 1;
        int cur = (m + n - 1);
        while (i >= 0 && j >= 0){
            if (nums1[i] >= nums2[j]){
                nums1[cur--] = nums1[i--];
            } else {
                nums1[cur--] = nums2[j--];
            }
        }

        while (i >= 0){
            nums1[cur--] = nums1[i--];
        }
        while (j >= 0){
            nums1[cur--] = nums2[j--];
        }
        return;
        
    }
};
// @lc code=end

