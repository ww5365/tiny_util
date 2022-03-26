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
 * topic： 顺序容器
 *
 * 1、有哪些顺序容器？使用特点？
 *
 *    vector :
 *    deque
 *    list
 *    forward_list
 *    string
 *    array: 固定大小；随机访问；不能添删
 *
 *    选用原则：
 *    除非你有很好理由选其它containor,否则应该使用vector
 *    头尾可以插入删除元素，并支持随机访问，使用deque
 *    中间可以插入删除元素，可以考虑list/forward_list
 *    中间有插入、删除的还可以考虑用vector + sort 或者 list -> vector中
 *
 *    头文件：和类名同名
 *
 * 2、通用的一些容器的操作
 *
 *    iterator: c.begin() c.end()
 *    reverse_iterator: c.rbegin() c.rend()
 *
 *    const_iterator: c.cbegin() c.cend()
 *    const_reverse_interator: c.crbegin()
 *
 *    size_type:        最大可能容器大小
 *    difference_type:  计算两个迭代器距离，有符号整数
 *    value_type:       容器内元素类型
 *    reference:        元素左值类型，value_type &
 *    const_reference:  const value_type &
 *
 *
 *    c.insert(args):    使用args中元素拷贝进c
 *
 *    c.emplace(inits):  使用inits构造c中的一个元素
 *
 *
 * 3、迭代器
 *
 *   标识范围：[begin, end) 左闭，右开区间
 *
 *   迭代器不支持： it += 2  移动迭代器多个位置的操作吗？
 *
 *   常见的操作迭代器的操作：
 *
 *   std::begin()   std::end()
 *
 *   std::distance(itor1，itor2);
 *
 *   std::advance(itor, n);  //itor向后移动 n 个位置；itor 的值改变；（n<0 的话，向前移动）
 *
 *   c++11 : 支持
 *  new_itor next(itor, n)  ; //itor向后移动 n 个位置；itor 不改变，返回值是：最新的位置迭代器；
 *  new_itor pre(itor, n) ; //itor向前移动 n 个位置；itor 不改变，返回值是：最新的位置迭代器；
 *
 *
 * 4、初始化，赋值， swap
 *
 *    C c1(c2)
 *    C c1(m, n); //知道m,n含义
 *
 *    赋值：
 *    =
 *    assign
 *
 *    有什么不同？ assign可以接受参数，实现不同容器类型和元素类型的赋值。将原容器中内容会清空；
 *
 *    vector<char *> v;
 *    list<string> l;
 *    l.assign(v.begin(), v.end());
 *
 *
 *    swap:  建议使用非成员版本
 *
 *    swap(c1,c2) : 我的理解：除了array，只交换两个容器名字的指向，不涉及元素拷贝，插入，删除操作，所以比较快；
 *                  同时，由于元素不移动，原来容器的迭代器，引用，指针，都不失效；swap之后再使用，已经是另外名字下的内容了。
 *
 *
 */

const unsigned int SIZE = 10;


//定义一个类，没有默认构造函数

class NoDefault{

public:
    using pos = std::string::size_type;

private:
    std::string str;
    pos index;

public:

    explicit NoDefault(std::string s):str(s),index(0){}//只有一个带参数的构造函数，没有默认构造函数

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
    std::vector<NoDefault> t2(10, NoDefault("test")); //容器有10个元素；容器中元素没有默认构造函数；第二个参数，也就是元素的初始值，必须要有

    std::cout << "-------" << std::endl;

    std::vector<NoDefault>::iterator itr = t2.begin(); //c++11之前，必须这样使用
    std::vector<NoDefault>::const_iterator itr2 = t2.cbegin(); //常量迭代器，只能访问，不能修改元素内值； cbegin() 是c++11 支持；

    auto it3 = t2.begin(); //it3根据t2的类型，决定是否是const迭代器

    //容器初始化

    std::vector<NoDefault> t3(t2); //t2中内容拷贝构造t3; 保持容器类型和元素类型都必须相同

    std::deque<NoDefault> t4 (t2.begin(), t2.end()); // 使用t2的迭代器构造；保证元素类型相同即可；

