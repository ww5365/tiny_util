
#include "01_all.h"


class Solution{
    public:

    float minEditDistance(int *iter1_first, 
                        int *iter1_last,
                        int *iter2_first,
                        int *iter2_last){

        std::size_t len1 = (iter1_last - iter1_first);
        std::size_t len2 = (iter2_last - iter2_first);
        std::size_t dp[len1+1][len2+1];

        //初始化 
        for(std::size_t i = 0; i <= len1; ++i){
            dp[i][0] = i;
        }
        for(std::size_t j = 0; j <= len2; ++j){
            dp[0][j] = j;
        }

        //更新计算两个vector存储token的编辑距离
        for(std::size_t i = 1; i <= len1; ++i){
            for(std::size_t j = 1; j <= len2; ++j){
                if(*(iter1_first + i - 1) == *(iter2_first + j - 1)){
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = std::min(std::min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]) + 1;
                }
            }

        }
        std::size_t max_len = std::max(len1, len2);
        float result = 0.0;
        result =  (max_len == 0) ? 0.0 : (1 - (float)(1.0 * dp[len1][len2] / max_len));
        std::cout << "min edit distacne: " << dp[len1][len2] << std::endl;
        std::cout << "max_len: " << max_len << std::endl;
        std::cout << "result:  " << result << std::endl;
        return result;
    }

};


void testEditDistance(){

    Solution s;
    std::vector<int32_t> vec1 = {1,2,3,4};
    std::vector<int32_t> vec2 = {2,4};
    float editDist = s.minEditDistance(vec1.data(), 
                                     vec1.data() + vec1.size(),
                                     vec2.data(),
                                     vec2.data() + vec2.size());

    std::cout <<"test distance edit ratio: " << editDist << std::endl;
}