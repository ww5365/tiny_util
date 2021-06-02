
#include "01_all.h"

#include <algorithm>


/*
*状态转移方程：
* 
*/

class Solution{
    public:

    float jaccardDistance(int *iter1_first, 
                        int *iter1_last,
                        int *iter2_first,
                        int *iter2_last){

        std::size_t len1 = (iter1_last - iter1_first);
        std::size_t len2 = (iter2_last - iter2_first);

        std::set<int32_t> query(iter1_first, iter1_last);
        std::set<int32_t> title(iter2_first, iter2_last);

        //for (auto e : query){
        //    std::cout << "set query: " << e << std::endl;
        //}
        //for (auto e : title){
        //    std::cout << "set title: " << e << std::endl;
        //}

        std::set<int32_t> unionSet;
        std::set<int32_t> intersectionSet;

        std::set_intersection(query.begin(),query.end(),title.begin(), title.end(), inserter(intersectionSet, intersectionSet.begin()));

        std::set_union(query.begin(), query.end(), title.begin(), title.end(), inserter(unionSet, unionSet.begin()));


        //for (auto e : unionSet){
        //    std::cout << "set unionSet: " << e << std::endl;
        //}
        //for (auto e : intersectionSet){
        //    std::cout << "set intersectionSet: " << e << std::endl;
        //}

        float result = 0.0;

        result = unionSet.size() == 0 ? 0.0 : 1.0 * intersectionSet.size() / unionSet.size();

        std::cout << "jaccard distance :  " << result << std::endl;
        return result;
    }

};


void testJaccardDistance(){

    Solution s;
    std::vector<int32_t> vec1 = {1,2,3,5};
    std::vector<int32_t> vec2 = {2,4,3};
    float lcs = s.jaccardDistance(vec1.data(), 
                                     vec1.data() + vec1.size(),
                                     vec2.data(),
                                     vec2.data() + vec2.size());
}