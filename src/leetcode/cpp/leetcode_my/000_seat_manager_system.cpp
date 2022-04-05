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

请你设计一个管理 n 个座位预约的系统，座位编号从 1 到 n 。

请你实现 SeatManager 类：

SeatManager(int n) 初始化一个 SeatManager 对象，它管理从 1 到 n 编号的 n 个座位。所有座位初始都是可预约的。
int reserve() 返回可以预约座位的 最小编号 ，此座位变为不可预约。
void unreserve(int seatNumber) 将给定编号 seatNumber 对应的座位变成可以预约。




*/


class SeatManager {
public:
    SeatManager(int n) {
        for (int i = 0; i < n; i++) {
            mSeatAmount.push(i + 1);
        }
    }
    
    int reserve() {
        int curMinSeat = mSeatAmount.top();
        mSeatAmount.pop();
        return curMinSeat;
    }
    
    void unreserve(int seatNumber) {
        mSeatAmount.push(seatNumber);
    }
private:
    priority_queue<int, deque<int>, greater<int>> mSeatAmount;
};


