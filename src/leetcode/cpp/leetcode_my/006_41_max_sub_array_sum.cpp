
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
