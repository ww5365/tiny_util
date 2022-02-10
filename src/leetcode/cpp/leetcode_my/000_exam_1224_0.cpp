


#include "01_all.h"
#include <iostream>
#include <vector>
using namespace std;

/*

服务器：serverNum
任务：task ： [] 下标是类型， 值是这种类型的任务数量

求：最大负载的最小值

*/


class Solution {
public:
    // 待实现函数，在此函数中填入答题代码;
    int GetMinLoad(int serverNum, const vector<int>& task)
    {
        int result = 0;



        return result;
    }

};

inline int ReadInt()
{
    int number;
    cin >> number;
    return number;
}

template<typename T>
inline vector<T> ReadVector(int size)
{
    vector<T> objects(size);
    for (int i = 0; i < size; ++i) {
        cin >> objects[i];
    }
    return objects;
}

int TestExam1224One()
{
    int serverNum;
    cin >> serverNum;
    int taskNum = ReadInt();
    vector<int> task = ReadVector<int>(taskNum);

    Solution solu;
    int result = solu.GetMinLoad(serverNum, task);
    cout << result << endl;
    return 0;
}
