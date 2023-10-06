#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>

#include <iterator>


using namespace std;

/*

leetcode 121 https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/
121. 买卖股票的最佳时机
给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。
返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。


输入：[7,1,5,3,6,4]
输出：5
解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。

思路：

* 差分

1：生成差分数组，diff[0] = 0 diff[i] = nums[i] - nums[i - 1]
2: 求diff数组，i>=1 之后的连续子数组的最大和; 最大和> 0 : 即为最大利润 否则：利润为0
   7   1  5  3  6  4
   0  -6  4  -2 3  -2
      -6 -2  -4 -1 -3

* 单调栈

1： 最小的元素在栈底，自下而上，单调递增
2： 出栈时，计算出栈元素与栈底的差值，并计算最大利润
3： 最后增加一个哨兵元素：0


* 同向双指针
1: left 到目前为止，向左看，最小的元素
2： right 

* dp 算法
dp[i] 表示前i天的最大利润，因为我们始终要使利润最大化，则：dp[i]=max(dp[i−1],prices[i]−minprice)

*/

class Solution {
public:
    // 差分 + 前缀和 时间：o(n), 空间：o(n)
    int maxProfit(vector<int>& prices) {

        if(prices.size() <= 1) {
            return 0;
        }
        vector<int> diff( prices.size(), 0);
        for (int i = 1; i < prices.size(); ++i) {
            diff[i] = prices[i] - prices[i - 1];
        }
        
        // 计算差分数组的最大连续子数组的和: 前缀和
        int sum = 0;
        int minSum = 0;
        int maxSeqSum = std::numeric_limits<int>::min();
        for (int i = 1; i < diff.size(); ++i) {
            sum += diff[i];
            maxSeqSum = std::max(maxSeqSum, sum - minSum);
            minSum = std::min(minSum, sum);
        }
        if (maxSeqSum <= 0) {
            return 0;
        }
        return maxSeqSum;
    }

    // 单调栈 o(n)  空间：o(n)

    int maxProfit2(vector<int>& prices) {
        vector<int> st;
        int result = 0;
        prices.push_back(0); //放入哨兵0
        for (int i = 0; i < prices.size(); ++i) {
            while (!st.empty() && st.back() >= prices[i]) {
                result = std::max(result, st.back() - st.front());
                st.pop_back();
            }
            st.push_back(prices[i]);
        }
        return result;
    }

    // 双指针 贪心 时间：o(n) 空间: o(1)
    int maxProfit3(vector<int>& prices) {

        int left = 0;
        int right = 0;
        int result = 0;

        for (int i = 0; i < prices.size(); ++i) {
            int diff = prices[i] - prices[left];  // left指向最小的元素
            if (diff > 0) {
                if (diff > result) {
                    right = i;      // right指向最大的元素
                    result = diff;  
                }
            } else { //当前元素，比最小的元素都要小
                left = i;
                right = i; // 也可以不更新right ，不影响结果
            }
        }
        return result;
    }
    
    // dp 时间o(n) 空间o(n) 能否优化空间复杂度：o(1)?

    int maxProfit4(vector<int>& prices) {
        // dp[i] 表示前i天的最大利润，因为我们始终要使利润最大化，则：dp[i]=max(dp[i−1],prices[i]−minprice)

        if (prices.size() <= 1) {
            return 0;
        }
        vector<int> dp(prices.size(), 0);
        dp[0] = 0;
        int minPrice = prices[0];
        for (int i = 1; i < prices.size(); ++i) {
            dp[i] = std::max(dp[i - 1] , prices[i] - minPrice);
            minPrice = std::min(minPrice, prices[i]);
        }
        return dp[prices.size() - 1];
    }

     // dp 优化了空间复杂度
    int maxProfit5(vector<int>& prices) {
        // dp[i] 表示前i天的最大利润，因为我们始终要使利润最大化，则：dp[i]=max(dp[i−1],prices[i]−minprice)

        if (prices.size() <= 1) {
            return 0;
        }
        // vector<int> dp(prices.size(), 0);
        int preDp = 0; //前i-1天最大利润
        int res = 0;
        // dp[0] = 0;
        int minPrice = prices[0];
        for (int i = 1; i < prices.size(); ++i) {
            // res = std::max(preDp, prices[i] - minPrice);
            // preDp = std::max(preDp, res);

            if (preDp >= prices[i] - minPrice) {
                res = preDp; //保持i-1天的最大利润
            } else {
                res = prices[i] - minPrice;
                preDp = res; // 更新为当前的利润
            }
            minPrice = std::min(minPrice, prices[i]);
        }
        return res;

    }

};


void TestBuyStock1()
{
    vector<int> prices = {2, 4, 1};
    Solution s;
    cout << "-----------TestBuyStock1----------------" << endl;
    int result =  s.maxProfit(prices);
    cout << " result1 : " <<  result << endl;
    
    int result2 =  s.maxProfit2(prices);
    cout << " result2 : " <<  result2 << endl;
    
    int result3 =  s.maxProfit3(prices);
    cout << " result3 : " <<  result3 << endl;

    int result4 =  s.maxProfit4(prices);

    cout << " result4 : " <<  result4 << endl;

    cout << "-----------TestBuyStock1 finished-------------" << endl;
}
