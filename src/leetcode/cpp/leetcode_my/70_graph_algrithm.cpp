/**
* 
*
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
#include <limits>
using namespace std;

class Solution {
public:
    //实现基于矩阵存储的dijkstra算法: 单源点的最短路径
    bool Dijkstra(vector<vector<int>> &graph, vector<int> &path)
    {

        if (graph.size() <= 0) {
            return false;
        }

        int nodes = graph.size();
        vector<bool> visited(nodes, false);
        visited[0] = true;
        path[0] = 0; 
        
        //初始化，源点0到各个顶点的距离
        for (int i = 1; i < nodes; ++i) {
            path[i] = graph[0][i]; 
        }
    
        int v = -1;
        for (int i = 1; i < nodes; ++i) {
            // 针对剩余所有顶点，逐步加入到S结合
            int minDist = std::numeric_limits<int>::max();
            for (int j = 1; j < nodes; ++j) {
                // 寻找当前集合U中节点的最短路径
                if (path[j] < minDist && !visited[j]) {
                    minDist = path[j];
                    v = j;
                }
            }
            std::cout << "the " << i << " v: " << v << std::endl;
            if (v == -1) break;
            visited[v] = true;
            // 更新，经过节点v, 到各个节点的距离更新
            for (int j = 1; j < nodes; ++j) {
                // 不加第2个条件，会溢出
                if (!visited[j] && graph[v][j] != numeric_limits<int>::max() &&((path[v] + graph[v][j]) < path[j])) {
                    path[j] = path[v] + graph[v][j];
                }
            }
        }
        if (v == -1) {
            std::cout << "graph not connection!" << std::endl;
            return false;
        }
        return true;
    }

    //实现基于矩阵存储的dijkstra算法: 优先级队列优化算法实现
    bool Dijkstra2(vector<vector<int>> &graph, vector<int> &dist, vector<int> &path) {

        if (graph.size() <= 0) {
            return true;
        }
        int nodes = graph.size();
        //vector<int> parent(nodes, -1); //记录最短路径上的每个节点，使用这种方式记录
        vector<Node> tmpDist(nodes); // 到当前节点的最短路径
        vector<bool> visited(nodes, false); //已经被访问的节点
        priority_queue<Node, deque<Node>> qu; // 优先级队列

        //初始化
        for (int i = 0; i< nodes; ++i) {
            tmpDist[i].id = i;
            if (i == 0) {
                tmpDist[i].weight = 0; //源点到自己的距离是0,最小
            } else {
                tmpDist[i].weight = std::numeric_limits<int>::max();
            }
        }

        qu.push(tmpDist[0]); //选距离最小的源点进入队列
        while (!qu.empty()) {
            Node minNode = qu.top();
            qu.pop();
            int u = minNode.id;
            if (visited[u]) continue; //如果已被访问过顶点，直接出栈不再访问了; 因为一个顶点可能多次进栈，但只有距离最短的那次会被访问。 
            visited[u] = true;
            dist[u] = minNode.weight;

            for (int v = 0; v < nodes; ++v) {
                // 剩下的节点中，做松弛
                if (!visited[v] && u != v && graph[u][v] < std::numeric_limits<int>::max() && tmpDist[u].weight + graph[u][v] < tmpDist[v].weight) {
                    tmpDist[v].weight = tmpDist[u].weight + graph[u][v];
                    qu.push(tmpDist[v]);
                    path[v] = u; // 从u->v路径: v的父节点可能是u: 最终表达是一个路径树;可以回溯到每个顶点到源点的最近路径上的所经历的顶点。
                }
            }
        } // while

    }


private:

    struct Node {
        int id; // 顶点编号
        int weight; // 源点到本顶点的最短路径

        // 重载< 运算符号，进行入队时的比较，路径更短的节点放在队头： 小顶堆
        bool operator< (const Node &right) const{
            return this->weight > right.weight;
        }
    };


};

void TestGraph()
{

    vector<vector<int>> graph = {
        {0,5,3,3},
        {5,0,1,numeric_limits<int>::max()},
        {3,1,0,4},
        {3,numeric_limits<int>::max(),4, 0}
    };

    vector<int>dist(graph.size(), 0); // 从源点到各个顶点的最短距离
    Solution s;


    s.Dijkstra(graph, dist);
    for (std::size_t i = 0; i < dist.size(); ++i) {
        std::cout << "path from 0 to " << i << " mindist path: " << dist[i] << std::endl; 
    }
    
    vector<int>dist2(graph.size(), 0); // 从源点到各个顶点的最短距离
    vector<int> path2(graph.size(), -1); // 每个顶点经历最短路径，其父节点; 实际是一个路径树;可以回溯到每个顶点到源点的最近路径上的所经历的顶点。
    
    s.Dijkstra2(graph, dist2, path2);

    for (std::size_t i = 0; i < dist2.size(); ++i) {
        std::cout << "v2 path from 0 to " << i << " mindist path: " << dist2[i] << std::endl; 
    }

    std::cout << "parent path: " << std::endl;
    for (auto & e : path2) {
        std::cout << " " << e << " ";
    }

    std::cout <<std::endl;



}
