#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>

#include <iterator>


using namespace std;

/*

题目描述
给出一个M*N的矩阵区域，用二维数组grid[m][n]表示，数组元素由“A”，“B”，“.”，“*”，“#”组成。其中，“A”“B”分别表示基站A和基站B，“.”表示可达道路，“*”表示障碍物（无法通过），“#”表示地铁站。
现要求得出矩阵局域内，维修人员从基站A到达基站B的最短移动距离，有如下规则：
1.如果区域内没有同时具备基站A和基站B，则返回-1。
2.维修人员每移动一格，视为移动距离1。
3.所有地铁站互通，即维修人员到达“#”后，可以将距离+1后出现在任意其他一个“#”。
4.可能存在多个基站，需计算所有基站A到基站B中距离最短的那一对。

*/

const int MAX_VALUE = numeric_limits<int>::max();
class Solution {
public:
    int solve(vector<string> &matrix) {
        //A B 最短距离
        int distanceAb = MAX_VALUE;
        //# A 最短距离
        int distanceA = MAX_VALUE;
        //# B 最短距离
        int distanceB = MAX_VALUE;
 
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                if ('A' == matrix[i][j]) {
                    //求 A B 最短距离
                    findDis(i, j, 'B', matrix, distanceAb);
                    //求 A # 最短距离
                    findDis(i, j, '#', matrix, distanceA);
                } else if ('#' == matrix[i][j]) {
                    //求 # B 最短距离
                    findDis(i, j, 'B', matrix, distanceB);
                    //求 # A 最短距离
                    findDis(i, j, 'A', matrix, distanceA);
                } else if ('B' == matrix[i][j]) {
                    //求 B A 最短距离
                    findDis(i, j, 'A', matrix, distanceAb);
                    //求 B # 最短距离
                    findDis(i, j, '#', matrix, distanceB);
                }
            }
        }
        int res = min(distanceAb, distanceA + distanceB + 1);
        return res == MAX_VALUE ? -1 : res;
    }

private:

    //计算距离
    void findDis(int row, int col, char target, vector<string> &matrix, int &distance) {
        int n = matrix.size(), m = matrix[0].size();
        queue<pair<int, int>> queue;
        queue.push({row, col});
        int dir[3] = {0, 1, 0};
        int step = 1;
        while (!queue.empty()) {
            int len = queue.size();
 
            //剪枝
            if (step >= distance) {
                break;
            }
 
            for (int num = 0; num < len; ++num) {
                auto node = queue.front();
                queue.pop();
                for (int i = 0; i < 2; ++i) {
                    int x = node.first + dir[i];
                    int y = node.second + dir[i + 1];
 
                    if (x < 0 || y < 0 || x >= n || y >= m || matrix[x][y] == '*') {
                        continue;
                    }
 
                    if (matrix[x][y] == target) {
                        distance = step;
                        return;
                    }
                    queue.push({x, y});
                }
            }
            step++;
        }
 
    }

};

void TestShortestDist()
{
    Solution s;
    cout << "-----------TestShortestDist----------------" << endl;
    vector<string> graph = {
            "#A...*",
            "......",
            "....#*",
            "A.....",
            "*....B"};
    int res = s.solve(graph);

    cout << "result: " << res << endl;

    cout << "-----------TestShortestDist finished-------------" << endl;
}

