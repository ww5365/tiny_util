/**
* https://leetcode-cn.com/problems/kth-largest-element-in-an-array/
* 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
* 请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
* 输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
* 输出: 4

* 核心考察点：
* 快速排序中使用的划分思路，具体实现也是双指针的一种思想: 相向指针
* 
*/
#include "01_all.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <stack>
#include <queue>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {

        if (k < 1 || k > nums.size()){
            return -1;
        }

        return FindKLargeElem(nums, 0, nums.size() - 1, nums.size() - k);
    }

    void Sort(vector<int>& nums)
    {
        if (nums.size() <= 1) {
            return;
        }
        quick_sort(nums, 0, nums.size() - 1);       
    }

private:

    // 划分的思路：双指针  来解决第K大元素的问题
    int FindKLargeElem(vector<int> &nums, int start, int end, int k) 
    {
        if (start >= end) {
            return nums[start];
        }
        int pos = partition(nums, start, end);

        std::cout << "the k: " << k << std::endl;
        std::cout << "the pos: " << pos << std::endl;
        if (pos == k) {
            return nums[pos];
        }

        if (pos > k) {
            return FindKLargeElem(nums, start, pos - 1, k);
        } else if (pos < k) {
            return FindKLargeElem(nums, pos + 1, end, k);
        }
        return nums[pos];
    }

    //进行范围内的快排
    void quick_sort(vector<int> &nums, int start, int end)
    {
        if (start >= end) {
            return;
        }
        int pos = partition(nums, start, end);
        quick_sort(nums, start, pos - 1);
        quick_sort(nums, pos + 1, end);
    }

    // 进行一次划分，并返回轴点的位置; 这是支持最大K和快排的核心
    int partition(vector<int>& nums, int start, int end) 
    {   
        if (start > end){
            return -1;
        }

        int left = start;
        int right = end;
        int pivot = nums[(start + end)/2];
        // swap(nums, start, (start + end)/2);
        std::swap(nums[start], nums[(start + end) / 2]);
        
        //左右互相覆盖的原理
        while (left < right) {
            while (left < right &&  nums[right] >= pivot) {
                right--;
            }
            if (left < right) {
                nums[left] = nums[right];
            }
            while (left < right && nums[left] <= pivot) {
                left++;
            }
            if (left < right) {
                nums[right] = nums[left];
            }
        }
        nums[left] = pivot;
        return left;
    }

    void swap (vector<int> &nums, int i, int j) 
    {   
        if (i < j && j < nums.size()) {
            int tmp = nums[j];
            nums[j] = nums[i];
            nums[i] = tmp;
        }
    }

public:
    // 使用heap：优先级队列 方式解决第k大元素问题： 队列大小为k； 小顶堆，每次出队最小元素；
    // 最终结果保留k个最大元素在队列中，依次出队，第一个出队的为第K大元素，最后一个出队的为最大元素
    int findKthLargest2(vector<int> &nums, int k)
    {   
        if (nums.size() < k){
            return -1;
        }
        priority_queue<int, deque<int>, greater<int>> qu; // 小顶堆
        for (int i = 0; i < nums.size(); ++i) {
            qu.push(nums[i]);
            if (qu.size() > k) {
                qu.pop();
            }
        }
        return qu.top();
    }

};

void TestKLargeElem()
{
    Solution s;
    vector<int> nums = {4, 5, 3, 7, 1, 9, 12};
    std::cout << "quick_sort: " << std::endl;

    s.Sort(nums);

    for (auto e : nums) {
        std::cout << e << " "; 
    }
    std::cout << std::endl;

    int k = 1;
    int k_large_elem = s.findKthLargest(nums, k);

    std::cout << "the K = " << k << " partition(double pointer) large elem: "<< k_large_elem << std::endl;
    
    k = 2;

    int res = s.findKthLargest2(nums, k); // 9

    std::cout << "the K = " << k << " heap(priority_queue) large elem: "<< res << std::endl;



}
