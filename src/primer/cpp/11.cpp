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
 *  ��11��  ��������
 *
 *  ���� ���ֵ� : set map
 *
 *  �ؼ��Ƿ�����ظ��� multi
 *
 *  �ײ�洢�Ƿ����� unordered ���� hash ��ʽ�洢�� ���򣺣�������洢
 *
 *
 *  ���ϣ�<set> <unordered_set>
 *
 *  set
 *  multiset
 *  unordered_set
 *  unordered_multiset : ���򣬹ؼ��ֿ����ظ��� ����
 *
 *  �ֵ䣺 <map> <unordered_map>
 *
 *  map              �ؼ��ֲ��ظ������򱣴��map
 *  unordered_map    �ؼ��ֲ��ظ������򱣴��map
 *  multimap         �ؼ����ظ������򱣴��map
 *  unordered_multimap �ؼ����ظ������򱣴��map
 *
 *  ����������ѡ��ʹ�ÿ��ǵ㣺
 *    ���ݱ��治��Ҫ���Ե�˳���ϵ��ά��˳��ɱ��ܸߣ����Կ��Կ���ʹ������������
 *
 *  ���ң�
 *
 *  find
 *  count
 *
 *  lower_bound(k): ���ص���������һ��>=k�ĵ�����
 *  upper_bound(k): ���أ���һ��>k�ĵ�����; ������ҵ�Ԫ�ز����ڣ�lower��upper�ĵ�������ͬ��
 *
 *  equal_range(k): ����,k�ķ�Χ����Ҫ���multiset��multimap������[k)�ĵ�����pair��
 *
 *  ������������������Ĳ������������е�"Ͱ����"�Ĳ�����
 *
 *  c.bucket_count()
 *  c.bucket(k) : �ؼ���k�ڵڼ���Ͱ�У�����size_t
 *  c.bucket_size(n) : ��n��Ͱ���ж���Ԫ������
 *
 *  local_iterator:
 *  const_local_iterator: Ͱ��Ԫ�صĵ�����
 *  c.begin(n) c.end(n):
 *  c.cbegin(n) c.cend(n):
 *
 *  c.reserve(num) : ����洢����������n��Ԫ���Ҳ���rehash
 *
 *  c.load_factor() : ����c��ÿ��Ͱ��ƽ��Ԫ����
 *
 *
 *  ���������Ĺؼ��֣�
 *
 *    ʹ��==�Ƚϣ��ܹ�����hash���������ͣ�string������ָ�룬������������������ȡ����Ϊ������hash��
 *
 *    ���ж�����hashģ���ࣺ hash<key_type>, ����string��hashֵ�� hash<string>
 *
 *    һ����Զ��������࣬����ʹ��������������Ϊû�йؼ���hash������
 *
 *
 */


/*
 * topic: set multiset  �ؼ��Ƿ���ȣ�����ж���
 *   �ؼ��ֵıȽϣ�Ĭ������£���׼��ʹ��<��������Ƚ�
 *
 *   1�����ڲ�ʵ�֣� operator<
 *
 *   2������ʵ��compare���������ڳ�ʼ����ʱ�򸳸���������
 *
 *     multiset<TYPE, decltype(compare)*> obj{compare};
 *
 *   Ϊʲô����<�Ϳ����ˣ����Ұ��չؼ��ִ�С��������򡣣�
 *
 */

 //������ѧ���࣬������set�У����б�����<������Ķ��壻��Ȼ����������ظ��ؼ���set����


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



//�Զ���hash����
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
     * ʹ��unordered_set �洢pair�����ݣ�
     * set<pair<int, int>>  ��ok�ġ�
     * unordered_set<pair<int, int>> �ǲ�ok��
     *
     * set ��Ҫoperator< ����������key�ıȽϡ�pair�ж���operator<��������ok�ġ�
     * unordered_set����keyҪ����hash����Ϊhash �಻֧��pair�����Բ�ok����Ҫ�Լ�����hash����
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

    //mutiset����Ԫ�صı���
    for (auto it = stu.begin(); it != stu.end(); it ++) {
        cout << "multiset first: " << it->get_ID() << " second: " << it->get_name() << endl;
    }
    //multiset������һ���ؼ���, ��ͬkey��Ԫ�صĸ�����
    for (auto it = stu.cbegin(); it != stu.cend(); it = stu.upper_bound(*it)){
        cout << "multiset only key: " << it->get_ID() << " " << it->get_name() <<" numbers: "<< stu.count(*it) << endl;
    }

    auto it_1 = stu.lower_bound({11,"wangwei2"});
    auto it_2 = stu.upper_bound({11,"wangwei"});//������id��Ϊ�Ƚ�Ԫ�صģ����ص�һ��>11��Ԫ�صĵ�������Ҳ����keyԪ�ص���һ��λ�ã����ָ��"ni"

    cout << "lower_bound: " << it_1->get_name() << endl;
    cout << "upper_bound: " << it_2->get_name() << endl;

    auto it_3 = stu.equal_range({11,"wangwei2"});

    cout << "equal range first: " <<it_3.first->get_name() << " second: " << it_3.second->get_name() << endl;

    //�����������е�Ͱ�������

    unordered_map<int, string> u_map;

    for (int i = 1; i<= 100000; i++){
        u_map[i] = "test";
    }

    pair <int, string> pr = make_pair(1, "12333");

    u_map.insert(pr);

    std::size_t bucket_cnt = u_map.bucket_count();  //����ʹ�õ�Ͱ��Ŀ,���:102877 ����100000��Ҳ����˵��Ԥ����
    std::size_t which_bucket = u_map.bucket(1); //�ؼ���Ϊ1��Ԫ�����Ǹ�Ͱ�У�

    std::unordered_map<int, string>::local_iterator  it_4 = u_map.begin(which_bucket); //����Ͱn�ı��ص�����,ָ��pair<int,string>

    std::unordered_map<int, string>::local_iterator it_4_end = u_map.end(which_bucket);
    cout << "bucket count: " << bucket_cnt << " which bucket: " << which_bucket << endl;
    cout << "local iterator: " << it_4->second << " each bucket has element: " << u_map.load_factor() << endl;

    unordered_map<int, string>::const_iterator it_find = u_map.find(pr.first);

    cout << "const iterator first: " << it_find->first << " second: " << it_find->second << endl; //insert ����Ѿ�����key���������ֵ��

    //����ĳ��string��hashֵ����

    string str("ab");

    hash<string> hash_str;  //���������()�󣬷���size_t
    cout << "hash str: " << hash_str(str) << endl;

    //���Ҫ��������������Student�࣬����Ҫ�ṩhash�����ģ����Կ�������ôʵ�֡���

    //unordered_set  �����������洢ʱʹ��key�� hash����ֵ

    //���ʹ��unordered_set�洢pair�ԣ�

    test_unordered_set();





}
