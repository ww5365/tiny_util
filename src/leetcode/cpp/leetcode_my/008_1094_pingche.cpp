#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>


using namespace std;

/*

1094. 拼车

车上最初有 capacity 个空座位。车 只能 向一个方向行驶（也就是说，不允许掉头或改变方向）
给定整数 capacity 和一个数组 trips ,  trip[i] = [numPassengersi, fromi, toi] 表示第 i 次旅行有 numPassengersi 乘客，接他们和放他们的位置分别是 fromi 和 toi 。这些位置是从汽车的初始位置向东的公里数。
当且仅当你可以在所有给定的行程中接送所有乘客时，返回 true，否则请返回 false。

示例 1：
输入：trips = [[2,1,5],[3,3,7]], capacity = 4
输出：false

示例 2：
输入：trips = [[2,1,5],[3,3,7]], capacity = 5
输出：true

向东行驶最大公里：<= 1000

思路：

1. 抽象出来，有点像，区间交集内，求最大和 <= capacity

2. 实现： 
记录区间的两个端点增减人数

累加区间内值的变动：计算交集的和： x1 + x2 + (-x2) + (-x1)  正数代表在某个时间点上车，负数代表在某个时间点下车  

*/

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

void TestCarPooling()
{
    vector<vector<int>> tirps = {{2,1,5}, {3,3,7}};
    Solution s;
    cout << "-----------TestCarPooling----------------" << endl;
    
    bool result = s.carPooling(tirps, 5);
    
    cout << " result1 : " <<  result << endl;

    result = s.carPooling(tirps, 4);

    cout << " result2 : " <<  result << endl;
    cout << "-----------TestCarPooling finished-------------" << endl;
}