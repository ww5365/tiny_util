
/*
 * Copyright (c) Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: 文件功能描述 
 
 * leetcode 240  lintcode 38
编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：

每行的元素从左到右升序排列。
每列的元素从上到下升序排列。
 
 * 
 */

#include "01_all.h"
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:

    int searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(); 
        if (m <= 0)
            return 0;
        int n = matrix[0].size();
        int result = 0; 
        for (int i = m -1, j = 0; i >= 0, j <= n - 1;) {

            if (matrix[i][j] == target) {
                i --;
                j ++;
                result ++;
            } else if (matrix[i][j] > target) {
                i --;
            } else {
                j ++;
            }
        }
        return result;
    }

};

void TestSerachMatrixII()
{
    std::vector<vector<int>> vec = {{1,2,3,4}, {4, 8, 9 , 10}, {5, 9, 15, 16}};
    Solution s;
    std::cout << "-------TestSearchMatrixII-------" << std::endl;

    int result = s.searchMatrix(vec, 4);
    std::cout << "TestSearchMatrixII result:  " << result << std::endl;


}
