/*
 * ds_tree_buid.h
 *
 *  Created on: Jan 15, 2018
 *      Author: wangwei69
 */



#include "ds_common.h"
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

/*
 *
 */

class Solution {

public:

    //////////////////////////*构建*///////////////////////////////////////

    /*
     * 功能：
     * 1、输入：前序 和 中序 序列 生成一颗二叉树
     * 2、返回：二叉树树根
     *
     * 比如：下面的树如何通过前序和中序构造？
     *
     *       1
     *    2     3
     *  4   5      6
     *
     * 前序：1 2 4 5 3 6
     * 中序：4 2 5 1 3 6
     *
     * 思路：
     *
     * 1、前序中，可以知道，第一个元素是根节点的位置，通过中序序列确定出左右子树的子序列；
     * 2、通过左右子树的子序列（前，中），又递归的创建左右子树；
     *
     *
     * 迭代器版本，使用前+中序列，构建二叉树
     */
    TreeNode* build_tree1(vector<int>& pre_order, vector<int>& in_order){
        //使用前，中序序列，递归创建二叉树
        return build(pre_order.begin(),pre_order.end(),
                in_order.begin(),in_order.end());
    }

    /*
     * 下标版本，使用前+中序列，构建二叉树
     */
    TreeNode* build_tree2(vector<int>& pre_order,vector<int>& in_order){
        return build(pre_order,0, pre_order.size()-1, in_order,0,in_order.size()-1);
    }


    //使用中序和后序序列来构建一颗二叉树
    TreeNode* build_tree3(vector<int>& in_order,vector<int>&post_order){
        return build_post(in_order.begin(),in_order.end(),post_order.rbegin(),post_order.rend());
    }


    //////////////////////////*遍历*///////////////////////////////////////

    /*
     * 前序序列的非递归版本的遍历,使用栈
     * 这是self自己写的版本，参考别人写的版本，发现可以少用while？
     * 具体实现，参考pre_traverse2实现
    */

    void pre_traverse(TreeNode* root){
        stack<TreeNode*> st;
        if(!root)
            return ;
        TreeNode *p = root;
        cout <<  root->val << " ";
        st.push(root);
        p = p->left;

        while(p || !st.empty()){
            while(p){//左子树不为空，一直访问
                cout << p->val << " ";
                st.push(p);
                p = p->left;
            }
            p = st.top()->right;
            st.pop();
        }
    }

    /*
     * 参考别人的版本，少用个while；
     */
    void pre_traverse2(TreeNode* root){
        if (!root)
            return ;
        stack<TreeNode*> st;
        TreeNode* p = root;
        st.push(p);
        while(!st.empty()){
            p = st.top();
            st.pop();
            cout << p->val << " ";
            if(p->right){
                st.push(p->right);
            }//先右子树入栈

            if(p->left){
                st.push(p->left);
            }//左子树后进，要先出来，进行访问
        }//while
    }//pre_traverse2

    /*
     * 中序遍历的非递归版本，stack版本
     */
    void  in_traverse(TreeNode* root){
        stack<TreeNode*> st;
        if(!root)
            return;
        TreeNode* p = root;
        while(p||!st.empty()){
            if(p){
                st.push(p);
                p = p->left;
            }else{//p为nullptr
                //访问
                cout << st.top()->val << " ";
                p = st.top()->right;
                st.pop();
            }
        }//while
    }


    /*
     * 中序遍历的非递归，morris算法思想版本,优势：空间复杂度：o(1)
     * 利用了叶子节点空指针域，建立后继节点线索；
     *
     * 1、当前节点cur，开始，如果左子树为空，直接访问该节点；否则，从左子树，寻找其直接前驱节点（左子树最右下);
     * 2、如果前驱节点指针域为空，把其指向cur；
     * 3、如果前驱节点指针域非空了，访问cur节点(已经访问过前驱，这是第二次回环到cur了，直接访问就可以了)；同时，要把指针域恢复为nullptr；
     *
     */

    void in_traverse_morris(TreeNode* root){
        //..
    }

    //递归版本的后续遍历
    void post_traverse(TreeNode* root){

        if (!root)
            return;
        post_traverse(root->left);
        post_traverse(root->right);
        cout << root ->val << " ";
    }

    /*
     * 后序遍历stack版本 ,时间：o(n) 空间：o(n)
     * 思想：
     * 1、左子树节点入栈；同时，记录其右子树是否被访问的标识；
     * 2、为空时，出栈；如果标识为已访问，直接access此节点；
     * 3、如果右子树访问标识是未访问，置为访问，此节点再次入栈（二次入栈）；同时，其右子树节点开始入栈；
     *
     */

    void post_traverse2(TreeNode* root){
        stack<pair<TreeNode*,bool> > st;

        if(!root)
            return;

        TreeNode* p = root;
        while(p || !st.empty()){

            while(p){
                st.push(make_pair(p, false));
                p = p->left;
            }
            p = st.top().first;
            bool flag = st.top().second;
            //flag标识右子树是否被访问过
            if(!flag){
                st.top().second = true;
                p = p->right;
            }else{
                //可以访问；访问，出栈，置空
                cout << p->val << " ";
                st.pop();
                p = nullptr; //记得置空，不然结束条件不成立，死循环
            }
        }//while
    }

    //计算树的最大高度
    int min_depth(TreeNode *root);


private:

    //使用下标的版本,元素范围：[pre_start,pre_end] [in_start,in_end]

    TreeNode* build(vector<int> &pre, size_t pre_start,size_t pre_end,
                    vector<int> &in, size_t in_start,size_t in_end );

