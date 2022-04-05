#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>

#include <iterator>


using namespace std;

/*

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
                    dp[i][j] = (s[i] == s[j]);
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
};

void TestMaxLongestPalindrome()
{
    Solution s;
    cout << "-----------TestMaxLongestPalindrome----------------" << endl;
    string str = "babad";
    string result = s.PalindromeMemo(str);
    cout << "result: " << result << endl;
    cout << "-----------TestMaxLongestPalindrome finished-------------" << endl;
}
