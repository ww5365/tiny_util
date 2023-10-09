
/*
 * 402 lintcode / leetcode: 
 */

#include "01_all.h"
#include <deque>
#include <queue>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

/*

leetcode : 152 : https://leetcode.cn/problems/maximum-product-subarray/description/
lintcode: 191 : https://www.lintcode.com/problem/191/description

给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。
测试用例的答案是一个 32-位 整数。
子数组 是数组的连续子序列。
 
示例 1:
输入: nums = [2,3,-2,4]
输出: 6
解释: 子数组 [2,3] 有最大乘积 6。

输入:[-1,2,4,-2]
输出:16

算法思路：

dp[i] : 当前的最大连续子数组的乘积：nums[0] * nums[1] * .. * nums[i]

dp[i] : 有三种取值情况： nums[i]: 当前元素自身(前面dp[i-1]是负值初始化态 或 有负值出现过，前面的dp[i-1]还没有当前的元素大）
                        dp[i-1] * nums[i] ： nums[i] > 0
                        minValue[i-1]  * nums[i] : nums[i] < 0  还有可能，当前是负值，前面连续积最小值出现过负值，这也是最大值的可能
抽象整理下思路：

记住当前元素之前，最大的乘积maxProduct 和  最小乘积minProduct

result = nums[0];
maxProduct = nums[0];
minProduct = nums[0];

nums[i] >= 0 :
maxProduct = std::max(maxProduct * nums[i] , nums[i]);
minProduct = std::min(minProdcut * nums[i], nums[i]);

nums[i] < 0 : 
maxProduct = std::max(minProdcut * nums[i], nums[i]);
minProdcut = std::min(maxProdcut * nums[i], nums[i]);

result = std::max(result,maxProduct);

*/


class Solution {
public:
    int maxProduct(vector<int>& nums) {

        int res = nums[0];
        int preMaxProduct = nums[0];
        int preMinProduct = nums[0];

        std::cout << preMaxProduct << " : " << preMinProduct << std::endl;

        for (int i = 1; i < nums.size(); ++i) {

            if (nums[i] >= 0) {
                preMaxProduct = std::max(preMaxProduct * nums[i], nums[i]);
                preMinProduct = std::min(preMinProduct * nums[i], nums[i]);
            } else {
                // std::cout << "before: " << i << " : " << nums[i] << " :  "<< preMaxProduct << " : " << preMinProduct << std::endl;
                int tmp = preMaxProduct;
                preMaxProduct = std::max(preMinProduct * nums[i], nums[i]);
                preMinProduct = std::min(tmp * nums[i], nums[i]);

                // std::cout << preMaxProduct << " : " << preMinProduct << std::endl;
            }
            res = std::max(res, preMaxProduct);
        }
        return res;
    }
};



void testMaxSubArrayProduct()
{

    std::vector<int> nums =  {-4,-3,-2};

    Solution s;

    int res  = s.maxProduct(nums);

    std::cout << "the final res: " << res << std::endl;

}
