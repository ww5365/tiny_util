
/*
 * 15.https://leetcode-cn.com/problems/3sum/

   57. https://www.lintcode.com/problem/57

 * 5_3Sum.cpp
 *Given an array S of n integers,are there elements a, b, c in Find all unique triplets in the array which gives the sum of zero（a+b+c=0）
 *Note: Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c) The solution set must not contain duplicate triplets.
 * For example, given array S = {-1 0 1 2 -1 -4} .
 * A solution set is:
 * (-1, 0, 1)
 * (-1, -1, 2)
 
 *分析：
 *疑问：有时间复杂度要求？空间复杂度？
 *self idea：将S中元素存在hashtable中；利用a+b=-c,顺序取数组中相邻两个元素ab，查询是否存在-(a+b)；找到c后，排下序列；
 *self idea 问题：
 *1、时间：o(n),但空间：o(n)
 *2、取出来数据，需要排序，还得去重
 *
 *reference idea：
 * 1、排序
 * 2、左右夹逼，同时去重； 核心：使用两个指针，怎么移动？
 * 时间复杂度o(n^2)
 * -c = a+b
 *
 *(-2,-1,-1,0,1,2,2,3,3,4,5)
 *
 */

#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <iterator>

#include "01_all.h"

using namespace std;

class Solution{
public:
    vector<vector<int> > threeSum(vector<int> &vec){

        vector<vector<int> >res;

        if (vec.size() < 3){
            return res;
        }

        sort(vec.begin(),vec.end());//对数组中元素排序，升序排

        for (int i = 0;i < vec.size(); i++){
            int target = -vec[i];

            int front = i+1;
            int end = vec.size() - 1;

            while(front < end){//前，后，夹逼着来找target
                int sum = vec[front] + vec[end];
                if (sum < target){
                    front++;
                }else if(sum > target){
                    end--;
                }else{ //-c = a+b
                    res.emplace_back(vector<int> {vec[i],vec[front],vec[end]});
                    //使用emplace_back比push_back快：20ms左右，从23%-》65%
                    //res.push_back({vec[i],vec[front],vec[end]});
                    while(vec[++front] == vec[front - 1]);//去掉重复的 a
                    while(vec[--end] == vec[end + 1]); //去掉重复的 b
                }
            }//end while
            while(vec[i] == vec[i + 1]) i++;//去掉重复的c
        }//end for

        return res;

    }//end threeSum

    /*
     * 升级版本
     */
    vector<vector<int>> threeSum2(vector<int>& nums) {

            /*
            *  思路：类似两个a+b = 0 ， -a = b + c 是其一般的情况
            *  1、排序
            *  2、当前位置a=nums[i],从i+1和len-1,两头使用两个指针 i,j，寻找满足条件：b + c = -a
            *     如果大于-a，  j-- ; 如果小于-a， i++;
            *     相等，yes，that is
            *     还要考虑：有重复的数字，怎么不要重复选择？
            *  时间复杂度：o(n^2)
            *
            */

            vector<vector<int>> res;
            if (nums.size() < 3) return res;

            sort(nums.begin(), nums.end(), std::less<int>());
            for (int i = 0; i < nums.size() - 2; ++i){
                int a = -nums[i];
                int left = i + 1, right = nums.size() - 1;
                while(left < right){
                    if (nums[left] + nums[right] > a) {
                        --right;
                    } else if (nums[left] + nums[right] < a){
                        ++left;
                    } else{
                        //yes 找到了
                        vector<int> tmp = {nums[i], nums[left], nums[right]};
                        res.emplace_back(tmp);
                        ++left;
                        --right;
                        //去掉重复
                        while(left < right && nums[left] == nums[left - 1]) ++left;
                        while(left < right && nums[right] == nums[right + 1]) --right;
                    }
                }
                //主数字去重
                while( i < nums.size() - 2 && nums[i] == nums[i + 1]) ++i;

            }
            return res;
        }
};

// 2023.10.17 
class Solution2 {
public:
    /**
     * @param numbers: Give an array numbers of n integer
     * @return: Find all unique triplets in the array which gives the sum of zero.
     *          we will sort your return value in output

     输入：numbers = [-1,0,1,2,-1,-4]
     输出：[[-1, 0, 1],[-1, -1, 2]] 是符合条件的2个三元组
     [-1,0,1] 和 [0, 1, -1] 是相同的2个三元组，注意算1个

     思路：
     1. a + b + c = 0 转成-a = b + c  同向双指针
     2. 有重复，边界的处理，被选择的时候，判断left和right指针是否有重复的数字； 同时也要判断a是否有重复的；


     */
    vector<vector<int>> threeSum(vector<int> &numbers) {
        // write your code here
        vector<vector<int>> result;
        if (numbers.size() <= 2) {
            return result;
        }

        std::sort(numbers.begin(), numbers.end(), std::less<int>());
        
        int len = numbers.size();

        for (int i = 0; i < len - 2; ++i) {

            // target是否有重复的？
            if(i > 0 && numbers[i] == numbers[i - 1]){
                continue;
            }
            
            int target = -numbers[i];
            int left = i + 1;
            int right = len - 1;

            while(left < right){
                if(left < right && numbers[left] + numbers[right] < target) {
                    left ++;
                }else if (left < right && numbers[left] + numbers[right] > target) {
                    right--;
                } else {
                    result.push_back({numbers[i], numbers[left], numbers[right]});
                    left ++;
                    right --;
                    while (left < right && numbers[left - 1] == numbers[left]) left ++;
                    while (left < right && numbers[right] == numbers[right + 1]) right --;
                }
            } 
        }
        return result;
    }
};



void TestThreeSum(){

    int arr[] = {-2,-1,-1,0,1,2,2,11,3,3,4,5};
    vector<int> num(arr,arr + 12);
    cout <<"before process" <<endl;
    for(size_t i = 0; i < num.size(); i++){
        cout << num[i] << " ";
    }

    std::cout << std::endl;

    std::sort(num.begin(), num.end(), std::less<int>()); // 最后1个参数是比较对象

    std::copy(num.begin(), num.end(), ostream_iterator<int>(std::cout, ","));

    std::cout << std::endl;
    
    std::priority_queue<int, vector<int>, std::less<int>> qp; // 大顶堆，突然想到大顶堆的使用了,模板中最后1个参数是比较类型

    for (size_t i = 0; i < 5; ++i) {
        qp.push(i);
    }

    while(!qp.empty()) {
        std::cout << "queue elem: " << qp.top() << " ";
        qp.pop();
    }


    cout << endl;

    Solution s;
    vector<vector<int> > res = s.threeSum(num);
    cout <<"after process" <<endl;
    for(size_t i = 0; i < num.size(); i++){
        cout << num[i] << " ";
    }
    cout << endl;

    cout << "the final res is: " <<endl;
    for(auto i = 0; i < res.size(); i++){
        for(size_t j = 0;j < res[i].size(); j++){
            cout <<res[i][j]<<" ";
        }
        cout << endl;
    }
    cout << endl;
}
