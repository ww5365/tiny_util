#include "01_all.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

/*
* url: https://www.lintcode.com/problem/76/description
* 给定一个整数序列，找到最长上升子序列（LIS），返回LIS的长度。
* eg: nums = [5,4,1,2,3]  输出：3
*/

class Solution {
public:
    /**
     * @param nums: An integer array
     * @return: The length of LIS (longest increasing subsequence)

      动规：方法1
      dp[i] : 以nums[i]结尾的最长上升子序列的长度
      dp[0] = 1
      dp[i] = max{dp[j] + 1} 满足 j < i && nums[j] < nums[i]

      最后从dp数组中找最大值，作为最长连续上升子序列的长度

     方法2： 贪心 + 二分
    
     d[len] : 记录最大长度为len时，形成的上升子序列，最后1个元素的值  d[len]随len的增加是单调递增的数组

     nums[i] > d[len] : d[++len] = nums[i]

     nums[i] <= d[len] :  使用二分方法，找到最后一个比nums[i]小的数的位置k，将d[k+1] = nums[i]

     最后返回len即可

     */


    int longestIncreasingSubsequence(vector<int> &nums) {
        // write your code here  方法1

        if (nums.size() <= 0){
            return 0;
        }

        vector<int> dp(nums.size(), 1);

        for (std::size_t i = 0; i < nums.size(); ++i) {
            for (std::size_t j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
        }
        return *(std::max_element(dp.begin(), dp.end()));
    }

    // 方法2

    int longestIncreasingSubsequence2(vector<int> &nums) {

        if (nums.size() <= 0) {
           return 0;
        }

        vector<int> d(nums.size() + 1, 0);  // 长度len时，最后1个最小值

        d[1] = nums[0];
        int len = 1;

        for (std::size_t i = 1; i < nums.size(); ++i) {

            if (nums[i] > d[len]) {
                d[++len] = nums[i];  // nums值大，递增序列长度+1，同时，最后一个最小值赋值为nums[i]
            } else {
                // nums值小, nums[i] <= d[len] 
                // 从d[1, len]中寻找第1次大于等于nums[i]值的位置，
                // 满足d[k - 1] < nums[i] <= d[k], 将d[k] = nums[i] 

                std::size_t left = 1, right = len;
                std::size_t pos = 1;

                while (left < right) {
                    std::size_t mid = (left + right) / 2;

                    if (d[mid] >= nums[i]) {
                        pos = mid;
                        right = mid - 1;
                    } else {
                        left = mid + 1;
                    }
                }
                if (d[left] >= nums[i]) {
                    pos = left;
                }
                d[pos] = nums[i];
            }
        }
        return len;
    }
};



/*

https://www.lintcode.com/problem/397
397 · 最长上升连续子序列
给定一个整数数组（下标从 0 到 n-1， n 表示整个数组的规模），请找出该数组中的最长上升连续子序列。（最长上升连续子序列可以定义为从右到左或从左到右的序列。）

输入：[5, 4, 2, 1, 3]
输出：4
解释：
给定 [5, 4, 2, 1, 3]，其最长上升连续子序列（LICS）为 [5, 4, 2, 1]，返回 4。

输入：[1, 5, 2, 3, 4]
输出：3
解释：
给定 [1, 5, 2, 3, 4]，其最长上升连续子序列（LICS）为 [2, 3, 4]，返回 3。

*/


class Solution2 {
public:
    /**
     * @param a: An array of Integer
     * @return: an integer
     */
    int longestIncreasingContinuousSubsequence(vector<int> &a) {
        // write your code here

        if (a.size() <= 1) {
            return a.size();
        }

        int result = 1;
        int tmp = 1;

        for (std::size_t i = 1; i < a.size(); ++i) {
            if (a[i] >= a[i - 1]) {
                tmp += 1;
            } else {
                tmp = 1;
            }
            result = std::max(result, tmp);
        }

        tmp = 1;
        for (std::size_t i = a.size() - 1; i > 0; --i) {
            if (a[i] >= a[i - 1]) {
                tmp += 1;
            } else {
                tmp = 1;
            }
            result = std::max(result, tmp);
        } 
        return result;
    }
};

void TestLIS()
{
    std::cout << "----begin to TestTopSort ---" << std::endl;
    std::cout << "----finished TestTopSort ---" << std::endl;
}
