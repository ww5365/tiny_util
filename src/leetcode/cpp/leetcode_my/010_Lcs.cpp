
#include "01_all.h"


/*
*状态转移方程：
* 
*/

class Solution{
    public:

    float longestCommonSubsequence(int *iter1_first, 
                        int *iter1_last,
                        int *iter2_first,
                        int *iter2_last){

        std::size_t len1 = (iter1_last - iter1_first);
        std::size_t len2 = (iter2_last - iter2_first);
        //定义和初始化 
        std::vector<std::vector<std::size_t>> dp(len1 + 1, std::vector<size_t>(len2 + 1, 0));
        //计算两个vector存储token的lcs
        for(std::size_t i = 1; i <= len1; ++i){
            for(std::size_t j = 1; j <= len2; ++j){
                if(*(iter1_first + i - 1) == *(iter2_first + j - 1)){
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
                }
            }

        }
        std::size_t max_len = std::max(len1, len2);
        float result = 0.0;
        result =  (max_len == 0) ? 0.0 : (float)((1.0) * dp[len1][len2] / max_len);
        std::cout << "max lcs: " << dp[len1][len2] << std::endl;
        std::cout << "max_len: " << max_len << std::endl;
        std::cout << "result:  " << result << std::endl;
        return result;
    }

};


void testLcs(){

    Solution s;
    std::vector<int32_t> vec1 = {5,2,3};
    std::vector<int32_t> vec2 = {2,4,3};
    float lcs = s.longestCommonSubsequence(vec1.data(), 
                                     vec1.data() + vec1.size(),
                                     vec2.data(),
                                     vec2.data() + vec2.size());

    std::cout <<"test lcs: " << lcs << std::endl;
}