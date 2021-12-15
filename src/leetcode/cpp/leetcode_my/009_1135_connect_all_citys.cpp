/**
* 想象一下你是个城市基建规划者，地图上有 N 座城市，它们按以 1 到 N 的次序编号。
* 给你一些可连接的选项 conections，其中每个选项 conections[i] = [city1, city2, cost] 表示将城市 city1 和城市 city2 连接所要的成本。
* 连接是双向的，也就是说城市 city1 和城市 city2 相连也同样意味着城市 city2 和城市 city1 相连。
* 返回使得每对城市间都存在将它们连接在一起的连通路径（可能长度为 1 的）最小成本。
* 该最小成本应该是所用全部连接代价的综合。如果根据已知条件无法完成该项任务，则请你返回 -1。
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
#include <unordered_map>
#include <exception>
using namespace std;

class Solution {
public:

    /* 
    * kruskal算法:
    * 从边出发，选最小的边加入生成树，保持没有回路。如果有回路舍弃。
    * 回路判断：归并集 ?
    */

    int ConnectAllCitys(int N, vector<vector<int>> &connctions)
    {
        if (connctions.size() < N -1) {
            // 边的总数小于顶点数-1
            return -1;
        }
        vector<int> root(N + 1, -1);
        for (int i = 1; i <= N; ++i) {
            root[i] = i; // 每个顶点的代表元，是自己
        }

        //按照第3个元素进行从小到大的排序
        sort(connctions.begin(), connctions.end(), CompareClass());
        int total = 0;
        int edgeNum = 0;
        for (auto &e: connctions) {
            std::cout << "after sort connections: " << e[0] << " : " << e[1] << " cost: " << e[2] << std::endl;
            // 循环遍历所有的边, 加边，判断回路
            int u = e[0];
            int v = e[1];
            int cost = e[2];

            if (edgeNum == N -1) {
                return total;
            }

            int uRoot = FindRoot(root, u);
            int vRoot = FindRoot(root, v);
            if (uRoot != vRoot) {
                // 不存在回路
                edgeNum ++;
                total += cost;
                // 归并两个顶点
                // UnionRoot(root, u, v);
                root[uRoot] = vRoot;
            }
        }

        return (edgeNum == N -1) ? total : -1;
    }

private:

    class CompareClass {
    public:
        bool operator()(const auto &left, const auto&right) const{
            return left[2] < right[2]; // 按照第3个元素，从小到大排序
        }
    };
    
    int FindRoot(vector<int> &root, int x)
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

/* 
* 使用prim算法思路实现
* 1:从顶点开始，将和此顶点关联的权重最小的边顶点，加入集合U
* 2： 重复1，直至所有节点加入集合U
*/

class Solution2 {
public:
    int ConnectAllCitys(int N, vector<vector<int>> &connctions)
    {
        if (connctions.size() < N -1) {
            // 边的总数小于顶点数-1
            return -1;
        }

        std::unordered_map<int, vector<pair<int, int>>> graph;

        for (auto &e : connctions) {
            //顶点u对应的边cost和边的另一个顶点,类似临接表的存储方式;双向
            for (int i = 0; i < 2; ++i) {
                auto it = graph.find(e[i]);
                if (it == graph.end()) {
                    graph[e[i]] = vector<pair<int, int>>();
            }
            graph[e[i]].emplace_back(std::make_pair(e[(i + 1)%2], e[2]));
            }
        }

        for (auto &e : graph) {
            std::cout << "graph result: " << e.first << " second: " <<e.second.size() << std::endl;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, CompareClass> qu;
        // 初始化起始节点
        for (auto &edge : graph[1]) {
            qu.push(edge);
        }
        vector<bool> visited(N, false);
        visited[1] = true; //节点1被访问
        int addVertexNum = 1;
        int res = 0;
        while (!qu.empty()) {
            //出队cost最小的顶点和cost
            int v = qu.top().first;
            int cost = qu.top().second;
            qu.pop();
            if (visited[v]) continue;
            res += cost;
            visited[v] = true;
            addVertexNum ++;
            if (addVertexNum == N) {
                break;
            }

            for (auto &e : graph[v]) {
                //v开始的边
                qu.push(e);
            }
        }
        return (addVertexNum == N) ? res : -1;
    }

private:

    struct CompareClass {
        bool operator()(const auto &left, const auto &right)const{
            return left.second > right.second; // 小顶堆
        }
    };

};

void TestConnectAllCitys()
{
    Solution s;
    vector<vector<int>> connections = {
        {1, 2, 5},
        {1, 3, 4},
        {2, 3, 3}
    };
    std::cout << "size: " << connections.size() << std::endl;
    int totalCost = s.ConnectAllCitys(3, connections);
    std::cout << "total cost: " << totalCost << std::endl;

    Solution2 s2;  
    vector<vector<int>> connections2 = {
        {1, 2, 5},
        {1, 3, 4},
        {2, 3, 3}
    };
    int totalCost2 = s2.ConnectAllCitys(3, connections2);
    std::cout << "total cost2: " << totalCost2 << std::endl;

}
