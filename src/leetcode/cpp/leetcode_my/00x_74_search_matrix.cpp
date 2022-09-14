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

74. 搜索二维矩阵
https://leetcode.cn/problems/search-a-2d-matrix/

编写一个高效的算法来判断 m x n 矩阵中，是否存在一个目标值。该矩阵具有如下特性：

每行中的整数从左到右按升序排列。
每行的第一个整数大于前一行的最后一个整数。


思路：

1. 拉通成一维数组来看，是递增有序的数组，使用二分的方法进行查询

2. 搜索空间：start 和 end 的起始点
   start = 0;
   end = m * n - 1;
   i * COLS + j = idx  -> idx / COLS  idx%COLS 
*/

class Solution {
public:
bool SearchMatrix(vector<vector<int>>& matrix, int target) {

    int m = matrix.size();
    if (m <= 0) {
        return false;
    }
    int n = matrix[0].size();

    int start = 0;
    int end = m * n - 1;

    while (start + 1 < end) {
        int mid = start + (end - start)/2;
        if (matrix[mid / n][mid % n] == target) {
            return true;
        } else if (matrix[mid / n][mid % n] > target) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }

    if (matrix[end / n][end % n] == target) {
        return true;
    }
    
    if (matrix[start / n][start % n] == target) {
        return true;
    }

    return false;
}
};

void TestSearchMatrix()
{
    Solution s;
    cout << "-----------TestSearchMatrix----------------" << endl;
    vector<vector<int>> matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    int target = 3;
    bool result = s.SearchMatrix(matrix, target);
    cout << "result is : " << result << endl;
    cout << "-----------TestSearchMatrix finished-------------" << endl;
}

