
/*
 * basic_3_binary_tree_divide_conquer.cpp
 *
 * Created on: Aug 5, 2019
 * Author: wangwei69
 */

#include "chapater_nine.h"
#include <iterator>

typedef struct TreeNode {
    TreeNode *left;
    TreeNode *right;
    int value;
    TreeNode(int val = 0) : left(nullptr), right(nullptr), value(val) {}
} TreeNode;


/*
 * 二叉树的遍历：前序遍历 中序遍历  后续遍历
 * 使用三种算法思路来实现
 *
 * 1、递归
 * 2、迭代：iterative   非递归的思路实现：
      也可以参考：https://github.com/ww5365/tiny_util/blob/master/src/leetcode/cpp/leetcode_my/011_binary_tree_traversal.cpp
 * 3、分治算法
 *
 */

class PreOrderTree {
public:
    // 非递归实现前序遍历：方法1
    void preOrderTraverse(TreeNode *root, vector<int> &res)
    {
        if (!root)
            return;
        stack<TreeNode *> st;
        st.push(root);
        while (!st.empty()) { // 这里只用了一个栈是否为空的条件来控制？注意怎么实现的, 很奇妙
            TreeNode *ptr = st.top();
            st.pop();
            res.push_back(ptr->value); // 出栈，访问元素
            // cout << "pre: " << ptr->value << endl;
            if (ptr->right) {
                st.push(ptr->right); // 右子树不为空，直接入栈
            }

            if (ptr->left) {
                st.push(ptr->left); // 左子树不为空，直接入栈
            }
        }
        return;
    }

    // 非递归的方式实现前序遍历： 常用思路
    void preOrderTraverse2(TreeNode *root, vector<int> &res)
    {
        if (!root) {
            return;
        }

        stack<TreeNode *> st;
        TreeNode *ptr = root;

        while (ptr || !st.empty()) {
            // 访问 并 入栈
            while (ptr) {
                res.push_back(ptr->value);
                if (ptr->right) { // 仅入栈右子树上的节点
                    st.push(ptr->right);
                }
                ptr = ptr->left;
            }

            if (!st.empty()) {
                ptr = st.top();
                st.pop();
            }
        }
        return;
    }

    // 递归的方式实现：recursion
    void preOrderTraverse(TreeNode *root)
    {
        if (!root)
            return;
        vector<int> res;
        traverse(root, res);

        return;
    }

    // divide and conquer : 分治方法来实现前序遍历

    std::shared_ptr<vector<int>> preOrderTraverse_new(TreeNode *root)
    {
        std::shared_ptr<vector<int>> res = std::shared_ptr<vector<int>>(new vector<int>());
        if (!root) {
            return res;
        }
        std::shared_ptr<vector<int>> left = preOrderTraverse_new(root->left);
        std::shared_ptr<vector<int>> right = preOrderTraverse_new(root->right);
        res->push_back(root->value);

        /*
        for (auto it = left->begin(); it != left->end(); ++it){
            res->push_back(*it);
        }
        for (auto it = right->begin(); it != right->end(); ++it){
            res->push_back(*it);
        }
        */

        res->insert(res->end(), left->begin(), left->end()); // 直接调用插入函数
        res->insert(res->end(), right->begin(), right->end());

        return res;
    }

private:
    void traverse(TreeNode *root, vector<int> &res)
    {
        if (!root)
            return;
        res.push_back(root->value);
        traverse(root->left, res);
        traverse(root->right, res);
    }
};


class InOrderTree {
public:
    // 采用分治的思想来实现中序遍历
    vector<int> InOrderTraverse_new(TreeNode *root)
    {
        vector<int> res;
        if (!root) {
            return res;
        }

        // 分成左右两部分：左子树前序遍历  右子树前序遍历
        vector<int> left = InOrderTraverse_new(root->left);
        vector<int> right = InOrderTraverse_new(root->right);

        // merge
        res.insert(res.end(), left.begin(), left.end());
        res.insert(res.end(), root->value);
        res.insert(res.end(), right.begin(), right.end());

        // 返回结果
        return res;
    }

    // 迭代方式实现: 中序遍历
    void InOrderTraverse(TreeNode *root, vector<int> &res)
    {
        if (!root)
            return;
        TreeNode *ptr = root;
        stack<TreeNode *> st;

        while (ptr || !st.empty()) {
            while (ptr) {
                st.push(ptr);
                ptr = ptr->left; // 左分支一直入栈，等待被访问
            }
            // 左边has nothing；出栈访问
            ptr = st.top();
            st.pop();
            res.push_back(ptr->value);
            // cout << "inorder : " << ptr->value << endl;

            // 右子树
            ptr = ptr->right; // 不用判断是否为空了
        }
    }
};

class PostOrderTree {
public:
    /*
     * 迭代方式实现后root遍历：
     * 有个小技巧，是不是可以不用标记栈？
     *
     */


