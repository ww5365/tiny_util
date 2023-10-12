
/*
 * 402 lintcode / leetcode: 
 */

#include "01_all.h"
#include <deque>
#include <queue>
#include <iostream>
#include <limits>
#include <vector>

#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
lintcode: 200 
https://www.lintcode.com/problem/200/description

leetcode: 5
https://leetcode.cn/problems/longest-palindromic-substring/description/

给你一个字符串 s，找到 s 中最长的回文子串。

示例 1：

输入：s = “babad”
输出：“bab”
解释：“aba” 同样是符合题意的答案。
示例 2：

输入：s = “cbbd”
输出：“bb”

提示：

1 <= s.length <= 1000
s 仅由数字和英文字母组成

*/

class Solution {
public:
    string PalindromeMemo(const string &s)
    {
        /*
        * dp 的 备忘录法，找字符串中的所有的回文子串
        * 0<= i <= j < length 上三角
        * f(i,j) =  true  j - i = 0
          f(i,j) = s[i] == s[j]  j -i = 1

          f(i,j) = f(i+1, j-1) + s[] == s[j] j - i >= 2

          自下而上的记忆搜索
        */
        string result;
        if (s.size() <= 1) {
            result = s;
            return result;
        }

        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                if ((j - i) < 2) {
                    dp[i][j] = (s[i] == s[j]); // 注意点1： 初始条件， 从尾部开始的上三角，初始化两个对角线
                } else {
                    dp[i][j] = dp[i + 1][j - 1] & (s[i] == s[j]);
                }

                if (dp[i][j]) {
                    string tmp = s.substr(i, j - i + 1); // 是回文子串
                    if (tmp.size() > result.size()) {
                        result = tmp;
                    }
                }
            }
        }
        return result;
    }

    string longestPalindrome(string &s) {
        /*
         * 2023.10.12
         * 双指针，从中间往两边进行扩展
         * 本质是穷举所有s[i], 进行扩展，得到最长回文子串；需要考虑单点起扩和两个邻接点起扩的两种情况
        */

        int start = 0;
        int end = 0;

        for(int i = 0; i < s.size() - 1; ++i) {

            pair<int, int> tmp1 = oneLongestValid(s, i, i);
            pair<int, int> tmp2 = oneLongestValid(s, i, i + 1);

            if (tmp1.second - tmp1.first > end - start) {
                start = tmp1.first;
                end = tmp1.second; // 求单点扩，最大长度
            }
            
            if (tmp2.second - tmp2.first > end - start) {
                start = tmp2.first;
                end = tmp2.second; // 在前面的基础上，求双点扩，最大长度
            }
        }

        return s.substr(start, end - start + 1);
    }

    //  返回[left, right]开始扩展，得到的最长回文子串的起始位置
    pair<int, int> oneLongestValid(string &s, int left, int right) {

        while(left >= 0 && right < s.size() && s[left] == s[right]) {
            left --;
            right ++;
        }
        return {left + 1, right - 1};
    }

};

void TestMaxLongestPalindrome()
{
    Solution s;
    cout << "-----------TestMaxLongestPalindrome----------------" << endl;
    string str = "babad";
    string result = s.PalindromeMemo(str);

    string result2 = s.longestPalindrome(str);
    cout << "result2: " << result2 << endl;
    cout << "-----------TestMaxLongestPalindrome finished-------------" << endl;
}
