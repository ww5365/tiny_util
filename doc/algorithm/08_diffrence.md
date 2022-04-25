#  差分

## 介绍

差分，是一种和前缀和相对的策略。这种策略是，令$$b_i = a_i - a_(i-1)$$，即相邻两数的差。
在每一个点上记录变化数值，因为有增加有减少，通过求和判断是否有超过指定容量的情况发生，超过则代表无法满足要求。
对于数组array[N]中的某一段进行增减操作，通过差分可在O（n）时间内完成。
如trips = [[2,1,5],[3,3,7]]
第一步：更新array[1] = 2, array[5] = -2;
第一个站点上车2人占用两个座位，第5个站点下车2人，空出两个座位。
第二步：更新array[3] = 3, array[7] = -3;
第三步：进行求和,得到结果array[] = {0,2,2,5,5,3,3,0};


## 使用场景和原理

### 场景
* 差分数组的主要适用场景是频繁对原始数组的某个区间的元素进行增减。
* 差分可以看作是前缀和的逆向过程。
* 差分数组本质上刻画的是相邻元素的相对大小关系，因此在差分数组某个索引对应的值变化后，原始数组从该索引之后的数据都会受到影响。

### 原理

参考：[差分数组技巧](https://leetcode-cn.com/problems/corporate-flight-bookings/solution/by-lfool-cc1i/)

index: 0  1  2  3  4
nums:  8  2  6  3  1

diff:  8  -6 4 -3 -2

* diff的构造：diff[0] = nums[0]  diff[i] = nums[i] - nums[i - 1]

* 还原当前元素的值： nums[i] = nums[i - 1] + diff[i]   nums[0] = diff[0]

* 如何修改数组区间[i, j]内的值? 比如：区间内的值，都 + 3 
  nums[i] : diff[i] += 3 nums[i] = nums[i-1] + diff[i] : 元素nums[i] 加上3
  nums[i + 1] 的值？ nums[i + 1] = nums[i] + diff[i + 1]   diff[i+1]不变，但nums[i]已经加上3了，所以累加的效应已经传递到下一步了。
  nums[j] 的值? 同理累加

  nums[j + 1] ?  diff[j+1] -= 3; nums[j + 1] = nums[j] + diff[j + 1] 消除索引 >= j + 1 之后的元素， +3 带来的传递效果影响, 因为diff[j+1] 减去了3

### 模板




## 区间求和的问题总结：

对于各类「区间求和」问题，该用什么方式进行求解，[区间和问题解决方案](https://leetcode-cn.com/problems/range-sum-query-mutable/solution/guan-yu-ge-lei-qu-jian-he-wen-ti-ru-he-x-41hv/)提到过。

此处可以再总结一下（加粗字体为最佳方案）：
数组不变，区间查询：前缀和、树状数组、线段树；
数组单点修改，区间查询：树状数组、线段树；
数组区间修改，单点查询：差分、线段树；
数组区间修改，区间查询：线段树。


>> 数组区间的问题求解： 能看到几个常用的算法：前缀和， 差分， 树状数组， 线段树
>> 其中，线段树 了解不深入？





## 代表题目：拼车（#1094）

车上最初有 capacity 个空座位。车 只能 向一个方向行驶（也就是说，不允许掉头或改变方向）

给定整数 capacity 和一个数组 trips ,  trip[i] = [numPassengersi, fromi, toi] 表示第 i 次旅行有 numPassengersi 乘客，接他们和放他们的位置分别是 fromi 和 toi 。这些位置是从汽车的初始位置向东的公里数。
当且仅当你可以在所有给定的行程中接送所有乘客时，返回 true，否则请返回 false。
输入：trips = [[2,1,5],[3,3,7]], capacity = 4
输出：false


思路：

1. 抽象出来，有点像，区间交集内，求最大和 <= capacity
2. 实现： 
记录区间的两个端点增减人数
累加区间内值的变动：计算交集的和： x1 + x2 + (-x2) + (-x1)  正数代表在某个时间点上车，负数代表在某个时间点下车  

``` c++
// 差分： 008_1094_pingche.cpp

constexpr int MAX_DISTANCE = 1001;
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {

        if (trips.size() <= 0) {
            return false;
        }
        vector<int> changes(MAX_DISTANCE, 0);
        for (int i = 0; i < trips.size(); ++i) {
            int persons = trips[i][0];
            int from = trips[i][1];
            int to = trips[i][2];
            changes[from] += persons;
            changes[to] -= persons; 
        }
        int curTotal = 0;
        for (auto &elem : changes) {
            curTotal += elem;
            if (curTotal > capacity) {
                return false;
            }
        }
        return true;

    }
};

```



## 触类旁通

###  7.3.1	航班预订统计(#1109)

这里有 n 个航班，它们分别从 1 到 n 进行编号。
有一份航班预订表 bookings ，表中第 i 条预订记录 bookings[i] = [firsti, lasti, seatsi] 意味着在从 firsti 到 lasti （包含 firsti 和 lasti ）的 每个航班 上预订了 seatsi 个座位。
请你返回一个长度为 n 的数组 answer，里面的元素是每个航班预定的座位总数。

输入：bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
输出：[10,55,45,25,25]
解释：
航班编号        1   2   3   4   5
预订记录 1 ：   10  10
预订记录 2 ：       20  20
预订记录 3 ：       25  25  25  25
总座位数：      10  55  45  25  25
因此，answer = [10,55,45,25,25]


```c++
    // 差分 008_1109_flight_booking.cpp
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        
        vector<int> result(n, 0);
        if (bookings.size() <= 0) {
            return result;
        }

        vector<int> diff(n, 0);
        for (int i = 0;i < bookings.size(); ++i) {
            int from = bookings[i][0] - 1;
            int to = bookings[i][1] - 1;
            int tickets = bookings[i][2];
            diff[from] += tickets;
            if (to + 1 < n) {
                diff[to + 1] -= tickets;
            }
        }
        result[0] = diff[0];
        for (int i = 1; i < n; ++i) {
            result[i] = result[i - 1]  + diff[i]; // o(n) 时间复杂度 区间[i,j] + 固定的数
        }

        return result;
    }

```

### 7.3.2	买卖股票的最佳时机(#121)

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


```c++

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

    // 双指针 贪心
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
                right = i;
            }
        }
        return result;
    }
    
    // dp
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

};
```


### 7.3.3	买卖股票的最佳时机 II(#122)

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


```c++

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

```


### 7.3.4	会议室 II （#253会员）

253 会议室II

[[s1,e1],...] 有一组预定会议室的安排，s1 开始时间，e1标识结束时间， 为避免会议室冲突，并充分利用会议室资源，请计算至少需要多少会议室满足会议安排。

输入：{{0, 30}{5, 10}{15, 20}}
输出：2

>> 问题抽象： 求区间交集的最大个数

```c++

const int MAX_LAST_TIME = 366;

class solution {
public:

 int minMeetingRooms(vector<vector<int>>& intervals) {

    if (intervals.size() <= 0) {
        return 0;
    }

    vector<int> diff(MAX_LAST_TIME, 0);  // 空间优化思路：如果时间数据大，可以使用hash来存值
    for (int i = 0; i < intervals.size(); ++i) {
        int start = intervals[i][0];
        int end = intervals[i][1] + 1;
        diff[start] += 1;
        if (end < MAX_LAST_TIME) {
            diff[end] -= 1;
        }
    }

    int result = 0;
    int interNum = 0;
    for (int i = 0; i < diff.size(); ++i) {
        interNum += diff[i];
        result = std::max(result, interNum);
    }

    return result;
 }
};



```



