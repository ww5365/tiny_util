/*
 * 19_longest_com_substr_seq.cpp
 *
 *  Created on: 2019年11月21日
 *      Author: wangwei69
 */
#include <string>
#include <vector>
#include <iostream>
#include <stack>

using namespace std;

/*
 * 问题：
 * 字符串： abcde  abycde   求两个字符串的最长公共子串(连续)
 *
 * 应用：
 * 把公共部分提取起出来？
 * 中国建设银行(上支行)
 * 中国建设银行(广支行)
 * 中国建设银行 ATM
 *
 * 思路：？
 *
 * 方法1、以其中的一个字符串为母串，生成所有子串；再一个个去匹配； 时间复杂度高： 子串生成o(2^n)，匹配
 *
 * 方法2、 dp
 *
 *   str1 str2
 *
 *   f(i,j) : str1[0,i] str2[0,j] 以str1[i], str2[j] 结尾的所有子串，是公共子串情况下，最大长度
 *            关键点，子串必须以str1[i], str2[j] 结尾
 *
 *   f(i,j)转移方程 : str1[i] = str2[j]  f(i-1, j-1) + 1  斜对角线关系
 *            str1[i] != str2[j]  0   这点不好理解。。
 *            i=0 或 j = 0  相等为1，否则为0
 *
 *   结果： result 记录f[i,j] 计算过程中最大值
 *
 *
 */

class Solution{

public:

    /*
     * 未优化版本：计算了最大公共子串的长度
     */
    int longest_com_substr_v1(const string &str1, const string &str2){
        int m = str1.size();
        int n = str2.size();
        if (m <= 0 || n <= 0){
            return 0;
        }
        vector<vector<int>> matrix(m);
        for (int i = 0; i < m; ++i){
            matrix[i].resize(n);
        }
        int result = 0;
        //初始化 + 构造状态矩阵
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j){
                if (i == 0 || j == 0){
                    //初始化
                    matrix[i][j] = (str1[i] == str2[j] ? 1 : 0);
                } else {
                    //构造状态矩阵
                    matrix[i][j] = (str1[i] == str2[j] ? (matrix[i-1][j-1] + 1) : 0);
                }

                if (matrix[i][j] > result)
                    result = matrix[i][j];
            }
        }
        return result;
    }

    /*
     * 优化版本：
     * 1、求最大公共长度以及最大公共子串内容？
     *    记录最大公共子串的长度，以及匹配最大公共子串长度时的下标索引。这样可以截取出公共子串。
     * 2、空间复杂度上，o(m*n) 是否可以优化？
     *    可以优化到o(n), 从后往前进行匹配（以某个字符结尾的子串）
     *
     *
     *
     */
    int longest_com_substr_v2(const string &str1, const string &str2, string &lcs){

        int m = str1.size();
        int n = str2.size();
        if (m <= 0 || n <= 0){
            return 0;
        }
        vector<int> matrix(n);
        int result = 0;
        int pos = 0;
        //初始化 + 构造状态矩阵
        for (int i = 0; i < m; ++i){
            for (int j = n - 1; j >= 0; --j){
                if (i == 0 || j == 0){
                    //初始化
                    matrix[j] = (str1[i] == str2[j] ? 1 : 0);
                } else {
                    //从后往前构造状态矩阵： matrix[j-1] 就是原来的：[i-1]行 [j-1] 列
                    matrix[j] = (str1[i] == str2[j] ? (matrix[j-1] + 1) : 0);
                }

                if (matrix[j] > result){
                    result = matrix[j];
                    pos = j;
                }
            }//end for j
        } // end for i

        if (result > 0){
            lcs.assign(str2.substr(pos - result + 1, result));
        }
        return result;
    }

};


/*
 * 问题2：最长公共子序列  和上个问题的区别，在于可以不连续
 *
 * s1： abcde
 * s2:  ace
 * 最长公共子序列：3
 *
 * 状态：f(x,y) : 前x,y个字符构成的子串, 拥有的最长公共子序列
 *
 * 转移方程：
 * f(x,y) =  f(x-1, y-1) + 1  s1[x] == s2[y]
 *           max{f(x-1, y), f(x, y-1)}  s1[x] != s2[y]
 *           0 x = 0 y = 0  方便计算，多0行和0列空间；长度为0，最长公共子序列是0
 *
 * 结果：f(m,n) 最右下角的值就是最长公共子序列
 *
 */

class Solution2{

public:
    int lcs(const string &s1, const string &s2, string &lcs_str){

        int m = s1.size();
        int n = s2.size();

        if (m <= 0 || n <= 0){
            return 0;
        }

        vector<vector<int>> matrix(m + 1);
        for (int i = 0; i <= m; ++i){
            matrix[i].resize(n + 1);
        }

        for (int i = 0; i <= m; ++i){
            for (int j = 0; j <= n; ++j){
                if (i == 0 || j == 0){
                    matrix[i][j] = 0; //便于计算，不用特殊考虑
                } else {
                    if (s1[i - 1] == s2[j - 1]){
                        matrix[i][j] = matrix[i-1][j-1] + 1;
                    } else {
                        matrix[i][j] = std::max(matrix[i-1][j], matrix[i][j-1]);
                    }
                }
            }//end for j
        } //end for i

        string lcs_content = get_lcs_content(matrix, s1, s2);
        lcs_str.assign(lcs_content);
        return matrix[m][n];

    }


private:

    /*
     * 利用状态数组和 str，反向搜索公共子序列； 搜索终止点: i = 0 或 j=0
     */
    string get_lcs_content(vector<vector<int>> &matrix, const string &s1, const string &s2){

        string result("");
        if (matrix.size() <= 0 || s1.size() <=0 || s2.size() <= 0){
            return result;
        }

        int m = s1.size();
        int n = s2.size();
        stack<char> st;
        while (m > 0 && n > 0) {
            if (s1.at(m - 1) == s2.at(n - 1)) {
                //是一个公共子序列字符，斜对角线获取
                st.push(s1.at(m - 1));
                --m;
                --n;
            } else {
                if (matrix[m][n] <= matrix[m][n - 1]) {
                    --n; //左移
                } else {
                    --m; //上移
                }
            }
        }

        //将结果正序输出
        while (!st.empty()){
            result.push_back(st.top());
            st.pop();
        }
        return result;
    }
};

/*
 * 问题3： 求最长回文子串
 *
 *   给出一个字符串，求这个字符串的最长回文子串,比如，abcb
 *
 *
 *
 */





void longest_com_substr_seq(){

    string str1("abcd");
    string str2("aecfcd");

    Solution s;

    int comm_len = s.longest_com_substr_v1(str1, str2);

    cout << "the longest common substr v1: " << comm_len << endl;

    string lcs;
    int comm_len2  = s.longest_com_substr_v2(str1, str2, lcs);

    cout << "the longest common substr v2: " <<  comm_len2 << " com str: " <<lcs << endl;

    Solution2 s2;

    string lcs_str;
    int lcs_len = s2.lcs(str1, str2, lcs_str);

    cout << "lcs len: " <<  lcs_len  << " lcs str: " << lcs_str<< endl;



}
