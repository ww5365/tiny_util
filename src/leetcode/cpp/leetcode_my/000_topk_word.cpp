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

某系统中有一空间连续的内存，被划分成多个大小相同的内存块。内存的使用状态记录在字符串 memory 中，每个内存块的状态用字符 x 或 . 表示，其中：

. 表示该内存块空闲；

x 表示该内存块被使用，x 为小写字母。

现在可释放其中 最多 cnt 个内存块（即字符串中的 x 变成 .），以获得一块空间连续的、且 最长的 空闲内存，请计算并返回该最长空闲内存的内存块数量。

*/


class Solution {
public:

    vector<string> TopKFrequent(vector<string>& words, int k)
    {
        vector<string> res(k);
        unordered_map<string ,int> freq;

        auto cmp = [](pair<string, int> &a, pair<string, int> &b) {
            return a.second > b.second || (a.second == b.second && a.first < b.first); 
        };
        priority_queue<pair<string, int>, deque<pair<string, int>>, decltype(cmp)> qu(cmp);

        for (auto word : words) ++freq[word];

        for (auto f : freq) {
            qu.push(f);
            if (qu.size() > k) {
                qu.pop(); // 保持前k大的数据
            }
        }

        for (int i = res.size() - 1; i >= 0; --i) {
            res[i] = qu.top().first;
            qu.pop();
        }
        return res;
    }
};

void TestTopKWords()
{
    Solution s;
    cout << "-----------TestTopKWords----------------" << endl;
    vector<string> words = {"the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"};
    int k = 4;
    vector<string> res = s.TopKFrequent(words, k);
    std::copy(res.begin(), res.end(), std::ostream_iterator<string>(std::cout, " "));
    cout << endl << "-----------TestTopKWords finished-------------" << endl;
}

