#include "01_all.h"

#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;


/*
47. 全排列 II
https://leetcode.cn/problems/permutations-ii/

给定一个可包含重复数字的序列nums ，按任意顺序 返回所有不重复的全排列。

输入：nums = [1,2,3]
输出：
[[1,2,3],
 [1,3,2],
 [2,1,3],
 [2,3,1],
 [3,1,2],
 [3,2,1]
 ]

输入：nums = [1,1,2]
输出：
[[1,1,2],
 [1,2,1],
 [2,1,1]]

 思路：dfs
 1、无重复的情况： 
    每轮水平方向，搜索空间0~len，通过标识数组来知道选择哪个已被选，剩余哪些未选
    深度方向：更新标识数组，标识已选结果

 2、 有重复的情况：难点：如何判断重复的元素，已经被选过？那不能再选了。
     
     原始的数据排序，且
     水平方向，搜索空间中，vec[i-1] == vec[i] 元素相同，且 选vec[i]时，vec[i-1] 选择标识是false，说明此重复元素已经被选择过了。不用再选了。

*/



class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {

        std::sort(nums.begin(), nums.end(),less<int>());

        vector<int> path;
        vector<bool> selected;
        // path.reserve(nums.size());
        selected.reserve(nums.size());
        vector<vector<int>> result;

        dfs(nums, selected, path, result);

        return result;

    }

private:
    void dfs(const vector<int> &nums, vector<bool> &selected, vector<int> &path, vector<vector<int>> &result) {

        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }

        for (size_t i = 0; i < nums.size(); ++i) {
            if (selected[i]) {
                continue;
            }
            if (i != 0 && nums[i - 1] == nums[i] && !selected[i - 1]){
                // 去掉重复的元素，前提是nums是要排序的
                continue;
            }
            path.push_back(nums[i]);
            selected[i] = true;
            dfs(nums, selected, path, result);
            path.pop_back();
            selected[i] = false;
        }

    }

};


// 2023.9.28
class Solution2 {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {

        vector<vector<int>> res;
        vector<int> path; 
        vector<bool> selected(nums.size(), false); // 这个可以初始化， size大小和nums相同，都为false
        path.reserve(nums.size()); // 这个size大小为0，只预留空间但size大小为0
        // 先排序，去重的需要
        std::sort(nums.begin(), nums.end(), std::greater<int>());
        dfs(nums, path, selected, res);
    
        return res;
    }

private:

    void dfs(const vector<int> &nums, vector<int> &path, vector<bool> & selected, vector<vector<int>> &res) {

        if (path.size() == nums.size()) {
            res.push_back(path);
            return;
        }

        for (size_t i = 0; i < nums.size(); i++) {

            if (selected[i]) continue;

            // 去掉重复数字: 前后两个数字相同且前一个数字未被选择到，说明再选i就重复了，第i-1个数字已经被选择过了

            if (i != 0 && nums[i - 1] == nums[i] && selected[i - 1] == false) continue;

            selected[i] = true;
            path.push_back(nums[i]);
            dfs(nums, path, selected, res);
            path.pop_back();
            selected[i] = false;
        }
    }
};






void TestPermuteUnique() {

    // vector<int> nums = {1, 2, 3};
    vector<int> nums = {1, 2, 2};
    
    vector<int> test(nums.size());
    vector<int> test2;
    test2.reserve(nums.size());

    cout << "the size of vector: " << nums.size() << " " << test.size() << " " << test2.size()<< endl;
    vector<vector<int>> result;

    Solution s;
    result = s.permuteUnique(nums);

    cout << "-----------TestPermuteUnique----------------" << endl;

    for (const auto &vec : result) {
        for (const auto &elem : vec) {
            cout << elem << " ";
        }
        cout << endl;
    }

    cout << "-----------TestPermuteUnique finished----------------" << endl;

}
