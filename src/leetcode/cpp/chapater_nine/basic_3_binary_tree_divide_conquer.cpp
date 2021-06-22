/*
 * basic_3_binary_tree_divide_conquer.cpp
 *
 *  Created on: Aug 5, 2019
 *      Author: wangwei69
 */

#include "chapater_nine.h"

typedef struct TreeNode{
    TreeNode *left;
    TreeNode *right;
    int value;
    TreeNode(int val = 0):left(nullptr),right(nullptr),value(val){}
}TreeNode;



/*
 * 二叉树的遍历：三种算法思路来实现
 *
 * 1、递归
 * 2、迭代：iterative
 * 3、分治算法
 *
 */

class PreOrderTree{

public:

    //迭代方式实现前序遍历：iterative
    void preOrderTraverse(TreeNode *root, vector<int> &res){
        if (!root) return;
        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty()){  //这里只用了一个栈是否为空的条件来控制？注意怎么实现的
            TreeNode *ptr = st.top();
            st.pop();
            res.push_back(ptr->value); //访问元素
            //cout << "pre: " << ptr->value << endl;
            if (ptr -> right){
                st.push(ptr->right); //右子树不为空，直接入栈
            }

            if (ptr->left){
                st.push(ptr->left); //左子树不为空，直接入栈
            }
        }
        return;
    }

    //递归的方式实现：recursion

    void preOrderTraverse(TreeNode *root){
        if (!root) return;
        vector<int> res;
        traverse(root, res);

        return;
    }

    //divide and conquer : 分治方法来实现前序遍历

    shared_ptr<vector<int>> preOrderTraverse_new(TreeNode *root){

        shared_ptr<vector<int>> res = shared_ptr<vector<int>>(new vector<int>());
        if (!root){
            return res;
        }
        shared_ptr<vector<int>> left = preOrderTraverse_new(root->left);
        shared_ptr<vector<int>> right = preOrderTraverse_new(root->right);
        res->push_back(root->value);

        /*
        for (auto it = left->begin(); it != left->end(); ++it){
            res->push_back(*it);
        }
        for (auto it = right->begin(); it != right->end(); ++it){
            res->push_back(*it);
        }
        */

        res->insert(res->end(), left->begin(), left->end()); //直接调用插入函数
        res->insert(res->end(), right->begin(), right->end());

        return res;
    }

private:
    void traverse(TreeNode *root, vector<int> &res){
        if(!root) return;
        res.push_back(root->value);
        traverse(root->left, res);
        traverse(root->right, res);
    }

};


class InOrderTree{
public:

    //采用分治的思想来实现中序遍历
    vector<int> InOrderTraverse_new(TreeNode *root){
        vector<int> res;
        if (!root){
            return res;
        }

        //分成左右两部分：左子树前序遍历  右子树前序遍历
        vector<int> left = InOrderTraverse_new(root->left);
        vector<int> right = InOrderTraverse_new(root->right);

        //merge
        res.insert(res.end(), left.begin(), left.end());
        res.insert(res.end(), root->value);
        res.insert(res.end(), right.begin(), right.end());

        // 返回结果
        return res;
    }

    //迭代方式实现: 中序遍历
    void InOrderTraverse(TreeNode* root, vector<int> &res){

        if (!root) return ;
        TreeNode *ptr = root;
        stack<TreeNode*> st;

        while (ptr || !st.empty()){
            while(ptr){
                st.push(ptr);
                ptr = ptr->left; //左分支一直入栈，等待被访问
            }
            //左边has nothing；出栈访问
            ptr = st.top();
            st.pop();
            res.push_back(ptr->value);
            //cout << "inorder : " << ptr->value << endl;

            //右子树
            ptr = ptr->right;  //不用判断是否为空了
        }
    }
};

class PostOrderTree{

public:

    /*
     * 迭代方式实现后root遍历：
     *
     * 有个小技巧，是不是可以不用标记栈？
     *
     */





};







/*
 * 判断一棵树：是否为平衡二叉树？
 *
 * 分治思想：
 * 1、左右子树 为平衡二叉树
 * 2、左右子树的最大高度
 * 3、
 */


class BalanceTree{





};


/*
 * example：
 *
 * 给出一颗二叉树，计算这个二叉树中平均值最大的子树，并返回这颗子树的root；
 *
 * 比如：
 *        1
 *    -5     11
 *   1  3  3    5
 *
 * 平均值最大的子树根节点：11
 *
 *
 */

class MaxAverageSubTree{

};


/*
 * example:
 * LCA:  lowest common Ancestor  最近公共祖先
 *
 * 假设：需要计算的两个点都在二叉树中；
 *
 * 比如：
 *
 *      1
 *   2     4
 * 6   5  7  9
 *
 * LCA(6,4) -> 1
 *
 * LCA(7,9) -> 4
 *
 * LCA(2,5) -> 5
 *
 *
 *  升级： 假设需要计算的两个点不一定都在二叉树中；
 *
 *
 *
 */

class LCA{

public:

    TreeNode* lca(TreeNode *root, TreeNode *A, TreeNode *B){

        /*
         * 怎么使用的分治？
         *   A B
         *
         *   如果命中A或B，就返回这个节点
         *
         *   左子树返回A， 右子树返回B  此时根节点就是lca
         *   左子树返回null，那么AB同在右子树
         *   右子树返回null，那么AB同在左子树
         *
         */


        if (!root || root == A || root == B){
            //当前的根，是谁？
            return root;
        }

        TreeNode *left = lca(root->left, A, B); //左子树上是否有A或B

        TreeNode *right = lca(root->right, A, B);

        if (left && right){
            //分别在左右子树找到AB，此时root就是lca
            return root;
        }

        if (left){
            return left;
        }

        if (right){
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
 *
 * 思路：
 * 左子树是bst && 右子树是bst && 左子树最大节点值< root->value <= 右子树最小节点值
 *
 *
 */




/*
 * flatten binary tree to fake "link list" in preorder traversal
 *
 * 把二叉树，变成一个假的链表：用二叉树节点right指针，指向下一个节点；
 *
 *
 */








void test_basic_3_binary_tree_divide_conquer(){

    /*
     * 手工构造一颗二叉树
     *         1
     *       2  3
     *        5
     *
     * 前序：1 2 5 3
     * 中序：2 5 1 3
     *
     */

    TreeNode *tree = new TreeNode(1);

    TreeNode *ptr = tree;

    if (ptr){
        ptr->left = new TreeNode(2);
        ptr->right = new TreeNode(3);
        ptr = tree->left;

        if (ptr){
            ptr->right = new TreeNode(5);
        }
    }

    PreOrderTree pre;
    //用分治思想实现：前序遍历
    shared_ptr<vector<int>> res = pre.preOrderTraverse_new(tree);
    cout << "preorder traverse: " << res.use_count() << endl;
    for (auto ele: *res){
        cout << ele << "  ";
    }
    cout << endl;
    //迭代方式实现：前序遍历
    vector<int> res_iterative;
    pre.preOrderTraverse(tree, res_iterative);
    for (auto elem : res_iterative){
        cout << elem << "  ";
    }
    cout << endl;


    InOrderTree in;
    cout <<"InOrder Traverse" <<endl;
    //分治：实现中序遍历
    vector<int> res2;
    res2 = in.InOrderTraverse_new(tree);

    for(auto elem: res2){
        cout <<  elem << " " ;
    }
    cout << endl;

    //迭代： 实现中序遍历
    res2.clear();
    in.InOrderTraverse(tree, res2);
    for(auto elem: res2){
        cout <<  elem << " " ;
    }
    cout << endl;









}

