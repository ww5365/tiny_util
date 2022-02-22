#include "all.h"

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>
#include <iterator>
using namespace std;


/*
* 描述：
  一个编解码系统采用一种编解码策略，一个数字后面跟相应数目个字符，比如118computer1a,可以拆成11 +“ 8computer1a”，也可以拆成1+“1”+8+“computer”+1+“a”，这种情况称为歧义。
  给一个字符串，如果按编码策略只有一种解码方式即无歧义则返回去掉数字后的长度，否则返回-1。

题意的理解：
  1、字符串肯定是以数字开头或连续的数字开头，因为这个编码系统是一个数字加字符串的编码系统。

思路：
  1、不需要遍历所有的字符串，把数字提取出来，形成深度搜索标的即可。
  2、搜索的宽度，回溯宽度，就是开头的连续的数字。
  3、搜索的深度, 从当前start + 上面连续数字的偏移量，之后的编码串形成下一轮的深搜
  4、剪枝：？

*/

class Solution {
public:
    int getLength(string encodedString)
    {
        // 从字符串中提取出所有数字字符, nums长度保持和encodedString相同；
        vector<char> nums(encodedString.size(), 0);
        for (size_t i = 0; i < encodedString.size(); ++i) {
            if (isdigit(encodedString[i])) {
                nums[i] = encodedString[i];
            } 
        }

        // 打印
        std::copy(nums.begin(), nums.end(), std::ostream_iterator<char>(std::cout, ","));
        std::cout << std::endl;
        
        vector<int> path;  // 一种情况的数字分割的结果
        vector<vector<int>> result;
        dfs(nums, 0, path, result);

        // 打印结果
        for (auto &vec: result) {
            for (auto elem : vec) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }

        int numLen = 0;
        if (result.size() == 1) {
            for (auto &elem : result[0]) {
                numLen += std::to_string(elem).size();
            }
            // 去掉关键分割数字后的长度
            return (encodedString.size() - numLen);
        } else {
            return -1;
        }
    }

private:
    
    void dfs (const vector<char> &nums, size_t start, vector<int> &path, vector<vector<int>> &result)
    {

        if (start > nums.size()) {
            return;
        }
        if (result.size() > 1) {
            // 当有2个结果时，其实就不用在回溯了; 剪枝
            return;
        }
        if (start == nums.size()) {
            result.push_back(path);
            return;
        }
        string tmp = "";
        size_t idx = start;
        while (idx < nums.size() && nums[idx] != 0) {
            // 开头是数字或连续的数字 
            tmp += nums[idx];
            int jump = std::stoi(tmp);
            path.push_back(jump);
            dfs(nums, idx + jump + 1, path, result);
            path.pop_back();
            ++idx;
        }
    }
};

void TestEncodingAmbiguity()
{
    Solution s;
    // string str = "118computer1a";

    // string str = "118computer1a118computer1a";
    string str = "1a1b";

    std::cout <<"---------TestEncodingAmbiguity----------------" <<std::endl;
    int len = s.getLength(str);
    
    std::cout << "TestEncodingAmbiguity result: " << len << std::endl;

    return;

}