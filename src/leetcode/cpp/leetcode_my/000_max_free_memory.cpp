#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>

#include <iterator>


using namespace std;

/*

某系统中有一空间连续的内存，被划分成多个大小相同的内存块。内存的使用状态记录在字符串 memory 中，每个内存块的状态用字符 x 或 . 表示，其中：

. 表示该内存块空闲；

x 表示该内存块被使用，x 为小写字母。

现在可释放其中 最多 cnt 个内存块（即字符串中的 x 变成 .），以获得一块空间连续的、且 最长的 空闲内存，请计算并返回该最长空闲内存的内存块数量。

*/



class Solution {
public:
    int solve(const string &memory, int cnt)
    {
        if (memory.size() <= cnt) {
            return cnt;
        }
        int result = 0;
        int left = 0;
        int xCnt = 0;
        for (int right = 0; right < memory.size(); ++right) {
            if (memory[right] == 'x') {
                ++xCnt;
            }
            while (xCnt > cnt) {
                if (memory[left ++] == 'x'){
                    --xCnt;
                }
            }
            result = std::max(result, right - left + 1);
        }

        return result;
    }
};

void TestMaxFreeMemory()
{
    Solution s;
    cout << "-----------TestMaxFreeMemory----------------" << endl;

    string s1 = "..x..x..xx...";
    int cnt = 2;
    int result = s.solve(s1, cnt);
    cout << "result1: " << result << endl;

    string s2 = "....x.";
    cnt = 3;
    result = s.solve(s2, cnt);
    cout << "result2: " << result << endl;

    cout << "-----------TestMaxFreeMemory finished-------------" << endl;
}

