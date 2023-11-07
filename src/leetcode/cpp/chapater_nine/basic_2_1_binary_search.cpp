/*
 * basic_2_binary_search.cpp
 *
 *  Created on: Jul 15, 2019
 *      Author: wangwei69
 */
#include "chapater_nine.h"

/*
 * 二分查找：
 *
 *  排序好的整数数组(可能包含重复), 二分查找first (last)出现元素target的索引位置（从0开始）；
 *
 *  eg： 1,2,3,4,5,5,6,7,8   target=5  first_pos = 4 last_pos = 5
 *
 *  下面也是实现二分法的通用的模板
 *
 */


int BinarySearch(vector<int> &vec, int target){

    if (vec.empty()){
        return -1;
    }

    // 初始状态
    int start = 0;
    int end = vec.size() - 1;
    //循环条件结束时，停留在最后两个元素的位置；
    while(start + 1  < end){
        int mid = start + (end - start)/2;
        if (vec[mid] == target){
            end = mid;  //查收第一个出现target索引位置
        }else if (vec[mid] < target){
            start = mid; //不断往右移动，减少搜索空间
        }else{
            end = mid;  //不断往左移动
        }
    }
    if (vec[start] == target)
        return start;
    if (vec[end] == target)
        return end;

    return -1;
}


void base_2_binary_search(){

    vector<int> vec = {3,1,5,9,10,13,2,10};
    std::stable_sort(vec.begin(), vec.end());

    int target = 10;
    int pos1 = BinarySearch(vec, target);

    int pos2 = BinarySearch(vec, 15);


    cout << "first find pos : " << pos1  << endl;

    cout << "second find pos : " << pos2  << endl;



}





