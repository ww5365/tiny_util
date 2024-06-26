
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
lintcode : 402 · 连续子数组求和
https://www.lintcode.com/problem/402/?showListFe=true&page=1&problemTypeId=2&tagIds=390&pageSize=50
给定一个整数数组，请找出一个连续子数组，使得该子数组的和最大。输出答案时，请分别返回第一个数字和最后一个数字的下标。（如果存在多个答案，请返回字典序最小的

*/
class Solution {
public:
    /**
     * @param a: An integer array
     * @return: A list of integers includes the index of the first number and the index of the last number
     */
    vector<int> continuousSubarraySum(vector<int> &a) {
        // write your code here

        int maxSum = std::numeric_limits<int>::min();
        int preSum = 0;
        int minSum = 0;

        int start = -1;
        int end = -1;
        int minIndex = -1;

        vector<int> res;

        for (std::size_t i = 0; i < a.size(); ++i) {

            preSum += a[i];

            if (preSum - minSum > maxSum) {
                maxSum = preSum - minSum;
                end = i;
                start = minIndex + 1;
            }

            if (preSum < minSum) {
                minIndex = i;
                minSum = preSum;
            }
        }

        // if (start < end) {
        //     res.push_back(start + 1);
        //     res.push_back(end);
        // }

        // if (start >= end) {
        //     res.push_back(start);
        //     res.push_back(start);
        // }
        res.push_back(start);
        res.push_back(end);
        return res;
    }
};



void testMaxSubArraySum()
{

    std::vector<int> nums =  {-3,1,3,-3,4};

    Solution s;

    vector<int> res  = s.continuousSubarraySum(nums);

    std::cout << "the final res: " << res.size() << std::endl;
    std::cout << "the final res: " << res[0] << " : " << res[1] << std::endl;

}