    //迭代器版本 [pre_first,pre_last)
    TreeNode* build(vector<int>::iterator pre_first, vector<int>::iterator pre_last,
                    vector<int>::iterator in_first, vector<int>::iterator in_last);

    //后根序列+中根序列，构造二叉树；迭代器版本

    TreeNode* build_post(vector<int>::iterator in_first, vector<int>::iterator in_last,
            vector<int>::reverse_iterator post_first, vector<int>::reverse_iterator post_last);

};

/*
 * 使用下标的版本,元素范围：[pre_start,pre_end] [in_start,in_end]
 */

TreeNode* Solution::build(vector<int> &pre, size_t pre_start,size_t pre_end,
                vector<int> &in, size_t in_start,size_t in_end ){
    if (pre_start > pre_end|| in_start > in_end ) return nullptr;
    TreeNode* root = new TreeNode(pre[pre_start]);
    size_t pos = in_start;
    for( size_t i = in_start;i <= in_end ;i++){
        if(in[i] == pre[pre_start]){
            pos = i;
            break;
        }
    }
    cout << "pos: " << pos << " in_start:"<< in_start << endl;
    size_t len = pos - in_start;
    root -> left = build(pre, pre_start+1, pre_start + len,
                         in, in_start, in_start + len - 1);
    root -> right = build(pre, pre_start + 1 + len,pre_end,
                          in, in_start + len + 1, in_end);
    return root;
}

/*
 * 迭代器版本 [pre_first,pre_last)
 */
TreeNode* Solution::build(vector<int>::iterator pre_first, vector<int>::iterator pre_last,
                vector<int>::iterator in_first, vector<int>::iterator in_last){
    if (pre_first == pre_last) return nullptr;
    if (in_first == in_last) return nullptr;

    TreeNode *root = new TreeNode(*pre_first);
    //使用迭代器访查找某个范围内[in_first,in_last)值；返回找到值的迭代器值，否则返回in_last
    auto it = std::find(in_first,in_last, *pre_first); //algorithm
    int left_size = distance(in_first, it);

    root->left = build(next(pre_first), next(pre_first,left_size+1),
                       in_first, next(in_first, left_size));

    root->right = build(next(pre_first,left_size+1),pre_last,
                        next(it),in_last);
    return root;
}

/*
 * in:  2,3,4,5,7,8
 * post:3,2,4,8,7,5
 *
 * 后根遍历最后一个元素是：root节点元素
 *
 */

TreeNode* Solution::build_post(vector<int>::iterator in_first, vector<int>::iterator in_last,
        vector<int>::reverse_iterator post_rfirst, vector<int>::reverse_iterator post_rlast){


    //结束条件：首位指针位置相同
    if ((in_first == in_last) || (post_rfirst == post_rlast))
        return nullptr;

    //构造节点
    TreeNode *root = new TreeNode(*post_rfirst);

    auto it = std::find(in_first,in_last, *post_rfirst);//在in序列中查找元素
    int right_len = std::distance(it,in_last) - 1;

    root->left = build_post(in_first,it,post_rfirst+right_len+1,post_rlast);
    root->right = build_post(it+1,in_last,post_rfirst+1,post_rfirst+right_len+1);

    return root;

}


//计算树的最小高度
//非递归：使用按层次遍历(广度)遍历思想 + 剪枝
int Solution::min_depth(TreeNode *root){

    if (!root)
        return 0;
    queue<pair<TreeNode*, int> > qu;
    int result = INT_MAX;
    int depth = 1;
    qu.push(make_pair(root,depth));

    while(!qu.empty()){
        TreeNode *p = qu.front().first;
        depth = qu.front().second;
        qu.pop();
        //如果是叶子，需要计算深度
        if(!p->left && !p->right){
            result = min(result,depth);
        }
        //左子树，入队;如果本层的depth已经大于等于当前res了，没有必要再把高的分支入队了
        if(p->left && depth < result){
            qu.push(make_pair(p->left,depth+1));
        }
        //右子树
        if(p->right && depth < result){
            qu.push(make_pair(p->right,depth+1));
        }
    }//end while
    return result;
}




void binary_tree_build_test(){

//    int pre[] = {1, 2, 4, 5, 3, 6};
//    int in[] =  {4, 2, 5, 1, 3, 6};

    int pre[] = {5,4,2,3,7,8};
    int in[] =  {2,3,4,5,7,8};
    int post[] = {3,2,4,8,7,5};

    int len = sizeof(pre)/sizeof(int);

    cout << "pre sequence len: " << len <<endl;
    vector<int> pre_order(pre,pre+len);
    vector<int> in_order(in,in+len);
    vector<int> post_order(post,post+len);

    Solution s;

    //使用构建版本1，迭代器版本
    TreeNode* root1 = s.build_tree1(pre_order,in_order);

    //使用构建版本2，使用下标版本
    TreeNode* root2 = s.build_tree2(pre_order,in_order);

    //使用版本3，后序+中序 构造二叉树

    TreeNode *root3 = s.build_tree3(in_order,post_order);

    cout << "post travese root1: " << endl;
    s.post_traverse(root1);

    cout << endl << "post travese root2: " << endl;
    s.post_traverse(root2);

    cout << endl << "pre travese using stack: " << endl;
    s.pre_traverse(root1);

    cout << endl << "pre travese2 using stack: " << endl;
    s.pre_traverse2(root1);


    cout << endl << "in order travese using stack: " << endl;
    s.in_traverse(root1);

    cout << endl << "post order travese2 using stack: " << endl;
    s.post_traverse2(root1);

    cout << endl << "pre travese root3 using stack: " << endl;
    s.pre_traverse2(root3);

    cout << endl <<"the max depth of tree:  " << s.min_depth(root1) << endl;





}






