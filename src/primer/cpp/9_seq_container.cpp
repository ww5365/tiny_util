/*
 * 9.cpp
 *
 *  Created on: Jan 23, 2019
 *      Author: wangwei69
 */

#include <string>
#include <vector>
#include <deque>
#include <list>
#include <array>
#include <iostream>

#include <stack>
#include <queue>

/*
 * topic�� ˳������
 *
 * 1������Щ˳��������ʹ���ص㣿
 *
 *    vector :
 *    deque
 *    list
 *    forward_list
 *    string
 *    array: �̶���С��������ʣ�������ɾ
 *
 *    ѡ��ԭ��
 *    �������кܺ�����ѡ����containor,����Ӧ��ʹ��vector
 *    ͷβ���Բ���ɾ��Ԫ�أ���֧��������ʣ�ʹ��deque
 *    �м���Բ���ɾ��Ԫ�أ����Կ���list/forward_list
 *    �м��в��롢ɾ���Ļ����Կ�����vector + sort ���� list -> vector��
 *
 *    ͷ�ļ���������ͬ��
 *
 * 2��ͨ�õ�һЩ�����Ĳ���
 *
 *    iterator: c.begin() c.end()
 *    reverse_iterator: c.rbegin() c.rend()
 *
 *    const_iterator: c.cbegin() c.cend()
 *    const_reverse_interator: c.crbegin()
 *
 *    size_type:        ������������С
 *    difference_type:  �����������������룬�з�������
 *    value_type:       ������Ԫ������
 *    reference:        Ԫ����ֵ���ͣ�value_type &
 *    const_reference:  const value_type &
 *
 *
 *    c.insert(args):    ʹ��args��Ԫ�ؿ�����c
 *
 *    c.emplace(inits):  ʹ��inits����c�е�һ��Ԫ��
 *
 *
 * 3��������
 *
 *   ��ʶ��Χ��[begin, end) ��գ��ҿ�����
 *
 *   ��������֧�֣� it += 2  �ƶ����������λ�õĲ�����
 *
 *   �����Ĳ����������Ĳ�����
 *
 *   std::begin()   std::end()
 *
 *   std::distance(itor1��itor2);
 *
 *   std::advance(itor, n);  //itor����ƶ� n ��λ�ã�itor ��ֵ�ı䣻��n<0 �Ļ�����ǰ�ƶ���
 *
 *   c++11 : ֧��
 *  new_itor next(itor, n)  ; //itor����ƶ� n ��λ�ã�itor ���ı䣬����ֵ�ǣ����µ�λ�õ�������
 *  new_itor pre(itor, n) ; //itor��ǰ�ƶ� n ��λ�ã�itor ���ı䣬����ֵ�ǣ����µ�λ�õ�������
 *
 *
 * 4����ʼ������ֵ�� swap
 *
 *    C c1(c2)
 *    C c1(m, n); //֪��m,n����
 *
 *    ��ֵ��
 *    =
 *    assign
 *
 *    ��ʲô��ͬ�� assign���Խ��ܲ�����ʵ�ֲ�ͬ�������ͺ�Ԫ�����͵ĸ�ֵ����ԭ���������ݻ���գ�
 *
 *    vector<char *> v;
 *    list<string> l;
 *    l.assign(v.begin(), v.end());
 *
 *
 *    swap:  ����ʹ�÷ǳ�Ա�汾
 *
 *    swap(c1,c2) : �ҵ���⣺����array��ֻ���������������ֵ�ָ�򣬲��漰Ԫ�ؿ��������룬ɾ�����������ԱȽϿ죻
 *                  ͬʱ������Ԫ�ز��ƶ���ԭ�������ĵ����������ã�ָ�룬����ʧЧ��swap֮����ʹ�ã��Ѿ������������µ������ˡ�
 *
 *
 */

const unsigned int SIZE = 10;


//����һ���࣬û��Ĭ�Ϲ��캯��

class NoDefault{

public:
    using pos = std::string::size_type;

private:
    std::string str;
    pos index;

public:

    explicit NoDefault(std::string s):str(s),index(0){}//ֻ��һ���������Ĺ��캯����û��Ĭ�Ϲ��캯��

    NoDefault(std::string s, int ind):str(s),index(ind){
        std::cout << "two args constructor!" << std::endl;
    }

    NoDefault(const NoDefault &other){
        std::cout << "copy constructor!"  << std::endl;
    }

    std::string get_str(){
        return str;
    }

};




