
/*
 * Copyright (c) Technologies Co., Ltd. 2021-2021. All rights reserved.
 * Description: 文件功能描述 

 * leetcode 363
 * 题目描述：
 * 给你一个 m x n 的矩阵 matrix 和一个整数 k ，找出并返回矩阵内部矩形区域的不超过 k 的最大数值和。
 * 题目数据保证总会存在一个数值和不超过 k 的矩形区域。

 * 示例1：
 * 输入：matrix = [[1,0,1],[0,-2,3]], k = 2
 * 输出：2
 * 解释：蓝色边框圈出来的矩形区域 [[0, 1], [-2, 3]] 的数值和是 2，且 2 是不超过 k 的最大数字（k = 2）。


 * 解法： 暴力 + 动态规划
 * 
 * 1. 矩阵，怎么遍历所有的子矩阵？
      
      左上（i, j）-> 右下（m, n）  

      for (i = 0; i < row; ++i) {
          for (j=0; j < col; ++j) {
              //左上角

              for (m = i; m < row; ++m) {
                  for (n = j; n < col; ++n) {
                      // 右下角

                  }
              }
          }
      }

 * 2. 每个子矩阵中的面积计算： 不用每次都循环计算了，使用下面dp的思路进行计算
 *    s(i,j): 表示从某个固定点开始，到(i,j)，形成的左上，右下的矩形框的面积
 *    s(i,j) = s(i-1,j) + s(i, j-1) + s(i-1, j-1) + matrix[i][j] i>0&j>0
 *    初始化：
 *    
 * 
 *
 */

#include "01_all.h"
#include <stack>
#include <vector>
#include <iostream>
#include <limits>

using namespace std;

class Solution {

public:
    int MaxSumSubmatrix(vector<vector<int>>& matrix, int k)
    {   

        const std::size_t rows = matrix.size();
        const std::size_t cols = matrix[0].size();

        int max = std::numeric_limits<int>::min();
        
        for (std::size_t i = 1; i <= rows; ++i) {
            for (std::size_t j = 1; j <= cols; ++j) {
                //左上角
                std::vector<std::vector<int>> dp(rows + 1, std::vector<int>(cols + 1, 0));
                for (std::size_t m = i; m <= rows; ++m) {
                    for (std::size_t n = j; n <= cols; ++n) {
                    // 右下角, 形成的子矩阵的面积
                    dp[m][n] = dp[m - 1][n] + dp[m][n - 1] - dp[m - 1][n - 1] + matrix[m - 1][n - 1];

                    if (dp[m][n] <= k && dp[m][n] > max) {
                        max = dp[m][n];
                    }
                    }
                }
            }
        }
        return max;
    }
};


void testMaxSumSubmatrix()
{
    std::vector<vector<int>> vec = {{1, 0, 1},{0, -2, 3}};

    // 二维数组  m * n 
    const std::size_t M = 2; 
    const std::size_t N = 3; 
    
    // vector定义二维数组
    std::vector<std::vector<int>>matrix(M,std::vector<int>(N, -1));
    std::cout << "two diamension vector: " <<  M << " * " << N << std::endl;
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0 ; j < N; ++j) {
            std::cout <<  matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    //动态分配二维数组
    int **tmp = new int*[M];
    for (std::size_t row = 0; row < N; ++row) {
        tmp[row] = new int[N](); //后面的这个括号，是要进行初始化的，都为0
    }
    std::cout << "two diamension vector22: " <<  M << " * " << N << std::endl;
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0 ; j < N; ++j) {
            std::cout <<  tmp[i][j] << " ";
        }
        std::cout << std::endl;
    }
    //动态分配的数组回收
    for (std::size_t row = 0; row < M; ++row) {
        delete []tmp[row];
    }
    delete []tmp;

    Solution s;
    std::cout <<"largest rectangle area: " << s.MaxSumSubmatrix(vec, 4) << std::endl;

}
