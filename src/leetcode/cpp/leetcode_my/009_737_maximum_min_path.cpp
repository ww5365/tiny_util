/**
* 寻找最大最小值路径：lintcode ： 1418  leetcode:1102
* 给你一个R行C列的整数矩阵A。矩阵上的路径从 [0,0] 开始，在 [R-1,C-1] 结束。
* 路径沿四个基本方向（上、下、左、右）展开，从一个已访问单元格移动到任一相邻的未访问单元格。路径的得分是该路径上的最小值。
* 例如，路径 8 → 4 → 5 → 9 的值为 4 。
* 找出所有路径中得分最高的那条路径，返回其得分。
* 
*
*/
#include "trust_pro.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <stack>
#include <deque>
#include <queue>
#include <set>
#include <unordered_map>
#include <exception>
using namespace std;

class Solution {
public:

    /* 
    * 排序 + 归并集 
    * 1：按照节点权重值，从大到小排序
    * 2：按照从大到小的顺序，形成一个从(0,0)->(R-1, C-1)的一个连通分量。这个连通分量的最后一个顶点的值，就是整个路径的最大值
    * 3: 怎么形成一个连通分量？ 同属一个归并集
    */

    int MaximumMinPath(vector<vector<int>> &matrix)
    {
        if (matrix.size() <= 0 || matrix[0].size() <= 0) {
            return -1;
        }
        
        int rows = matrix.size();
        int cols = matrix[0].size();

        vector<int> root(rows * cols, -1);
        for (int i = 0; i < root.size(); ++i) {
            root[i] = i; //每个元素的代表元是自己，初始化
        }
        
        vector<Node> vertex(rows * cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                vertex[i*cols + j].pos.first = i;
                vertex[i*cols + j].pos.second = j;
                vertex[i*cols + j].weight = matrix[i][j];
            }
        }
        // 按照weight值对vertex进行排序, 从大到小
        std::sort(vertex.begin(), vertex.end());

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        const vector<vector<int>> dirs{{0, 1},{0, -1},{-1, 0},{1, 0}};

        visited[0][0] = true;
        visited[rows-1][cols-1] = true; //起始点, 作为连通的印子
        int res = std::min(matrix[0][0], matrix[rows - 1][cols - 1]);
        for (int i = 0; i < vertex.size(); ++i) {
            //对Node数组从大到小进行遍历
            int x = vertex[i].pos.first;
            int y = vertex[i].pos.second;
            visited[x][y] = true;
            res = std::min(res, vertex[i].weight);
            // std::cout << "x= " << x << " y= " << y << "weight:" << vertex[i].weight<< std::endl;

            for (int j = 0; j < dirs.size(); ++j) {
                int nx = x + dirs[j][0];
                int ny = y + dirs[j][1];
                bool flag = IsValid(matrix, nx, ny) && visited[nx][ny];
                if (flag) {
                    Union3(root, x * cols + y, nx * cols + ny); // 归并相邻被访问过的单元格，形成连通分量
                }
            }
            bool break_flag = (Find3(root, 0) == Find3(root, cols * rows - 1));
            if (break_flag) {
                std::cout << "break when i: " << i << std::endl;
                // 如果起始顶点的代表元相同，即连通了
                break;
            }
        }
        return res;
    }
    
    // djstrja算法变形
    int MaximumMinPath2(vector<vector<int>> &matrix)
    {
        if (matrix.size() <= 0 || matrix[0].size() <= 0) {
            return -1;
        }
        int rows = matrix.size();
        int cols = matrix[0].size();
        priority_queue<Node, deque<Node>, CompareClass> qu;
        int res = matrix[0][0];
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        //初始化
        qu.emplace(Node(0, 0, matrix[0][0]));
        const vector<vector<int>> dirs{{0, 1},{0, -1},{-1, 0},{1, 0}};

        while (!qu.empty()) {
            int x = qu.top().pos.first;
            int y = qu.top().pos.second;
            int weight  = qu.top().weight;//保持当前为止全局的最大最小值
            qu.pop();
            if (visited[x][y]) continue;
            res = weight; 
            bool overFlag = (x == rows - 1) && (y == cols - 1);
            if (overFlag) {
                return res;
            }

            visited[x][y] = true;
            for (int i = 0; i < dirs.size(); ++i){
                int nx = x + dirs[i][0];
                int ny = y + dirs[i][1];
                if (IsValid(matrix, nx, ny)) {
                    qu.emplace(Node(nx, ny, std::min(res, matrix[nx][ny]))); // 栈顶始终保持，最大的最小值;
                }
            }
        }
        return res;
    }

private:
    struct Node {
        std::pair<int, int> pos;
        int weight;
        Node() : pos(-1, -1), weight(0){}
        Node(int x, int y, int w) : pos(x, y), weight(w) {
            // pos = make_pair(x, y);
        }

        // 重载<运算符
        bool operator<(const Node & right) const
        {
            return (this->weight > right.weight); // 从大到小排序
        }
    };

    class CompareClass {
    public:
        bool operator()(const Node &left, const Node &right) const{
            return left.weight < right.weight; // 大顶堆
        }
    };
    
    bool IsValid (vector<vector<int>> &grid, int x, int y)
    {
        int rows = grid.size();
        int cols = grid[0].size();
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }


    void Union3(vector<int> &root, int x, int y)
    {

        int root_x = Find3(root, x);
        int root_y = Find3(root, y);

        if (root_x != root_y) {
            root[root_x] = root_y;
        }
        return;
    }

    int Find3(vector<int> &root, int x)
    {
        int origin_x = x;
        while (x != root[x]) {
            x = root[x];
        }
        if (x != origin_x) {
            root[origin_x] = x;
        }
        return x;
    }

};

void TestMaximumMinPath()
{
    Solution s;

    vector<vector<int>> graph = {
        {5, 4, 5},
        {1, 2, 6},
        {7, 4, 6}
    };


    std::cout << "graph size: " << graph.size() << std::endl;
    int weight = s.MaximumMinPath(graph);
    std::cout <<"the min weight: " << weight << std::endl;

    int weight2 = s.MaximumMinPath2(graph);
    std::cout <<"the min weight2: " << weight2 << std::endl;

}
