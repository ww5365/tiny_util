#include "01_all.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
using namespace std;

/*

https://www.lintcode.com/problem/1014/?utm_source=sc-cheatsheet-cyc


有一个由 1 和 0 组成的网格: 单元格中的 1 表示砖块. 当且仅当一个砖块直接连接到网格顶部, 
或者其四周相邻的砖块至少有一个不会掉落时, 这个砖块不会掉落.
我们将按顺序进行一些消除. 每次会指定一个位置 (i, j), 消除该位置上的砖块, 然后可能会有一些砖块因这次消除操作而掉落.
返回一个数组, 表示每次消除后会有多少砖块掉落.


输入: grid = [[1,0,0,0],[1,1,0,0]], hits = [[1,1],[1,0]]
输出: [0,0]
解释: 当我们消除 (1, 0) 的砖块时, (1, 1) 的砖块已经在前一次操作中被消除了.


输入: grid = [[1,0,0,0],[1,1,1,0]], hits = [[1,0]]
输出: [2]
解释: 消除 (1, 0) 处的砖块时, 位于 (1, 1) 和 (1, 2) 的砖块会掉落, 所以返回 2.


思路：
1. 规则： 网格顶部每个砖块不会掉，除非被消除掉

2. 针对每个要消除的hit=[i,j]，都做如下的处理：
   
   消除hit=[i,j]位置元素为0，初始化归并集
   对砖块，即元素值为1 ， 进行归并集的merge
   边关系如何生成? bfs  dfs


   记录i=0行的所有砖块为1的连通分量父节点

   i>0行后面的砖块的父节点，是否能命中i=0的父节点，不能明命中都是要被消除的

*/


class Solution {
public:
    /**
     * @param grid: a grid
     * @param hits: some erasures order
     * @return: an array representing the number of bricks that will drop after each erasure in sequence
     */
    vector<int> hitBricks(vector<vector<int>> &grid, vector<vector<int>> &hits) {
        // Write your code here

        if (hits.empty()) {
            return vector<int>();
        }
        vector<int> result;
        for(int i = 0; i < hits.size(); ++i) {
            grid[hits[i][0]][hits[i][1]] = 0; 
            result.push_back(eraseOneBrick(grid));
        }
        return result;
    }
private:
    int eraseOneBrick(const vector<vector<int>> &grid) {

        int m = grid.size();
        int n = grid[0].size();
        father.resize(m*n);

        int result = 0;

        vector<vector<bool>> visited(m, vector<bool>(n, false));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                father[i*n + j] = (i*n + j);
                if (grid[i][j] == 0) {
                    visited[i][j] = true;
                }
            }
        }

        // 通过bfs， 遍历邻接点，构成归并集，有多个连通分量
        queue<pair<int, int>> qu;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0 || visited[i][j]) {
                    continue;
                }

                visited[i][j] = true;
                qu.push(make_pair(i,j));

                while (!qu.empty()) {
                    pair<int, int> elem = qu.front();
                    qu.pop();
                    
                    for (const auto &direction : directions) {
                        
                        int newx = direction.first + elem.first;
                        int newy = direction.second + elem.second;

                        if (newx >= 0 && newx < m && newy >= 0 && newy < n && !visited[newx][newy]){
                            // 访问的未访问过的1节点
                            visited[newx][newy] = true;
                            qu.push(make_pair(newx, newy));
                            merge(elem.first * n + elem.second, newx * n + newy);
                        }
                    }
                }
            }
        }

        // i = 0 行的1节点的所在连通分量，如果i>0的1节点，不在某个0行所在的连通分量中，必然会倒塌

        set<int> fatherBottomSet;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {

                if (grid[i][j] == 0) {
                    continue;
                }
                if (i == 0) {
                    int fatherBottom = findFather(j);
                    fatherBottomSet.emplace(fatherBottom);
                } else {
                    int fatherOther = findFather(i*n + j);
                    if (fatherBottomSet.find(fatherOther) == fatherBottomSet.end()) {
                        result += 1;
                    }
                }
            }
        }
        return result;
    }

void merge(int cur, int other) {

    int curFather = findFather(cur);
    int otherFather = findFather(other);

    if (curFather != otherFather) {
        father[curFather] = otherFather;
    }
    return;
}


int findFather(int pos) {
    int origin = pos;

    while (pos != father[pos]) {
        pos = father[pos];
    }
    father[origin] = pos;
    return pos;
}

private:

    vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0, -1}, {0, 1}};
    vector<int> father;
};

void TestBuildBinaryTree()
{
    std::cout << "----begin to TestBuildBinaryTree ---" << std::endl;
    std::cout << "----finished TestBuildBinaryTree ---" << std::endl;
}
