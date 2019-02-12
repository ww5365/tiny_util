/*
 * stl_use.cpp
 *
 *  Created on: Jun 16, 2017
 *      Author: wangwei69
 *
 *  主要展现stl库中各个容器的使用方法
 *
 */

#include <iostream>
#include <vector>
#include "stl_use.h"
using namespace std;

/*
 * @brief 定义结构体，测试set用法
 */

typedef struct DistrictInfo
{
    uint32_t cid;
    uint32_t level;
    DistrictInfo(uint32_t cid_, uint32_t level_):
        cid(cid_), level(level_){}

    bool operator<(const DistrictInfo &right)const{
        if ((this->cid==right.cid)&&(this->level==right.level)){
            return false; //让比较函数对相同元素返回false
        }else{
            return true;
        }
    }

}DistrictInfo;

class Compare{
public:
    bool operator()(const int left, const int right){
        return (left <= right) ? true : false; //true 是位置已经排好，不用交换了(升序)；
    }
};

vector<int>::iterator bin_search(vector<int> &vec, int val){

    sort(vec.begin(), vec.end(), Compare());//先排序，升序
    vector<int>::iterator start = vec.begin();
    vector<int>::iterator end = vec.end();
    while(start != end){//为空的情况也考虑进来了；
        vector<int>::iterator mid = start + (end - start)/2;//迭代器运算
        cout << "mid val: " << *mid << endl;
        if ( *mid == val){
            return mid;
        }else if(*mid > val){
            end = mid;
        }else{
            start = mid + 1;
        }
    }
    return vec.end();
}

void stl_use::iterator_use(){

    std::vector<int> vec = {1,2,3,4,5,6,7,8};
    std::vector<int>::iterator it = vec.begin();
    std::vector<int>::iterator it2 = vec.end();
    std::cout << "iterator + n :" << *(it + 3) << " distance: "<< distance(it2,it)<<std::endl; //4
    std::vector<int>::reverse_iterator rit = vec.rbegin();
    std::cout << "next rit: " << *(next(rit)) << endl; //7

    //迭代器典型应用实例：二分查找

    int val = 2;
    vector<int>::iterator pos = bin_search(vec, val);

    if (pos != vec.end()){

        std::cout << "binary find: " << *pos << std::endl;
     }else{
         std::cout << "binary not find!" << std::endl;
     }


}


void stl_use::list_use(){

    //test splice
    std::list<int> li_t{3,4,5,6,9};
    list<int>::iterator itor = li_t.begin();
    std::advance(itor, 2); //point to 5
    li_t.splice(li_t.end(), li_t, itor); //cut 5 to the end of list
    //itor is valid? yes
    std::cout << "itor is valid?" << *itor << std::endl;

}

void stl_use::set_use() {

    //测试set存相同结构的情况,如何去重struct类型的数据？
    // 重载 operater<


    std::set<DistrictInfo> test_set;

    if (true) {
        DistrictInfo test_d1(131, 3);
        DistrictInfo test_d2(131, 3);
        DistrictInfo test_d3(0, 0);
        test_set.insert(test_d1);
        test_set.insert(test_d2);  //会被去重的
        test_set.insert(test_d3);
        test_set.insert(test_d3);
    }

    cout << "test set size: " << test_set.size() << endl;

    DistrictInfo test_d3(131, 3);

    auto it = test_set.find(test_d3);
    std::size_t elem_count = test_set.count(test_d3);

    cout << "test set element: " << (*it).cid << " elem count: " << elem_count<< endl;

}



void stl_use::map_use() {

    //pair make_pair map
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
}


void stl_use::priority_queue_use(){
    //下面是使用优先级队列的常见形式；deque中数据是按照分数从小到大排序
    std::priority_queue<Student,std::deque<Student>,CompareFun> qu_test;

    Student s1("wang",60);
    Student s2("wei",60);
    Student s3("song",54);
    Student s4("ni",76);
    Student s5("havy",80);

    qu_test.push(s1);
    qu_test.push(s2);
    qu_test.push(s3);
    qu_test.push(s4);
    qu_test.push(s5);

    std::cout << "score \t name " <<std::endl;

    while(!qu_test.empty()){
        std::cout << qu_test.top().get_score() << "\t"
                <<qu_test.top().get_name() <<std::endl;

        qu_test.pop();
    }
}

void stl_use::vector_use(){

    //test emplace

    vector<int> test1;
    vector<int> test2;

    test1.emplace_back(1);//直接构造
    test1.emplace_back(2);
    test1.emplace_back(3);
    test2.emplace_back(4);
    test2.emplace_back(5);
    test2.emplace_back(6);
    vector<int> res;

    //使用insert插入多个元素
    res.insert(res.end(),test1.begin(),test1.end());
    res.insert(res.end(),test2.begin(),test2.end());

    for(auto e:res){
        cout <<"emplace1 res:" << e << endl ;
    }

    res.clear();
    //emplace插入多个元素？

    for(auto e:test1){
        res.emplace_back(e);
    }

    for(auto e:test2){
        res.emplace_back(e);
    }

    for(auto e:res){
        cout <<"emplace2 res:" << e << endl ;
    }

    cout << endl;

}






