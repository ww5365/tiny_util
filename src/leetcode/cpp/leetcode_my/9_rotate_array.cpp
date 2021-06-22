/*
 * 9_rotate_array.cpp
 * Created on: Dec 13, 2017
 * Author: wangwei69
 *
 * problem:
 * Rotate an array of n elements to the right by k steps.
 * For example, with n = 7 and k = 3 ,
 * the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4]
 * Note: Try to come up as many solutions as you can,
 * there are at least 3 different ways to solve this problem.
 *
 * 分析：尽可能多的解法。
 * 1、简单粗暴：将前n-k个元素放到arr1；把后k个元素放到数组arr2；将两个数组中合并；时间：o(n)空间:o(n)
 * 2、直接把元素放到合适的位置：从前往后，第i位置上元素，放到i'=(i+k)%n的位置上；将i'的元素放到i''=(i'+k)%n位置上。。
 *    依次类推。。 时间：o（n） 空间：o（1）
 * 3、三次reverse
 *
 */





class Solution{


};