    void PostOrderTraverse(TreeNode *root, vector<int> &result)
    {
        if (!root) {
            return;
        }

        stack<TreeNode *> st;
        TreeNode *ptr = root;
        TreeNode *lastVisited = nullptr;

        while (ptr || !st.empty()) {
            while (ptr) {
                st.push(ptr);
                ptr = ptr->left;
            }

            ptr = st.top();
            // 可以被访问的条件: 叶子结点(或者是右子树为空) /右子树为空，左子树非空，上一个访问节点是左子树最父节点/ 右子树不为空，上一个访问节点是其右子树最父节点
            if ((!ptr->left && !ptr->right) || (!ptr->right && ptr->left == lastVisited) || ptr->right == lastVisited) {
                // 左子树节点已访问
                st.pop();
                result.push_back(ptr->value);
                lastVisited = ptr;
                ptr = nullptr;
            } else {
                ptr = ptr->right;
            }
        }
    }
};


/*
 * 判断一棵树：是否为平衡二叉树？
 leetcode ： 110 https://leetcode.cn/problems/balanced-binary-tree/
 *
 * 分治思想：
 * 1、左右子树 为平衡二叉树
 * 2、左右子树的最大高度
 */

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return helper(root).isBalancedTree;
    }
private:
    struct RetType {
        int height;
        bool isBalancedTree;
        RetType(): height(0), isBalancedTree(true){}
    };


    RetType helper(TreeNode* root) {

        RetType result;
        if (!root) {
            return result;
        }

        RetType left = helper(root->left);
        RetType right = helper(root->right);
        
        result.height = std::max(left.height, right.height) + 1;
        result.isBalancedTree = (left.isBalancedTree && right.isBalancedTree && std::abs(left.height - right.height) <= 1);
        return result;
    }
}


/*
 * example：
 * leetcode：1120 ： https://leetcode.cn/problems/maximum-average-subtree/
 * 给出一颗二叉树，计算这个二叉树中平均值最大的子树，并返回这颗子树的root；
 
 *
 * 比如：
 * 1
 * -5     11
 * 1  3  3    5
 *
 * 平均值最大的子树根节点：11
 *
 * 分治思路： 
   1. 左子树平均值
   2. 右子树平均值
   3. 最终结果：std::max(左，右，左和 + 右和 + root / 总节点数)
 */

class Solution2 {
public:
    TreeNode* isBalanced(TreeNode* root) {
        helper(root);
        return resultRoot;
    }

private:
TreeNode *resultRoot = nullptr;
float maxAverage = std::numeric_limits<float>::min();
private:
    struct RetType {
        int nodeNum;
        int sum;
        RetType(): nodeNum(0), sum(0){}
    };


    RetType helper(TreeNode* root) {

        RetType result;
        if (!root) {
            return result;
        }

        RetType left = helper(root->left);
        RetType right = helper(root->right);

        result.nodeNum = left.nodeNum + right.nodeNum + 1;
        result.sum = left.sum + right.sum + root->val;

        if (result.sum/result.nodeNum > maxAverage) {
            resultRoot = root;
        }
        
        return result;
    }
};


/*
 * example:
 * LCA:  lowest common Ancestor  最近公共祖先
 *
 * 假设：需要计算的两个点都在二叉树中；
 *
 * 比如：
 *
 * 1
 * 2     4
 * 6   5  7  9
 *
 * LCA(6,4) -> 1
 *
 * LCA(7,9) -> 4
 *
 * LCA(2,5) -> 5
 *
 *
 * 升级： 假设需要计算的两个点不一定都在二叉树中；
 *
 *
 *
 */

class LCA {
public:
    TreeNode *lca(TreeNode *root, TreeNode *A, TreeNode *B)
    {
        /*
         * 怎么使用的分治？
         * A B
         *
         * 如果命中A或B，就返回这个节点
         *
         * 左子树返回A， 右子树返回B  此时根节点就是lca
         * 左子树返回null，那么AB同在右子树
         * 右子树返回null，那么AB同在左子树
         *
         */


        if (!root || root == A || root == B) {
            // 当前的根，是谁？
            return root;
        }

        TreeNode *left = lca(root->left, A, B); // 左子树上是否有A或B

        TreeNode *right = lca(root->right, A, B);

        if (left && right) {
            // 分别在左右子树找到AB，此时root就是lca
            return root;
        }

        if (left) {
            return left;
        }

        if (right) {
            return right;
        }


        return nullptr;
    }
};

/*
 * BST: binary search tree  二叉查找树 二叉搜索树
 *
 * 定义： 左子树小于根；右子树不小于根；
 *
 * 判断一棵树，是否为BST？
* leetcode: 98 : https://leetcode.cn/problems/validate-binary-search-tree/
* lintcode: 95 : https://www.lintcode.com/problem/95/?utm_source=sc-v2ex-thx0322

* 给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。
* 有效 二叉搜索树定义如下：
* 节点的左子树只包含 小于 当前节点的数。
* 节点的右子树只包含 大于 当前节点的数。
* 所有左子树和右子树自身必须也是二叉搜索树。

思路： 
1. 左子树是bst
2. 右子树是bst
3. 左子树最大节点值小于root，右子树的最小节点值大于root
*/

