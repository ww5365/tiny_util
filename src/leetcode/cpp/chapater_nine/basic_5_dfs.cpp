/*
 * basic_5_dfs.cpp
 *
 *  Created on: Sep 27, 2019
 *      Author: wangwei69
 */

#include <string>
#include <vector>

#include <iostream>


using namespace std;

/*
 * 1、给定字符串s，切成子串，使得每个子串都是回文的子串;返回所有可能的分割方案。
 * problem:
 * https://www.jiuzhang.com/solutions/palindrome-partitioning/
 * https://www.lintcode.com/problem/palindrome-partitioning/description
 *
 * Decribe:
 * Given a string s. Partition s such that every substring in the partition is a palindrome.
 * Return all possible palindrome partitioning of s.
 *
 * 
 * 一个问题包含了两种算法考察：？
 * a. 如何得到字符串的所有的子串：  组合问题
 * b. 如何判断一个字符串是回文：    动态规划
 *
 */

class Solution{

public:
    void all_substring(string &s){
        vector<string> path;
        vector<vector<string> > res;
        palindromeTable(s);
        dfs(s, 0, path, res);

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
                cout << elem << "|";
            }
            cout << endl;
        }
    }

    //version1: 深度优先算法，切分字符串s，得到所有切割方案;参考版本
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
     * 判断一个字符串是否为回文串
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
    Solution test;
    string s = "abc";
    //test.all_substring(s);
    vector<string> path;
    vector<vector<std::string> > res;
    test.dfs(s, path, res);
    test.print_res(res);

}



