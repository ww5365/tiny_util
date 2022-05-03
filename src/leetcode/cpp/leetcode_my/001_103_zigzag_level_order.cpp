#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>

#include <iterator>

#include <unordered_map>


using namespace std;

/*

103. 二叉树的锯齿形层序遍历 : https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/

给你二叉树的根节点 root ，返回其节点值的 锯齿形层序遍历 。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

思路：
1. 二叉树的层次遍历
2. 记录二叉树的高度，height = 1 开始的话，奇数的那层，赋值时，从左到右； 偶数的那层，赋值时从右向左；
*/

  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };
 
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {

        if (root == nullptr) return {};
        int height = 1;
        vector<vector<int>> res;
        queue<TreeNode *> q;
        q.emplace(root);
        while (!q.empty()) {
            int sz = q.size();
            vector<int> v(sz);
            for (int i = 0; i < sz; ++i) {
                TreeNode *node = q.front();
                q.pop();
                if (height % 2 == 1) {
                    v[i] = node -> val; // 从左向右
                } else {
                    v[sz - i - 1] = node -> val; // 从右向左赋值
                }
                if (node->left != nullptr) q.emplace(node->left);
                if (node->right != nullptr) q.emplace(node->right);
            }
            res.emplace_back(v);
            height ++;
        }
        return res;
    }
};

void TestZigzagLevelOrder()
{
    cout << "-----------TestZigzagLevelOrder----------------" << endl;
}

