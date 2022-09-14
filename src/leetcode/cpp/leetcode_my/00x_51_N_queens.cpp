#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>

#include <iterator>

#include <set>

using namespace std;

/*

https://leetcode.cn/problems/n-queens/

51. N 皇后

n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。(水平，垂直，斜线)
给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。


思路: 深搜 + 回溯

1. 水平方向，每个空格进行尝试
2. 垂直方向，深度搜索
3. 技巧点：皇后的位置冲突：对角线和反对角线的位置怎么判定

*/

class Solution {
public:

    vector<vector<string>> solveNQueens(int n) {

        vector<int> path;
        vector<vector<int>> queens;
        dfs(n, 0, path, queens);

        vector<vector<string>> results;

        //std::cout << queens.size() << std::endl;
        //std::cout << queens[0].size() << std::endl;

        for (int i = 0; i < queens.size(); ++i) {

            vector<string> oneResult;
            for (int j = 0; j < queens[i].size(); ++j) {
                //std::cout << queens[i][j] << " , ";
                string oneRow(n, '.');
                oneRow[queens[i][j]] = 'Q';
                oneResult.push_back(oneRow);
            }
            // std::cout << std::endl;
            results.push_back(oneResult);
            
        }
        return results;
    }

private:
    void dfs(int n, int row, vector<int> &path, vector<vector<int>> &result) {
        if (path.size() == n) {
            result.push_back(path);
            return;
        }

        for (int i = 0; i < n; ++i) {
            if (!IsValid(path, row, i)) {
                continue;
            }
            path.push_back(i);
            dfs(n ,row + 1, path, result);
            path.pop_back();

        }

        return;
    }

    bool IsValid(vector<int> &path, int row, int col) {
        // path记录了皇后放置的列，其下标代表行
        for (int i = 0; i < path.size(); ++i) {

            if (path[i] == col) {
                return false;
            }

            if ((i - path[i]) == (row - col)) {
                return false;
            }
            
            if ((i + path[i]) == (row + col)) {
                return false;
            }
        }

        return true;
    }

};

void TestSolveNQueens()
{
    Solution s;
    cout << "-----------TestSolveNQueens----------------" << endl;
    
    int n = 4;
    vector<vector<string>> result = s.solveNQueens(n);

    cout << "TestSolveNQueens result is : "<< endl;
    for (auto &res : result) {
        for (auto &str: res) {
            cout << str << " ";
        }
        cout << endl;
    }

    cout << "-----------TestSolveNQueens finished-------------" << endl;
}

