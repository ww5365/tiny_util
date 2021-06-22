/*
 * 1_remove_duplicates_sort_array.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: wangwei69
 */

#include <vector>
#include <iostream>
#include "test_main.h"
using namespace std;

class Solution {

public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty())
            return 0;
        int index = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != nums[index - 1])
                nums[index++] = nums[i];
        }
        return index;
    }
};

void remove_duplicates_sort_array(){

    Solution s;
    vector<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(2);

    s.removeDuplicates(test);

    cout <<"test vector size:" <<s.removeDuplicates(test)<<endl;

    return;
}






