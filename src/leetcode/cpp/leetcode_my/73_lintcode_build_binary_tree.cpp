#include "01_all.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

/*
* url: https://www.lintcode.com/problem/73/
* 73 · 前序遍历和中序遍历树构造二叉树

*/

/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */

 class TreeNode {
 public:
    int val;
    TreeNode *left, *right;
    TreeNode(int val) {
        this->val = val;
        this->left = this->right = NULL;
    }
 };

class Solution {
public:
    /**
     * @param preorder: A list of integers that preorder traversal of a tree
     * @param inorder: A list of integers that inorder traversal of a tree
     * @return: Root of a tree
     */

    TreeNode* buildTree(vector<int> &preorder, vector<int> &inorder) {
        // write your code here
        if (preorder.size() <= 0 || inorder.size() <= 0) {
            return nullptr;
        }
        return helper(preorder, inorder);
    }

private:
    TreeNode *helper(const vector<int> &preorder, const vector<int> &inorder) {

        if (preorder.size() <= 0 || inorder.size() <= 0) {
            return nullptr;
        }
        int val = preorder[0];
        TreeNode *root = new TreeNode(val);
        auto it = std::find(inorder.begin(), inorder.end(), val);
        std::size_t leftLen = (it - inorder.begin());
        if (leftLen == 0) {
            root->left = nullptr;
        } else {
            root->left = helper(vector<int>(preorder.begin() + 1, preorder.begin() + 1 + leftLen), vector<int>(inorder.begin(), it));
        }

        if (leftLen == inorder.size() - 1) {
            root->right = nullptr;
        } else {
            root->right = helper(vector<int>(preorder.begin() + 1 + leftLen, preorder.end()), vector<int>(it + 1, inorder.end()));
        }
        return root;
    }
};

/*
* https://www.lintcode.com/problem/72/
* 
* 72 · 中序遍历和后序遍历树构造二叉树
* 
*/

class Solution2 {
public:
    /**
     * @param inorder: A list of integers that inorder traversal of a tree
     * @param postorder: A list of integers that postorder traversal of a tree
     * @return: Root of a tree
     */
    TreeNode* buildTree(vector<int> &inorder, vector<int> &postorder) {
        // write your code here

        if (inorder.empty() || postorder.empty()) {
            return nullptr;
        }

        return helper(inorder, postorder);

    }

private:

    TreeNode* helper(const vector<int> &inorder, const vector<int> &postorder) {

        if (inorder.empty() || postorder.empty()) {
            return nullptr;
        }

        int val = postorder.back();

        TreeNode *root = new TreeNode(val);

        auto it = std::find(inorder.begin(), inorder.end(), val);

        std::size_t leftLen = (it - inorder.begin());

        if (leftLen == 0) {
            root->left = nullptr;
        } else {
            root->left = helper(vector<int>(inorder.begin(), it),vector<int>(postorder.begin(), postorder.begin() + leftLen));
        }

        if (leftLen == inorder.size() - 1) {
            root->right = nullptr;
        } else {
            root->right = helper(vector<int>(it + 1, inorder.end()),vector<int>(postorder.begin() + leftLen, postorder.begin() + postorder.size() - 1));
        }

        return root;
 }


};


void TestBuildBinaryTree()
{
    std::cout << "----begin to TestBuildBinaryTree ---" << std::endl;
    std::cout << "----finished TestBuildBinaryTree ---" << std::endl;
}
