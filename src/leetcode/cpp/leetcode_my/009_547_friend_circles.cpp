/**
* https://leetcode-cn.com/problems/friend-circles/
* https://leetcode-cn.com/problems/number-of-provinces/

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
#include <deque>
using namespace std;

class Solution {
public:

    // 归并集
    int FindCircleNum(std::vector<std::vector<int>>& isConnected) {
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
    
    //深度优先遍历DFS, 图使用矩阵表示
    int FindCircleNum2(std::vector<std::vector<int>>& isConnected) {

        if (isConnected.size() <= 0) {
            return 0;
        }
        int rows = isConnected.size();
        std::vector<bool> visited(rows, false); //标识某个节点是否被访问过
        int result = 0;
        for (int i = 0; i < rows; ++i) {
            // 最多也就N个节点的连通图
            if (visited[i] == false) {
                dfs(isConnected, visited, i); //节点i没有被访问过，深度优先访问这个连通子图
                result++;  // 记录一个连通子图，连通子图的个数，也就是朋友圈的个数
            }
        }
        return result;
    }

    // 广度优先搜索
    int FindCircleNum3(vector<vector<int>>& isConnected)
    {   
        if (isConnected.size() <= 0) {
            return 0;
        }
        int n =  isConnected.size();
        vector<bool> visited(n, false);
        std::deque<int> qu;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                qu.push_back(i);
                while (!qu.empty()) {  //访问一个完整的连通子图
                    int node = qu.front();
                    visited[node] = true;
                    qu.pop_front();
                    for (int j = 0; j < n; ++j) {
                        if (isConnected[node][j] == 1 && !visited[j]) {
                            qu.push_back(j); //关联的节点入队
                        }
                    }
                } // while
                result++;
            }
        }
        return result;
    }

private:

    //DFS 从节点id开始进行深度优先遍历
    void dfs(std::vector<std::vector<int>> &isConnected, std::vector<bool> &visited, int i) {

        int cols = isConnected[i].size();
        // 从节点i开始，深度优先遍历这个点开始的连通子图
        for (int j = 0; j < cols; ++j) {
            if (isConnected[i][j] == 1 && visited[j] == false) {
                visited[j] = true;
                dfs(isConnected, visited, j);
            }
        }
    }



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
    
    int circle_nums2 = s.FindCircleNum2(friends);
    std::cout << "find the friend circles2: " << circle_nums2 << std::endl;
    
    int circle_nums3 = s.FindCircleNum3(friends);
    std::cout << "find the friend circles3: " << circle_nums3 << std::endl;

}
