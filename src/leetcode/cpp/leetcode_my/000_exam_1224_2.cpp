#include "01_all.h"

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

class TreeNode {
public:
    int val;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;

    explicit TreeNode(int val) : val(val) {}

    ~TreeNode()
    {
        delete left;
        delete right;
    }
};


class Solution {
public:
    TreeNode *buildTree(const vector<int> &nodeValues)
    {
        queue<TreeNode *> queue;
        TreeNode *root = new TreeNode(nodeValues[0]);
        queue.push(root);
        int headChildCnt = 0;
        for (int i = 1; i < nodeValues.size(); ++i) {
            TreeNode *node = nullptr;
            if (nodeValues[i] != -1) {
                node = new TreeNode(nodeValues[i]);
                queue.push(node);
            }
            if (queue.front()->left == nullptr) {
                queue.front()->left = node;
            } else {
                queue.front()->right = node;
            }
            headChildCnt++;
            if (headChildCnt % 2 == 0) {
                queue.pop();
            }
        }
        return root;
    }


    void dfs(vector<pair<TreeNode *, int>> &parents, vector<int> &cpuTimes, int coreCount, int &res)
    {
        // pair.first表示树节点，pair.second表示树节点在哪个CPU运算周期运行
        vector<pair<TreeNode *, int>> next;
        // 父节点反查索引（儿子找爸爸用）。next数组中 next[i] 的父节点是 parents[parentIdx[i]]
        vector<int> parentIdx;

        /* *
         * 分析 1 使用层次遍历
         */
        for (int i = 0; i < parents.size(); ++i) {
            TreeNode *node = parents[i].first->left;
            if (node != nullptr) {
                parentIdx.emplace_back(i);
                next.emplace_back(node, 0);
            }
            node = parents[i].first->right;
            if (node != nullptr) {
                parentIdx.emplace_back(i);
                next.emplace_back(node, 0);
            }
        }

        // 递归出口
        if (next.empty()) {
            return;
        }

        /* *
         * 进入下一层递归
         */
        dfs(next, cpuTimes, coreCount, res);

        /* *
         * 回溯
         */
        // 分析 2 中的第一个影响因素，左右子树所在的运算周期。
        // 根据左右子树的周期得到父节点最早的运算周期
        for (int i = 0; i < next.size(); ++i) {
            const auto &child = next[i];
            // 这里就是儿子找爸爸
            int idx = parentIdx[i];
            auto &parent = parents[idx];
            // 子节点的运算周期 影响 父节点的运算周期
            parent.second = max(parent.second, child.second + 1);
        }

        // 分析 2 中的第二个影响因素，CPU目前的运行情况
        for (auto &node : parents) {
            if (node.second == 0) {
                continue;
            }
            int minTime = node.second;

            // 线性探测，寻找第一个有空闲的周期
            while (cpuTimes[minTime] >= coreCount) {
                minTime++;
            }
            cpuTimes[minTime]++;
            res = max(res, minTime);
            node.second = minTime;
        }
    }

    // 待实现函数，在此函数中填入答题代码
    int GetCycleCount(int coreCount, const vector<int> &nodeValues)
    {
        TreeNode *root = buildTree(nodeValues);

        // 记录CPU每个周期运行情况的数组
        vector<int> cpuTimes(nodeValues.size(), 0);
        cpuTimes.emplace_back(0);
        int res = 0;
        vector<pair<TreeNode *, int>> parent;
        parent.emplace_back(root, 0);
        dfs(parent, cpuTimes, coreCount, res);

        delete root;
        return res;
    }
};


int main()
{
    Solution solution;
    vector<int> nodes = { 0, 0, 0, 0, 1, 0, 0, 1, 1, -1, -1, 1, 1, 0, 1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1 };
    int res;
    res = solution.GetCycleCount(2, nodes);
    assert(res == 4);

    nodes = { 0, 0, 0, 1, 1, 1, 1 };
    res = solution.GetCycleCount(3, nodes);
    assert(res == 2);
}