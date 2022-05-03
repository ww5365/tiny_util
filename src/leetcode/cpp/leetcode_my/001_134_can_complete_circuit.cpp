#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>

#include <iterator>

#include <unordered_map>


using namespace std;

/*

134. 加油站  https://leetcode.cn/problems/gas-station/

在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。
你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第
i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。

给定两个整数数组 gas 和 cost ，如果你可以绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1 。如果存在解，则 保证
它是 唯一 的。


思路：

1. 贪心算法，局部最优-->全局最优

*/

class Solution {
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int len = gas.size();
        int spare = 0;
        int minSpare = std::numeric_limits<int>::max();
        int minIndex = 0;

        for (int i = 0; i < len; i++) {
            spare += gas[i] - cost[i];
            if (spare < minSpare) {
                minSpare = spare;
                minIndex = i;
            }
        }

        return spare < 0 ? -1 : (minIndex + 1) % len;
    }
};

void TestCanCompleteCircuit()
{
    cout << "-----------TestCanCompleteCircuit----------------" << endl;
    Solution s;
    vector<int> gas = { 1, 2, 3, 4, 5 };
    vector<int> cost = { 3, 4, 5, 1, 2 };

    int result = s.canCompleteCircuit(gas, cost);

    std::cout << "TestCanCompleteCircuit result : " << result << endl;
}
