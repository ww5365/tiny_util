#include "01_all.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <list>
#include <deque>
#include <vector>
#include <stack>
using namespace std;


/* 
* 对应的leetcode编号：
后序：https://leetcode.cn/problems/binary-tree-postorder-traversal/submissions/
中序： https://leetcode.cn/problems/binary-tree-inorder-traversal/description/
前序：https://leetcode.cn/problems/binary-tree-preorder-traversal/
* 
* 非递归的算法: 基本使用了统一的模板来实现
* 分治算法实现，参考如下：
* https://github.com/ww5365/tiny_util/blob/master/src/leetcode/cpp/chapater_nine/basic_3_binary_tree_divide_conquer.cpp
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
    // 后序遍历
    vector<int> postOrderTraverse(TreeNode *root) {

        vector<int> result;
        if (!root) {
            return result;
        }
        TreeNode *ptr = root;
        stack<TreeNode*> st;
        stack<bool> stFlag;
        while (ptr || !st.empty()) {
            
            while(ptr) {
                st.push(ptr);
                stFlag.push(false);
                ptr = ptr->left;
            }
            ptr = st.top();
            bool flag = stFlag.top(); // 右子树是否被访问
            stFlag.pop();
            st.pop();
            if (!flag) {
                stFlag.push(true);
                st.push(ptr);
                ptr = ptr->right;
            } else {
                result.push_back(ptr->val);
                ptr = nullptr;
            }
        }
        return result;
    }

    // 后序遍历 V2 不用标记栈
    vector<int> postOrderTraverse(TreeNode *root) {
        vector<int> result;
        if (!root) {
            return result;
        }
        TreeNode *ptr = root;
        stack<TreeNode*> st;
        TreeNode *lastVisited = nullptr; // 记录上一个被访问节点
        while (ptr || !st.empty()) {
            while(ptr) {
                st.push(ptr);
                ptr = ptr->left;
            }
            ptr = st.top();
            // 可以访问情况: 左右均为空; 左不空，右空 上一个访问节点是左子树的最父节点; 右不空，上一个访问节点是右子树的最父节点;
            if ((!ptr->left && !ptr->right) || (!ptr->right && ptr->left == lastVisited) || ptr->right == lastVisited) {
                result.push_back(ptr->val);
                st.pop();
                lastVisited = ptr;
                ptr = nullptr;
            } else {
                // 不可访问，
                ptr = ptr->right;
            }
        }
        return result;
    }

    // 中序遍历
    vector<int> inOrderTraverse(TreeNode *root) {

        vector<int> result;
        if (!root) {
            return result;
        }

        TreeNode *ptr = root;
        stack<TreeNode*> st;
        while (ptr || !st.empty()) {
            while (ptr) {
                st.push(ptr);
                ptr = ptr -> left;
            }
            ptr = st.top();
            st.pop();
            // std::cout << ptr->val << std::endl;
            result.push_back(ptr->val);
            ptr = ptr->right;
        }
        return result;
    }

        // 前序遍历
    vector<int> preOrderTraverse(TreeNode *root) {

        vector<int> result;
        if (!root) {
            return result;
        }
        TreeNode *ptr = root;
        stack<TreeNode*> st;
        while (ptr || !st.empty()) {
            while (ptr) {
                result.push_back(ptr->val);
                if (ptr->right) {
                    st.push(ptr->right);
                }
                ptr = ptr -> left;
            }
            if (!st.empty()) {
                ptr = st.top();
                st.pop();
            }
        }
        return result;
    }

};
