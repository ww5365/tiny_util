#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>

#include <iterator>

#include <unordered_map>


using namespace std;

/*

214. 最短回文串  https://leetcode.cn/problems/shortest-palindrome/

给定一个字符串 s，你可以通过在字符串前面添加字符将其转换为回文串。找到并返回可以用这种方式转换的最短回文串。

输入：s = "aacecaaa"
输出："aaacecaaa"

思路：

1、暴力：
   首先求最長的回文前缀，把最长回文前缀去掉(已经是回文了，不用管)，求剩余部分的逆序reverse；最终将reverse部分加到原字符串上，就得到了最短的回文串

2. KMP: 
    KMP 的 next 数组记录的就是一个字符串的每个位置上，最长公共前后缀的长度。公共前后缀指的是前后缀相同

*/

class Solution {
public:
    string shortestPalindrome(string s) {
        if (s.size() == 0) {
            return "";
        }
        string rev = s;
        std::reverse(rev.begin(), rev.end());
        string str = s + "#" + rev;
        vector<int> next(str.size());
        int res = GetNext(str, next);
        return rev + s.substr(res + 1, s.size() - res);
    }
    
    int GetNext(string p, vector<int>& next) {
        next[0] = -1;
        int i = 0;
        int j = -1;
        while (i < p.size() - 1) {
            if (j == -1 || p[i] == p[j]) {
                i++;
                j++;
                next[i] = j;
            } else {
                j = next[j];
            }
        }
        return next[i];
    }
};

void TestShortestPalindrome()
{
    Solution s;
    cout << "-----------ShortestPalindrome----------------" << endl;
    string str = "aacecaaa";
    string result = s.shortestPalindrome(str);
    cout << "ShortestPalindrome result is : " << result << endl;
    cout << "-----------ShortestPalindrome finished-------------" << endl;
}

