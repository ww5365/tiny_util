#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>

#include <iterator>


using namespace std;

/*


1109. 航班预订统计

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

*/

class Solution {
public:

    // 暴力
    vector<int> corpFlightBookings2(vector<vector<int>>& bookings, int n) {
        vector<int> result(n, 0);
        if (bookings.size() <= 0) {
            return result;
        }

        for (int i = 0;i < bookings.size(); ++i) {
            int from = bookings[i][0];
            int to = bookings[i][1];
            int tickets = bookings[i][2];
            for (int j = from; j <= to; ++j) { // 暴力解法，leetcode上会超时 : o(K*n)
                result[j - 1] += tickets;  // 怎么更有技巧的实现的：区间[i,j]上的 +val  这个固定的数 ?
            }
        }
        return result;
    }

    // 差分
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
};

void TestCorpFlightBookings()
{
    vector<vector<int>> bookings = {{1,2,10},{2,3,20},{2,5,25}};
    Solution s;
    cout << "-----------TestCorpFlightBookings----------------" << endl;
    
    vector<int> vec = s.corpFlightBookings(bookings, 5);
    
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));

    cout << endl << "-----------TestCorpFlightBookings finished-------------" << endl;
}