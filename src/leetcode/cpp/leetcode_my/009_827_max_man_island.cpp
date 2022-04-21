#include "01_all.h"

#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;


/*
827. 最大人工岛

给你一个大小为 n x n 二进制矩阵 grid 。最多 只能将一格 0 变成 1 。
返回执行此操作后，grid 中最大的岛屿面积是多少？
岛屿 由一组上、下、左、右四个方向相连的 1 形成。

输入: grid = [[1, 0], [0, 1]]
输出: 3
解释: 将一格0变成1，最终连通两个小岛得到面积为 3 的岛屿。


思路：DSU  计算最大岛屿面 -> 连接起来岛屿面积

1、set 初始化：
parent 1维度向量，记录元素的父节点, 归并树
area   1维度向量，记录以此元素为父节点的归并树的节点个数，即：岛屿面积
2、Union 归并：
相邻陆地归并到一起，具有相同的父节点；
更新被归结为父节点的元素的area值；同时计算最大的岛屿面积；maxArea
3、循环遍历节点为0的水域，如果没有0水域，maxConnectArea = maxArea 就是结果；否则，计算其上下左右，是否有岛屿；有的话，连接起来计算面积maxConnectArea


leetcode :
惨痛教训：
if (newRow < 0 || newRow >= rows || newCol < 0 || newCol > cols || grid[newRow][newCol] == 0)
边界条件判断时，应该是newCol >= cols 错写成下面，漏掉等号，导致leetcode上报RE错误；

Line 1034: Char 34: runtime error: addition of unsigned offset to 0x607000000020 overflowed to 0x60700000001c
(stl_vector.h) SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior
/usr/bin/../lib/gcc/x86_64-linux-gnu/9/../../../../include/c++/9/bits/stl_vector.h:1043:34


边界条件：
[[1,1],[1,1]] 没过


*/


class Solution {
public:
    int largestIsland(vector<vector<int>> &grid)
    {
        if (grid.size() <= 0) {
            return 0;
        }
        int rows = grid.size();
        int cols = grid[0].size();
        vector<int> parent(rows * cols, -1);
        vector<int> area(rows * cols, 0); // 以这个元素为父节点的节点个数, 即所形成的岛屿面积

        // 初始化
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 0) {
                    continue;
                }
                parent[i * cols + j] = i * cols + j;
                area[i * cols + j] = 1;
            }
        }

        // 归并，同时求最大岛屿面积
        const vector<int> directions = { -1, 0, 1, 0, -1 };
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 0) {
                    continue;
                }
                // 遇到陆地, 上下左右归并
                int curIdx = i * cols + j;
                for (int k = 0; k < 4; ++k) {
                    int newRow = i + directions[k];
                    int newCol = j + directions[k + 1];
                    if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols || grid[newRow][newCol] == 0) {
                        continue;
                    }
                    Union(parent, area, curIdx, newRow * cols + newCol);
                }
            }
        }
        // 整个最大岛屿的面积
        int maxArea = GetMaxArea(area);

        // 如果有水域，并能连通两个及以上的岛屿的情况下，最大人工岛计算
        int maxConnectArea = maxArea;
        // 下面再求，0可以变成1，连接起来后的最大面积
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 1) {
                    continue;
                }

                // 遇到水域, 上下左右是否有陆地可以连接起来，并计算最大connetArea
                int curIdx = i * cols + j;
                int connectArea = 0;
                unordered_set<int> pSet;
                pSet.clear();
                for (int k = 0; k < 4; ++k) {
                    int newRow = i + directions[k];
                    int newCol = j + directions[k + 1];
                    if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols || grid[newRow][newCol] == 0) {
                        continue;
                    }
                    // 此水域紧邻的陆地的父节点
                    int newParentIdx = Find(parent, newRow * cols + newCol);
                    pSet.insert(newParentIdx);
                }
                connectArea += 1;
                for (auto &elem : pSet) {
                    connectArea += area[elem]; // 相邻的陆地：上下左右可能是相通的，所以用他们的root放到set中来计算
                }

                maxConnectArea = std::max(maxConnectArea, connectArea);
            }
        }

        return maxConnectArea;
    }

private:
    void Union(vector<int> &parent, vector<int> &area, int curIdx, int newIdx)
    {
        int curParent = Find(parent, curIdx);
        int newParent = Find(parent, newIdx);

        if (curParent != newParent) {
            parent[newParent] = curParent;
            area[curParent] += area[newParent]; // 把被挂的归并树的节点量，累加到新的父节点的节点量上
            // maxArea = std::max(maxArea, area[curParent]);
        }
        return;
    }

    int Find(vector<int> &parent, int idx)
    {
        // int oriIdx = idx;
        while (idx != parent[idx]) {
            // std::cout << "Find idx: " << idx << endl;
            idx = parent[idx];
        }
        // parent[oriIdx] = idx;
        return idx;
    }

    int GetMaxArea(vector<int> &area)
    {   int maxArea = 0;
        for (auto &elem : area) {
            maxArea = std::max(maxArea, elem);
        }
        return maxArea;
    }
};

void TestMaxManIsland()
{
    Solution s;
    vector<vector<int>> grid = { { 1, 1, 0, 0, 0 }, { 1, 1, 0, 0, 0 }, { 0, 0, 0, 1, 1 }, { 0, 0, 0, 1, 1 } };


    std::cout << "----begin to TestMaxManIsland ---" << std::endl;

    int result = s.largestIsland(grid);

    std::cout << "result = " << result << std::endl;

    std::cout << "----finished TestMaxManIsland ---" << std::endl;
}