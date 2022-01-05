


#include "01_all.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

/*
* 给定一个任务数组tasks，tasks[i]表示第 i 号任务的个数。给定服务器的数量serverNum，表示有serverNum个服务器可使用。任务需要分配到服务器上运行，规则如下
* 
* 一台服务器只能运行一种类型的任务，但可以运行任意个同类型的任务，也可以不运行任务（资源浪费）。
* 所有服务器上中运行任务数量最多的那台服务器上的任务数，称为最大负荷。
* 求最小的最大负荷。数据范围：1<=tasks.length<=1e5 , 1<=tasks[i]<=10e9 , 1<=serverNum<=1e5
* 
* 输入：tasks={7,4} serverNum=5
* 输出：3
* 说明：
* 第一个任务分配3台服务器，负荷分别为：3,3,1 或者 3，2，2
* 第二个任务分配2台服务器，负荷分别为：3,1 或者 2,2
* 所以最小的最大负荷为3

* 思路解析：
* 1) 不优化的思路：枚举， 从1开始尝试
  {7, 4}
  负荷是1： 需要服务器： 11  不够
  负荷是2： 需要服务器： 4 + 2 = 6  不够
  负荷是3： 需要服务器： 3 + 2 = 5 正好
  负荷是4： 需要服务器： 2 + 1 = 3 有服务资源浪费， 最小的最大负载3

  2) 二分的思路优化： 枚举  + 二分
    
    最大的负载，不会超过t = max{t1,t2,...} 任务的最大值
    最小的负载：1

    left = 1 ,right = t 取 mid = （1 + t)/2 作为load，看是否满足服务器的个数限制
    如果不满足大于个数限制，左边移动，放大每个服务器上个数，left = mid + 1
    如果满足个数的限制，收缩右边范围，减少每台服务器上的任务数量，right = mid

*/


class Solution {
public:
    // 待实现函数，在此函数中填入答题代码;
    int GetMinLoad(int serverNum, const vector<int>& task)
    {
        int result = 0;

        if (task.empty()) {
            return result;
        }

        vector<int>::const_iterator it = std::max_element(task.begin(), task.end());
        int pos = std::distance(it, task.begin()); // 最大元素的下标

        int left = 1;
        int right = std::max(1, *it); // 取最大元素

        while (left < right) {
            int mid_load = left + (right - left) / 2;
            if (CheckServerNum(task, mid_load, serverNum)) {
                right = mid_load;
            } else { // 不够
                left = mid_load + 1;
            }
        }
        result = right;
        return result;
    }

private:
    bool CheckServerNum(const vector<int> &task, int load, int serverNum) {
        int needServerNum = 0;
        for (auto & item : task) {
            needServerNum += std::ceil((float)item / load); // 上取整
        }
        return  needServerNum <= serverNum;
    }

};


void TestExamBinarySearch()
{
    int serverNum = 5;
    vector<int> task = {7, 4};

    Solution solu;
    int result = solu.GetMinLoad(serverNum, task);
    std::cout << "getMinLoad result: "<< result << endl;
    return ;
}
