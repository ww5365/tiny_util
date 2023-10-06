/*
lintcode：52  
leetcode：31  https://leetcode.cn/problems/next-permutation/
1.1 问题描述

不重复的N(1<=N<=9)个数,给出个全排列，计算下一个比它大的全排序序列；如果是最大的给出起始最小的序列；
比如：[1,2,3] : 1,3,2 -> 2,1,3

1.2 算法

1.partitionNumber: find the first number from right to left which has descending trend.
 If don't have ,it suggests current sequence is biggest one.
2.changeNumber: find number from right to left which is firstly bigger than partitionNumber
3.swap: swap partitionNumber and changeNumber
4.reverse: reverse the numbers from partitionNumber index to the end;


初始态： x1 x2 x3 x4 x5  
从右往左看，x2 变小了，即：x1 x2 < x3 > x4 > x5  从右开始，找第1个大于x2的元素，假设是x4 则x2和x4交换
x1 x4 < x3 > x2 > x5  ,可以看到数组肯定是变大了，同时可以看到：x3 x2 x5 是单调递减的，reverse后，可以得到整体最小的排列即：x1 x4 x5  x2  x3


 */

#include "test_main.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution{
public:
    void nextPermutation(vector<int> &nums){
        //nums中保存的是序列：312 求下一个大的序列：321
        next_permutation(nums, 0, nums.size());
    }

private:
    void next_permutation(vector<int> &nums, int begin ,int end){
        if (nums.empty() || begin >= end){
            return;
        }
        //from right to left find first descending number
        int index = end - 2;
        while (index >= begin && nums[index] >= nums[index + 1]) --index;
        if (index < begin){//没有找到，说明已经是最大的了
            reverse(&nums[begin],&nums[end]); //参数是：iterator 翻转[begin,end)之间的元素；但使用了地址作为参数?
            return ; //没有AC，漏了这句；
        }
        //from right to left find the firstly bigger num than index ，swap
        int change_index = end - 1;
        while (nums[index]>=nums[change_index] && change_index > index) --change_index;
        swap(nums[index],nums[change_index]);
        //reverse index+1 to end
         (&nums[index + 1], &nums[end]);
    }
};

//2023.10.16 https://leetcode.cn/problems/next-permutation/submissions/
class Solution2 {
public:
    void nextPermutation(vector<int>& nums) {  

        
        if (nums.size() <= 1) {
            return;
        }

        int right = nums.size() - 1;
        int left = 0;
        int index = right - 1;

        // 找到第1处变小的位置
        while(index >= left && nums[index] >= nums[index + 1]) {
            --index;
        }

        if (index < left) {
            // 已是最大的排列情况
           reverse(nums.begin(), nums.end()); 
        //    std::cout << "reverse 111111111111" << std::endl;
           return;
        }

        // 不是最大排列，要正常处理

        // 从右往左，找第1个比nums[index]大的元素
        int changeIdx = right;
        while (changeIdx > index && nums[changeIdx] <= nums[index]) changeIdx--;

        std::swap(nums[index], nums[changeIdx]);

        // std::cout << "1111111111111111111111111111: " << index << " : " << changeIdx << std::endl; 
        // std::copy(nums.begin(), nums.end(), std::ostream_iterator<int>(std::cout, ","));
        // std::cout << std::endl; 

        // 从index + 1 到尾部，逆转, 得到比原排序大的最小的排序数
        std::reverse(nums.begin() + index + 1, nums.end()); // reverse 使用iterator进行操作
        
        // std::cout << "222222222222222222222222222222: " << right << std::endl; 
        // std::copy(nums.begin(), nums.end(), std::ostream_iterator<int>(std::cout, ","));
        // std::cout << std::endl; 

        return;
    }
};


void next_permutation_test(){

    vector<int> nums = {5,2,3,1};

    Solution s;

    cout << "current permutation sequence: ";
    for(auto e:nums)
        cout << e << " ";

    s.nextPermutation(nums);


    cout << endl << "next permutation sequence: ";

    for(auto e:nums)
        cout << e << " ";

    cout << endl;

}



