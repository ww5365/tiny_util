/*
 * 13_largest_rectangle_histogram.cpp
 *
 *  Created on: Jan 11, 2018
 *      Author: wangwei69
 */


/*
 * 问题：
 * Given n non-negative integers representing the histogram's bar height where the width of each bar is 1,
 * find the area of largest rectangle in the histogram。
 *
 * 分析：[2,1,5,6,2,3]
 *
 * 笨方法：扫描，每个index处，对前面的每个数据求最小值，计算最大面积；时间复杂度：o(n^2)
 *
 *
 * stack:
 *
 * 1 、栈中保存递增序列的index下标；
 * 2、栈为空 或 当前元素大于栈顶元素，继续入栈
 * 3、当前元素小于栈顶元素，发生转折；计算之前所有比当前元素大的构成最大面积；直至栈顶比当前元素小或者为空；
 *
 *
 */

#include "test_main.h"
#include <algorithm>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

class Solution {

public:

    int largestRectangleArea(vector<int> &heights) {

        stack<int> s;
        heights.push_back(0);
        int result = 0;
        for (int i = 0; i < heights.size();) {
            if (s.empty() || heights[i] > heights[s.top()]){
                cout << "push i: " << i <<" value: " << heights[i] << endl;
                s.push(i++);
            }
            else {
                int tmp = s.top();
                cout << "pop i: " << i <<  " value: " << heights[tmp] << endl;
                s.pop();
                result = max(result,
                heights[tmp] * (s.empty() ? i : i - s.top() - 1));
            }
            cout << "------result: " << result << endl;
        }//end for

        return result;
    }
};


void largest_rectange_histogram_test(){

    int arr[] = {2,1,5,6,2,3,0};
    vector<int> vec(arr,arr+7);

    for(auto e: vec){
        cout << e << " ";
    }

    cout << endl;

    Solution s;
    int result = s.largestRectangleArea(vec);


    cout << "largest rectangle area: " << result << endl;


}




