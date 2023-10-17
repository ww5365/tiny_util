#include "01_all.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
using namespace std;

/*
136 : https://www.lintcode.com/problem/136/description

给定字符串 s, 需要将它分割成一些子串, 使得每个子串都是回文串.
返回所有可能的分割方案.

输入: "aab"
输出: [["aa", "b"], ["a", "a", "b"]]
解释: 有两种分割的方式.
    1. 将 "aab" 分割成 "aa" 和 "b", 它们都是回文的.
    2. 将 "aab" 分割成 "a", "a" 和 "b", 它们全都是回文的.

思路：dfs
1. 关键怎么取到所有的子串？  2^(n - 1)
2. 再判断这个子串是否为回文子串  n

*/

class Solution {
public:
    /*
     * @param s: A string
     * @return: A list of lists of string
     */
    vector<vector<string>> partition(string &s) {
        // write your code here

        vector<string> path;
        vector<vector<string>> res;

        dfs(s, path, res);
        
        return res;
    }


private:
    void dfs(const string &s, vector<string> &path, vector<vector<string>> &result) {


        if (s.size() <= 0) {
            result.push_back(path);
            return;
        }

        // DFS + 剪枝
        for (int len = 1; len <= s.size(); ++len) {

            string tmp = s.substr(0, len); // 注意第2个参数len最大可以是s.size()
            // std::cout << "tmp: " << tmp << std::endl;
            if (IsParlidrome(tmp)) {
                path.push_back(tmp);
                dfs(s.substr(len), path, result);

                // std::cout << "pop elem: " << path.back() << std::endl;
                path.pop_back();
            }
        }

        return;

        // 时间复杂度：o(n*2^n)  空间：o(n)
    }

    // 判断是否为回文串
    bool IsParlidrome(const string &s) {

        if (s.size() <= 1){
            return true;
        }

        int left = 0;
        int right = s.size() - 1;
        
        while (left < right) {

            if (s[left] != s[right]) {
                return false;
            }

            left ++;
            right --;
        }

        return true;
    }
};


/*
108 · 分割回文串（二）
108 : https://www.lintcode.com/problem/108

给定字符串 s, 需要将它分割成一些子串, 使得每个子串都是回文串.
最少需要分割几次?

输入：
s = "aab"  
输出：1

分析:

f(i) : 前i个字符串的最少分割次数, 前i个字符可以分为： s[0, j] + s[j+1, i] 两部分, 0 <= j <= i -1
       如果s[j+1, i] 是回文串，则：f(i) = f(j) + 1  或  0  s[0,i]是回文串

抽象:
f(i) = 0  s[0, i] 是回文串
f(i) = min{f(j)} + 1  s[j+1, i]是回文串， 0 <= j <= i-1

s[0, i] / s[j+1, i] : 是否为回文串，怎么获取？使用dp先判断各子串的是否为回文的情况，查表

dp[i][j] =  dp[i + 1][j - 1] & (s[i] == s[j]) j - i >= 2
dp[i][j] = (s[i] == s[j]) j-i <= 1


*/


class Solution2 {
public:
    /**
     * @param s: A string
     * @return: An integer
     */
    int minCut(string &s) {
        // write your code here

        if (s.size() <= 0)
            return 0;

        int n = s.size();
        vector<vector<bool>> dp(n , vector<bool>(n, true));

        // 是否为回文子串的回忆录表
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                if (j - i <= 1) {
                    dp[i][j] = (s[i] == s[j]);
                } else {
                    dp[i][j] = dp[i+1][j-1] & (s[i] == s[j]);
                }
            }
        }

        // 搜索memo表，计算最少分割次数

        vector<int> f(n, std::numeric_limits<int>::max());
        for (int i = 0; i < n; ++i) {
            if (dp[0][i]) {
                f[i] = 0;
                continue;
            }
            for (int j = 0; j < i; ++j) {
                if (dp[j+1][i]) {
                    f[i] = std::min(f[i], f[j] + 1);
                }
            }
        }

        return f[n - 1];
    }
};



void TestSplitParlidrome()
{
    std::cout << "----begin to TestSplitParlidrome ---" << std::endl;

    string str = "abc";

    Solution s;
    vector<vector<string>>res = s.partition(str);

    std::cout << "res size: " << res.size() << std::endl;

    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[i].size(); ++j) {

            std::cout << res[i][j] << " ";
        }

        std::cout << std::endl;
    }


    Solution2 s2;
    string str2 = "aab";
    int minCutNum = s2.minCut(str);

    std::cout << "min cut num parlidrome: " << minCutNum << std::endl; 

    std::cout << "----finished TestSplitParlidrome ---" << std::endl;
}
