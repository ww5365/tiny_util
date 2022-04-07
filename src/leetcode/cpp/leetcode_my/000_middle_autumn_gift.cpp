#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>

#include <iterator>
#include <unordered_map>


using namespace std;

/*

公司为了迎接即将到来的中秋节，需要挑选一些产品组成中秋礼盒来发放给大家，产品 sales
以三元组的方式给出，分别是**[产品id，产品成本，产品利润]**，不同产品的数量是有限的，以二元组 [产品id, 限定数量]
的方式给出，存储在 limit 列表中。礼盒的选取规则如下：

优先选取产品成本最低的；
如成本相同，选取产品利润较高的；
若成本和利润均相同，选取产品 id 较小的
需要选取的礼盒数量为 cnt ，若能按要求选取出要求数量的礼盒，则返回不同产品的在sales数组中的 index
排序后的结果；否则返回空列表。

核心实现：多优先级的索引下标排序 ?



*/


class Solution {
public:
    vector<int> GetSalesIdx(vector<vector<int>> &sales, int cnt, vector<vector<int>> &limit)
    {
        vector<int> result;
        // 实现基于多个优先级的下标排序
        vector<int> indexVec(sales.size());
        for (int i = 0; i < sales.size(); ++i) {
            indexVec[i] = i;
        }
        sort(indexVec.begin(), indexVec.end(), [&sales](int leftIdx, int rightIdx) {
            if (sales[leftIdx][1] != sales[rightIdx][1]) {
                return sales[leftIdx][1] < sales[rightIdx][1]; // 成本升序
            } else if (sales[leftIdx][2] != sales[rightIdx][2]) {
                return sales[leftIdx][2] > sales[rightIdx][2]; // 利润降序
            }
            return leftIdx <= rightIdx;
        });
        // std::copy(indexVec.begin(), indexVec.end(), std::ostream_iterator<int>(std::cout, " "));
        // 构建hash词典
        unordered_map<int, int> limitDict;
        for (auto elem : limit) {
            limitDict.insert(make_pair(elem[0], elem[1]));
        }
        for (auto idx : indexVec) {
            auto itor = limitDict.find(sales[idx][0]);
            if (itor != limitDict.end()) {
                if (itor ->second > 0) {
                    result.push_back(idx);
                    itor->second --;
                }
            } else {
                result.push_back(idx);
            }
        }
        if (result.size() < cnt) {
            result.reserve(0);
        }
        sort(result.begin(), result.end());
        return result;
    }
};

void TestGetSalesIdx()
{
    Solution s;

    cout << "-----------TestGetSalesIdx----------------" << endl;

    vector<vector<int>> sales = { { 100, 30, 10 }, { 200, 10, 10 }, { 100, 50, 20 },
                                  { 200, 10, 10 }, { 400, 20, 20 }, { 200, 20, 10 } };

    vector<vector<int>> limit = { { 100, 1 }, { 200, 1 }, { 400, 2 } };
    Solution solution;
    auto res = solution.GetSalesIdx(sales, 3, limit);

    for (const auto &item : res) {
        cout << item << endl;
    }

    cout << "-----------TestGetSalesIdx finished-------------" << endl;
}