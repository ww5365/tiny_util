/*
 * stl_use.cpp
 *
 *  Created on: Jun 16, 2017
 *      Author: wangwei69
 *
 *  主要展现stl库中map容器的使用方法
 *
 */

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <map>
#include <unordered_map>
#include "../inc/com_use.h"

using namespace std;

class TestMap {

public:
    explicit TestMap(): graph(){
        //初始化一个空的map变量
    }
    void set(int id, int adjvetex)
    {
        graph[id].push_back(adjvetex);
        return;
    }

    bool update(int key, vector<int> &vec)
    {   auto it = graph.find(key);
        if (it != graph.end()){
            graph[key].clear();
        }
        graph[key] = vec;
        return true;
    }
    bool empty()
    {
        return graph.empty();
    }

    void del(int id)
    {
        auto it = graph.find(id);
        if (it != graph.end()) {
            graph.erase(it);
        }
        return;
    }

    void Swap(){
        std::map<int ,vector<int>> tmp;
        tmp[5] = std::vector(3, 1);
        std::swap(graph, tmp);
    }

    // 重载<< 打印此类的对象
    friend ostream& operator<< (ostream &os, const TestMap &obj)
    {   
        for (auto const &elem : obj.graph) {
            for (auto const &adjv : elem.second) {
                os << "edge from:" << elem.first  << " to: "<< adjv << std::endl;
            }
        }
        return os;
    }

private:
    map<int, vector<int>> graph;  // 遍历时按照key时有序的;类中成员变量需要初始化吗？ 默认会调用初始化构造函数进行
};

// 用于排序的仿函数
template <typename T>
class CmpFun {
public:
    bool operator()(const T &left, const T &right) {
        return left > right;
    }
};

/*
*  通用的 map 使用方法
*/
void com_map_use() {

    std::cout << "---- com_map_use -----" << std::endl;

    // map 定义 初始化
    map<string, string> mTest{{"bba", "val1"}};


    // pair make_pair map  往map中插入元素
    pair<int, string> pa(1, "wang"); //直接初始化
    pair<int, string> pb;
    pb = make_pair(2, "wei");
    pair<int, string> pc;
    pc = make_pair(4, "ni");  //使用make_pair初始化:pair
    pc.first = 3;

    map<int, string> ma;
    ma.insert(pa);
    ma.insert(pb);
    ma.insert(pc);
    ma.insert(make_pair(4, "hao"));

    for (auto e : ma) {
        cout << e.first << ":" << e.second << endl;
    }

    // map是按照key排序, 输出有序使用map，不能用unordered_map
    
    std::cout << "---- com_map_use : map sort output -----" << std::endl;
    mTest.insert(make_pair("baa", "val2"));
    for_each(mTest.cbegin(), mTest.cend(), [](const pair<string, string>& elem){ std:: cout << elem.first << " : " << elem.second << std::endl;}); // 按照string的字典序输出 : baa, bba
    std::cout << std::endl;

    /*
     map: 按照key进行排序  eg：按照key降序排序输出
    */

    map<string, int, CmpFun<string>> mTest2;
    mTest2.insert(make_pair("niu", 1));
    mTest2.insert(make_pair("wang", 2));
    mTest2.insert(make_pair("ni", 3));
    mTest2.insert(make_pair("hao", 4));

    std::cout << "---- com_map_use : map sort by dict desc output -----" << std::endl;
    for_each(mTest2.cbegin(), mTest2.cend(), [](const pair<string, int>& elem){ std:: cout << elem.first << " : " << elem.second << std::endl;}); // 按照string的字典逆序输出

    //unoreder_map 无序

    std::unordered_map<uint32_t, int> brand_cnt;

    vector<uint32_t> vec{123,123,124};

    for (auto e : vec){
        auto it = brand_cnt.find(e);
        if (it == brand_cnt.end()){
            brand_cnt.insert(std::make_pair(e, 1));
        }else{
            it->second ++;
        }
    }

    for (auto itor = brand_cnt.begin(); itor != brand_cnt.end(); ++itor){

        cout << "unordered_map count: " << itor->first << " : " << itor->second << endl;
    }

    //multimap

    multimap<int, string> mm1;
    mm1.insert(make_pair(1,"test1"));
    mm1.insert(make_pair(1,"test11"));
    mm1.insert(make_pair(2, "test2"));
    mm1.insert(make_pair(2, "test22"));
    mm1.insert(make_pair(2, "test222"));
    mm1.insert(make_pair(3, "test3"));


    auto it = mm1.find(1);

    cout << "key: test1 -> " << it->second << endl;

    for(auto it = mm1.lower_bound(2); it != mm1.upper_bound(2); ++it){

        cout << "key range: test1 -> " << it->second << endl;
    }

    /*
     * multimap的遍历
     *
     * 第一层循环：it->first it->second 分别是map每一条元素:key value
     *
     * 第二层循环：range: 某个key对应的所有元素；
     * range.first是第一个元素的迭代器；range.second是最后一个元素的迭代器；
     *
     * range.first->first 第一个元素的key
     * range.first->second 第一个元素的value
     *
     */

    cout << "multi map tranverse ---" << endl;


    list<string> l_in;
    l_in.push_back("wang");
    l_in.push_back("wei");
    l_in.push_back("ni");
    l_in.push_back("a");


    auto l_it = l_in.begin();
    int last_pos = 0;
    int pos = 0;
    int l_len = l_in.size();

    /*
     * key 是要插入list中位置；value是要插入的值
     * 要实现的是：保持原有list中的位置顺序，在任意位置插入multimap中的value值；
     *
     * 1、基于mutimap的遍历
     * 2、基于list的任意位置插入
     *
     */


    for (auto it = mm1.begin(); it != mm1.end(); it = mm1.upper_bound(it->first)){

        auto range = mm1.equal_range(it->first);

        if (it->first <= (l_len + 1)) {
            pos = (it->first - 1);
            int diff_pos = pos - last_pos;
            std::advance(l_it, diff_pos);
            cout << "mm1 first: " << it->first << " second: " << it->second << endl;
        } else {
            l_it = l_in.end();
        }

        while (range.first != range.second) {
            cout << "range first: " << range.first->first
                    << " range second: " << range.first->second << endl;
            l_in.insert(l_it, range.first->second);
            ++range.first;
        }

        last_pos = pos;
    }

    for (auto e: l_in){
        cout << "l_in list: "  << e << endl;
    }

}


void map_use_test() {

    com_map_use();


    TestMap test;

    std::cout << "begin to test mmapap use-----" << std::endl; 

    std::cout << test << std::endl;
    test.set(1, 2);
    test.set(1, 3);
    test.set(2, 3);

    //结果为：{1,<2,3>},{2,<3>}
    std::cout << "begin to test mmapap use111-----" << std::endl; 
    std::cout << test << std::endl;

    // 更新key=2对应的值:<4,5,6>
    std::cout << "begin to test map use222-----" << std::endl; 
    std::vector<int> tmp = {4,5,6};
    test.update(2,tmp);
    std::cout << test << std::endl;
    
    // 删除key=1对应的值
    std::cout << "begin to test map use333-----" << std::endl; 
    test.del(1);
    std::cout << test << std::endl;

    // 
    std::cout << "begin to test map use444-----" << std::endl; 
    test.Swap();
    std::cout << test << std::endl;

}
