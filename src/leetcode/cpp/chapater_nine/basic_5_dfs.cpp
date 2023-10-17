/*
 * basic_5_dfs.cpp
 *
 *  Created on: Sep 27, 2019
 *      Author: wangwei69
 */

#include <string>
#include <vector>

#include <iostream>
#include <algorithm>
#include <iterator>

#include "chapater_nine.h"

using namespace std;

/*

深度优先搜索的总结、关注点

1、确定搜索空间： leetcode类的问题比较少，但对于应用类问题，需要首先确定搜索空间是什么？这类题目的难度稍大些。

2、搜索空间的大小： 水平方向的移动，每次单步或每次多步

3、搜索深度： 如何进入下一层的深度搜索；问题规模减少，问题类似；可能需要判断进入下一层的条件。

4、剪枝：水平 或 进入到下一层 都有可能剪枝


*/




/* 分割回文串 · Palindrome Partitioning
 * 1、给定字符串s，切成子串，使得每个子串都是回文的子串;返回所有可能的分割方案。
 * problem:
 * https://www.jiuzhang.com/solutions/palindrome-partitioning/
 * https://www.lintcode.com/problem/palindrome-partitioning/description
   
   lintcode : 136 
 *
 * Decribe:
 * Given a string s. Partition s such that every substring in the partition is a palindrome.
 * Return all possible palindrome partitioning of s.
 *
 * 输入: "aab"
   输出: [["aa", "b"], ["a", "a", "b"]]
   解释: 有两种分割的方式.
    1. 将 "aab" 分割成 "aa" 和 "b", 它们都是回文的.
    2. 将 "aab" 分割成 "a", "a" 和 "b", 它们全都是回文的.

 * 两种算法思路？
 * a. 如何得到字符串的所有的子串：  组合问题 dfs  + 判断子串是否为回文串
 * b. 备忘录方法来判断字符串的子串是否为回文串？：    动态规划
 *
 */

class Solution{

public:
    void all_substring(string &s){
        vector<string> path;
        vector<vector<string> > res;
        // palindromeTable(s);
        // dfs(s, 0, path, res);
        dfs2(s, path, res);
        print_res(res);
    }
    Solution(): arr(nullptr), arr_len(0){}
    ~Solution(){
        if (arr){
            for (int i = 0; i < arr_len; ++i){
                delete []arr[i];
            }

            delete []arr;
        }
    }
private:
    bool **arr;
    int arr_len;

public:

    void print_res(vector<vector<string> > &res){
        //打印结果
        if (res.empty()){
            cout << "there is no sub string result!" << endl;
        }
        cout << "all substring : " << res.size() << endl;
        for (auto elems: res){
            for (auto elem: elems){
                cout << elem << ",";
            }
            cout << endl;
        }
    }

    //version1: 深度优先算法，切分字符串s，得到所有子串的方案;参考版本
    //切割的方案：2^n 组合问题

    void dfs(const string &s, vector<string> &path, vector<vector<string> > &res){

        size_t len = s.size();
        if (len == 0) {
            res.push_back(path);
            return;
        }

        for(int idx = 1; idx <= len ; ++idx){
            path.push_back(s.substr(0, idx));
            dfs(s.substr(idx), path, res);  //怎么保持递归调用中，s是同一个，而不是发生值拷贝？ 参数定义为const
            path.pop_back();
        }
    }

    //version2： 字符串s的切割成子串开始位置：start  自己实现的一个版本
    void dfs(string &s, int start, vector<string> &path, vector<vector<string> > &res){
        int len = s.size();
        if (start >= len){
            res.push_back(path);
            return;
        }
        //i代表截取长度
        for(int i = 1; i <= (len - start); ++i){
            string sub_str = s.substr(start, i);
            if (isPalindrome(s, start, start + i - 1)){
                path.push_back(sub_str);
                //cout << "sub_str---:" << sub_str  << " : " << start << ":"<< i << endl;
                dfs(s, start + sub_str.size(), path, res); //最关键：start + sub_str.size()  下层递归，起始点变化也就是水平方向和垂直方向相互制约
                path.pop_back();
            }
            //cout << "---------" << endl;
        }
    }


    /*
     * 判断一个字符串是否是回文子串/存在回文子串/多少回文子串/
     *  dp 算法
     *
     *  f(i,j): 0 <= i <= j < len  代表从索引位置i到j的子串
     *
     *  i==j ： true
     *  i==j-1: 两个字符： s[i] == s[j]
     *  i < j-1: f(i+1,j-1) + (s[i]==s[j])
     *
     */

