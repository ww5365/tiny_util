
/*
 * leetcode: 121 122 123 188 309 714   团灭stock利润

参考：
https://labuladong.github.io/algo/di-er-zhan-a01c6/yong-dong--63ceb/yi-ge-fang-3b01b/

状态转移：

1). 初始状态：
dp[-1][...][0] = dp[...][0][0] = 0
dp[-1][...][1] = dp[...][0][1] = -infinity

说明：
dp[-1][...][0] = 0
解释：因为 i 是从 0 开始的，所以 i = -1 意味着还没有开始，这时候的利润当然是 0。

dp[-1][...][1] = -infinity
解释：还没开始的时候，是不可能持有股票的。
因为我们的算法要求一个最大值，所以初始值设为一个最小值，方便取最大值。

dp[...][0][0] = 0
解释：因为 k 是从 1 开始的，所以 k = 0 意味着根本不允许交易，这时候利润当然是 0。

dp[...][0][1] = -infinity
解释：不允许交易的情况下，是不可能持有股票的。
因为我们的算法要求一个最大值，所以初始值设为一个最小值，方便取最大值。


2). 状态转移方程：
dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])

1、我昨天就没有持有，且截至昨天最大交易次数限制为 k；然后我今天选择 rest，所以我今天还是没有持有，最大交易次数限制依然为 k。
2、我昨天持有股票，且截至昨天最大交易次数限制为 k；但是今天我 sell 了，所以我今天没有持有股票了，最大交易次数限制依然为 k。


dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])

1、我昨天就持有着股票，且截至昨天最大交易次数限制为 k；然后今天选择 rest，所以我今天还持有着股票，最大交易次数限制依然为 k。
2、我昨天本没有持有，且截至昨天最大交易次数限制为 k - 1；但今天我选择 buy，所以今天我就持有股票了，最大交易次数限制为 k。

说明：

1. 时刻牢记「状态」的定义，状态 k 的定义并不是「已进行的交易次数」，而是「最大交易次数的上限限制」。
如果确定今天进行一次交易，且要保证截至今天最大交易次数上限为 k，那么昨天的最大交易次数上限必须是 k - 1

2. 以前我以为在 sell 的时候给 k 减小 1 和在 buy 的时候给 k 减小 1 是等效的，
但细心的读者向我提出质疑，经过深入思考我发现前者确实是错误的，因为交易是从 buy 开始，如果 buy 的选择不改变交易次数 k 的话，会出现交易次数超出限制的的错误。
（没有太明白，没有分析过类似case）





 */

#include "01_all.h"
#include <deque>
#include <queue>
#include <iostream>
#include <limits>

#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

class Solution {
public:    

    /*
    * leetcode : 122 https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/

    给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。
    在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。
    返回 你能获得的 最大 利润 。
    
    示例 1：
    输入：prices = [7,1,5,3,6,4]
    输出：7
    解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。
    随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6 - 3 = 3 。
    总利润为 4 + 3 = 7 。
    * 
    */


    // 直接使用dp实现
    int maxProfit(vector<int>& prices) {

        /* dp 算法： 交易次数没有限制
           
           状态转移：i >= 0  0 空仓  1 满仓  dp[i][0]: 截止第i天空仓最大利润
           dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])  
           dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])   原来空仓，第i天买入,消耗prices[i]

           初始状态： i = -1
           dp[-1][0] = 0
           dp[-1][1] = minValue  

           结果：dp[n][0] 
        */
        int n = prices.size();
        vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
        for (std::size_t i = 0; i < prices.size(); ++i) {

            if (i == 0) {
                // 初始态
                dp[i][0] = 0;
                dp[i][1] = -prices[i];
                continue;
            }

            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);  // 落袋/卖出
            dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i]);  // 换股/持股
        }
        return dp[n - 1][0];
    }

    // dp 优化空间复杂度
    int maxProfit2(vector<int>& prices) {

        int n = prices.size();
        if (n <= 1) return 0;

        int maxProfit0 = 0; // 空仓时最大利润
        int maxProfit1 = -prices[0]; // 满仓最大利润

        for (int i = 1; i < n; ++i) {
            int tmp = maxProfit0;
            maxProfit0 = std::max(maxProfit0, maxProfit1 + prices[i]);
            maxProfit1 = std::max(maxProfit1, tmp - prices[i]);
        }
        return maxProfit0;
    }
};

