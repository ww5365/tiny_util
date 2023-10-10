
/*
 * lintcode: 41
 */

#include "01_all.h"
#include <deque>
#include <queue>
#include <iostream>
#include <limits>

#include <vector>

using namespace std;


/*
lintcode ： 41 · 最大子数组
https://www.lintcode.com/problem/41/?showListFe=false&page=1&problemTypeId=2&tagIds=390&pageSize=50
给定一个整数数组，找到一个具有最大和的子数组，返回其最大和。
每个子数组的数字在数组中的位置应该是连续的
*/

class Solution {
public:
    /**
     * @param nums: A list of integers
     * @return: A integer indicate the sum of max subarray
     */
    int maxSubArray(vector<int> &nums) {
        // write your code here

        int res = std::numeric_limits<int>::min();

        int preSum = 0;
        int minPreSum = 0;

        for (std::size_t i = 0; i < nums.size(); ++i) {

            preSum += nums[i];
            res = std::max(res, preSum - minPreSum);
            minPreSum = std::min(minPreSum, preSum);
        }

        return res;
    }
};

void testMaxSubArraySum()
{

    vector<int> nums = {-1, 2, 3, -3};

    Solution s;

    int res  = s.maxSubArray(nums);

    std::cout << "the final res: " << res << std::endl;

}
