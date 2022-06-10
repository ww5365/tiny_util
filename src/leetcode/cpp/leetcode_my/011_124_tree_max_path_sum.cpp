#include "01_all.h"

#include <algorithm>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;


/*
124. 二叉树中的最大路径和
https://leetcode.cn/problems/binary-tree-maximum-path-sum/


路径 被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。

路径和 是路径中各节点值的总和。

给你一个二叉树的根节点 root ，返回其 最大路径和 。


关键点： 
需要理解路径的定义：之前的理解的路径，都是从任意节点出发，沿子节点连接；从垂直方向来理解；  但这里的路径是，沿父节点/子节点, 说明还有水平方向；

root为根的一整颗树的最大路径和，可能的情况6种：

root
left子树最大路径和(可能是:left.root子树的水平方向，也可能是垂直方向，构成的最大路径)
right子树最大路径和

root + left子树最大路径和(仅能是否用left.root子树垂直方向构成的最大值；水平方向不会走到root了)
root + right子树最大路径和
left最大路径和 + root + right最大路径和



思路1： 错的
1、	依赖二叉树的中序遍历序列；
2、	寻找中旬遍历序列的最大子和。

这个思路不对，原因是，沿父节点-子节点链接， 如果左子树的最右节点和root节点，及右子树最左节点，形成最大子和的话。这种情形不是最大路径和；


思路2：参考关键点分析

1. 返回值，记录root为根整棵树的最大路径；同时也得记录，垂直方向,包含root的最大路径，供下一轮使用。


*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct RetType {
    int maxPathSum;  // 以root为根节点，最大路径和；不一定过root；
    int verticalPathSum; // 垂直方向最大路径和
    RetType(int s1 = std::numeric_limits<int>::min(), int s2 = 0): maxPathSum(s1), verticalPathSum(s2){}
};


class Solution {
public:
    int maxPathSum2(TreeNode* root) {

        // 思路不对


        if (!root) {
            return 0;
        }

        stack<TreeNode*> st;
        vector<int> path;
        TreeNode *node = root;
        // 中序序列
        while (node || !st.empty()) {
            while (node) {
                st.push(node);
                node = node -> left;
            }
            node = st.top();
            st.pop();
            path.push_back(node->val);
            node = node->right;
        }

        // 最大子和

        int minSum = 0;
        int result = std::numeric_limits<int>::min();
        int sum = 0;
        for (int i = 0; i < path.size(); ++i) {
            sum += path[i];
            result = std::max(result, (sum - minSum));
            minSum = std::min(sum, minSum);
        }

        return result;
    }

    int maxPathSum(TreeNode* root)
    {   

        return helper(root).maxPathSum;

    }

private:

    RetType helper(TreeNode *root){

        if (!root) {
            return RetType(std::numeric_limits<int>::min(),0);
        }

        RetType leftRes = helper(root->left);
        RetType rightRes = helper(root->right);

        // root为根节点的垂直方向最大的路径: 必过root
        int mVerticalPathSum = std::max(std::max(leftRes.verticalPathSum + root->val, rightRes.verticalPathSum + root->val), root->val);

        // root为根的整个树的最大路径 : 前两个不过root， 后面都是过root的
        int mPathSum = std::max(std::max(leftRes.maxPathSum, rightRes.maxPathSum), std::max(leftRes.verticalPathSum + root->val + rightRes.verticalPathSum, mVerticalPathSum));
        return RetType(mPathSum, mVerticalPathSum);
    }

private:

    int result  = 0;

};



void TestMaxPathSum()
{
    Solution s;
  

    std::cout << "----begin to TestMaxPathSum ---" << std::endl;

    cout << "result is : " << endl;

    std::cout << "----finished TestMaxPathSum ---" << std::endl;
}