/*
309. 买卖股票的最佳时机含冷冻期
https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/

给定一个整数数组prices，其中第  prices[i] 表示第 i 天的股票价格 。​
设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:
卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。
注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

示例 1:
输入: prices = [1,2,3,0,2]
输出: 3 
解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出

*/


class Solution2 {
public:
    int maxProfit(vector<int>& prices) {

        /* dp 算法： 交易次数没有限制,但交易完成后，有1天的冷冻期
           
           状态转移：i >= 0  0 空仓  1 满仓  
           dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])  
           dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i])   原来空仓，相隔1天才能买入,所以是i-2，消耗prices[i]

           初始状态： i = 0
           dp[-1][0] = 0
           dp[-1][1] = minValue
           dp[-2][0] = 0  

           结果：dp[n][0] 
        */

        int n = prices.size();
        if (n <= 1) return 0;
        vector<vector<int>> dp(n, vector<int>(2, 0));
        for (std::size_t i = 0; i < n; ++i) {

            if (i == 0) {
                // 初始态
                dp[i][0] = 0;
                dp[i][1] = -prices[i];
                continue;
            }

            if (i == 1) {
                dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
                dp[i][1] = std::max(dp[i - 1][1], -prices[i]); // dp[-1][0] = 0
                continue;
            }

            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);  // 落袋/卖出
            dp[i][1] = std::max(dp[i - 1][1], dp[i - 2][0] - prices[i]);  // 换股/持股
        }
        return dp[n - 1][0];
    }

        // dp 优化空间复杂度
    int maxProfit2(vector<int>& prices) {

        int n = prices.size();
        if (n <= 1) return 0;
        int maxProfit0 = 0; // 空仓时最大利润
        int maxProfit1 = -prices[0]; // 满仓最大利润(赔的最少)
        int preMaxProfit0 = 0;  // 空仓前1个最大利润
        
        for (int i = 1; i < n; ++i) {
            int tmp = maxProfit0;
            maxProfit0 = std::max(maxProfit0, maxProfit1 + prices[i]);
            maxProfit1 = std::max(maxProfit1, preMaxProfit0 - prices[i]);
            preMaxProfit0 = tmp;
        }
        return maxProfit0;
    }
    
};


/*
https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/

714. 买卖股票的最佳时机含手续费

给定一个整数数组 prices，其中 prices[i]表示第 i 天的股票价格 ；整数 fee 代表了交易股票的手续费用。

你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。

返回获得利润的最大值。

注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。

 

示例 1：

输入：prices = [1, 3, 2, 8, 4, 9], fee = 2
输出：8
解释：能够达到的最大利润:  
在此处买入 prices[0] = 1
在此处卖出 prices[3] = 8
在此处买入 prices[4] = 4
在此处卖出 prices[5] = 9
总利润: ((8 - 1) - 2) + ((9 - 4) - 2) = 8



*/

class Solution3 {
public:
    int maxProfit(vector<int>& prices, int fee) {
        /* dp 算法： 交易次数没有限制, 有交易费用
           
           状态转移：i >= 0  0 空仓  1 满仓  
           dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])  
           dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i] -fee)   原来空仓，第i天买入,消耗prices[i],同时把费用加入到成本

           初始状态： i = -1
           dp[-1][0] = 0
           dp[-1][1] = minValue  

           结果：dp[n][0] 
        */
        int n = prices.size();
        vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
        for (std::size_t i = 0; i < prices.size(); ++i) {

            if (i == 0) {
                // 初始态
                dp[i][0] = 0;
                dp[i][1] = -prices[i] - fee;
                continue;
            }

            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);  // 落袋/卖出
            dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i] - fee);  // 持股/换股买入
        }
        return dp[n - 1][0];
    }

        // dp 优化空间复杂度
    int maxProfit2(vector<int>& prices, int fee) {

        int n = prices.size();
        if (n <= 1) return 0;

        int maxProfit0 = 0; // 空仓时最大利润
        int maxProfit1 = -prices[0] - fee; // 满仓最大利润

        for (int i = 1; i < n; ++i) {
            int tmp = maxProfit0;
            maxProfit0 = std::max(maxProfit0, maxProfit1 + prices[i]);
            maxProfit1 = std::max(maxProfit1, tmp - prices[i] - fee);
        }
        return maxProfit0;
    }
};

