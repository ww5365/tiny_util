/**
* https://blog.csdn.net/qq_21201267/article/details/107881526
* 
* 给定两个句子 words1, words2 （每个用字符串数组表示），和一个相似单词对的列表 pairs ，判断是否两个句子是相似的。

* 例如，当相似单词对是 pairs = [["great", "fine"], ["acting","drama"], ["skills","talent"]]的时候，
* words1 = ["great", "acting", "skills"] 和 words2 = ["fine", "drama", "talent"] 是相似的。

* 注意相似关系是 具有 传递性的。
* 例如，如果 “great” 和 “fine” 是相似的，“fine” 和 “good” 是相似的，则 “great” 和 “good” 是相似的。
* 而且，相似关系是具有对称性的。

* 例如，“great” 和 “fine” 是相似的相当于 “fine” 和 “great” 是相似的。
* 并且，一个单词总是与其自身相似。
* 例如，句子 words1 = [“great”], words2 = [“great”], pairs = [] 是相似的，尽管没有输入特定的相似单词对。
* 最后，句子只会在具有相同单词个数的前提下才会相似。
* 所以一个句子 words1 = [“great”] 永远不可能和句子 words2 = [“doubleplus”,“good”] 相似。

* DSU实现思路：
* 1): 
* 1): 基于pairs对，构建归并集
* 
*/
#include "01_all.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <stack>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <exception>
using namespace std;

class Solution {
public:
    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<vector<string>>& pairs) {
        
        if (words1.size() != words2.size()) {
            return false;
        }
        unordered_map<string, string> parent; //下面的find时,必须先初始化
        std::cout << "pairs size: " << pairs.size() << std::endl;

        for (int i = 0; i < pairs.size(); ++i) {
            // 归并数组初始化
            string key1 = pairs[i][0];
            string key2 = pairs[i][1];
            auto it1 = parent.find(key1);
            if (it1 == parent.end()){
                // parent[key1] = key1;
                parent.insert(make_pair(key1, key1));
             }
            auto it2 = parent.find(key2);
            if (it2 == parent.end()){
                //parent[key2] = key2;
                parent.insert(make_pair(key2, key2));
            }
        }
        //归并
        Union(parent, pairs);
        for (int i = 0; i < words1.size(); ++i) {
            if (words1[i] == words2[i]) {
                continue;
            }
            string p1 = Find2(parent, words1[i]);
            string p2 = Find2(parent, words2[i]);
            if (p1 != p2) {
                return false;
            }
        }
        return true;
    }

private:

    void Union(unordered_map<string, string> & parent, const vector<vector<string>> & pairs)
    {
        if (pairs.size() <= 0 ){
            return;
        }
        for (int i = 0; i < pairs.size(); ++i) {
            // 归并数组归并
            string key1 = pairs[i][0];
            string key2 = pairs[i][1];

            string p_key1 =  Find2(parent, key1);
            string p_key2 =  Find2(parent, key2);
            parent[p_key1] = p_key2;
        }
    }

    string Find2(unordered_map<string,string> &parent, string key) {

        string origin_key = key;
        while (key != parent[key]) {
            key = parent[key];
        }
        parent[origin_key] = key;
        return key;
    }

};

void TestAreSentencesSimilarTwo()
{
    Solution s;

    vector<vector<string>> pairs = {{"great", "fine"}, {"acting","drama"}, {"skills","talent"}};

    vector<string> words1 = {"great", "acting", "skills"};
    vector<string> words2 = {"fine", "drama", "talent"};

    std::cout << "begin to test two sentence are similar!" <<std::endl;
    bool res = s.areSentencesSimilarTwo(words1, words2, pairs);

    if (res) {
        std::cout << "two sentence are similar!" <<std::endl;
    } else {

        std::cout << "two sentence are not similar!" <<std::endl;
    }
}
