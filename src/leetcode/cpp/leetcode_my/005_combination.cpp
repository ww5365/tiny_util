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
        {1,2,3}=》{} {1} {2} {3} {12} {13} {23} {123}

 * 场景2： 集合C中元素有重复,  求所有重复的子集
        先排序
        水平方向的搜索空间，控制重复的数字，不再进入下一次结果
        {1,2,2} => {} {1} {1,2} {1, 2, 2} {2} {2, 2}  
 *
 */

// 2023.10.19

class Solution {

public:
    vector<vector<int>> Combination(vector<int> &vec)
    {
        vector<vector<int>> result;
        if (vec.size() <= 0) {
            return result;
        }
        vector<int> path;
        path.reserve(vec.size());
        dfs(vec, 0, path, result);
        return result;
    }


private:

    //  返回{1,2,3}的所有子集

    void dfs(const vector<int> &vec, int start, vector<int> &path, vector<vector<int>> &result)
    {

        if (start >= vec.size()) {
            result.push_back(path);
            return;
        }

        // 兩個深搜分支
        dfs(vec, start + 1, path, result);  // 不选当前元素
        
        path.push_back(vec[start]);   
        dfs(vec, start + 1, path, result);  // 选择当前元素
        path.pop_back();
    }


public:
    // 有重复数字{1,2,2} 所有子集  注意：{2} {2} 是重复的，只能算1个
    void dfs2(const vector<int> &vec, int start, vector<bool> &path, vector<vector<int>> &result) {

        if (start >= vec.size()) {
            vector<int> tmp;
            for (int i = 0; i < path.size(); ++i) {
                if (path[i])
                    tmp.push_back(vec[i]);
            }
            result.push_back(tmp);
            return;
        }


        // 选择当前元素，条件：前面的元素相同 && 没有被选择， 则当前重复元素已经被选择过,不选择

        if (start == 0 || vec[start] != vec[start - 1] || (vec[start] == vec[start-1] && path[start - 1])) {
            path[start] = true;
            dfs2(vec, start + 1, path, result);
            path[start] = false;
        } 
        
        dfs2(vec, start + 1, path, result); //还是不选当前元素

        return;
    }

};


// 之前
class Solution {

public:

    vector<vector<int>> combination(vector<int> &vec){

        vector<int> path;
        vector<vector<int>> res;
        //dfs1(vec, path, 0, res);
        // dfs2(vec, path, 0, res);

        sort(vec.begin(), vec.end(), less<int>());
        dfs3(vec, 0, path, res);

        return res;
    }


    // 对应场景2： 有重复的数据的情况: 
    void dfs3(const vector<int> &vec, int start, vector<int> &path, vector<vector<int>> &result) {

        // 无需条件控制，每个深度的中间结果，直接进入结果
        result.push_back(path);
        for (int i = start; i < vec.size(); ++i) {
            if (i != start && vec[i] == vec[i - 1]) {
                continue; // 水平防线，去掉重复的
            }
            path.push_back(vec[i]);
            dfs3(vec, i + 1, path, result);
            path.pop_back();
        }
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

    cout << "combination3 res:------ " << endl;

    res.clear();
    vector<int> test3 = {1, 2, 2};
    res = s.combination(test3);

    for (auto one_subset : res){
        for (auto e : one_subset) {
            cout << e << " ";
        }
        cout << endl;
    }

    cout << "combination3 res:------- " << endl;
}





