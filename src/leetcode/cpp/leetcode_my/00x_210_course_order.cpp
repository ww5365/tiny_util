#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <iterator>
#include <unordered_map>
#include <set>

using namespace std;

/*

210. 课程表 II  https://leetcode.cn/problems/course-schedule-ii/

现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1。给你一个数组 prerequisites ，其中 prerequisites[i] = [ai,
bi] ，表示在选修课程 ai 前 必须 先选修 bi 。

例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示：[0,1] 。
返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序，你只要返回 任意一种
就可以了。如果不可能完成所有课程，返回 一个空数组 。

输入：numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
输出：[0,2,1,3]
解释：总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和课程 2。并且课程 1 和课程 2 都应该排在课程 0 之后。
因此，一个正确的课程顺序是 [0,1,2,3] 。另一个正确的排序是 [0,2,1,3] 。


思路：

1、构建课程的有向图： 每个节点要计算入度；构建出的邻接表；
2、入度节点为0的开始，进行广度优先遍历；每次输出入度为0的节点，输出时将邻接点的入度减1
*/

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        unordered_map<int, int> inDegree;
        unordered_map<int, set<int>> adjVetex;
        queue<int> qu;
        vector<int> result;

        for (int i = 0; i < numCourses; i++) {
            inDegree[i] = 0;
        }
        // 构建有向图临接表
        for (auto &v : prerequisites) {
            adjVetex[v[1]].insert(v[0]);
            inDegree[v[0]]++;
        }

        for (auto &m : inDegree) {
            if (m.second == 0) {
                qu.push(m.first);
            }
        }
        while (!qu.empty()) {
            int node = qu.front();
            qu.pop();
            result.push_back(node);
            if (!adjVetex.count(node)) {
                continue;
            }
            for (auto &v : adjVetex[node]) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    // 入度为0时，进队，继续遍历
                    qu.push(v);
                }
            }
        }
        if (result.size() != numCourses) {
            return vector<int> {};
        }

        return result;
    }
};


void TestCourseOrder()
{
    cout << "-----------TestCourseOrder----------------" << endl;

    Solution s;
    vector<vector<int>> prerequisites = {{1,0},{2,0},{3,1},{3,2}};
    int numCourses = 4;

    vector<int> result = s.findOrder(numCourses, prerequisites);

    for (auto elem : result) {
        cout << elem << " ";
    }
    cout << endl;



}
