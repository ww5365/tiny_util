#include "01_all.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

/* 
127 · 拓扑排序
给定一个有向图，图节点的拓扑排序定义如下:
对于图中的每一条有向边 A -> B , 在拓扑排序中A一定在B之前.
拓扑排序中的第一个节点可以是图中的任何一个没有其他节点指向它的节点.
针对给定的有向图找到任意一种拓扑排序的顺序.

挑战点：两种遍历方式实现
1. dfs
2. bfs 

*/

 struct DirectedGraphNode {
    int label;
    vector<DirectedGraphNode *> neighbors;
    DirectedGraphNode(int x) : label(x) {};
};

class Solution {

public:
    /**
     * @param graph: A list of Directed graph node
     * @return: Any topological order for the given graph.
     */
    vector<DirectedGraphNode*> topSort(vector<DirectedGraphNode*> graph) {
        // write your code here

        for(auto node : graph) {
            helper(node);
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

private:

    unordered_map<DirectedGraphNode* , short> status;
    vector<DirectedGraphNode*> result;

private:

    /*
    * bfs 思路：
    * 1. 节点状态： 未搜索，搜索中，已搜索
    * 2. 从任一未搜索状态节点开始：
    * 使用stack保存结果，入栈的条件是：这个节点u出度为0或节点都被已被访问完；如果还有未访问的出度节点v：v未搜索，继续深度优先搜索；v已搜索，在栈中，不用处理；v搜索中，有环； 
    * 

    * 要实现的是：拓扑排序 -> 判断图是否有环 
    * 还可以参考：
    * https://www.cnblogs.com/littlehb/p/15125824.html
    */


    void helper(DirectedGraphNode* node) {
        // 有向无环图，实现拓扑排序
        
        if (status[node] == 1) return;  // 无环，所以只有两种状态：未搜， 已搜  已搜过那就不用搜了
        status[node] = 1;
        if (node->neighbors.size() == 0) {
            // 无出度节点
            result.push_back(node);
            return;
        }
        for (auto neighbor : node->neighbors) {
            helper(neighbor);
        }
        result.push_back(node); // 邻接点都访问完了，再访问自己
        return;
    }


public:
    /**
     * @param graph: A list of Directed graph node
     * @return: Any topological order for the given graph.

     * bfs 思路：
     * 1. 计算入度
     * 2. 入度为0的节点入queue
     * 3. bfs
     */
    vector<DirectedGraphNode*> topSort2(vector<DirectedGraphNode*> graph) {
        // write your code here

        unordered_map<DirectedGraphNode*, int> indegree;
        for(DirectedGraphNode* node : graph) {
            for (auto neighbor : node->neighbors) {
                indegree[neighbor] += 1;
            }
        }

        // queue<DirectedGraphNode*> qu;
        // for (const pair<DirectedGraphNode*, int> &degree: indegree) {
        //     if (degree.second == 0) {
        //         qu.push(degree.first);
        //     }
        // }

        // 用上面的代码， result最后输出为空
        queue<DirectedGraphNode*> qu;
        for (DirectedGraphNode* node : graph) {
            if (indegree[node] == 0) {
                qu.push(node);
            }
        }

        vector<DirectedGraphNode*> result;
        result.reserve(graph.size());
        while (!qu.empty()) {
            DirectedGraphNode* node = qu.front();
            qu.pop();
            result.push_back(node);
            for (auto nb : node->neighbors) {
                indegree[nb] -= 1;
                if (indegree[nb] == 0) {
                    qu.push(nb);
                }
            }
        }

        return result;
    }

};


void TestTopSort()
{
    std::cout << "----begin to TestTopSort ---" << std::endl;
    std::cout << "----finished TestTopSort ---" << std::endl;
}
