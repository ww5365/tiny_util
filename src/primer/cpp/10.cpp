/*
 * 10.cpp
 *
 *  Created on: Feb 12, 2019
 *      Author: wangwei69
 */


#include "all.hpp"

#include <algorithm>
#include <numeric>
#include <vector>
#include <list>
#include <string>
#include <deque>
#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;


bool cmp_len(const string &s1, const string &s2){
    return s1.size() < s2.size();
}

bool cal_len(const string &s){
    return s.size() >= 3;
}

bool bigger_len(const string &s, string::size_type len){

    return s.size() >= len;
}

void print(const string &s, const string &tips){
    cout << tips << " " << s << endl;
}

/*
 *  第10章 泛型算法
 *
 *  "泛型": 对某种数据结构拥有更多的操作,不是容器的成员函数，更具通用性； 操作集中在： 搜索 和 排序
 *
 *  algorithm
 *  numeric
 *
 *  算法：不依赖容器，只依赖迭代器；所以所有操作通过迭代器来实现。
 *       100多个算法？如何去通用性的理解使用他们？
 *       算法：是否读取元素、改变元素、重排元素？
 *
 *
 *  算法汇总：
 *
 *  find
 *  find_if
 *  count
 *  accumulate
 *  equal
 *
 *  fill
 *  fill_n
 *  copy
 *
 *  remove
 *  remove_if
 *  remove_copy_if
 *
 *  unique
 *  sort
 *  stable_sort
 *  partition
 *  reverse
 *
 *
 *  针对list forward_list的特殊算法，是其成员函数:
 *  改变容器种元素
 *
 *
 *
 *
 *  算法命名规范：
 *
 *  1. 好多又重载的形式，支持传递谓词
 *     sort(b,e)
 *     sort(b,e, predicate)
 *
 *  2. _if版本
 *
 *     不是重载了，直接重名了一个函数，因为参数个数相同，不好重载
 *
 *     find
 *     find_if
 *  3. 拷贝和不拷贝版本
 *
 *     reverse(b,e) : 直接在原容器中进行操作，翻转
 *     reverse(b,e,dest)  : 反转后的结果，保存到dest，原容器种元素不变
 *
 *     remove_if(b,e, predicate)
 *     remove_copy_if(b,e,dest, prdicate)
 *
 *  4. 经典辨识：
 *
 *     replace(b,e, old, new)
 *     replace_if(b,e, predict, new)  //谓词
 *     replace_copy(b,e,dest,old, new) //原容器中值不变；结果放到dest容器中；
 *     replace_copy_if(b,e,dest,predicate, new)
 *
 *
 *
 *
 */


