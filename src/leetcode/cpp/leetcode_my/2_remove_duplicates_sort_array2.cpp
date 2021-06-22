/*
 * 2_remove_duplicates_sort_array2.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: wangwei69
 */


#include "test_main.h"

#include <vector>
#include <iostream>

using namespace std;


/* 1、problem description:
 * Follow up for "Remove Duplicates":
 * What if duplicates are allowed at most twice?
 * For example, given sorted array A = [1,1,1,2,2,3] ,
 * your function should return length = now [1,1,2,2,3]
 *
 *2、solution:
 * Remove Duplicates from Sorted Array II
 * Time complexity: O(n), Space Complexity: O(1)
 */

class Solution {

public:

    int removeDuplicates(vector<int>& nums) {

        if (nums.size() <= 2)
            return nums.size();
        int index = 2;
        for (int i = 2; i < nums.size(); i++) {
            if (nums[i] != nums[index - 2])
                nums[index++] = nums[i];
        }
        return index;
    }
};

void remove_duplicates_sort_array2(){
    Solution s;
    vector<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(2);
    test.push_back(2);

    s.removeDuplicates(test);

    cout <<"test vector2 size:" <<s.removeDuplicates(test)<<endl;



}


