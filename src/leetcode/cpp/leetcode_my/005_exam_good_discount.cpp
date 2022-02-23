#include "01_all.h"

#include <vector>
#include <unordered_map>
#include <cassert>
#include <iostream>

using namespace std;

/*

price[6] = {10,5,8,8,6,3}; // 商品 0 单价10， 商品1 单价5
pro[][] = {
         {0， 7}，
         {4， 10}，
         {2, 6，1,  9}，
         {5，2}
};
dis[] = {4, 3, 5, 1};
上面共有4个折扣规则，1.  0号商品买7个，可以减4元，2. 4号商品买10个可以减3元。 3.  2号商品买6个 && 1号商品买9个可以减5元
order[] = {2,17,3,10,1,27,5,2,4,9}； // 顾客需要买的商品列表
问题： 按最大折扣后，用户最终需要支付多少？

*/

class Solution {
public:
    bool canDis(vector<int> &pro, unordered_map<int, int> &orders)
    {
        for (int j = 1; j < pro.size(); j += 2) {
            if (pro[j] > orders[pro[j - 1]]) {
                // 如果不检查，直接返回map[key]，可能会出现意想不到的行为。如果map包含key，没有问题.
                // 如果map不包含key，使用下标有一个危险的副作用，会在map中插入一个key的元素，value取默认值，返回value。也就是说，map[key]不可能返回null;
                // 這裡默認是0
                return false;
            }
        }
        return true;
    }

    void dfs(int idx, vector<vector<int>> &pro, vector<int> &dis, unordered_map<int, int> &orders, int &maxDisc,
        int curDis)
    {
        if (maxDisc < curDis) {
            maxDisc = curDis;
        }

        if (idx >= pro.size()) {
            return;
        }

        for (int i = idx; i < pro.size(); ++i) {
            if (canDis(pro[i], orders)) {
                for (int j = 0; j < pro[i].size(); ++j) {
                    int num = pro[i][j];
                    int cnt = pro[i][++j];
                    orders[num] -= cnt;
                }
                dfs(i + 1, pro, dis, orders, maxDisc, curDis + dis[i]);
                for (int j = 0; j < pro[i].size(); ++j) {
                    int num = pro[i][j];
                    int cnt = pro[i][++j];
                    orders[num] += cnt;
                }
            }
        }
    }

    int solve(vector<int> &price, vector<vector<int>> &pro, vector<int> &dis, vector<int> &order)
    {
        int res = 0;
        unordered_map<int, int> orders;
        for (int i = 0; i < order.size(); i += 2) {
            res += price[order[i]] * order[i + 1];
            orders.insert({ order[i], order[i + 1] });
        }

        int maxDisc = 0;
        dfs(0, pro, dis, orders, maxDisc, 0);

        return res - maxDisc;
    }
};

void TestExam1119One()
{
    vector<int> price = { 10, 5, 8, 8, 6, 3 };
    vector<vector<int>> pro = { { 0, 7 }, { 4, 10 }, { 2, 6, 1, 9 }, { 5, 2 } };
    vector<int> dis = { 4, 3, 5, 1 };
    // vector<int> order = { 2, 17, 3, 10, 1, 27, 5, 2, 4, 9 };
    vector<int> order = { 0, 14};
    cout << "------------TestExam1119One------------" << endl;

    Solution solution;
    int res = solution.solve(price, pro, dis, order);
    cout << "TestExam1119One result: " << res << endl;
    // assert(res == 405);
}