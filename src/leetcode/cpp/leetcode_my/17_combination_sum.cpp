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

