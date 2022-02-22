/*
 * 3_longest_consecutive_sequence.cpp
 *
 *  Created on: Nov 18, 2017
 *      Author: wangwei69
 */

#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;


/* 1、问题描述：
 * Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
 * For example, Given [100, 4, 200, 1, 3, 2] , The longest consecutive elements sequence is [1, 2, 3, 4] .
 * Return its length: 4.
 * Your algorithm should run in O(n) complexity.
 *
 * 2、问题分析：
 * 如果是O(nlogn)的时间复杂度，可以考虑排序再选取
 * 要求是：O(n)  而且是无序的vector,要实现O(n)算法，优先考虑：哈希;
 * 思路：使用hashtable，存放数据；对每个元素前后找寻；记录最长len； hashtable不用自己实现；
 *
 * C++11提供了：unorder_set 关联容器，实现了hashtable；-std=c++11
 *
 */

class Solution{
public:
    int longestConsecutive(const vector<int> &nums){

        unordered_set<int> nums_hash;
        for (auto e:nums){
            nums_hash.insert(e);
        }

        int longest_len = 0;


        for (auto e:nums){
            int len = 1;
            for(int j = e-1;nums_hash.find(j) != nums_hash.end(); --j){
                nums_hash.erase(j);
                len++;
            }

            for(int k = e+1;nums_hash.find(k) != nums_hash.end(); ++k){
                nums_hash.erase(k);
                len++;
            }

            if (longest_len < len)
                longest_len = len;
        }

        return longest_len;
    }
};


void longest_consecutive_sequence(){

    vector<int> test;
    test.push_back(110);
    test.push_back(120);
    test.push_back(11110);
    test.push_back(10);
    test.push_back(11);
    test.push_back(111);
    test.push_back(112);

    Solution s;
    int len = s.longestConsecutive(test);

    std::cout << "the longest consecutive sequence len: " << len <<std::endl;

}


