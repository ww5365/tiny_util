#include "01_all.h"

#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;


/*
https://leetcode.cn/problems/word-search/submissions/

给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。


思路：

1. 水平：针对每个字符，进行4个方向
2. 深度：以word的字符长度作为深度进行深度优先搜索；
3. 需要考虑，进行深度搜索的剪枝；深度方向：不匹配word的情况终止；水平方向：不符合界限的终止；

*/

const vector<int> directions79 = {-1, 0, 1, 0, -1};
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {

        if (board.size() <= 0 || word.size() <= 0) {
            return false;
        }
        bool result = false;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j] != word[0]) {
                    continue;
                }
                // 字符匹配word的第1个字符，深度搜索
                vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));
                dfs(board, i, j, word, 0, visited, result);

                if (result) {
                    return true;
                }
            }
        }
        return result;    
    }


private:

    // 判断i, j 是否合法
    bool IsValid79(vector<vector<char>> &board, int i, int j) 
    {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) {
            return false;
        }   
        return true;
    }

    void dfs(vector<vector<char>> &board, 
             int i, 
             int j, 
             string &word, 
             int idx, 
             vector<vector<bool>> &visited, 
             bool &result)
    {

        if (!IsValid79(board, i, j) || visited[i][j] || word[idx] != board[i][j]) {
            return;
        } 
        if (idx == word.size() - 1) {
            visited[i][j] = true;
            result = true;
            return ;
        }
        visited[i][j] = true;
        for (int k = 0; k < 4; ++k) {
            dfs(board, i + directions79[k], j + directions79[k + 1], word, idx + 1, visited, result);
            if (result) {
                return; // 找到
            }
        }
        visited[i][j] = false;
    }
};


void TestWordSearch()
{
    Solution s;
    vector<vector<char>> grid = { { 'A', 'B', 'C', 'E' },
                                  { 'S', 'F', 'C', 'S' },
                                  { 'A', 'D', 'E', 'E' }
                                  };

    string word = "ABCCED";

    std::cout << "----begin to TestWordSearch ---" << std::endl;

    std::cout << "word :  " << (word[0] == grid[0][0]) << endl;
    bool result  = s.exist(grid, word);

    cout << "result is : " << result << endl;
    std::cout << "----finished TestWordSearch ---" << std::endl;
}