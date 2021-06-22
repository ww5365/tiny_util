/*
 * 6_threeSumCloset.cpp
 *
 * Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target.
 * Return the sum of the three integers.
 * You may assume that each input would have exactly one solution.
 * For example, given array S = {-1 2 1 -4} , and target = 1 .
 * The sum that is closest to the target is 2. ( -1 + 2 + 1 = 2 ).
 *
 * 思路：？
 *
 * a + b + c ~= target  找三个数字他们的和最接近target；
 * 夹逼，绝对值最小
 *
 * 思路： 两根指针
 * 1、排序
 * 2、参考目标： -a  + target   也就是-nums[i] + target -》newtarget
 *    从left = i+1 和 right=len-1 两边开始，寻找nums[left] + nums[right] => newtarget
 *    如果相等，最接近target的三个数找到，而且a + b + c = target
 *    如果大于newtarget ， right--；计算绝对值，记录最小差距；
 *    如果小于newtarget ， left++； 计算绝对值，记录最小差距；
 *
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include "test_main.h"

using namespace std;

class Solution{
public:
    int threeSumClosest(vector<int> &num, int target){

        //默认前提，num长度大于3

        sort(num.begin(),num.end());

        int res = 0;
        int min_gap = INT_MAX;
        bool equal_flag = false; //空值循环次数

        for (auto e = num.begin(); !equal_flag && e != prev(num.end(),2); e++){
            auto k = next(e); // 获取迭代器前后位置的函数：prev & next
            auto l = prev(num.end());
            while(k < l){
                int sum = *e + *k + *l; //迭代器访问元素
                int gap = abs(sum - target);
                if(gap < min_gap){
                    min_gap = gap;
                    res = sum;
                }

                if (sum == target){
                    equal_flag = true;//相等情况下，最接近的。不用再找了
                    break;
                }else if(sum < target){
                    k++; //变大点
                }else{
                    l--; //变小点
                }
            }//while
        }//end for

        return res;
    }


    /*
     * 升级版本：发现这种问题，使用两个指针，同时也有比较统一的解决模板
     *
     */
    int threeSumClosest2(vector<int>& nums, int target) {

           sort(nums.begin(), nums.end(), std::less<int>());
           int min_dis = numeric_limits<int>::max();
           int dis = 0;
           int res;
           for (int i = 0; i < nums.size() - 2; ++i){
               int newtarget = target - nums[i];
               int left = i + 1;
               int right = nums.size() - 1;
               while (left < right){
                   if (nums[left] + nums[right] == newtarget){
                       return (nums[i] + nums[left] + nums[right]);
                   }else if (nums[left] + nums[right] < newtarget){
                       dis = std::abs(nums[left] + nums[right] - newtarget);
                       if (dis < min_dis){
                           res = nums[left] + nums[right] + nums[i];
                           min_dis = dis;
                       }
                       ++left;
                   }else{
                       dis = std::abs(nums[left] + nums[right] - newtarget);
                       if (dis < min_dis){
                           res = nums[left] + nums[right] + nums[i];
                           min_dis = dis;
                       }
                       --right;
                   }
               }
           }
           return res;
       }


};


void three_sum_closest(){

    int arr[] = {-2,-1,-1,0,1,2,2,11,3,3,4,5};
    vector<int> num(arr,arr + 12);
    cout <<"before process" <<endl;
    for(size_t i = 0; i < num.size(); i++){
        cout << num[i] << " ";
    }
    cout << endl;

    Solution s;
    int res = s.threeSumClosest(num,21);
    cout <<"after process" <<endl;
    for(size_t i = 0; i < num.size(); i++){
        cout << num[i] << " ";
    }
    cout << endl;

    cout << "the final res is: " << res <<endl;

}


