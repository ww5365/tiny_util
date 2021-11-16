/**
* https://leetcode-cn.com/problems/number-of-islands/

* 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
* 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

* 输入：grid = [
*   ["1","1","0","0","0"],
*   ["1","1","0","0","0"],
*   ["0","0","1","0","0"],
*   ["0","0","0","1","1"]
* ]
* 输出：3


* 解题思路：

* 1: BFS
  2: DFS
  
  3: DSU 并查集
     1) 每个连通图的集合，使用"代表元"来表示。计算一个连通分量的场景。
     2) 

*/
#include "01_all.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <stack>
#include <deque>
#include <queue>
#include <set>
using namespace std;

class Solution {
public:

    //DSU 归并集的思路
    int numIslands(vector<vector<char>>& grid)
    {

        if (grid.size() <= 0) {
            return 0;
        }

        int rows = grid.size();
        int cols = grid[0].size();

        std::vector<int> parent(rows * cols, -1); //归并集的思路，也是要用空间换取时间
        int result = 0;

        //初始化
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '1') {
                    parent[i * cols + j] = i * cols + j; //初始化，把matrix拉平，形成一维度的数组; 每个元素的代表元都是自己；
                    result++;
                }
            }
        }

        //cout << "the result: " << result << std::endl;
        //printParent(parent);

        //DSU:归并法计算岛数量
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int idx = i * cols + j;
                if (grid[i][j] == '1') {
                    // 此位置为1，上下左右进行探测归并
                    for (int r = 0; r < moveX.size(); ++r) {
                        int new_x = i + moveX[r];
                        int new_y = j + moveY[r];
                        int new_idx = new_x * cols + new_y;
                        if (IsValid(grid, new_x, new_y)) {
                            Union(grid, idx, new_idx, parent, result); //上下左右进行归并
                            //std::cout << "update parent: " << idx << " " << new_x << "," << new_y <<std::endl;
                            //printParent(parent);
                        }
                    }
                }//if
            }
        }
        return result;  
    }

    //BFS  连通分量的个数, 这种方法，在leetcode中会超时。。

    int numIslands2(vector<vector<char>>& grid)
    {
        if (grid.size() <= 0) return 0;
        queue<Point> qu;
        int rows = grid.size();
        int cols = grid[0].size();
        int result = 0;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false)); //当前位置是否被访问过标识
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    qu.push(Point(i,j));
                    while (!qu.empty()) {
                        Point tmp(qu.front().x,qu.front().y);
                        qu.pop(); 
                        visited[tmp.x][tmp.y] = true;
                        //std::cout <<"this is a test in whil!" << std::endl;
                        //上下左右在入队
                        for (int k = 0; k < moveX.size(); ++k) {
                            int new_x = tmp.x + moveX[k];
                            int new_y = tmp.y + moveY[k];
                            if (IsValid(grid, new_x, new_y) && !visited[new_x][new_y]) {
                                qu.emplace(Point(new_x, new_y));
                            }
                        }
                    }//while
                    result ++; //遍历完一个连通分量
                }
            }
        }
        return result;
    }

    //DFS
    int numIslands3(vector<vector<char>>& grid)
    {
        if (grid.size() <= 0) return 0;
        int rows = grid.size();
        int cols = grid[0].size();
        int result = 0;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false)); //当前位置是否被访问过标识
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {

                if (grid[i][j] == '1' && !visited[i][j]) {
                    dfs(grid, i, j, visited);
                    result ++;
                }
            }
        }
        return result;
    }

private:
    //DFS
    void dfs(vector<vector<char>> &grid, int i, int j, vector<vector<bool>> &visited) {

        if (!IsValid(grid, i, j) || grid[i][j] == '0' || visited[i][j] ){
            return;
        }
        visited[i][j] = true;
        for (int k = 0; k < moveX.size(); ++k){
            dfs(grid, i + moveX[k], j + moveY[k], visited);
        }

    }
    void printParent(vector<int> &parent) {
        if (parent.size() <= 0) {
            return;
        }
        int len = parent.size();
        for (int i = 0; i < len; ++i) {
            std::cout << parent[i] << " ";
        }
        std::cout << std::endl;
    }

    //判断是否为有效的元素
    bool IsValid (vector<vector<char>> &grid, int x, int y)
    {   
        int rows = grid.size();
        int cols = grid[0].size();
        return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == '1';
    }

    //并操作
    void Union(std::vector<std::vector<char>> &grid, int idx, int new_idx, std::vector<int> &parent, int &result)
    {

        int cur_idx = Find(parent, idx); //查找idx的代表元
        int neighbor_idx = Find(parent, new_idx); //查找相邻探测idx的代表元(上下左右)

        if (cur_idx != neighbor_idx) {
            parent[neighbor_idx] = cur_idx; 
            //探测位置的代表元的父节点，设置为当前元素;从而cur_idx成为最新的父节点(代表元)
            result --;  //归并一次，'1'不可能单独成岛了，所以岛的数量减1
        }
        return;
    }

    //查操作：这块稍难理解 重点理解
    int Find(std::vector<int> &parent, int idx) {

        //代表元就是自身的
        if (parent[idx] == idx) {
            return idx;
        }

        int end = Find(parent, parent[idx]);
        
        while (parent[idx] != end) { 
            //优化并查集合并, 进行树的压缩, 把原来路径上以parent[idx]为父节点的元素，都把父节点重置为最新的代表元
            int temp = idx;
            idx = parent[idx];
            parent[temp] = end;
        }
        return end;
    }


private:
    const std::vector<int> moveX = {-1, 1, 0, 0}; //上下左右
    const std::vector<int> moveY = {0, 0, -1, 1};

    struct Point {
        int x;
        int y;
        Point():x(-1),y(-1){}
        Point(int i, int j):x(i), y(j){}
    };

};



void TestIslandsNums()
{
    Solution s;
    std::vector<vector<char>> grids = {{'1','1','1'}, {'0','1','0'}, {'1','1','1'}};

    int islandsNums = s.numIslands(grids);
    std::cout << "find the island nums: " << islandsNums << std::endl;

    int islandNums2 = s.numIslands2(grids); 
    std::cout << "find the island nums2: " << islandNums2 << std::endl;
    
    int islandNums3 = s.numIslands3(grids); 
    std::cout << "find the island nums3: " << islandNums3 << std::endl;

}
