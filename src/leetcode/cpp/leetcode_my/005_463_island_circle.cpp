#include "01_all.h"

#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;


/*
https://leetcode-cn.com/problems/island-perimeter/

给定一个 row x col 的二维网格地图 grid ，其中：grid[i][j] = 1 表示陆地， grid[i][j] = 0 表示水域。
网格中的格子 水平和垂直 方向相连（对角线方向不相连）。整个网格被水完全包围，但其中恰好有一个岛屿（或者说，一个或多个表示陆地的格子相连组成的岛屿）。
岛屿中没有“湖”（“湖” 指水域在岛屿内部且不和岛屿周围的水相连）。格子是边长为 1 的正方形。网格为长方形，且宽度和高度均不超过 100 。计算这个岛屿的周长。

输入：grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
输出：16
解释：它的周长是上面图片中的 16 个黄色的边


输入：grid = [[1,0]]
输出：4

核心思路： dfs

1、遇到1陆地,开始深度搜索与之相连的岛屿:
   典型的矩阵中，四个方向上的DFS搜索

2、计算周长规则： 边临水0或是边界，此边界计入周长  否则，临着陆地的边，不计入周长

*/


class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid)
    {
        if (grid.size() <= 0) {
            return 0;
        }

        int result = 0;
        
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
        for (int row = 0; row < grid.size(); ++row) {
            for (int col = 0; col < grid[0].size(); ++col) {
                
                if (visited[row][col] || grid[row][col] == 0) {
                    // 被访问过或是水域，不进行深搜计算
                    continue;
                }
                // 是陆地的情况
                int circle = 0;
                dfs(grid, visited, row, col, circle);
                // std::cout << "circle: " << circle << std::endl;
                result += circle;
            } 
        }

        return result;
    }

private:

    // 从某个陆地网格开始，进行某个岛屿的深度优先的搜索,并计算这个岛屿的周长

    void dfs(vector<vector<int>> &grid, vector<vector<bool>> &visited, int row, int col, int &result)
    {

        if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size() || grid[row][col] == 0) {
            result += 1;
            return;
        }

        if (visited[row][col]) {
            return;
        }

        const vector<int> directions = {-1, 0, 1, 0, -1};
        visited[row][col] = true;
        
        // 计算网格(row,col)的周长
        for (int i = 0; i < 4; ++i) {
            int newRow = row + directions[i];
            int newCol = col + directions[i + 1];
            dfs(grid, visited, newRow, newCol, result);
        }

        return;
    } 

};

void TestIslandPerimeter() {

    vector<vector<int>> grid = {{0,1,0,0},{1,1,1,0},{0,1,0,0},{1,1,0,0}};

    Solution s;

    std::cout << "----begin to testIslandPerimeter ---"  << std::endl;

    int result = s.islandPerimeter(grid);

    std::cout << "result = " << result << std::endl;

    std::cout << "----finished testIslandPerimeter ---"  << std::endl;


}