/*
 * edit_distance.cpp
 *
 *  Created on: 2019年11月1日
 *      Author: wangwei69
 */

#include "test_main.h"

class Soultion{

public:

    /*
     * 针对两个英文字符串，计算两个字符串的编辑距离
     *
     * f(i,j) = min{f(i-1, j-1) + (ch[i] == ch[j]) , f(i, j-1) + 1, f(i-1, j) + 1}
     *
     * 实现注意：
     * 1、sug 中计算文本相似度时，使用了编辑距离； 中文的编辑距离计算 wstring 来实现，不太一样；
     *
     * 2、矩阵的构造和初始化
     *
     * 3、最后一个值: 就是要求的最少变动次数，即是结果；
     */

    static int calc_levenshtein_dis(const std::string &source, const std::string &target) {
           //step 1
           int n = source.length();
           int m = target.length();
           if (m == 0) {
               return n;
           }
           if (n == 0) {
               return m;
           }
           //Construct a matrix
           std::vector< std::vector<int> >  matrix(n + 1);
           for (int i = 0; i <= n; i++) {
               matrix[i].resize(m + 1);
           }

           //step 2 Initialize
           for (int i = 1; i <= n; i++) {
               matrix[i][0] = i;
           }
           for (int i = 1; i <= m; i++) {
               matrix[0][i] = i;
           }

           //step 3
           for (int i = 1; i <= n; i++) {
               const char si = source[i - 1];
               //step 4
               for (int j = 1; j <= m; j++) {
                   const char dj = target[j - 1];
                   //step 5
                   int cost = 0;
                   if (si == dj) {
                       cost = 0;
                   } else {
                       cost = 1;
                   }
                   //step 6
                   const int above = matrix[i - 1][j] + 1;
                   const int left = matrix[i][j - 1] + 1;
                   const int diag = matrix[i - 1][j - 1] + cost;
                   matrix[i][j] = std::min(above, std::min(left, diag));

               }
           }//step7

           return matrix[n][m];
       }

};






void test_edit_distance(){

}
