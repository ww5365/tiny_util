/**

给定一个整数数组 ribbons 和一个整数 k，数组每项 ribbons[i] 表示第 i 条绳子的长度。
对于每条绳子，你可以将任意切割成一系列长度为正整数的部分，或者选择不进行切割。
例如，如果给你一条长度为 4 的绳子，你可以：
保持绳子的长度为 4 不变；
切割成一条长度为 3 和一条长度为 1 的绳子；
切割成两条长度为 2 的绳子；
切割成一条长度为 2 和两条长度为 1 的绳子；
切割成四条长度为 1 的绳子。
你的任务是最终得到 k 条完全一样的绳子，他们的长度均为相同的正整数。
如果绳子切割后有剩余，你可以直接舍弃掉多余的部分。
对于这 k 根绳子，返回你能得到的绳子最大长度；
如果你无法得到 k 根相同长度的绳子，返回 0。


输入: ribbons = [9,7,5], k = 3
输出: 5

解释:
 把第一条绳子切成两部分，一条长度为 5，一条长度为 4；
 把第二条绳子切成两部分，一条长度为 5，一条长度为 2；
 第三条绳子不进行切割；
现在，你得到了 3 条长度为 5 的绳子。


输入: ribbons = [7,5,9], k = 4
输出: 4

解释:
 把第一条绳子切成两部分，一条长度为 4，一条长度为 3；
 把第二条绳子切成两部分，一条长度为 4，一条长度为 1；
 把第二条绳子切成三部分，一条长度为 4，一条长度为 4，还有一条长度为 1；
现在，你得到了 4 条长度为 4 的绳子。


输入: ribbons = [5,7,9], k = 22
输出: 0
解释: 由于绳子长度需要为正整数，你无法得到 22 条长度相同的绳子。


思路：二分法

start 和  end 怎么找？
sum(ribbons) < k : 返回0  否则： start 至少为长度1    end最大为长度max(ribbons)  在这个长度范围内，是否可以截出k条绳子？
1、长度为mid情况下，可以截出x条绳子， x < k   mid太长了，截出的绳子不够k条，把mid放小， end  = mid - 1；
2、 如果 x >= k 条绳子，说明mid太小了，截出的绳子多余k条了，可以把mid再放大些， start = mid ；
最终start < end 
结果 start

**/

#include "01_all.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {

    public:

    int GetMinLoad(int serverNum,  const vector<int>& task) {

        int maxTaskNum = 0;
        for (auto &elem : task) {
            maxTaskNum = std::max(maxTaskNum, elem);
        }

        int start = 1;
        int end = maxTaskNum;
        while (start < end) {
            int mid = start + (end - start) / 2;
            if (CheckServer(task, serverNum, mid)) {
                end = mid;
            } else {
                start = mid + 1;
            }
        }

        return end;
    }

    private:
    // 当每台机器上分配num个task时，服务器数量是否足够
    bool CheckServer(const vector<int>& task, int serverNum, int num) {
        // 实际占用机器数量
        int allocServerNum = 0;
        for (const int & elem : task) {
            allocServerNum += std::ceil((float) elem / num);
        }
        return (allocServerNum > serverNum) ? false : true;
    }
};

void TestChineseKnot()
{
    Solution s;
    vector<int> task = {7, 4};
    int result = s.GetMinLoad(6, task);

    std::cout << "minMaxServerLoad result is : " << result << std::endl;

}
