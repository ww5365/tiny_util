#include "01_all.h"

#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
using namespace std;


/*
695. 岛屿的最大面积

给你一个大小为 m x n 的二进制矩阵 grid 。
岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在 水平或者竖直的四个方向上
相邻。你可以假设 grid 的四个边缘都被 0（代表水）包围着。 岛屿的面积是岛上值为 1 的单元格的数目。 计算并返回 grid
中最大的岛屿面积。如果没有岛屿，则返回面积为 0 。



输入：
grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],
        [0,0,0,0,0,0,0,1,1,1,0,0,0],
        [0,1,1,0,1,0,0,0,0,0,0,0,0],
        [0,1,0,0,1,1,0,0,1,0,1,0,0],
        [0,1,0,0,1,1,0,0,1,1,1,0,0],
        [0,0,0,0,0,0,0,0,0,0,1,0,0],
        [0,0,0,0,0,0,0,1,1,1,0,0,0],
        [0,0,0,0,0,0,0,1,1,0,0,0,0]]

输出：6

思路一：DSU

1、set 初始化： parent 1维度向量，记录元素的父节点 : i * cols + j
2、Union 归并： 相邻节点归并到一起，具有相同的父节点
3、遍历归并集： 计算每个连通分量的父节点下挂载的节点数，最多节点数的，即为最大岛屿面积

*/


class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        if (grid.size() <= 0) {
            return 0;
        }
        int rows = grid.size();
        int cols = grid[0].size();
        vector<int> parent(rows * cols, -1);

        // 初始化set
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 1) {
                    parent[i * cols + j] = i * cols + j;
                }
            }
        }
        // 相邻归并
        Union(grid, rows, cols, parent);

        // 统计每个连通分量的节点数

        unordered_map<int, int> areaCount;
        for (int i = 0; i < parent.size(); ++i) {
            if (parent[i] != -1) {
                int root = Find(parent, i);
                areaCount[root]++;
            }
        }

        int result = 0;
        for (auto &elem : areaCount) {
            result = std::max(result, elem.second);
        }
        return result;
    }

private:
    void Union(vector<vector<int>> &grid, int rows, int cols, vector<int> &parent)
    {
        vector<int> directions = { -1, 0, 1, 0, -1 };
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 0) {
                    continue;
                }
                int curIdx = i * cols + j;
                int curParent = Find(parent, curIdx);
                // 和四个方向的节点，是否进行归并
                for (int k = 0; k < 4; ++k) {
                    int newRow = i + directions[k];
                    int newCol = j + directions[k + 1];
                    if (!IsValid(grid, newRow, newCol) || grid[newRow][newCol] == 0) {
                        continue;
                    }
                    int newParent = Find(parent, newRow * cols + newCol);
                    if (curParent != newParent) {
                        parent[newParent] = curParent;
                    }
                } // end for
            }     // end for
        }         // end for
        return;
    }

    bool IsValid(vector<vector<int>> &grid, int row, int col)
    {
        return (row >= 0 && row < grid.size() && col < grid[0].size() && col >= 0);
    }

    // 寻找idx的父节点
    int Find(vector<int> &parent, int idx)
    {
        int oriIdx = idx;
        while (idx != parent[idx]) {
            idx = parent[idx];
        }
        parent[oriIdx] = idx;
        return idx;
    }
};

void TestMaxAreaOfIsland()
{
    vector<vector<int>> grid = { { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
                                 { 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0 },
                                 { 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
                                 { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 } };

    // vector<vector<char>> grid = { { '1'}, {'1'}};

    Solution s;

    std::cout << "----begin to TestMaxAreaOfIsland ---" << std::endl;

    int result = s.maxAreaOfIsland(grid);

    std::cout << "result = " << result << std::endl;

    std::cout << "----finished TestMaxAreaOfIsland ---" << std::endl;
}