/*
 * 11.cpp
 *
 *  Created on: Feb 14, 2019
 *      Author: wangwei69
 */

#include "all.hpp"

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;



/*
 *  第11章  关联容器
 *
 *  集合 、字典 : set map
 *
 *  关键是否可以重复： multi
 *
 *  底层存储是否有序： unordered 无序 hash 方式存储； 有序：？红黑树存储
 *
 *
 *  集合：<set> <unordered_set>
 *
 *  set
 *  multiset
 *  unordered_set
 *  unordered_multiset : 无序，关键字可以重复的 集合
 *
 *  字典： <map> <unordered_map>
 *
 *  map              关键字不重复，有序保存的map
 *  unordered_map    关键字不重复，无序保存的map
 *  multimap         关键字重复，有序保存的map
 *  unordered_multimap 关键字重复，无序保存的map
 *
 *  无序容器的选择使用考虑点：
 *    数据保存不需要明显的顺序关系，维护顺序成本很高；所以可以考虑使用无序容器；
 *
 *  查找：
 *
 *  find
 *  count
 *
 *  lower_bound(k): 返回迭代器，第一个>=k的迭代器
 *  upper_bound(k): 返回，第一个>k的迭代器; 如果查找的元素不存在，lower和upper的迭代器相同；
 *
 *  equal_range(k): 返回,k的范围，主要针对multiset，multimap，返回[k)的迭代器pair；
 *
 *  无序容器，除了上面的操作，还有特有的"桶管理"的操作：
 *
 *  c.bucket_count()
 *  c.bucket(k) : 关键字k在第几个桶中，返回size_t
 *  c.bucket_size(n) : 第n个桶，有多少元素容量
 *
 *  local_iterator:
 *  const_local_iterator: 桶中元素的迭代器
 *  c.begin(n) c.end(n):
 *  c.cbegin(n) c.cend(n):
 *
 *  c.reserve(num) : 重组存储，容器保存n个元素且不必rehash
 *
 *  c.load_factor() : 容器c中每个桶的平均元素数
 *
 *
 *  无序容器的关键字：
 *
 *    使用==比较，能够进行hash：内置类型，string，智能指针，都可以用无序容器存取，因为定义了hash；
 *
 *    库中定义了hash模板类： hash<key_type>, 计算string的hash值： hash<string>
 *
 *    一般的自定义类型类，不能使用无序容器；因为没有关键字hash函数；
 *
 *
 */


/*
 * topic: set multiset  关键是否相等，如何判定？
 *   关键字的比较，默认情况下，标准库使用<运算符来比较
 *
 *   1、类内部实现： operator<
 *
 *   2、单独实现compare函数，并在初始化的时候赋给容器对象
 *
 *     multiset<TYPE, decltype(compare)*> obj{compare};
 *
 *   为什么定义<就可以了？而且按照关键字从小到大的排序。？
 *
 */

 //如果想把学生类，保存在set中，类中必须有<运算符的定义；不然建立不起非重复关键的set集合


class Student{
private:
    unsigned long ID;
    string name;
public:
    Student(unsigned long id, string n):ID(id),name(n){
        cout << "use class Studenct constructor" << endl;
    }

    bool operator< (const Student &s) const{

        return this->ID < s.ID;
    }

    unsigned long get_ID() const{
        return this->ID;
    }

    string get_name() const{
        return this->name;
    }


};



//自定义hash函数
struct hash_fun{
    template<class T1, class T2>
    std::size_t operator()(std::pair<T1, T2> const &val) const{
        std::size_t first = hash<T1>()(val.first);
        std::size_t second = hash<T2>()(val.second);
        return first ^ second;
    }
};


void test_unordered_set(){

    /*
     * 使用unordered_set 存储pair对数据？
     * set<pair<int, int>>  是ok的。
     * unordered_set<pair<int, int>> 是不ok的
     *
     * set 需要operator< 来进行两个key的比较。pair有定义operator<，所以是ok的。
     * unordered_set，对key要进行hash，因为hash 类不支持pair，所以不ok，需要自己定义hash函数
     *
     */

    std::pair<int, int> test1(1,3);
    std::pair<int, int> test2(1,3);

    std::unordered_set<std::pair<int, int>, hash_fun> u_set;

    //hash_fun tc;
    //std::pair<int, int> a(1,1);
    //cout << "hash value: " << tc(a) << endl;

    u_set.insert(test1);
    u_set.insert(test2);
    u_set.erase(test1);





}


void test_11(){

    //set<Student> stu {Student(10,"wangwei"),Student(11, "wangwei2"),Student(11, "nihao")};

    multiset<Student> stu { Student(10, "wangwei"), Student(11, "wangwei2"),Student(11, "nihao") };

    stu.insert({12,"ni"});

    //mutiset所有元素的遍历
    for (auto it = stu.begin(); it != stu.end(); it ++) {
        cout << "multiset first: " << it->get_ID() << " second: " << it->get_name() << endl;
    }
    //multiset仅遍历一个关键字, 相同key的元素的个数？
    for (auto it = stu.cbegin(); it != stu.cend(); it = stu.upper_bound(*it)){
        cout << "multiset only key: " << it->get_ID() << " " << it->get_name() <<" numbers: "<< stu.count(*it) << endl;
    }

    auto it_1 = stu.lower_bound({11,"wangwei2"});
    auto it_2 = stu.upper_bound({11,"wangwei"});//都是以id作为比较元素的；返回第一个>11的元素的迭代器；也就是key元素的下一个位置；结果指向："ni"

    cout << "lower_bound: " << it_1->get_name() << endl;
    cout << "upper_bound: " << it_2->get_name() << endl;

    auto it_3 = stu.equal_range({11,"wangwei2"});

    cout << "equal range first: " <<it_3.first->get_name() << " second: " << it_3.second->get_name() << endl;

    //无序容器特有的桶管理操作

    unordered_map<int, string> u_map;

    for (int i = 1; i<= 100000; i++){
        u_map[i] = "test";
    }

    pair <int, string> pr = make_pair(1, "12333");

    u_map.insert(pr);

    std::size_t bucket_cnt = u_map.bucket_count();  //正在使用的桶数目,结果:102877 大于100000；也就是说会预留；
    std::size_t which_bucket = u_map.bucket(1); //关键字为1的元素在那个桶中；

    std::unordered_map<int, string>::local_iterator  it_4 = u_map.begin(which_bucket); //返回桶n的本地迭代器,指向pair<int,string>

    std::unordered_map<int, string>::local_iterator it_4_end = u_map.end(which_bucket);
    cout << "bucket count: " << bucket_cnt << " which bucket: " << which_bucket << endl;
    cout << "local iterator: " << it_4->second << " each bucket has element: " << u_map.load_factor() << endl;

    unordered_map<int, string>::const_iterator it_find = u_map.find(pr.first);

    cout << "const iterator first: " << it_find->first << " second: " << it_find->second << endl; //insert 如果已经存在key，不会更新值；

    //计算某个string的hash值？？

    string str("ab");

    hash<string> hash_str;  //调用运算符()后，返回size_t
    cout << "hash str: " << hash_str(str) << endl;

    //如果要用无序容器保存Student类，是需要提供hash函数的？可以考虑下怎么实现。。

    //unordered_set  无序容器，存储时使用key？ hash过的值

    //如何使用unordered_set存储pair对？

    test_unordered_set();





}
