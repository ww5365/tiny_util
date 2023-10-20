/*
 * 17_combination_sum.cpp
 *
 *  Created on: Feb 24, 2018
 *      Author: wangwei69
 */

/*
 * 问题描述：
 *
 * 集合：C ={12，7，5，3，2} 要求是：递减序列  target=7 找出所有子集合subset，使得sum(subset) = target;
 *      并且C中的每个元素都只能使用一次；
 * 比如本例子:{7} {5,2}
 *
 * 思路：面临多叉树的搜索，使用深度搜索算法，需要所有可能的解
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include "test_main.h"

using namespace std;



// 10.20  参考dfs3，实现了子集和

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

public:
    
    // C ={12，7，5，3，2} 要求是：递减序列  target=7 找出所有子集合subset，使得sum(subset) = target;并且C中的每个元素都只能使用一次；
    // https://www.lintcode.com/problem/153/   153 · 数字组合 II
    
    void dfs3(const vector<int> &vec, int start, int sum, vector<bool> &path, vector<vector<int>> &result) {


        if (start >= vec.size()) {
            if (sum == 0) {
                vector<int> tmp;
                for (int i = 0; i < path.size(); ++i){
                    if (path[i]) {
                        tmp.push_back(vec[i]);
                    }
                }
                result.push_back(tmp);
            }
            return;
        }
        // 考虑去重 和 剪枝 传入的vec是先排序的
        if (vec[start] <= sum && (start == 0 || vec[start] != vec[start - 1] || (vec[start] == vec[start-1] && path[start - 1]))) {
            path[start] = true;
            dfs3(vec, start + 1, sum - vec[start], path, result);
            path[start] = false;
        }

        dfs3(vec, start + 1, sum, path, result);
        return;
    }
};


// 之前
bool compare(int m,int n){
    return m>n;//升序排序
}

class Solution{
public:
    vector<vector<int> > combination_sum(vector<int> num, int target);
private:
    void dfs(vector<int> &num,vector<int> &path, int start, int gap, vector<vector<int> > &res);
};

vector<vector<int> > Solution::combination_sum(vector<int> num, int target){
    vector<vector<int> > res;
    vector<int> path;
    sort(num.begin(),num.end(),compare);
    dfs(num,path,0,target,res);
    return res;
}


void Solution::dfs(vector<int> &num,vector<int> &path, int start, int gap, vector<vector<int> > &res){

    //收敛条件
    if(gap == 0){
        res.push_back(path);
        return;
    }
    //多叉搜索
    for(int i = start; i < num.size();i++){
        if(gap < num[i]) continue;//剪枝
        path.push_back(num[i]);
        dfs(num,path,i+1,gap-num[i],res);//走一步继续搜索
        path.pop_back();//恢复原来；继续回溯
    }
}

void combination_sum_test(){
    vector<int> num;
    num.push_back(2);
    num.push_back(3);
    num.push_back(5);
    num.push_back(7);
    num.push_back(12);
    num.push_back(1);
    vector<vector<int> >res;
    Solution s;
    res = s.combination_sum(num,8);
    for(auto v : res){
        for (auto e : v){
            cout << " " << e << " ";
        }
        cout << endl;
    }

}

