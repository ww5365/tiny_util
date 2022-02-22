/**

给定一个任务数组tasks，tasks[i]表示第 i 号任务的个数。给定服务器的数量serverNum，表示有serverNum个服务器可使用。
任务需要分配到服务器上运行，规则如下:

一台服务器只能运行一种类型的任务，但可以运行任意个同类型的任务，也可以不运行任务（资源浪费）。
所有服务器上中运行任务数量最多的那台服务器上的任务数，称为最大负荷。
求最小的最大负荷。
数据范围：1<=tasks.length<=1e5 , 1<=tasks[i]<=10e9 , 1<=serverNum<=1e5

输入：tasks={7,4} serverNum=5
输出：3

第一个任务分配3台服务器，负荷分别为：3,3,1 或者 3，2，2
第二个任务分配2台服务器，负荷分别为：3,1 或者 2,2
所以最小的最大负荷为3

思路：抽象建模

任务数量 >= 服务器的数量
最差的情况： 占用2台服务器，分别运行 7 4  个任务，最小的最大负载：7  任务中最大值
最理想情况：服务器足够，至多运行1个任务

result 肯定在[1, MAX_TASK] 之间， 使用二分的方法，进行探测扫描

最大最小值：

start = 1  end = MAX_TASK 
1、如果按照mid分配，占用的服务器的数量N > 实际serverNum ， 服务器不够； 分配的任务数需要增大： start = mid + 1
2、如果按照mid分配，占用的服务器的数量N <= 实际serverNum ， 服务器足够或正好； 分配的任务数需要减少： end  = mid

循环条件： start < end   

循环终止时： end 是可分配的最大的最小负载量

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

void TestMinMaxServerLoad()
{
    Solution s;
    vector<int> task = {7, 4};
    int result = s.GetMinLoad(6, task);

    std::cout << "minMaxServerLoad result is : " << result << std::endl;

}