    std::vector<int> t5(SIZE, 1); //两个参数的初始化构造函数；一个是容器大小，一个可选，说明元素的初始值，如果是类类型，需要考虑有没有默认构造函数；

    //array 容器

    std::array<int, 10> t6 = {1,2,3,4}; // array 必须有类型和大小；定义和初始化；后6个值默认为0；
    std::array<int, 10> t7 = t6;  //能直接赋值啊。这是和直接数组不同点


    //赋值和swap
    std::vector<const char *> v = {"test", "assign"};
    std::list<std::string> l;  //将v中的赋值给l；容器类型和元素类型都不同；
    l.assign(v.begin(), v.end());

    for (auto it = l.begin(); it != l.end(); ++it){
        std::cout << *it << std::endl;
    }


    std::list<std::string> l2 = {"wang", "wei", "nihao"};

    swap(l,l2);  //交换两个容器中内容

    for (auto it = l.begin(); it != l.end(); ++it){
        std::cout << *it << std::endl;
    }

    //容器的一些操作 push_back push_front insert

    auto iter_l = l.begin(); //准备在l的第3个元素之前，插入字符串 『 hello world』
    iter_l ++; iter_l ++;  // 尝试运算符： iter_l += 2 没有成功？？这是list的原因？

    auto it_re = l.insert(iter_l, {"hello",  "world"}); //结果: wang wei hello world nihao 返回值：it_re指向:hello

    /* topic: 插入范围值 函数insert
     * vector的iterator，支持 += 2；
     * 将别的容器中的元素：插入到本容器中，插入的范围：[begin, end) 函数：insert(self_iterator, other_begin, other_end)
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
     * topic:  emplace 和 insert 区别
     *
     *   emplace_back emplace  emplace_front 对应：push_back insert push_front
     *
     *   构造容器中元素：
     *
     *   emplace : 在容器中直接构造元素
     *
     *   调用构造函数的次数？
     *
     *
     *
     */


    //t1 的类型

    t1.emplace_back("wang",1);  //直接使用参数，在容器中直接构造元素;只调用1次两个参数的构造函数

    //t1.push_back("wang", 2);  // 不能直接构造 ，错误

    std::cout << "-----------" << std::endl;

    /* 下面"测试点1"要调用几次构造函数？3次 为什么？？
     * 解释1: 先调用1次两个参数的构造函数来构造这个对象；再调用1次拷贝构造函数，生成这个对象的临时对象；再调用1次拷贝构造函数，生成容器中元素；
     *
     * 解释2: 先调用1次两个参数的构造函数来构造这个临时对象； 由于提前没有分配空间，原来的元素需要再vector容器中发生内存移动，
     *       将原数据拷贝到新内存空间；
     *
     *       空间预先分配好合适的空间，对vector来说，也是很中重要的；提升性能；
     *
     * 总结，第一种解释错误；第二种解释合理；
     *
     */

    t1.push_back(NoDefault("wang", 2)); //测试点1
    std::cout << "测试点1----------end" << std::endl;


    t1.reserve(10);  //预留空间，仅改变capacity不改变size
    std::cout << "----------" << std::endl;
    NoDefault e1("wei", 3);
    std::cout << "----------" << std::endl;
    t1.push_back(e1);//不需要移动元素的情况下，仅2次构造函数。验证上面解释2的说法；
    std::cout << "----------" << std::endl;
    t1.emplace_back(e1); //这样和push_back 类似的，也是通过拷贝构造插入元素的；
    std::cout << "----------" << std::endl;




    /*
     * topic: string 的额外操作
     *
     * string的构造函数
     * substr : (pos,n)
     * assgin
     * insert
     * erase
     * append
     * replace : 替换
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
     * 字符串<->数值
     * to_string
     * stoi : (s,p,b) b是进制类型 p是第一个非数值字符的小标
     * stod
     * stoll
     *
     */

    //使用vec<char> 初始化一个string

    std::vector<char> vec = {'a', 'b', 'c'};

