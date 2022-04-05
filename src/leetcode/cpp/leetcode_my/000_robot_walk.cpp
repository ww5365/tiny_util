#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>

#include <iterator>


using namespace std;

/*

测试工程师正在测试某款新型扫地机器人。工程师设计了一个形如二叉树（根节点记为 root）的测试路径，扫地机器人自路径对应的根节点出发，一直行进至路径尽头（即二叉树叶节点）。如果这个路口的左右子节点都非空，机器人选择左转或右转的概率相等；如果这个路口的左右子节点仅一侧非空，则机器人选择非空侧走。工程师给每个路口标记了数字，并且仅在标记数字 target 的所有路口设置了监控摄像机。请问扫地机器人被监控至少拍到一次的概率是多少？

输入：tree_array = [1,2,3,2,5,6,2], target = 2

输出：0.75

关键点：

（1）使用递归的方式计算走到当前节点的概率

（2）遇到target后，不再走下去了

（3）使用全局变量来累和总的概率   --  这个要注意，怎么获取？

（4）如何根据数组创建二叉树



*/

struct TreeNode {
    TreeNode *left;
    TreeNode *right;
    int val;
    explicit TreeNode(int v): val(v), left(nullptr), right(nullptr){}
    virtual ~TreeNode(){}
};

class Solution {
public:
    float RobotWalk(vector<int>& treeArray, int target)
    {
        TreeNode* root = BuildTree(treeArray);
        if (!root) return result;
        helper(root, target, 1.0);
        return this->result;
    }

private:

    // 递归方式计算，左右子树上可能被监控到的概率
    void helper (TreeNode *root, int target, float p) {
        if (!root) return;

        if (root->val == target) {
            // 遍历到有相同的节点，累加概率结果
            this->result += p;
            return;
        }

        if (root->left && root->right) {
            helper(root->left, target, 0.5 * p);
            helper(root->right, target, 0.5 * p);
        } else if (root->left) {
            helper(root->left, target, p);
        } else if (root->right) {
            helper(root->right, target, p);
        }
    }

    TreeNode*  BuildTree(const vector<int>& treeArray)
    {
        if (treeArray.size() <= 0) {
            return nullptr;
        }
        queue<pair<TreeNode*, int>> qu;
        TreeNode* root = new TreeNode(treeArray[0]);
        qu.push(make_pair(root, 0));

        while (!qu.empty()) {
            auto tmp = qu.front();
            qu.pop();
            int idx = tmp.second;
            TreeNode *parent = tmp.first;
            
            if (2 * idx + 1 >= treeArray.size()) {
                break;
            }
            if (2 * idx + 1 < treeArray.size()) {
                parent->left = new TreeNode(treeArray[2 * idx + 1]);
                qu.push(make_pair(parent->left, 2 * idx + 1));
            }
            if (2 * idx + 2 < treeArray.size()) {
                parent->right = new TreeNode(treeArray[2 * idx + 2]);
                qu.push(make_pair(parent->right, 2 * idx + 2));
            }
        }
        return root;
    }

private:

    float result = 0.0;
};

void TestRobotWalk()
{
    Solution s;

    cout << "-----------RobotWalk----------------" << endl;
    vector<int> treeArray = {1,2,3,2,5,6,2};
    int target = 2;
    float result = s.RobotWalk(treeArray, target);
    cout << "result: " << result << endl;
    cout << "-----------RobotWalk finished-------------" << endl;
}