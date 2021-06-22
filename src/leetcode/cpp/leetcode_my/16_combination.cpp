/*
 * 16_combination.cpp
 *
 *  Created on: Feb 22, 2018
 *      Author: wangwei69
 */

#include <vector>
#include <iostream>
#include <cmath>
#include <memory>
#include <algorithm>
#include "test_main.h"

using namespace std;

/*
 * 求集合C的所有子集
 *
 * 场景1： 集合C中元素都不重复
 * 场景2： 集合C中元素有重复
 *        两种处理方法：
 *        1、直接排序后去重，再进行求子集
 *        2、排序后，不去重，进行求子集；在求子集的过程中
 *
 */

class Solution{

public:

    vector<vector<int>> combination(vector<int> &vec){

        vector<int> path;
        vector<vector<int>> res;

        //dfs1(vec, path, 0, res);

        dfs2(vec, path, 0, res);

        return res;
    }


    /*
     * 位向量法：非递归的方式
     * 二进制加1，实现全部的组合排列
     */

    vector<vector<int>> combination2(vector<int> &vec){

        vector<bool> *bit_set = new vector<bool>(vec.size(), false);
        vector<int> path;
        vector<vector<int>> res;
        res.push_back(path); //先把空集合加入
        if (vec.size() <= 0){
            return res;
        }

        for(auto e: vec){
            cout << "test in fun: " << e << endl;
        }

        while (add_one(*bit_set)){
            int index  = 0;
            path.clear();
            for (auto e : *bit_set){
                if (e){
                    path.push_back(vec[index]);
                }
                ++index;
            }
            res.push_back(path);
        }

        return res;
    }


private:

    //开开眼，不同的实现方式，来实现求集合的子集

    /*
     *  DFS: 深度搜索
     *  通用的深搜的实现方式: 递归调用树
     *
     *  比如：1，2，3
     *
     *  dfs1： 先找以当前path开头的子集合
     *  dfs2： 一层一层的决策要不要选择，类似实际人工计算子集合
     *
     */


    //递归的定义
    void dfs1(vector<int> &vec,
              vector<int> &path,
              int start,
              vector<vector<int>> & res){

        // 递归分拆： 先把以某个值开头的结果，加入到结果集合中
        res.push_back(path); //第一次是空集

        for(int i = start; i < vec.size(); ++i){

            path.push_back(vec[i]);

            dfs1(vec, path, i + 1, res);

            path.pop_back();

        }
        //递归出口
        //return;
    }

    void dfs2(vector<int> &vec,
              vector<int> &path,
              int start,
              vector<vector<int>> &res){

        //递归定义出口
        if (start >= vec.size()){
            res.push_back(path);
            return;
        }

        //选择当前元素进入到子集
        path.push_back(vec[start]);
        dfs2(vec, path, start + 1, res);
        path.pop_back();
        //不选当前元素进入子集
        dfs2(vec, path, start + 1, res);
    }

    //实现bool型数组作为二进制数，自动加1
    bool add_one(vector<bool> &selected);

};


/*
 * 实现bool型数组作为二进制数，自动加1
 * 正常返回true；溢出时，返回false；
 *
 * example：
 * 110 + 1 -> 111 返回true
 * 111 + 1 -> 1000 ,溢出，返回false
 */

bool Solution::add_one(vector<bool> &selected){
    bool flag = true; //进位标识
    int i = 0;
    for(i = selected.size() - 1; i >= 0 && flag; --i){
        flag = (selected[i] + 1)/2;  //判断进位标识
        selected[i] = (selected[i] + 1)%2; //每个位置进位后剩余的值
        //cout << "e: " << selected[i] << endl;
    }
    if (flag && i == -1){
        //溢出
        return false;
    }
    return true;
}


void combination_test(){

    Solution s;


    vector<int> test = {1, 4, 2, 3, 2};


    //先集合进行排序,去重
    std::sort(test.begin(), test.end(), std::less<int>());

    auto it = std::unique(test.begin(), test.end());  //去重后，返回的结果，是最后一个元素之后迭代器，但容器的大小没变，需要把it之后的元素删除
    test.erase(it, test.end());

    std::for_each(test.begin(), test.end(), [](const int elem){cout <<  "unique res:" << elem << endl;});


    vector<vector<int>> res = s.combination(test);

    cout << "all subset: " << endl;
    for (auto one_subset : res){
        for (auto e : one_subset){
            cout << e << " ";
        }
        cout << endl;
    }

    cout << "combination res: " << res.size() << endl;
    res.clear();

    res = s.combination2(test);

    cout << "all subset2: " << endl;
    for (auto one_subset : res){
        for (auto e : one_subset){
            cout << e << " ";
        }
        cout << endl;
    }

    cout << "combination2 res: " << res.size() << endl;

}





