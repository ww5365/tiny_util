/*
 * 1. https://leetcode-cn.com/problems/two-sum/
 * 56.https://www.lintcode.com/problem/56/solution/18046
 * problems:
 * Given an array of integers, find two numbers such that they add up to a specific target number.
 * The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2.
 * Please note that your returned answers (both index1 and index2) are not zero-based.
 * You may assume that each input would have exactly one solution.
 * Input: numbers={2, 7, 11, 15}, target=9
 * Output:index1=1, index2=2
 *

 *解析思路：
 *1、o(n^2)的好想
 *2、？有没有更少复杂度？o(n)
 *  关键就是c++标准库hashmap的使用：unordered_map
 */

#include <vector>
#include  <iostream>
#include <unordered_map>
#include <algorithm>

#include <iterator>
using namespace std;

class Solution{

    struct Elem{
        int val;
        int index;
        Elem(int x = 0, int idx = 0): val(x), index(idx){}
        bool operator<(const Elem &right) const{
            return (this -> val < right.val);
        }
    };
public:

    /*
     * 使用hashmap，其实还可以写的更加优雅；
     * 思路：
     * 1、因为是成对出现，第一次可以不在hashmap中，等待下一次的到来；
     * 先到hashmap中查找left部分，是否存在；
     * 不存在，将本number和index加入到hashmap中。
     * 存在，直接返回【hashmap[left],i】
     *
     * 时间复杂度：o(N)  空间复杂度：o(n)
     *
     */
    vector<int> twoSum(vector<int> &nums, int target){
        //返回索引位置
        vector<int> res;
        unordered_map<int, int> num_index_map;
        for (size_t i = 0 ;i < nums.size(); i++){
            num_index_map[nums[i]] = i+1;
        }

        for (size_t i = 0;i< nums.size(); i++){
            //unordered_map<int ,int>::const_iterator it = num_index_map.find(target - nums[i]);
            auto it = num_index_map.find(target - nums[i]); //使用下c11的自动化变量
            if (it != num_index_map.end() && it->second > (i+1)){
                res.push_back(i+1);
                res.push_back(it->second);
            }
        }//end for
        return res;
    }

    /*
     * 思路2:  使用双向指针
     *
     * 1、先排序
     * 2、两个指针，一前一后，相向而找：nums[left] + nums[right] = target
     *
     */
    vector<int> twoSum2(vector<int> &nums, int target){

        vector<int > res;
        vector<Elem> tmp;
        for (int i = 0; i < nums.size(); ++i){
            Elem e(nums[i], i);
            tmp.emplace_back(e);
        }

        std::sort(tmp.begin(), tmp.end());
        int i = 0, j = tmp.size() - 1;
        while (i < j){
            if (tmp[i].val + tmp[j].val < target){
                ++i;
            }else if (tmp[i].val + tmp[j].val > target){
                --j;
            }else{
                res.push_back(std::min(tmp[i].index, tmp[j].index));
                res.push_back(std::max(tmp[j].index, tmp[i].index));
                return res;
            }
        }
        res.push_back(-1);
        res.push_back(-1);
        return res;
    }
};

// 2023.10.17

class Solution2 {
public:
    /**
     * @param numbers: An array of Integer
     * @param target: target = numbers[index1] + numbers[index2]
     * @return: [index1, index2] (index1 < index2)
     */
    vector<int> twoSum(vector<int> &numbers, int target) {
        // write your code here
        vector<int> index(numbers.size(), 0);
        for (int i = 0; i < numbers.size(); ++i) {
            index[i] = i;
        }

        // 按照numbers的值大小，进行索引排序
        IndexSort(numbers, index);
        
        // std::copy(index.begin(), index.end(), std::ostream_iterator<int>(std::cout, " , "));
        // std::cout << std::endl;

        // 双指针

        int left = 0;
        int right = numbers.size() - 1;

        vector<int> result(2, -1);

        while (left < right) {
            if (numbers[index[left]] + numbers[index[right]] > target) {
                right --;
            } else if(numbers[index[left]] + numbers[index[right]] < target) {
                left ++;
            } else {
                break;
            }
        }

        if (left != right) {
            result[0] = std::min(index[left], index[right]);
            result[1] = std::max(index[left], index[right]);
        }
        return result;
    }

private:
    // 按照val大小，对索引进行排序
    void IndexSort(const vector<int> &num, vector<int> &result) {
        if (num.size() <= 1) 
            return;
        std::sort(result.begin(), result.end(), [&num](const int left, const int right)->bool{return num[left] < num[right];});
        return ;
    }
};

void TestTwoSum(){

    vector<int> data;

    data.push_back(23);
    data.push_back(1);
    data.push_back(4);
    data.push_back(6);
    data.push_back(8);

    data.push_back(3454);

    Solution s;
    vector<int> res = s.twoSum2(data, 24);

    std::cout << "twoSum result" << endl;
    for(auto e:res){
        std::cout << e << "  ";
    }
    std::cout <<endl;

    std::cout << "===============" << std::endl;

    Solution2 s2;
    vector<int> res2 = s2.twoSum(data, 24);

    std::copy(res2.begin(), res2.end(), std::ostream_iterator<int>(std::cout, ","));
    std::cout << std::endl;
}