void test_9(){

    std::cout << "--- test_9 begin ---" << std::endl;

    std::vector<NoDefault> t1;
    std::vector<NoDefault> t2(10, NoDefault("test")); //������10��Ԫ�أ�������Ԫ��û��Ĭ�Ϲ��캯�����ڶ���������Ҳ����Ԫ�صĳ�ʼֵ������Ҫ��

    std::cout << "-------" << std::endl;

    std::vector<NoDefault>::iterator itr = t2.begin(); //c++11֮ǰ����������ʹ��
    std::vector<NoDefault>::const_iterator itr2 = t2.cbegin(); //������������ֻ�ܷ��ʣ������޸�Ԫ����ֵ�� cbegin() ��c++11 ֧�֣�

    auto it3 = t2.begin(); //it3����t2�����ͣ������Ƿ���const������

    //������ʼ��

    std::vector<NoDefault> t3(t2); //t2�����ݿ�������t3; �����������ͺ�Ԫ�����Ͷ�������ͬ

    std::deque<NoDefault> t4 (t2.begin(), t2.end()); // ʹ��t2�ĵ��������죻��֤Ԫ��������ͬ���ɣ�

    std::vector<int> t5(SIZE, 1); //���������ĳ�ʼ�����캯����һ����������С��һ����ѡ��˵��Ԫ�صĳ�ʼֵ������������ͣ���Ҫ������û��Ĭ�Ϲ��캯����

    //array ����

    std::array<int, 10> t6 = {1,2,3,4}; // array ���������ͺʹ�С������ͳ�ʼ������6��ֵĬ��Ϊ0��
    std::array<int, 10> t7 = t6;  //��ֱ�Ӹ�ֵ�������Ǻ�ֱ�����鲻ͬ��


    //��ֵ��swap
    std::vector<const char *> v = {"test", "assign"};
    std::list<std::string> l;  //��v�еĸ�ֵ��l���������ͺ�Ԫ�����Ͷ���ͬ��
    l.assign(v.begin(), v.end());

    for (auto it = l.begin(); it != l.end(); ++it){
        std::cout << *it << std::endl;
    }


    std::list<std::string> l2 = {"wang", "wei", "nihao"};

    swap(l,l2);  //������������������

    for (auto it = l.begin(); it != l.end(); ++it){
        std::cout << *it << std::endl;
    }

    //������һЩ���� push_back push_front insert

    auto iter_l = l.begin(); //׼����l�ĵ�3��Ԫ��֮ǰ�������ַ��� �� hello world��
    iter_l ++; iter_l ++;  // ����������� iter_l += 2 û�гɹ���������list��ԭ��

    auto it_re = l.insert(iter_l, {"hello",  "world"}); //���: wang wei hello world nihao ����ֵ��it_reָ��:hello

    /* topic: ���뷶Χֵ ����insert
     * vector��iterator��֧�� += 2��
     * ����������е�Ԫ�أ����뵽�������У�����ķ�Χ��[begin, end) ������insert(self_iterator, other_begin, other_end)
     *
     */
    std::vector<std::string> vv = {"vector", "test", "insert"};
    auto it_v = vv.begin();
    it_re = l.insert(l.end(), it_v + 1, it_v + 2);


    for (auto it = l.begin(); it != l.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "insert return value: " << *it_re << std::endl;


    /*
     * topic:  emplace �� insert ����
     *
     *   emplace_back emplace  emplace_front ��Ӧ��push_back insert push_front
     *
     *   ����������Ԫ�أ�
     *
     *   emplace : ��������ֱ�ӹ���Ԫ��
     *
     *   ���ù��캯���Ĵ�����
     *
     *
     *
     */


    //t1 ������

    t1.emplace_back("wang",1);  //ֱ��ʹ�ò�������������ֱ�ӹ���Ԫ��;ֻ����1�����������Ĺ��캯��

    //t1.push_back("wang", 2);  // ����ֱ�ӹ��� ������

    std::cout << "-----------" << std::endl;

    /* ����"���Ե�1"Ҫ���ü��ι��캯����3�� Ϊʲô����
     * ����1: �ȵ���1�����������Ĺ��캯����������������ٵ���1�ο������캯������������������ʱ�����ٵ���1�ο������캯��������������Ԫ�أ�
     *
     * ����2: �ȵ���1�����������Ĺ��캯�������������ʱ���� ������ǰû�з���ռ䣬ԭ����Ԫ����Ҫ��vector�����з����ڴ��ƶ���
     *       ��ԭ���ݿ��������ڴ�ռ䣻
     *
     *       �ռ�Ԥ�ȷ���ú��ʵĿռ䣬��vector��˵��Ҳ�Ǻ�����Ҫ�ģ��������ܣ�
     *
     * �ܽᣬ��һ�ֽ��ʹ��󣻵ڶ��ֽ��ͺ���
     *
     */

    t1.push_back(NoDefault("wang", 2)); //���Ե�1
    std::cout << "���Ե�1----------end" << std::endl;


    t1.reserve(10);  //Ԥ���ռ䣬���ı�capacity���ı�size
    std::cout << "----------" << std::endl;
    NoDefault e1("wei", 3);
    std::cout << "----------" << std::endl;
    t1.push_back(e1);//����Ҫ�ƶ�Ԫ�ص�����£���2�ι��캯������֤�������2��˵����
    std::cout << "----------" << std::endl;
    t1.emplace_back(e1); //������push_back ���Ƶģ�Ҳ��ͨ�������������Ԫ�صģ�
    std::cout << "----------" << std::endl;




    /*
     * topic: string �Ķ������
     *
     * string�Ĺ��캯��
     * substr : (pos,n)
     * assgin
     * insert
     * erase
     * append
     * replace : �滻
     *
     * find
     * find_first_of
     * find_last_of
     * find_first_not_of
     * find_last_not_of
     *
     * compare
     *
     *
     * �ַ���<->��ֵ
     * to_string
     * stoi : (s,p,b) b�ǽ������� p�ǵ�һ������ֵ�ַ���С��
     * stod
     * stoll
     *
     */

    //ʹ��vec<char> ��ʼ��һ��string

    std::vector<char> vec = {'a', 'b', 'c'};

    std::string str(vec.begin(), vec.end()); //����ʹ����������ͬ���͵ĵ�������������ͬ���͵�����

    std::cout << "char initial a string: " << str << std::endl;


    const char *c_style_str = "this is a test!";

    //ʹ��c�����ַ�������string

    std::string str_c(c_style_str, 5, 2);  //���±�5��ʼ������2���ַ���: is

    str_c.insert(1, " do not like bu");  //��С��1֮ǰ�������ַ���: i do not like bus

    str_c.replace(str_c.find("bus"), 4, "bike"); //�ҵ�bus��������ʼpos����pos��ʼ�滻4���ַ���i do not like bike

    std::string str_other ="test";
    str_other.assign(str_c, 1, 5); //���±�1��ʼ����ȡ5���ַ������ǵ�str_other; ����� do n

    str_other.append("12345"); //" do n12345"
    std::string dict = "0123456789";
    std::string::size_type pos = str_other.find_first_of(dict); //��str_other��������һ������dict���ַ���λ�á���



    std::cout << "test:" << str_c << std::endl;
    std::cout << "test2:" << str_other << std::endl;
    std::cout << "pos:" << pos << std::endl;




    /*
     * ��������ʹ��
     */

    std::vector<int> vec1{1,2,3,4,5,6};

    auto itor_start = vec1.begin();

    auto itor_end = vec1.end();

    //itor_start ����ı䣬���µĵ�����ͨ������ֵ����
    auto itor_new = std::next(itor_start, 2);
    auto itor_end_new = std::prev(itor_end, 1);

    std::cout << "iterator using: " << *itor_start << std::endl;
    std::cout << "iterator using: " << *itor_new << std::endl;
    std::cout << "iterator using: " << *itor_end_new << std::endl;

    //itor_start����ᷢ���ı�
    std::advance(itor_start, 2);
    std::cout << "iterator using: " << *itor_start << std::endl;

    //back() �������һ��Ԫ�أ����Ƿ��ص�����
    //auto itor_back = vec1.back(); //����

    std::cout << "get last element: " << vec1.back() << std::endl;



    /*
     * topic: ���������� adptor
     *
     *  ������������һ�ֻ��ƣ�����ʹ���Ѿ��еģ���Ϊ�����޶�
     *
     *  ˳����������
     *                        Ĭ������         ���ò���                                       ��֧�ֵ�����
     *  stack                 deque          push_back pop_back back                     ����array,forward_list ������
     *  queue                 deque          back push_back front pop_front              list deque
     *  priority_queue        vector         front push_back pop_front �������             vector deque ����list
     *
     *
     *  �ı�������Ĭ��ʹ�õ������� ���� template�еڶ�������
     *
     *  stack<int, vector<int>> st; //ѡ����vector��װint���ݣ�ͬ�������������Ĺ���
     *
     *
     */


    //priority_queue ���ȼ�����

    std::priority_queue<int, std::deque<int>> pri_qu;  //����һ�����ȼ����У�ʹ��deque������װԪ������

    pri_qu.push(3);
    pri_qu.push(1);
    pri_qu.push(5);
    pri_qu.push(2);

    while(!pri_qu.empty()){
        int value = pri_qu.top(); //ȡ��ͷԪ��
        std::cout << "priority queue: " << value << std::endl;
        pri_qu.pop();
    }


    /*
     * topic�����ȼ����У���ô������������ȼ���
     * ���أ�< �����
     */


    class Rank {
    private:
        int rank; //����rankֵ���������ȼ���������
        std::string name;
    public:
        explicit Rank(int r = 0, std::string n = " "): rank(r),name(n){};

        bool operator<(const Rank &r) const{
            return this->rank < r.rank; //true ���ȼ���
        }

        std::string get_name() const{
            return this->name;
        }
    };


    std::priority_queue<Rank> pri_que_rank;

    pri_que_rank.emplace(4, "test4");
    pri_que_rank.emplace(1, "test1");
    pri_que_rank.emplace(5, "test5");
    pri_que_rank.emplace(2, "test2");

    while (!pri_que_rank.empty()){

        Rank tmp = pri_que_rank.top();

        std::cout << "priority test: " << tmp.get_name() << std::endl;

        pri_que_rank.pop();

    }

    //BFS�㷨�У�Ҫ����queue��ʵ��

    std::queue<int, std::deque<int>> qu; //ʹ��deque����ΪĬ������

    qu.push(4);//���
    qu.push(5);
    int ele = qu.front(); //ȡ��ͷԪ��
    qu.pop(); //����

    std::cout<< "elem queue: " << ele << std::endl;


}
