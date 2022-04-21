#include "01_all.h"

#include <algorithm>
#include <vector>
#include <iostream>

#include <numeric>

#include <unordered_set>

using namespace std;

/*


 无重复字符的最长子串([#3](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/))

给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。

示例 1:

输入: s = "abcbcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

*/


class Solution {
public:

    int lengthOfLongestSubstring(string s)
    {
        int res = 0;
        unordered_set<char> charSet;
        for (int right = 0, left = 0; right < s.size(); ++right) {
            if (charSet.find(s[right]) != charSet.end()) {

                while (left < right && s[left] != s[right]) {
                    charSet.erase(s[left++]); // 左侧找到和当前字符相同的字符为止
                }
                left ++; // 移动到和当前right位置相同字符的下一个字符为止
            } else {
                res = std::max(res, right - left + 1);
                charSet.insert(s[right]);
            }
        }
        return res;
    }

};

void TestMaxUniqueSubString()
{
    string str = "abcabcdbbd";
    Solution s;
    cout << "-----------TestMaxUniqueSubString----------------" << endl;

    int result = s.lengthOfLongestSubstring(str);
    cout << "the longestSubstring result = " << result << endl;

    cout << "-----------TestMaxUniqueSubString finished!----------------" << endl;

}