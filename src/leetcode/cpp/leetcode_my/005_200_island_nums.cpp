#include "01_all.h"

#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;


/*


给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。

输入：grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
输出：3

思路一：DFS

1、遇到陆地1 进行这个连通分量的深搜
2、使用visited记录已经被访问的陆地
3、每轮一个连通分量的计算

思路二： 连通分量的问题 - DSU

思路三： BFS


*/


class Solution {
public:
    int numIslands(vector<vector<char>> &grid)
    {
        if (grid.size() <= 0) {
            return 0;
        }

        int result = 0;
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
        for (int row = 0; row < grid.size(); ++row) {
            for (int col = 0; col < grid[0].size(); ++col) {
                if (visited[row][col] || grid[row][col] == '0') {
                    // 被访问过或是水域，不进行深搜计算
                    continue;
                }
                // 是陆地的情况
                dfs(grid, visited, row, col);
                // std::cout << "circle: " << circle << std::endl;
                result += 1;
            }
        }

        return result;
    }

private:
    // 从某个陆地网格开始，进行某个岛屿的深度优先的搜索,并标注这个连通分量(visited数组)
    void dfs(vector<vector<char>> &grid, vector<vector<bool>> &visited, int row, int col)
    {
        if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size() || grid[row][col] == '0' ||
            visited[row][col]) {
            return;
        }

        // 陆地情况
        const vector<int> directions = { -1, 0, 1, 0, -1 };
        visited[row][col] = true;
        for (int i = 0; i < 4; ++i) {
            int newRow = row + directions[i];
            int newCol = col + directions[i + 1];
            dfs(grid, visited, newRow, newCol);
        }
    }

public:
    // 思路2： DSU 算法
    int numIslands2(vector<vector<char>> &grid)
    {
        if (grid.size() <= 0) {
            return 0;
        }

        int rows = grid.size();
        int cols = grid[0].size();
        int result = 0;

        //  初始化归并集合
        vector<int> parent(rows * cols, -1);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '1') {
                    parent[i * cols + j] = i * cols + j;
                    result += 1; // 每个1都可能形成一个岛
                }
            }
        }

        // 归并
        vector<int> directions = { -1, 0, 1, 0, -1 };
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '1') {
                    // 上下左右进行归并
                    for (int k = 0; k < 4; ++k) {
                        int newRow = i + directions[k];
                        int newCol = j + directions[k + 1];
                        if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols ||
                            grid[newRow][newCol] == '0') {
                            continue;
                        }

                        int curParent = FindRoot(parent, i * cols + j);
                        int newParent = FindRoot(parent, newRow * cols + newCol);

                        if (curParent != newParent) {
                            parent[newParent] = curParent;
                            result--; // 合并一个1，岛屿量减1
                        }
                    }
                }
            }
        }

        return result;
    }

private:

    int FindRoot(vector<int> &parent, int idx) {
        int ori = idx;
        while (idx != parent[idx]) {
            idx = parent[idx];
        }
        parent[ori] = idx; // 优化路径
        return idx;
    }


public:
    // BFS  连通分量的个数
    int numIslands3(vector<vector<char>>& grid)
    {

        if (grid.size() <= 0) return 0;
        
        queue<pair<int, int>> qu;
        int rows = grid.size();
        int cols = grid[0].size();
        int result = 0;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false)); //当前位置是否被访问过标识

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {

                if (grid[i][j] == '1' && !visited[i][j]) {
                    qu.push(make_pair(i,j));
                    while (!qu.empty()) {
                        pair<int, int>tmp = qu.front();
                        qu.pop(); 
                        visited[tmp.first][tmp.second] = true;
                        //std::cout <<"this is a test in whil!" << std::endl;
                        //上下左右在入队
                        for (int k = 0; k < moveX.size(); ++k) {
                            int new_x = tmp.first + moveX[k];
                            int new_y = tmp.second + moveY[k];
                            if (IsValid(grid, new_x, new_y) && !visited[new_x][new_y]) {
                                qu.emplace(make_pair(new_x, new_y));
                            }
                        }
                    }//while
                    result ++; //遍历完一个连通分量
                }

            }
        }
        return result;
    }
private:

        //判断是否为有效的元素
    bool IsValid (vector<vector<char>> &grid, int x, int y)
    {   
        int rows = grid.size();
        int cols = grid[0].size();
        return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == '1';
    }

    const std::vector<int> moveX = {-1, 1, 0, 0}; //上下左右
    const std::vector<int> moveY = {0, 0, -1, 1};

};

void TestIslandNums()
{
    vector<vector<char>> grid = { { '1', '1', '0', '0', '0' },
                                  { '1', '1', '0', '0', '0' },
                                  { '0', '0', '1', '0', '0' },
                                  { '0', '0', '0', '1', '1' } };

    // vector<vector<char>> grid = { { '1'}, {'1'}};

    Solution s;

    std::cout << "----begin to TestIslandNums ---" << std::endl;

    int result = s.numIslands3(grid);

    std::cout << "result = " << result << std::endl;

    std::cout << "----finished TestIslandNums ---" << std::endl;
}