void test_10(){

    /*
     * 只读算法:
     * find
     * count
     * accumulate:求和
     *
     * equal: 比较两个容器中元素，是否一致；容器类型，元素类型，有时均可以不同；
     *
     */

    vector<string> vec1 = {"wang", "wei", "ni", "hao"};
    //vec1.pop_back();

    //find
    auto it = find(vec1.cbegin(), vec1.cend(), "ni");
    if (it != vec1.end()){
        //不等于尾后迭代器，就说明搜索到了指定字符串
        cout << "only read algorithm: find: " << *it << endl;
    }

    //accumulate: 求容器中"和"运算；第三个元素类型是初始值，同时必须和容器中元素类型相同；
    string sum = accumulate(vec1.cbegin(), vec1.cend(), string(" ")); //第三个元素不能是:"" ？ const char* 不支持 + 运算
    cout << "only read algorithm: accumulate: " << sum << endl; //结果：？ wangweinihao


    //equal: 接受3个参数；第3个参数是下个容器的起始迭代器；下个容器长度：大于等于第一个容器；比较元素个数：第一个容器的长度
    list<const char*> list1 = {"wang", "wei", "ni","hao", "a"};
    bool res = equal(vec1.cbegin(), vec1.cend(), list1.cbegin()); //虽然两个容器长度不同，但vec1长度范围内，元素值都是相等的；返回true
    cout << "only read algorithm: equal: " << res << endl;



    /*
     * 写操作算法：
     *
     * fill: (b, e, V) 第三个参数是插入的值
     * fill_n: (b, n, V) : 将迭代器b指向的容器中，前n个元素，置为V
     *
     */

    vector<string> vec2;

    //fill:
    fill(vec2.begin(), vec2.end(), "test"); //vec2是空;因为vec2初始为空,不会改变容器大小
    vec2.reserve(5);
    fill(vec2.begin(), vec2.end(), "test2");//因为vec2初始为空,不会改变容器大小

    cout << "test2-----" << endl;
    for_each(vec2.begin(), vec2.end(), [](const string &s){cout << "test fill " << s << endl;});
    cout << "test2------------" << endl;

   //数组是可以初始化的
    int arr[5];
    fill_n(arr, 5, 0);
    for_each(arr,arr+4, [](const int &i){cout << "element: " << i << endl;});

    //fill_n(vec2.begin(),1, "test"); //错误，向空容器中插入1个元素，改变容器大小了。插入迭代器来解决？？
    fill_n(vec2.begin(), vec2.size(), "test");

    fill_n(back_inserter(vec2), 1, "test"); //back_inserter返回容器的：插入迭代器
    cout << "write algorithm: fill: " << vec2.size() << endl;

    //copy(b, e, dest): 注意保证目的地址：dest大小假定是>=第一个容器的

    int ai[] = {1,2,3,4};
    constexpr int SIZE = sizeof(ai)/sizeof(*ai);
    vector<int> vec3;//(SIZE, 0);
    vec3.resize(SIZE);
    copy(begin(ai), end(ai), vec3.begin()); //必须保证vec3的size>=4

    cout << "write algorithm: copy: " << vec3.size() << endl;

    //实际工作中copy使用，场景
      //1、把一个小vector中的数据拷贝到一个大的vector中 ？

    vector<int> vec_b = {1,2,3,4,5,6,7};
    vector<int> vec_s = {8,9,10,11,12,13};

    auto it_start = vec_b.begin();
    advance(it_start, 3);  //迭代器向前移动3位

    copy(begin(vec_s), end(vec_s), it_start);

    cout << "copy vector into another: " << endl;
    for (auto elem : vec_b){

        cout << elem <<  " ";
        //结果：1 2 3 8 9 10 11
    }

    cout << std::endl;

    //如果要拷贝到某个容器之后，不覆盖原来值；需要插入迭代器
    std::copy(std::begin(vec_b), std::end(vec_b), std::back_inserter(vec_s));

    cout << "copy vector into another2: " << endl;

    for (auto elem : vec_s){
        cout << elem <<  " ";
        //运行结果：13 9 10 11 12 13 1 2 3 8 9 10 11
        //常规思路结果：8 9 10 11 12 13 1 2 3 8 9 10 11   为什么第一个值变化了？初步分析是：第一次 copy 导致溢出。
    }
    cout << std::endl;


    /*
     * 重排算法：
     *
     * sort    :  排序
     * unique  :  消除重复的元素，但不会真正删除元素，只是往前覆盖了；返回最后一个不重复的元素的尾后迭代器；
     *
     */

    //按照字典序排序，并去重

    vector<string> vec4 = {"wang", "wei", "ni", "ni","hao", "a", "a"};
    sort(vec4.begin(), vec4.end()); //默认使用元素的 < 元素符来比较大小

    vector<string>::iterator it4 =  unique(vec4.begin(), vec4.end()); //算法不会改变容器大小；返回不重复元素尾后迭代器；
    vec4.erase(it4, vec4.end()); //调用自带函数，删除多余的，"垃圾"元素

    for (auto e : vec4){
        cout << "sort and unique algorithm: " << e << endl;
    }



    /*
     * 定制操作：
     *
     *
     *  1、算法传递函数：predicate  谓词  一元和二元
     *
     *  以前接触到。 完成比较的小函数，返回bool；
     *
     *   bool cmp(const string &s1, const string &s2)
     *
     *   sort
     *   stable_sort
     *   partition
     *
     *
     *  2、lambda： 匿名函数：快速定义的当行最小函数， 从lisp借鉴来的；
     *
     *  形式：  [捕获列表](参数列表)->TYPE {函数体}
     *
     *  选用： 只在一两个地方使用简单操作； 如果是多次使用，还是建议设计成函数；没有捕获变量的匿名函数，可以考虑用谓词替代；
     *        部分操作，使用谓词时，只能有1，2个相同类型参数；有捕获变量的匿名函数，通常不好用函数替代；
     *
     *  说明：
     *
     *    捕获的变量，是在函数的生命周期内的；
     *     []
     *     [names]
     *     [=] : 隐式 值捕获
     *     [&] : 隐式 引用捕获
     *     [=, identifier_list]  : identifier_list,必须是显示 引用捕获
     *     [&, identifier_list]  : identifier_list,必须是显示 值捕获
     *
     *     捕获列表显式，隐式； 值捕获，引用捕获
     *
     *     值捕获： 要在lambda中改变变量值，需要在()后加mutable
     *
     *    函数体内有除return之外的语句，必须得有尾置返回类型，否则默认是void；
     *
     *    3、bind  :  <functional>
     *
     *
     *    不用lambda，又想传递参数给算法中的可调用对象参数部分；
     *
     *    bind 函数适配器 实际就是用： newCallable(X,Y) 来真正调用 int callable(..,X,Y)
     *
     *    建立 fun <=> newfun 之间的等价关系
     *
     *    auto newCallable = bind(callable, ARG_LIST);
     *
     *    新的可调用对象： newCallable
     *    ARG_LIST: 占位符： _1 代表newCallable的第一个参数，依次类推。定义在空间:placeholders
     *
     *              要使用外部参数的引用，怎么办？都是值拷贝。。通过：ref，cref,把引用值传给callable函数
     *
     *
     *    bind返回的数据类型是什么？
     *
     *    function<原函数返回值类型(原函数参数列表)>
     *
     *    newCallable 的类型：function<int(..., X, Y)>
     *
     *
     */


     /*
      * 谓词使用:
      *
      * sort 函数常使用的比较两个元素的方式
      *
      * 1、常用的std可调用对象:普通数据类型比较
      *    std::less<TYPE>()
      *    std::greater<TYPE>()
      * 2、自定义比较函数
      *    bool cmpfun(const TYPE&left, const Type&right);
      * 3、自定义比较类
      *    struct cmpClass{
      *       bool operator()(const TYPE&left, const TYPE&right){
      *       }
      *    }
      * 4、待排序数据元素是个结构体，重载<运算符
      *   struct Elem{
      *     bool operator<(const &Elem){
      *        return this->val < Elem.val;
      *     }
      *   }
      *
      *
      */

    //将vec4按照字符串的长度大小进行排列,长度递增；长度相同的按照原来的字段序列；

    //比较函数
    stable_sort(vec4.begin(), vec4.end(), cmp_len);


    vector<string> vec5 = {"abcd", "abc", "ab","abcde","a"};
    //partition : 谓词返回true，把元素放到前面；返回false，把元素放到后面；返回：最后一个使谓词为true之后的位置；
    auto it5 = partition(vec5.begin(), vec5.end(), cal_len); //一元  结果：abcd abc abcde ab a


    //lambda使用：

    //寻找长度>=5的字符串，并打印；

    vector<string> vec6 = {"abcdef", "abc", "ab","abcde","abcdefg"};
    string::size_type sz = 4;

    stable_sort(vec6.begin(), vec6.end(),
                [](const string &s1, const string &s2)
                  { return s1.size() < s2.size(); }
               );//先按照长度大小对字符串进行排序  ab abc abcde abcdef abcdefg


    //find_if
    auto it6 = find_if(vec6.begin(), vec6.end(),
                       [sz](const string &s)  mutable -> string::size_type  //值捕获的方式,改变sz值，必须mutable; 有除return之后语句，->也不可少；
                       { if(sz <= 4) sz = 5;
                         return s.size() >= sz;
                       } );//每个元素判断是否大于sz；找到第一个大于sz的元素，返回此位置迭代器；

    cout << "find_if: " << *it6 << endl;  //指向abcde的位置

    //for_each
    for_each(it6, vec6.end(), [](const string &s)
             {cout << "bigger len 5: " << s << endl;}); //打印从it6开始的元素；


    // bind
    auto bigger_len_new = bind(bigger_len, _1, sz); //_1:占位符 代表cmp_len_new的第一个参数;sz是值拷贝的方式传递；引用方式？ref,cref
    //调用bigger_len_new(str), 相当于调用bigger_len(str,sz)
    auto it6_2 = find_if(vec6.begin(), vec6.end(), bigger_len_new); //bind产生新的可调用对象：cmp_len_new 一元谓词
    cout << "find_if_2: " << *it6_2 << endl;  //指向abcde的位置


    /*
     * 再探迭代器：
     *
     * 1、插入迭代器
     *
     *    普通迭代器是不能改变容器大小，不好往容器插入，删除数据，所以才有了插入迭代器；实际是迭代器的适配器;
     *    参数：接收容器
     *    返回：迭代器
     *    实现：插入元素的功能
     *
     *   back_inserter(c)
     *   front_inserter(c) :  这个返回值： 一直保持最新的头元素位置;
     *   inserter(c, iter) : c容器，iter是要插入元素的位置；返回值，一直保持最初的这个iter位置不变；
     *
     *  2、输入输出流迭代器
     *
     *    平时用的少些，有需要继续深入
     *
     *  3、反向迭代器
     *
     *    正常迭代器：cbegin,cend, begin , end
     *
     *    反向迭代器：
     *    rbegin: 最后一个元素的位置
     *    rend: 第一个元素之前的位置
     *    crbegin : 常量迭代器
     *    crend
     *
     *    ++ : 运算是从后往前移动
     *    __ : 是从前往后移动
     *
     */


    list<string> l7 = {"wang", "wei", "ni", "hao"};
    deque<string> dec8,dec9; //定义两个空vector向量,要copy插入元素，需要用：插入迭代器

    //front_inserter
    copy(l7.begin(), l7.end(), front_inserter(dec8)); //头插，得到逆序dec8： hao ni wei wang
    for_each(dec8.begin(), dec8.end(), [](const string &s) {cout << "front inserter: " << s << endl;});

    //inserter
    copy(l7.begin(), l7.end(), inserter(dec9, dec9.begin())); //inserter返回值，一直保持在原来迭代器位置上；
    string tips_str("");
    tips_str.assign("inserter: ");
    auto printstr = bind(print, _1, tips_str); //绑定一个打印函数，后面可以经常配合for_each来使用

    for_each(dec9.begin(), dec9.end(), printstr); //算法会给一元谓词，传递一个参数:str

    //reverse_iterator
    string str10 = "this is test reverse_iterator";  //截取_之后的字符串
    auto it10 =  find(str10.crbegin(), str10.crend(), '_');
    cout << "reverse_iterator : " << *it10 << endl;
    string::const_iterator it100 = it10.base(); //base，把反向迭代器变成正向迭代器；同时，位置指向'_'的下一个位置

    cout << "reverse_iterator base: " << string(it100, str10.cend()) << endl;



    /*
     * 算法命名规范
     *
     *  remove
     *  remove_if
     *  remove_copy_if
     *
     */


    vector<int> vec11 = {1,2,3,4,5,6,7,8,9,10};
    vector<int> dest;
    remove(vec11.begin(), vec11.end(), 5); //删掉值: 5  返回新vec的尾后迭代器
    cout << "remove size: " << vec11.size() << endl;  //不真正删除元素，容器大小不变；

    remove_copy(vec11.begin(), vec11.end(), back_inserter(dest), 5);

    for(auto e : dest){
        cout << "remove: " << e << endl;
    }


    /*
     * topic: list forward_list特有的算法，设计成成员函数
     *
     *    l1.merge(l2)
     *    l1.merge(l2, cmp): 注意 l1 和 l2 必须是有序的；合并后l2删除为空；
     *
     *    l1.remove(val)
     *    l1.remove(pre): 要真删除，相当于erease
     *
     *    l1.reverse(): 链表翻转
     *
     *    l1.sort
     *    l1.sort(cmp):
     *
     *    l1.queue()
     *    l1.queue(pre):
     *
     *
     *    l1.splice()/splice_after(): 剪切另一个链表或自身中的元素，放到本链表的某个位置
     *
     *    (p, l2):       剪切l2中所有元素，放到p之前/之后位置； l1和l2不同
     *
     *    (p, l2, p2):   剪切l2中p2指向的元素，到l1中；l1和l2可以相同
     *
     *    (p, l2, b, e):  把l2种[b,e)范围内的元素剪切到p之前；
     *
     *
     *
     */


    list<int> l1 =  {4,2,5,6};
    list<int> l2 =  {1,3,5,2};

    l1.sort();
    l2.sort();
    //merge 排完序之后，有序集合合并
    l1.merge(l2);

    //reverse
    l1.reverse(); //结果：6,5,5,4,3,2,2,1

    cout << "the length l2: " << l2.size() << endl;
    list<int>::iterator it_l1 = ++ l1.begin();  //链表中iterator是一步步滚动？

    //splice
    l1.splice(l1.begin(), l1 , it_l1); //把l1中第2个元素，剪切到l1首元素之前，结果应该是：5,6,5,4,3,2,2,1;

    l1.splice(l1.begin(), l1, ++l1.begin(), --l1.end()); //把l1第二个元素到倒数第二个元素之间的list，剪切到手元素之前；6,5,4,3,2,2,5,1

    //最经常使用的是，将链表的某个元素剪切到链表的最后或首元素
    l1.splice(l1.end(), l1, l1.begin()); //把首元素剪切到尾部

    for(auto e : l1){

        cout << "the splice: " << e << endl;
    }

    /*
     *
     * 求有序集合的交，并，补集；
     * 注意：有序集合
     * set_intersection
     *
     */

    //A^B
    std::vector<int> vector1{ 1, 3, 4, 6, 9 };
    std::vector<int> vector2{ 2, 4, 6, 8, 9 };
    std::vector<int> result;

    std::set_intersection(
        vector1.begin(), vector1.end(),  //第一个区间
        vector2.begin(), vector2.end(),  //第二个区间
        std::back_inserter(result)
    );

    result.clear();

    //AUB
    std::set_union(
        vector1.begin(), vector1.end(),  //第一个区间
        vector2.begin(), vector2.end(),  //第二个区间
        std::back_inserter(result)
    );

    //第一个区间去除第二区间：A-B
    std::set_difference(
        vector1.begin(), vector1.end(),  //第一个区间
        vector2.begin(), vector2.end(),  //第二个区间
        std::back_inserter(result)
    );

    vector<string> v1{"美食", "火锅店"};
    vector<string> v2{"美食", "牛肉面"};
    vector<string> result_s;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    std::set_intersection(v1.begin(), v1.end(),
                          v2.begin(), v2.end(), back_inserter(result_s));

    for (auto str : result_s){

        cout << "intersection: " << str << " len: " << str.size() << endl;

        for (auto e : str){
            cout << "each elem: " << e << endl;
        }
    }



}
