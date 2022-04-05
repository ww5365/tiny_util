#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>


using namespace std;

/*

MWCS 展共有 N 个展厅，每个展厅的报名人数记于数组 nums。因疫情原因，所有展厅参展总人数上限为 cnt。若报名人数之和大于 cnt，则需限制参展人数。请计算单个展厅的 最大 参展人数 limit，使得参展总人数不超过 cnt，参展限制规则为：

对于报名人数不超过 limit 的展厅，凡报名即参展；

对于报名人数超过 limit 的展厅，则均要求 limit 名人员参展。

若报名人数之和小于等于 cnt，此时不需要限制参展人数，请返回 -1。

请返回 limit 的最大值或 -1。

样例1：

输入：nums = [1,4,2,5,5,1,6]，cnt = 13

输出：2

解释：报名总人数为24，大于cnt，需要限制参展人数。当 limit = 2 时，展厅报名人数大于 2 的，均有 2 人参加，参展人数总和为 1+2+2+2+2+1+2 = 12，不超过 13；若limit = 3 时，参展人数总和为 1+3+2+3+3+1+3 = 16，则超过 13。因此返回 2。

样例2

输入：nums = [1,3,2,1]，cnt = 197

输出：-1

解释：所有报名人数之和为 7，小于等于 197，此时不需要限制参展人数，因此返回 -1。

样例3

输入：nums = [1,1]，cnt = 1

输出：0

解释：limit = 0 时，无人参展即满足规则；若 limit = 1，则参展人数为 1 + 1 = 2，超过 cnt。


*/


class Solution {
public:
    int MaxPersonsLimit(vector<int>& nums, int cnt)
    {

        int totalSum = 0;
        int maxNum = 0; // 展厅最大人数
        for (const auto &elem : nums) {
            totalSum += elem;
            maxNum = std::max(maxNum, elem);
        }
        if (totalSum <= cnt) {
            return -1;
        }
        // 超过人数限制时，使用二分搜索最大人数限制；搜索空间[0, maxNum]
        int start = 0;
        int end = maxNum;
        int result = 0;
        while (start <= end) {
            int mid = start + (end - start) / 2;
            if (check(nums, mid, cnt)) {
                start = mid + 1;
                result = std::max(result, mid);
            } else {
                end = mid - 1;
            }
        }
        return result;
    }

private:
    bool check(const vector<int> &nums, int limit, int cnt)
    {
        int realCnt = 0;
        for (auto &elem : nums) {
            realCnt += ((elem > limit) ? limit : elem);
        }
        return  realCnt <= cnt ? true : false ;
    }
};

void TestMaxPersonsLimit()
{

    Solution s;

    cout << "-----------TestMaxPersonsLimit----------------" << endl;
    int result = -2;
    vector<int> nums = { 1,4,2,5,5,1,6};
    int cnt = 13;
    result = s.MaxPersonsLimit(nums, cnt);
    cout << "TestMaxPersonsLimit result1 = " << result << endl;
    
    vector<int> nums2 = { 1,3, 2, 1};
    int cnt2 = 197;
    result = s.MaxPersonsLimit(nums2, cnt2);
    cout << "TestMaxPersonsLimit result2 = " << result << endl;
    
    vector<int> nums3 = { 1, 1};
    int cnt3 = 1;
    result = s.MaxPersonsLimit(nums3, cnt3);
    cout << "TestMaxPersonsLimit result3 = " << result << endl;

    cout << "-----------TestMaxPersonsLimit finished-------------" << endl;
}