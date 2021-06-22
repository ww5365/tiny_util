
#include "chapater_nine.h"


/*
 *
 *  Created on: Oct 14, 2019
 *      Author: wangwei69
 */

/*
 * 讨论基于数组的一些算法:  数组， 数据结构简单但算法并不简单
 *
 * 1、子数组和相关
 *
 *    定义:前i个子数组只和： prefixSum[i] = A[0] + A[1] + .. + A[i-1]  prefixSum[0] = 0
 *    定义:[i,j]索引值构成的子数组之和： sum(i,j) = prefixSum(j+1) - prefixSum(i)
 *
 */



/*  最大子数组之和：
 *
 *  Given an array of integers, find a contiguous subarray which has the largest sum.
 *
 *  要求时间复杂度：o(n)   难点就是在这里：？怎么用o(n)实现；
 *
 *  举个例子：
 *  Input: [−2,2,−3,4,−1,2,1,−5,3]
 *  Output: 6
 *  Explanation: the contiguous subarray [4,−1,2,1] has the largest sum = 6.
 *
 *  思路1：
 *  sum(i,j) = max{ prefixSum[j+1] - min{prefixSum[i]} }
 *
 *  实际就是求一小，一大
 *
 *
 */


int maxSubArraySum(vector<int> arr){

    int result = 0;
    int len = arr.size();
    if (len <= 0) return result;

    //计算prefixSum
    int prefixsum = 0;
    int min_prefixsum = 0; //前i个pefixsum中，值最小的prefixsum
    result = std::numeric_limits<int>::max();
    for (int i = 0; i <= len; ++i){
        if (i==0){
            prefixsum = 0;
            min_prefixsum = prefixsum;
        }else{
            prefixsum += arr[i-1];
            min_prefixsum = std::min(min_prefixsum, prefixsum);
            result = std::max(result, prefixsum - min_prefixsum);
        }
    }//end for

    //参考别人的实现代码：更简洁
    int sum = 0, min_sum = 0;
    result = std::numeric_limits<int>::min();
    for(int i = 0; i < len; ++i){
        sum += arr[i];
        result = std::max(result, sum - min_sum);
        min_sum = std::min(min_sum, sum);
    }
    return result;
}



/*
 * Valid Triangle Number：
 *
 * Given an array of integers, how many three numbers can be found in the array,
 * so that we can build an triangle whose three edges length is the three numbers that we find?
 * 数组中给出了边长，计算数组中三个数字是否能构成三角形？不去除重复的数字组成的三角形边
 *
 * Input: [2,2,3,4]
 * Output: 3
 * Explanation:
 * Valid combinations are:
 * 2,3,4 (using the first 2)
 * 2,3,4 (using the second 2)
 * 2,2,3
 *
 *  构成三角形的充要条件：a + b > c   也就是寻找两个数，大于第三个数
 *
 *  two sum; three sum   套路
 *  1、排序
 *  2、左右指针，定位相等元素
 *     循环其中一个变量，其它部分在用左右指针，寻找：=target >target <target的组合
 *
 *     重复数字怎么忽略？ 这里不用忽略
 *     步长问题？ 一般是left++， right--； 也有：n= right-left计算总个数的
 *
 *
 */

int countsOfTriangle(vector<int>& nums){

    int res = 0;
    if (nums.size() < 3) return res;
    sort(nums.begin(), nums.end(), std::less<int>());
    for (int i = nums.size() - 1; i >= 2; --i){
        int c = nums[i];
        int left = 0;
        int right = i - 1;
        while (left < right){
            if (nums[left] + nums[right] > nums[i]){
                //找到，a + b  > c    在 [a,b]之间任意选2个数和c都可构成三角形 ： 想法不对  比如【2,2,3,4】就是个case
                //int n = right - left + 1;
                //res += (n*(n-1)/2);

                //找到a + b  > c  那么知道在b（较大）不变的情况下，[a,b)之间任意选择一个数字，都可以使：a+b>c
                int n = right - left;
                res += n;
                --right;
            }else{
                // a + b <= c
                ++left;
            }
        }//end while
    }//end for

    return res;
}

/*
 * 寻找第K大的元素；
 * Input: [3,2,3,1,2,4,5,5,6] and k = 4
 * Output: 4
 *
 *
 *
 */
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {


        return helper(nums, 0, nums.size() - 1, k);


    }

private:

    /*
    * 对数组进行划分，返回一次划分后，轴点在合适位置的索引下标；
    * 划分按照：左边大，右边小  方式划分
    */

    int partition(vector<int>& nums, int start, int end){

        if (start == end) return start;
        int pivot = nums[start + (end - start)/2];
        std::swap(nums[start], nums[start + (end - start)/2]);
        int left = start, right = end;
        while (left < right){
            while(left < right && nums[right] <= pivot) --right;
            if(left < right){
                nums[left] = nums[right];
                ++left;
            }

            while(left < right && nums[left] >= pivot) ++left;
            if (left < right){
                nums[right] = nums[left];
                --right;
            }
        }

        nums[left] = pivot;
        return left; //返回轴点所在的下标索引
    }


    //在[start,end]之间寻找，第k大的数
    int helper(vector<int> &nums, int start, int end, int k){

        if (start == end) return nums[start];

        int index = partition(nums, start, end); //进行一次划分

        cout << "helper index : " << index << endl;
        cout << "helper start:end:K: " << start <<":" << end << ":"<< k << endl;
        for (auto e : nums){
           cout << e << " " ;
        }

        cout << endl;
        /*
          轴点左边元素个数（包含轴点）: len = index - start + 1
          最佳情况：如果轴点左边有3个数，寻找第3大的数，那么轴点就是要找的第3大的数；
          k = index - start + 1

          寻找第3大数，但轴点左边的个数大于3个了，继续在左边找，第3大的数
          index - start + 1 > k

          寻找第3大数，但轴点左边的个数不足3个，在右边找，第 k - len 大的数
          index - start + 1 < k

          */

        int len = index - start + 1;
        if (len > k){
            return helper(nums, start, index - 1, k);
        }

        if (len < k){
            return helper(nums, index + 1, end, k - len);
        }

        return nums[index];
    }


};











void test_base_6_array(){


    vector<int> nums = {7,6,5,4,3,2,1};

    int k = 5;

    Solution  s;
    int k_elem = s.findKthLargest(nums, k);

    cout << "the K largetest elem: " << k_elem << endl;




}


