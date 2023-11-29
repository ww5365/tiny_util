/*
* leetcode : 236  https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/description/
* lca： 最近公共祖先

* leetcode : 235 : 二叉搜索树的lca 是不是有更好的解法？

如果两个节点值都小于根节点，说明他们都在根节点的左子树上，我们往左子树上找
如果两个节点值都大于根节点，说明他们都在根节点的右子树上，我们往右子树上找
如果一个节点值大于根节点，一个节点值小于根节点，说明他们他们一个在根节点的左子树上一个在根节点的右子树上，那么根节点就是他们的最近公共祖先节点。

参考：https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/

* 
*/

class Solution5 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        return helper(root, p, q);
    }

private:
    TreeNode* helper(TreeNode* root, TreeNode* p, TreeNode* q) {

        if (!root || root == p || root == q) {
            return root;
        }

        TreeNode* left = helper(root->left, p, q);
        TreeNode* right = helper(root->right, p, q);

        if (!left) {
            return right;
        }

        if (!right) {
            return left;
        }

        return root;
    }

private:
    TreeNode* helper2(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 二叉搜索树 : 下面这个实现思路，还是很精巧的

        // 大于0 从左或右子树中继续找
        while ((long)(root->val - p->val) * (long)(root->val - q->val) > 0) {
            root = p->val < root->val ? root->left : root->right;
        }
        
        // 小于等于0 都是root : 等于0说明p/q== root 小于0说明p/q在root的两侧， 都返回root没问题
        return root;
    }
};
