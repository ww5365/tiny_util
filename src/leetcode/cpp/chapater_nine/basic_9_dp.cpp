/*
 * basic_9_dp.cpp
 *
 *  Created on: 2019年11月18日
 *      Author: wangwei69
 */

#include <iostream>
#include <vector>
#include <limits>
#include <numeric>

using namespace std;


/*
 * 问题1：
 * Given a triangle, find the minimum path sum from top to bottom.
 * Each step you may move to adjacent numbers on the row below.
 * example:
 * [
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
* ]
* Output: 11
* Explanation: The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
*
*
* 算法思路：
* 思路1：DFS  搜索所有的相邻的路径
*
* 第一行选择：只有1个元素，选择
* 假设第m行选择元素的下标i,第m+1行可选择的元素:i, i+1
* 搜索出所有的相邻路径，计算所有相邻路径中和最小的
*
*  时间复杂度：？2^h   会抱超时
*
* 思路2： 分治法
*
* 计算出从左子点开始到底的最小和 left；计算从右子点出发到底的最小和right；
* 选择left 和 right 中较小的加上当前节点的值，就计算出了从当前节点开始，到底部的最小和；
*
* 思路3： dp
*
*  详见下面的分析；
*
* 比较三种思路：1，2 时间复杂度，都是o(2^n)  3是o(n^2)
*
*/

class Solution{
public:
    /*
     * DFS
     */
    int minimumTotal(vector<vector<int>> &triangle) {
        int result = numeric_limits<int>::max();
        if (triangle.size() <= 0)
            return result;
        vector<int> path;
        path.reserve(triangle.size());
        dfs(triangle, path, 1, 0, result);
        return result;
    }

    /*
     * divide conquer
     *
     */
    int minimumTotal_dc(vector<vector<int>> &triangle) {
        int result = numeric_limits<int>::max();
        if (triangle.size() <= 0)
            return result;
        return helper(triangle, 0, 0);
    }

    /*
     * dp:  有方向性
     *
     * 自顶而下：
     * state: f(x,y) 标识从(0,0)走到(x,y)最小路径和
     *        分析：(x,y) 这个点，只有(x-1, y) 和 (x-1, y-1) 这两个点可能进入
     *
     * 方程： f(x,y) = min{f(x-1,y), f(x-1, y-1)} + array[x][y]
     *
     * 初始化： y=0:没有y-1,初始化，f(x,0) = sum(array[x][0])   就一条路可以走
     *         x=y: 对角线，没有(x-1,y), f(x,x) = sum(array[x][x]) 就一条路可以走
     * 结果：  最右下角f()
     *
     */

    int minimumTotal_dp(vector<vector<int>> &triangle) {

        int result = numeric_limits<int>::max();
        if (triangle.size() <= 0)
            return result;

        int m = triangle.size();
        vector<vector<int>> matrix(m);
        for (int i = 0; i < m; ++i){
            int n = triangle[i].size();
            matrix[i].resize(n); //resize调整size的大小，并进行初始化
        }
        //初始化
        matrix[0][0] = triangle[0][0];

        for (int i = 1; i < m; ++i){;
            matrix[i][0] = matrix[i-1][0] + triangle[i][0];
            matrix[i][i] = matrix[i-1][i-1] + triangle[i][i];
        }

        //迭代计算，结果就是
        for (int x = 1; x < m; ++x){
            for (int y = 1; y < triangle[x].size() - 1; ++y){
                matrix[x][y] = std::min(matrix[x-1][y], matrix[x-1][y-1]) + triangle[x][y];
            }
        }
        //获取结果：最后一行的最小值
        for (int i = 0; i < matrix[m - 1].size(); ++i){
            if (matrix[m - 1][i] < result){
                result = matrix[m - 1][i];
            }
        }
        return result;
    }


private:

    /* path 搜索路径上所有的值；
     * step 搜索到第几行了；idx 搜索到第几个下标位置； result 当前最终路径上的结果和；
     * 搜索所有的相邻路径；
     */

    void dfs(vector<vector<int>> &triangle, vector<int> &path, int step, int idx, int &result){

        if (step > triangle.size()){
            return;
        }

        for (int i = idx; i < triangle[step - 1].size() && i <= idx + 1; ++i){
            path.push_back(triangle[step - 1][i]);
            dfs (triangle, path, step + 1, i, result);
            if (step == triangle.size()){
                int path_sum = std::accumulate(path.begin(), path.end(), 0);
                if (path_sum < result){
                    result =  path_sum;
                }
            }
            path.pop_back();
        }
        return;
    }

    /*
     * step: 从0开始，第0层。。
     * idx：该层的数据下标
     *
     * 自底而上：bottom->up
     *
     */

    int helper(vector<vector<int>> &triangle, int step, int idx){

        if (step == triangle.size()){
            return 0;
        }
        //计算，左右，子节点开始的最小 sum
        return triangle[step][idx] + std::min(helper(triangle, step + 1, idx), helper(triangle, step + 1, idx + 1));

    }
};


/*
 * 问题2：unique path
 *
 *      从网格m*n的(0,0)只能向下或向右行走，走到(m-1,n-1)网格的位置，总共有多少中不同的走法。
 *
 *      算法：
 *
 *      状态： f(x,y)标识从(0,0)走到(x,y)总共有多少种不同的走法；
 *
 *      方程：f(x,y) = f(x-1,y) + f(x, y-1)
 *
 *      初始化：f(0,y) = 1   f(x,0) = 1
 *
 *      结果：f(m-1,n-1)
 *
 *
 */


class Soultion2{

public:
    int uniquePaths(int m, int n){

        vector<vector<int>> matrix(m);
        for (int i = 0; i < matrix.size(); ++i){
            matrix[i].resize(n); //构造m*n的矩阵
        }
        //初始化 + 构造
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j){
                if(i == 0 || j == 0){
                    matrix[i][j] = 1;
                } else {
                    matrix[i][j] = matrix[i-1][j] + matrix[i][j-1];
                }
            }
        }
        return matrix[m - 1][n - 1];
    }

};


/*
 * longest increasing subsequence:
 *  最长的递增子序列 ： 给定一个整数序列，找到最长上升子序列（LIS），返回LIS的长度。
 *
 *  For [5, 4, 1, 2, 3], the LIS is [1, 2, 3], return 3
 *  For [4, 2, 4, 5, 3, 7], the LIS is [4, 4, 5, 7], return 4
 *
 */


class Solution3{



};






void test_base_9_dp(){

    vector<vector<int>> tri;
    vector<int> test{-10};
    tri.push_back(test);

    Solution s;
    cout << "test base 9 dp: " << s.minimumTotal_dp(tri) << endl;


    cout << "test base 9 dp over " << endl;
}


