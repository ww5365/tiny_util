/*
 * ds_bst_rb_tree.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: wangwei69
 */

/*
 * bsTree：二叉排序树 (binary sort tree)
 * 实现：
 * 1、search 某个 key
 * 2、insert 某个不存在的key
 * 3、delete 某个存在的key
 * 4、build一颗二叉排序树：通过一个数组元素，创建一个二叉排序树
 *
 */


#include "test_main.h"
#include <stddef.h> //NULL
#include <vector>
#include <iostream>
using namespace std;

//定义二叉树的节点的数据结构

template<typename T>
struct BiTNode{
    T data;
    BiTNode<T> *left,*right;
};

//定义模板类型别名，不能在struct之前，直接用typedef
template<typename T>
using BiTNodePtr = BiTNode<T>* ;


template<typename T>
class BiTree {
private:
    BiTNodePtr<T> root;//二叉排序树的树根

public:
    BiTree(){root = NULL;}

    //使用vector数组中的元素的构造一颗二叉排序树数据；
    BiTree(vector<T> vec){
        root = NULL;
    }

    BiTNodePtr<T> getRoot(){
        return root;
    }

    /*
     * 二叉排序树的查找:递归实现
     *
     * 从位置begin开始，查找key值；
     * (*pos)保存key值对应的位置的指针；
     * parent保存对应key值的父节点指针；
     * 找到返回TRUE；否则返回FALSE；
     */
    bool search(BiTNodePtr<T> begin, T key, BiTNodePtr<T> *pos, BiTNodePtr<T> parent) const{

        cout << "enter into function search!" <<endl;
        if (!begin){
            *pos = NULL;
            parent = NULL;
            return false;
        }

        if (begin->data == key){

            *pos = begin;
            return true;
        }else if (begin->data < key){
            //到左子树进行搜索
            return this->search(begin->left, key, pos, begin);
        }else{
            return this->search(begin->right, key ,pos, begin);
        }

    }//end search
};



void bsTree_test(){


    BiTree<int> test;
    BiTNodePtr<int> *pos = NULL;
    test.search(test.getRoot(), 5, pos, NULL);



}

