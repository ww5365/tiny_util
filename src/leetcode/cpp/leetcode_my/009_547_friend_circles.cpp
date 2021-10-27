/**
* https://leetcode-cn.com/problems/friend-circles/

* 班上有 N 名学生。其中有些人是朋友，有些则不是。他们的友谊具有传递性。如果已知 A 是 B 的朋友，B 是 C 的朋友，那么我们可以认为 A 也是 C 的朋友。所谓的朋友圈，是指所有朋友的集合。
* 给定一个 N * N 的矩阵 M，表示班级中学生之间的朋友关系。如果M[i][j] = 1，表示已知第 i 个和 j 个学生互为朋友关系，否则为不知道。你必须输出所有学生中的已知的朋友圈总数。
* 示例 1:
* 输入: 
* [[1,1,0],
*  [1,1,0],
*  [0,0,1]]
* 输出: 2 
* 说明：已知学生0和学生1互为朋友，他们在一个朋友圈。
* 第2个学生自己在一个朋友圈，所以返回2。
* 
* 示例 2:
* 输入: 
* [ [1,1,0],
*  [1,1,1],
*  [0,1,1] ]
* 输出: 1
* 说明：已知学生0和学生1互为朋友，学生1和学生2互为朋友，所以学生0和学生2也是朋友，所以他们三个在一个朋友圈，返回1。
* 注意：
* N 在[1,200]的范围内。
* 对于所有学生，有M[i][i] = 1。
* 如果有M[i][j] = 1，则有M[j][i] = 1。

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
using namespace std;

class Solution {
public:
    int FindCircleNum(vector<vector<int>>& isConnected) {

        if (isConnected.size() <= 0) {
            return 0;
        }
        int rows = isConnected.size();
        int cols = isConnected[0].size();
        std::vector<int> parent(rows, -1); //初始状态：每个元素的父节点就是它自身
        int result = 0;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (i != j && isConnected[i][j] == 1) {
                    Union(parent, i, j); // 因为i,j是朋友，所以这两个元素所在的集合是可以归并的
                }
            }
        }

        //计算总共有几个根节点，即：有几个连通子图  主要看有几个根
        for (int i = 0; i < parent.size(); ++i) {
            if (parent[i] == -1) {
                result ++;
            }
        }
        return result;
    }

private:

    // 将元素x和y所在的连通子图进行归并
    void Union(std::vector<int> &parent, int x, int y) 
    {
        int x_root = find(parent, x); //查找x所在集合的，根节点(代表元)
        int y_root = find(parent, y); 

        if (x_root != y_root) {
            // x y两个元素的代表元不同，也就是处于不同的连通子图中，连通
            parent[x_root] = y_root; // 把x子图的父节点挂到y_root子图，这样两个子图形成一个子图
        }
        return ;
    }

    // 查找元素x的父节点(代表元)
    int find(const vector<int> &parent, int x) {
        
        if (parent[x] == -1) {
            return x; //自身就是根节点(代表元)
        }
        return find(parent, parent[x]);
    }

};

void TestFriendCircles()
{
    Solution s;
    std::vector<vector<int>> friends = {{1,1,0}, {1,1,1}, {0,1,1}};
    int circle_nums = s.FindCircleNum(friends);

    std::cout << "find the friend circles: " << circle_nums << std::endl;

}