    std::string str(vec.begin(), vec.end()); //可以使用其它容器同类型的迭代器，来构造同类型的数据

    std::cout << "char initial a string: " << str << std::endl;


    const char *c_style_str = "this is a test!";

    //使用c类型字符串构造string

    std::string str_c(c_style_str, 5, 2);  //从下标5开始，拷贝2个字符串: is

    str_c.insert(1, " do not like bu");  //从小标1之前，插入字符串: i do not like bus

    str_c.replace(str_c.find("bus"), 4, "bike"); //找到bus，返回起始pos；从pos开始替换4个字符；i do not like bike

    std::string str_other ="test";
    str_other.assign(str_c, 1, 5); //从下标1开始，截取5个字符，覆盖掉str_other; 结果： do n

    str_other.append("12345"); //" do n12345"
    std::string dict = "0123456789";
    std::string::size_type pos = str_other.find_first_of(dict); //从str_other中搜索第一个出现dict中字符的位置。。



    std::cout << "test:" << str_c << std::endl;
    std::cout << "test2:" << str_other << std::endl;
    std::cout << "pos:" << pos << std::endl;




    /*
     * 迭代器的使用
     */

    std::vector<int> vec1{1,2,3,4,5,6};

    auto itor_start = vec1.begin();

    auto itor_end = vec1.end();

    //itor_start 不会改变，最新的迭代器通过返回值返回
    auto itor_new = std::next(itor_start, 2);
    auto itor_end_new = std::prev(itor_end, 1);

    std::cout << "iterator using: " << *itor_start << std::endl;
    std::cout << "iterator using: " << *itor_new << std::endl;
    std::cout << "iterator using: " << *itor_end_new << std::endl;

    //itor_start自身会发生改变
    std::advance(itor_start, 2);
    std::cout << "iterator using: " << *itor_start << std::endl;

    //back() 返回最后一个元素，不是返回迭代器
    //auto itor_back = vec1.back(); //错误

    std::cout << "get last element: " << vec1.back() << std::endl;



    /*
     * topic: 容器适配器 adptor
     *
     *  适配器更像是一种机制：容器使用已经有的，行为规则限定
     *
     *  顺序适配器：
     *                        默认容器         常用操作                                       能支持的容器
     *  stack                 deque          push_back pop_back back                     除了array,forward_list 都可以
     *  queue                 deque          push pop front  back              list deque
     *  priority_queue        vector         front push_back pop_front 随机访问             vector deque 不能list
     *
     *
     *  改变适配器默认使用的容器： 构造 template中第二个参数
     *
     *  stack<int, vector<int>> st; //选用了vector来装int数据，同理其它适配器的构造
     *
     *
     */


    //priority_queue 优先级队列

    std::priority_queue<int, std::deque<int>> pri_qu;  //定义一个优先级队列，使用deque容器来装元素数据

    pri_qu.push(3);
    pri_qu.push(1);
    pri_qu.push(5);
    pri_qu.push(2);

    while(!pri_qu.empty()){
        int value = pri_qu.top(); //取队头元素
        std::cout << "priority queue: " << value << std::endl;
        pri_qu.pop();
    }




    /*
     * topic：优先级队列，怎么来定义这个优先级？
     * 重载：< 运算符
     */


    class Rank {
    private:
        int rank; //按照rank值，进入优先级队列排序
        std::string name;
    public:
        explicit Rank(int r = 0, std::string n = " "): rank(r),name(n){};

        bool operator<(const Rank &r) const{
            return this->rank < r.rank; //true 优先级高
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
        Rank tmp = pri_que_rank.top(); // 取队头元素
        std::cout << "priority test: " << tmp.get_name() << std::endl;
        pri_que_rank.pop();
    }

    //BFS算法中，要借助queue来实现

    std::queue<int, std::deque<int>> qu; //使用deque来作为默认容器

    qu.push(4);//入队
    qu.push(5);
    int ele = qu.front(); //取队头元素
    qu.pop(); //出队

    int back_elem = qu.back(); // 取队尾元素

    std::cout<< "elem queue: " << ele << std::endl;
}
