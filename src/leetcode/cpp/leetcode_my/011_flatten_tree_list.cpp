/*
 * flatten binary tree to fake "link list" in preorder traversal
 * leetcode 114 : https://leetcode.cn/problems/flatten-binary-tree-to-linked-list/
 * lintcode 453 : https://www.lintcode.com/problem/453/
 * 把二叉树，变成一个假的链表：用二叉树节点right指针，指向下一个节点；
 *
 * 给你二叉树的根结点 root ，请你将它展开为一个单链表：
 * 展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
 * 展开后的单链表应该与二叉树 先序遍历 顺序相同。

 * 思路：
 * 1. 前序遍历
 * 2. 分治1 : 
 * 左边flatten 右边拉平  root 的right指向左子树，左子树的最后节点指向右子树
   
 *  3. 分治2：
 * 右左根思路， 后序

 *  4. 空间复杂度为o(1)的算法
 *
 */

 class Solution4 {
public:
    void flatten(TreeNode* root) {

        helper1(root);
    }

private:

    void helper1(TreeNode* root) {

        if (!root) {
            return;
        }

        TreeNode* cur = root;
        TreeNode* pre = nullptr;
        stack<TreeNode*> st;
        st.push(root);

        while (!st.empty()) {
            // 出栈访问
            cur = st.top();
            st.pop();
            if (cur->right) {
                st.push(cur->right);
            }
            if (cur->left) {
                st.push(cur->left);
            }

            if (pre) {
                pre->right = cur;
                pre->left = nullptr;
            }
            pre = cur;
        }
    }

private:

    TreeNode* helper2(TreeNode* root) {

        if (!root) {
            return nullptr;
        }
        TreeNode* left = helper2(root->left);
        TreeNode* right = helper2(root->right);
        // 如果左子树为空，root->right指向右子树不需要改变
        if (root->left) {
            TreeNode *tmp = root->right;
            root->right = left;
            root->left = nullptr;
            TreeNode *cur = root; //寻找左子树最后一个节点
            while(cur->right) {
                cur = cur->right;
            } 
            cur->right = tmp;
        }
        return root;
    }


    // v3 右左的python实现
    // def helper3(self, node):
    //     if node is None:
    //         return None

    //     self.helper(node.right)
    //     self.helper(node.left)
    //     node.right = self.prev
    //     node.left = None
    //     self.prev = node

private:

    void helper4(TreeNode* root) {

        TreeNode *curr = root;
        while (curr) {
            if (curr->left) {
                auto next = curr->left;
                auto predecessor = next;
                while (predecessor->right != nullptr) {
                    predecessor = predecessor->right;
                }
                predecessor->right = curr->right;
                curr->left = nullptr;
                curr->right = next;
            }
            curr = curr->right;
        }

    }
};
