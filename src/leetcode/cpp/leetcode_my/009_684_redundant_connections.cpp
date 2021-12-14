/**
* https://leetcode-cn.com/problems/redundant-connection/

* 树可以看成是一个连通且无环的无向图。

* 给定往一棵 n 个节点 (节点值 1～n) 的树中添加一条边后的图。添加的边的两个顶点包含在1到n中间，且这条附加的边不属于树中已存在的边。
* 图的信息记录于长度为n的二维数组edges，edges[i] = [ai, bi] 表示图中在 ai 和 bi 之间存在一条边。
* 请找出一条可以删去的边，删除后可使得剩余部分是一个有着 n 个节点的树。如果有多个答案，则返回数组 edges 中最后出现的边。

* 输入: edges = [[1,2], [2,3], [3,4], [1,4], [1,5]]
* 输出: [1,4]

* 解题思路：
  
  图删除一条边后，还保持是N个节点的树(连通)

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
using namespace std;

class Solution {
public:
    vector<int> FindRedundantConnection(vector<vector<int>>& edges)
    {

        if (edges.size() <= 0) {
            return vector<int>(2, 0);
        }

        int rows = edges.size();
        vector<int> parent(rows + 1, 0); //总共有N条边，N-1条形成树，1条时冗余。节点的个数也是N,但序号从1开始，所以多加1个空间
        for (int i = 0; i < parent.size(); ++i) {
            parent[i] = i;
        }
        for (int i = 0; i < rows; ++i) {
            int u = edges[i][0];
            int v = edges[i][1];
            int p_u = Find2(parent, u);
            int p_v = Find2(parent, v);
            if (p_u == p_v) {
                return vector<int>{u, v};
            } else {
                Union1(parent, p_u, p_v);
            }
        }
        return vector<int>{0, 0};
    }

private:

    int Find(vector<int> &parent, int idx) {
        if (parent[idx] == idx) {
            return idx;
        }
        int end = Find(parent, parent[idx]); 
        // 路径优化
        while (end != parent[idx]) {
            int tmp = idx;
            idx = parent[idx];
            parent[tmp] = end;
        } 
        return end;      
    }
    
    int Find2(vector<int> &parent, int idx) {
        // 非递归查找，并优化路径
        int origin_idx = idx;
        while (idx != parent[idx]) {
            idx = parent[idx];
        }
        parent[origin_idx] = idx;
        return idx;
    }

    void Union1(vector<int> &parent, int u, int v) {
        if (u != v) {
            parent[v] = u;
        }
        return;
    }

};

void TestRedundantConnections()
{
    Solution s;
    std::vector<vector<int>> edges{{1,2}, {2,3}, {3,4}, {1,4}, {1,5}};
    vector<int> res = s.FindRedundantConnection(edges);
    std::cout << "the redundant connections x->y : " << res[0] << " -> " << res[1] << std::endl; 
}
