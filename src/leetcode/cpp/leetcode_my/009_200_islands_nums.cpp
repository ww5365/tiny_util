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

* 1: 并查集 DSU
     
     1) 每个连通图的集合，使用"代表元"来表示.

*/
#include "01_all.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <stack>
#include <deque>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {


    }
};


void TestIslandsNums()
{
    Solution s;

    vector<vector<char>> grid = 
    { 
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}    
    };

    std::vector<vector<int>> friends = {{1,1,0}, {1,1,1}, {0,1,1}};


    int circle_nums = s.FindCircleNum(friends);
    std::cout << "find the friend circles: " << circle_nums << std::endl;
    
    int circle_nums2 = s.FindCircleNum2(friends);
    std::cout << "find the friend circles2: " << circle_nums2 << std::endl;
    
    int circle_nums3 = s.FindCircleNum3(friends);
    std::cout << "find the friend circles3: " << circle_nums3 << std::endl;

}