    void palindromeTable(const string &s){

        cout << "palindromeTable creating !" << endl;
        int len = s.size();
        arr_len = len;
        arr = new bool*[len];
        for(int i = 0; i < len; ++i){
            arr[i] = new bool[len];
        }
        //初始化 i==j 对角线位置
        for (int i = 0; i< len; ++i){
                arr[i][i] = true;
        }
        //初始化 i==j-1
        for (int j=1; j < len; ++j){
            arr[j-1][j] = (s[j-1] == s[j]);
        }

        //上三角：右下角开始，从左到右，自下而上  结果：f(0,len-1)
        for (int i = len-3; i >= 0; --i){
            for (int j = i + 2; j < len; ++j){
                arr[i][j] = arr[i+1][j-1] && (s[i]==s[j]);
            }
        }
        cout << "palindromeTable created == !" << endl;
    }

    bool isPalindrome(const string &s, int start, int end){
        if (start < 0 || start >= s.size() || end < 0 || end >=s.size()){
            return false;
        }
        if (arr[start][end]){
            return true;
        }
        return false;
    }

    vector<string> PalindromeMemo(const string &s) {
        /* 
        * dp 的 备忘录法，找字符串中的所有的回文子串
        * 0<= i <= j < length 上三角
        * f(i,j) =  true  j - i = 0
          f(i,j) = s[i] == s[j]  j -i = 1
          f(i,j) = f(i+1, j-1) + s[] == s[j] j - i >= 2

          自下而上的记忆搜索
        */
        vector<string> result;
        if (s.size() <= 1) {
            result.push_back(s);
            return result;
        }

        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                if ((j - i) < 2) {
                    dp[i][j] = (s[i] == s[j]);
                } else {
                    dp[i][j] = dp[i + 1][j - 1] & (s[i] == s[j]);
                }

                if (dp[i][j]) {
                    result.push_back(s.substr(i, j - i + 1)); // 是回文子串
                }
                std::cout << " i: " << i << " j: " << j << " size: " << result.size()<< std::endl;
            }
        }
        
        std::cout << " finish in parlindrome fun" << std::endl;

        return result;
    }

    /*
    * 使用深搜 + 剪枝 

    * 找出子串中： 所有的回文子串

    */
    void dfs2(const string &s, vector<string> &path, vector<vector<string> > &res){

        if (s.size() == 0) {
            res.push_back(path);
            return;
        }

        for (int len = 1; len <= s.size(); ++len) {  // 注意第2个参数len最大可以是s.size()
            string tmp = s.substr(0, len);

            if (IsPalindrome(tmp)) {
                path.push_back(tmp);
                dfs2(s.substr(len), path, res);
                path.pop_back();
            }
        }
    }
    
    bool IsPalindrome(const string &s) {

        if (s.size() <= 1) 
            return true;

        int i = 0; 
        int j = s.size() - 1;

        while (i < j) {
            if (s[i] != s[j]) {
                return false;
            }
            i ++;
            j --;
        }
        return true;
    }

};


/*
 * word ladder2
 * 题目
 * 给出两个字符串start和end，以及对应的dict字典，找到所有从start变成end的最短的转换序列，要求如下：
 * 1、每次变换只能变其中的一个字符
 * 2、变换后的中间字符串需要在字典中
 * 3、给出从start到end的所有接龙路径，且是最短的
 *
 * 比如：
 * start = hit
 * end  = cog
 * dict={hot,dot,dog, lot, log}
 *
 * 问题抽象：？建模
 *
 */


void test_base_5_dfs(){
    
    std::cout << "-------test_base_5_dfs------" << std::endl; 
    Solution test;
    string s = "abc";
    //test.all_substring(s);
    vector<string> path;
    vector<vector<std::string> > res;
    test.dfs(s, path, res);
    test.print_res(res);

    string s2 = "aba";

    vector<string>res2 = test.PalindromeMemo(s2);
    std::cout << "test_base_5_dfs dp result:" << std::endl;
    std::copy(res2.begin(), res2.end(),std::ostream_iterator<string>(std::cout, ","));
    std::cout << std::endl;
    
    std::cout << "test_base_5_dfs dfs result:" << std::endl;
    test.all_substring(s2);

    std::cout << std::endl;

}