/*
https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iii/

123. 买卖股票的最佳时机 III
困难
1.6K
相关企业
给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。       
设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 
示例 1:

输入：prices = [3,3,5,0,0,3,1,4]
输出：6
解释：在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。
     随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3 。

*/

class Solution4 {
public:
    int maxProfit(vector<int>& prices) {
    
    /*
    状态转移方程：

    dp[i][k][0] : 第i天，交易次数最大限制为k，当天空仓时，最大利润
    dp[i][k][1] : 第i天，交易次数最大限制为k，当天满仓时，持仓时的最大利润 
    
    dp[i][k][0] = std::max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
    dp[i][k][1] = std::max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])

    初始状态 i = 0 ,  k = 0:
    dp[0][0][0] = 0  
    dp[0][1][0] = 0  
    dp[0][2][0] = 0

    dp[0][0][1] = 0  
    dp[0][1][1] = -prices[0]
    dp[0][2][1] = -prices[0]

    */

    int n = prices.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(3, vector<int>(2))); //三维辅助数组

    dp[0][0][0] = 0;
    dp[0][1][0] = 0; 
    dp[0][2][0] = 0;

    dp[0][0][1] = 0;  
    dp[0][1][1] = -prices[0];
    dp[0][2][1] = -prices[0];

    for (int i = 1; i < n; ++i) {
        for (int k = 2; k >= 1; --k) {
        
            dp[i][k][0] = std::max(dp[i-1][k][0], dp[i-1][k][1] + prices[i]);
            dp[i][k][1] = std::max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i]);

            if ( k-1 == 0){
                std::cout << "k - 1:  " << dp[i-1][k-1][0] << std::endl;
            }
        }
    }

    return dp[n-1][2][0];

    }
    
    int maxProfit2(vector<int>& prices) {

        // 丝滑的代码实现
        int p10 = 0;
        int p20 = 0;
        int p11 = -prices[0];
        int p21 = -prices[0];
        int p00 = 0;
        int n = prices.size();

        for (int i = 0; i < n; ++i) {

            p20 = std::max(p20, p21 + prices[i]);
            p21 = std::max(p21, p10 - prices[i]);
            p10 = std::max(p10, p11 + prices[i]);
            p11 = std::max(p11, -prices[i]);

        }

        return p20;

    }
};



void testAllStock()
{

    vector<int> nums = {7,1,5,3,6,4};

    std::copy(nums.begin(), nums.end(), std::ostream_iterator<int>(std::cout, ","));
    std::cout << std::endl;
    
    Solution s1;
    int maxProfit11 = s1.maxProfit(nums);
    int maxProfit12 = s1.maxProfit2(nums);
    std::cout << "s1 max profit is :" << maxProfit11  << " : " << maxProfit12<< std::endl;

    Solution2 s2;
    int maxProfit21 = s2.maxProfit(nums);
    int maxProfit22 = s2.maxProfit2(nums);
    std::cout << "s2 max profit is :" << maxProfit21  << " : " << maxProfit22<< std::endl;

    vector<int> nums4 = {3,3,5,0,0,3,1,4};

    Solution4 s4;
    int maxProfit41 = s4.maxProfit(nums4);
    int maxProfit42 = s4.maxProfit2(nums4);

    std::cout << "s4 max profit is :" << maxProfit41  << " : " << maxProfit42<< std::endl;
    


}