class Solution3 {
// public:
//     bool isValidBST(TreeNode* root) {

//     }

public:
    /**
     * @param root: The root of binary tree.
     * @return: True if the binary tree is BST, or false
     */
    bool isValidBST(TreeNode *root) {
        // write your code here

        return helper(root).isBst;

        // return helper(root, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    }

private:
    struct RetType {
        bool isBst;
        int minVal;
        int maxVal;
        RetType(): isBst(true),minVal(std::numeric_limits<long>::max()),maxVal(std::numeric_limits<long>::min()){}
    };

private:

    RetType helper(TreeNode* root) {

        RetType result;

        if (!root) {
            return result;
        }

        if (!root->left && !root->right) {
           result.isBst = true;
           result.minVal = root->val;
           result.maxVal = root->val;
           return result;
        }

        RetType left = helper(root->left);
        RetType right = helper(root->right);

        if (!root->left) {
            result.minVal = root->val;
            result.maxVal = right.maxVal;
            result.isBst = right.isBst && (root->val < right.minVal);
        } else if (!root->right) {
            result.minVal = left.minVal;
            result.maxVal = root->val;
            result.isBst = left.isBst && (left.maxVal < root->val);
        } else {
            result.minVal = left.minVal;
            result.maxVal = right.maxVal;
            result.isBst = left.isBst && right.isBst && (left.maxVal < root->val) && (root->val < right.minVal);
        }
        return result;
    }

// 参考：版本V2 更简洁
private:
    bool helper(TreeNode* root, long min, long max) {
        // 返回是否为二叉搜索树
        if (!root) {
            return true;
        }
        if (root->val <= min || root->val >= max){
            // 开区间，val肯定大于min且小于max的，不符合的情况下，肯定是false
            return false;
        }
        // 满足val在(min, max) 之间， 有可能是二叉排序树;
        bool left = helper(root->left, min, root->val); // 左子树肯定要在(min, val)之间
        bool right = helper(root->right, root->val, max);
        return left && right;
    }



// 参考：基于中序遍历来判断是否为二叉排序树  
// 中序遍历序列是单调递增的序列
public:
    bool isValidBST2(TreeNode *root) {

        TreeNode* ptr = root;
        stack<TreeNode*> st;
        long lastVisit = std::numeric_limits<long>::min();

        while (ptr || !st.empty()) {
            while (ptr) {
                st.push(ptr);
                ptr = ptr->left;
            }
            ptr = st.top();

            if (lastVisit >= ptr->val) {
                return false;
            }

            lastVisit = ptr->val;
            st.pop();
            ptr = ptr->right;
        }
        return true;
    }
};

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
                while (predecessor->right) {
                    predecessor = predecessor->right;
                }
                predecessor->right = curr->right; // 把cur右子树截取后装到左子树最右节点上
                curr->left = nullptr;
                curr->right = next;
            }
            curr = curr->right;
        }
    }
};

void test_basic_3_binary_tree_divide_conquer()
{
    /*
     * 手工构造一颗二叉树
     * 1
     * 2  3
     * 5
     *
     * 前序：1 2 5 3
     * 中序：2 5 1 3
     *
     */

    TreeNode *tree = new TreeNode(1);

    TreeNode *ptr = tree;

    if (ptr) {
        ptr->left = new TreeNode(2);
        ptr->right = new TreeNode(3);
        ptr = tree->left;

        if (ptr) {
            ptr->right = new TreeNode(5);
        }
    }

    PreOrderTree pre;
    // 用分治思想实现：前序遍历
    std::shared_ptr<vector<int>> res = pre.preOrderTraverse_new(tree);
    cout << "preorder traverse: " << res.use_count() << endl;
    for (auto ele : *res) {
        cout << ele << "  ";
    }
    cout << endl;
    // 迭代方式实现：前序遍历
    vector<int> res_iterative;
    pre.preOrderTraverse(tree, res_iterative);

    cout << "-----preorder traverse 1-----" << endl;
    for (auto elem : res_iterative) {
        cout << elem << "  ";
    }
    cout << endl;

    res_iterative.clear();
    pre.preOrderTraverse2(tree, res_iterative);
    cout << "-----preorder traverse 2-----" << endl;
    std::copy(res_iterative.begin(), res_iterative.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;


    InOrderTree in;
    cout << "InOrder Traverse" << endl;
    // 分治：实现中序遍历
    vector<int> res2;
    res2 = in.InOrderTraverse_new(tree);

    for (auto elem : res2) {
        cout << elem << " ";
    }
    cout << endl;

    // 迭代： 实现中序遍历
    res2.clear();
    in.InOrderTraverse(tree, res2);
    for (auto elem : res2) {
        cout << elem << " ";
    }
    cout << endl;

    PostOrderTree post;
    vector<int> res_post;
    post.PostOrderTraverse(tree, res_post);
    cout << "-----postorder traverse iterator-----" << endl;
    std::copy(res_post.begin(), res_post.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

}
