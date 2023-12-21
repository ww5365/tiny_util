#include "01_all.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

/*
* url: https://www.lintcode.com/problem/974/description?utm_source=sc-cheatsheet-cyc
* 974 · 01 矩阵
* 给定一个由0和1组成的矩阵，求每个单元格最近的0的距离。
* 两个相邻细胞之间的距离是1。

1. 直接思路：
依次遍历：遇到0，不管； 遇到1，进行bfs，寻找距离最近的0  时间复杂度：m*n * m*n   多源点最短路径

2. 别人思路：
从0的角度看，距离最近的1，并记录distance[0, 1]
所有的0入队，所有的0，第1层最近的1，反过来看，0就是这些1距离最近的0，而且只需要visited访问1次，下一个0的周边不用再入队了；下一层，都是距离第一层0最近的1，如果还未被访问，那就bfs，且距离加1；依次再遍历的层，就是剩余未访问的1，且计算下distance + 1即可。

时间复杂度：m*n

学到的：bfs
在最短路问题中，如果我们要求多个源点出发的最短路时，一般我们都会建立一个「超级源点」连向所有的源点，用「超级源点」到终点的最短路等价多个源点到终点的最短路。

*/

class Solution {
public:
    /**
     * @param matrix: a 0-1 matrix
     * @return: return a matrix
     */
    vector<vector<int>> updateMatrix(vector<vector<int>> &matrix) {
        // write your code here

        int m = matrix.size();
        if (m <= 0) {
            return vector<vector<int>>();
        }
        int n = matrix[0].size();

        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<vector<int>> distance(m, vector<int>(n, 0));
        queue<pair<int, int>> qu;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    qu.push(make_pair(i, j));
                    visited[i][j] = true;
                }
            }
        }

        while(!qu.empty()) {
            pair<int, int> elem = qu.front();
            qu.pop();
            for (auto direction : directions) {
                int x = elem.first + direction.first;
                int y = elem.second + direction.second; 

                if (x >= 0 && x < m && y >= 0 && y < n && !visited[x][y]) {
                    qu.push(make_pair(x,y));
                    visited[x][y] = true;
                    distance[x][y] = distance[elem.first][elem.second] + 1;
                }
            }
        }

        return distance;
    }

private:
    vector<pair<int, int>> directions = {{-1, 0}, {+1, 0}, {0, -1}, {0, +1}};
};




void TestUpdateMatrix()
{
    std::cout << "----begin to TestBuildBinaryTree ---" << std::endl;
    std::cout << "----finished TestBuildBinaryTree ---" << std::endl;
}
