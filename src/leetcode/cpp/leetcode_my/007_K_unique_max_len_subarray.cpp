#include "01_all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>


using namespace std;

/*

### 2 至多包含 K 个不同字符的最长子串 ([#340](https://leetcode-cn.com/problems/longest-substring-with-at-most-k-distinct-characters/))

lintcode：[386 最多有k个不同字符的最长子字符串](https://www.lintcode.com/problem/386/solution)


给定字符串S，找到最多有k个不同字符的最长子串T。

输入: S = "eceba" 并且 k = 3
输出: 4
解释: T = "eceb"

1、循环遍历将字符加入到结果，同时hash记录已经选择的字符，出现次数
2、不同字符量>k, left指针移动，并将hash中出现的次数-1, 当出现次数为0的字符时，从hash中删除该字符。left 初始化为-1， 此窗口字符不在结果内；
3、每轮都需要计算子串的长度：right - left 

*/


class Solution {
public:
    
    int lengthOfLongestSubstringKDistinct(string &s, int k) {
        int left = -1;  // left的指向，就不在窗口内的了
        unordered_map<char, int> charCnt;
        int maxLen = 0;

        for (int right = 0; right < s.size(); ++right) {
            if (charCnt.count(s[right]) == 0) {
                charCnt[s[right]] = 0;
            }
            charCnt[s[right]] ++;
            
            int charDistinctCnt = charCnt.size();
            while (charDistinctCnt > k && left <= right) {
                charCnt[s[++left]]--;
                if (charCnt[s[left]] == 0) {
                    charCnt.erase(s[left]);
                    charDistinctCnt --;
                }
            }

            if ((right - left) > maxLen) {
                maxLen = (right - left);
            }
        }
        return maxLen;
    }
};

void TestKUniqueMaxLenSubArray()
{
    Solution s;
    string str = "eceba";
    cout << "-----------TestKUniqueMaxLenSubArray----------------" << endl;
    int result = s.lengthOfLongestSubstringKDistinct(str, 3);
    cout << "TestKUniqueMaxLenSubArray result = " << result << endl;
    cout << "-----------TestKUniqueMaxLenSubArray finished-------------" << endl;
}