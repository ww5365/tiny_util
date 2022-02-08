/*
 * basic_2_rotated_array.cpp
 *
 *  Created on: Jul 17, 2019
 *      Author: wangwei69
 */

/*
 * 问题一：
 *
 * 旋转数组： 1234 -> 3412
 *
 * 寻找旋转数组中最小的元素值? 比如上面的旋转数据：1
 *
 * 时间复杂度： logN
 *
 *  如果用二分，最大的痛点？没有target  怎么选？
 *
 *  选择last number作为target合理吗？
 *
 *  旋转数组：肯定是1个或2个递增数列 ，最小元素一定是<=最后一个元素
 *
 *  target = last number : 选择最后一个元素作为寻找的目标
 *
 *  最后问题抽象：寻找小于target的第一次出现的元素
 *
 *  first current   <=  last number
 *
 */
#include "chapater_nine.h"

//寻找旋转数组中最小的元素
int findMinElement(vector<int> &vec){

   if (vec.empty()){
       return -1;
   }

   int start = 0;
   int end = vec.size() - 1;

   /*
    * 1、实践：二分的模板
    * 2、旋转数组：二分法的变形；怎么个变化？没有target了，怎么确定target
    */

   int target = vec[end]; //这个target是固定的，没有问题。
   while (start + 1 < end){
       int mid = start + (end - start)/2;

       if (vec[mid] <= target){
           end = mid; //往左移区间；
       }else{
           start = mid;
       }
   }
   //最后有两个元素
   return std::min(vec[start], vec[end]);
}


/*
 *
 * 旋转数组：   3567 12
 *
 * 问题二：
 *
 * 查找旋转数组中指定的target，返回目标的索引下标；否则返回-1； 数组中不存在重复数字；
 *
 * 分析问题能力  +  实现能力
 *
 * 通过画图，分析旋转数组；mid截断之后，会发现至少有一半是单调的；
 * 利用这一半单调性，来缩小搜索空间；

 * leetcode : 33. 搜索旋转排序数组
 *
 *
 */

int findElement(vector<int> &vec, int target){

    if (vec.empty()){
        return -1;
    }

    int start = 0 ;
    int end = vec.size() - 1;

    while(start + 1 < end){
        int mid = start + (end - start)/2;
        if (vec[mid] == target){
            return  mid;
        }
        //如果左半边是单调区间
        if (vec[start] <= vec[mid]){
            if (vec[start] <= target && vec[mid] > target){
                end = mid; //循环下轮就可以在左半边进行正常的二分查找了
            }else{
                start = mid; //下轮继续进行旋转数组的查找
            }
        }else{//右边是单调区间
            if (vec[mid] < target && vec[end] >= target){
                start = mid;
            }else{
                end = mid;
            }
        }
    }


    if (vec[start] == target){
        return start;
    }

    if (vec[end] == target){
        return end;
    }

    //未搜索到结果
    return -1;
}


/*
 * 问题三：
 *
 * 1、给出一个旋转数组,请恢复成原来的位置 ： [3,4,5, 1,2]  -> [1,2,3,4,5]
 *
 * 2、给出一个字符串：abcdef  和 offset ，形成offset偏移的旋转字符串；
 *
 *    比如：abcdef offset=2 => efabcd
 *         abcdef offset=10 => cdefab
 *         abc offset = 0 => abc
 *
 *
 *  数学模型抽象:  AB <=> (B^-1 A^-1)^-1
 *
 */





void base_2_rotated_array(){

    std::cout << "base_2_rotated_array------------" << std::endl;

    vector<int> vec = {4,5,6,9,3,4};

    int element = findMinElement(vec);
    cout << "the minmum element is : " << element << endl;


    vector<int> vec2 = {4,5,7,9,1,2};
    int pos = findElement(vec2, 5);

    cout << "the target in rotated sorted array position: " << pos << endl;


}


