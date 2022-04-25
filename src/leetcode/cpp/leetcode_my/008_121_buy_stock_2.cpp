#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>

#include <iterator>


using namespace std;

/*

122. 买卖股票的最佳时机 II

给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。
在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。
返回 你能获得的 最大 利润 。

输入：prices = [7,1,5,3,6,4]
输出：7
解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。
     随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6 - 3 = 3 。
     总利润为 4 + 3 = 7 。


输入：prices = [1,2,3,4,5]
输出：4
解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。
     总利润为 4 。

* 差分：

1、生成差分数组，发现规律： ？ diff[i] > 0 都是有利润的

2、 差分数组中 >0 的元素，都加起来，就是获取的最大利润？




*/

class Solution {
public:
    int MaxProfit(vector<int>& prices) {

        std::size_t n = prices.size();
        if (n <= 1) {
            return 0;
        }
        vector<int> diff(n, 0);
        int result = 0;
        for (std::size_t i = 1; i < n; ++i) {
            diff[i] = prices[i] - prices[i - 1];
        }
        for (std::size_t j = 0; j < n; ++j) {
            if (diff[j] > 0) {
                result += diff[j];
            }            
        }
        return result;
    }
};



void TestBuyStock2()
{
    // vector<int> prices = {2, 4, 1};
    Solution s;
    vector<int> prices = {7, 1, 5,  3, 6, 4};
    cout << "-----------TestBuyStock2----------------" << endl;
    int result =  s.MaxProfit(prices);
    cout << " result: " <<  result << endl;
    
    cout << "-----------TestBuyStock2 finished-------------" << endl;
}