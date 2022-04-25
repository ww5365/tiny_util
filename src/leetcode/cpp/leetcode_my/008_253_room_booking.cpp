#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>

#include <iterator>


using namespace std;

/*

253 会议室II

[[s1,e1],...] 有一组预定会议室的安排，s1 开始时间，e1标识结束时间， 为避免会议室冲突，并充分利用会议室资源，请计算至少需要多少会议室满足会议安排。

输入：{{0, 30}{5, 10}{15, 20}}
输出：2

* 问题抽象： 求区间交集的最大个数

*/


const int MAX_LAST_TIME = 366;

class solution {
public:

 int minMeetingRooms(vector<vector<int>>& intervals) {

    if (intervals.size() <= 0) {
        return 0;
    }

    vector<int> diff(MAX_LAST_TIME, 0);  // 空间优化思路：如果时间数据大，可以使用hash来存值
    for (int i = 0; i < intervals.size(); ++i) {
        int start = intervals[i][0];
        int end = intervals[i][1] + 1;
        diff[start] += 1;
        if (end < MAX_LAST_TIME) {
            diff[end] -= 1;
        }
    }

    int result = 0;
    int interNum = 0;
    for (int i = 0; i < diff.size(); ++i) {
        interNum += diff[i];
        result = std::max(result, interNum);
    }

    return result;
 }
};



void TestRoomBooking()
{
    // vector<int> prices = {2, 4, 1};
    // vector<vector<int>> intervals = {{0, 30}, {5, 10}, {15, 20}};
    vector<vector<int>> intervals = {{7, 10}, {2, 4}};
    cout << "-----------TestRoomBooking----------------" << endl;
    solution s;
    
    int result = s.minMeetingRooms(intervals);

    cout << " result: " <<  result << endl;
    
    cout << "-----------TestRoomBooking finished-------------" << endl;
}