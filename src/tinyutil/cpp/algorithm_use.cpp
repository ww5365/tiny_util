/*
 * algorithm_use.cpp
 *
 *  Created on: Jul 31, 2017
 *      Author: wangwei69
 */

#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <iostream>
#include <iterator>

using namespace std;

/*
 * @biref 
 * 排序接口的使用：sort，stable_sort
 * 仿函数：
 *  1、比较函数： 参数可以是const
 *  2、比较类
 *  3、类中重载operator<
 */

template <class Type>
bool cmp_fun(const Type&t1,const Type &t2){
    return (t1.size() < t2.size());
}

void sort_algorithm_use(){

    //按照字符串的长度,从小到大排序
    vector<std::string> test;

    test.push_back("wang");
    test.push_back("wei");
    test.push_back("test");
    test.push_back("ni");
    test.push_back("hao");
    test.push_back("hello");

    //稳定排序：长度相同的字符串，保持原来的位置不变
    std::stable_sort(test.begin(),test.end(),cmp_fun<string>);
    vector<string>::iterator it = test.begin();
    for (;it != test.end();it++){
        std::cout << *it << "  ";
    }

    std::cout << std::endl;
    /*
     * 预期结果：ni  wei  hao  wang  test  hello
     */

    test.clear();
    test.push_back("wang");
    test.push_back("niooo");
    test.push_back("weii");
    test.push_back("test");
    test.push_back("haoo");
    test.push_back("hello");

    //不稳定排序：长度相同的字符串，位置可能变
    std::sort(test.begin(),test.end(),cmp_fun<string>);
    it = test.begin();
    for (;it != test.end();it++){
        std::cout << *it << "  ";
    }

    std::cout << std::endl;

    //sort中使用默认的比较函数，从大到校降序排列
    vector<int> test2 = {1,2,4,5,9};
    std::sort(test2.begin(), test2.end(), std::greater<int>());
    std::copy(test2.cbegin(), test2.cend(), std::ostream_iterator<int>(std::cout, " ")); // 输出每个元素

    cout << endl;

}


/*
 * @brief 想把字符串中的某个字符都替换成另一个字符？
 * 头文件：
 * #include <algorithm>
 * 原型：
 * template <class ForwardIterator, class T>
 * void replace (ForwardIterator first, ForwardIterator last,
                const T& old_value, const T& new_value);

 *参考：http://www.cplusplus.com/reference/algorithm/replace/?kw=replace
 */


void replace_str_use() {

    //替换字符串中所有的逗号-》$
    string test_replace_str = "王伟,test,n";
    std::replace(test_replace_str.begin(), test_replace_str.end(), ',', '$');
    cout << "test replace str: " << test_replace_str << endl;

}

/*
 * 容器、迭代器种 配合算法使用

 * copy : back_inserter
 * accumulate
 * partial_sum
 * all_of
 *
 */
void container_algorithm_use(){

    std::cout << "----container_algorithm_use---" << std::endl;
    //将vector中字符串，尾插的方法拷贝到map对应的某个key中
    std::map<uint32_t, std::vector<std::string>> test_map;
    test_map[1].push_back("one");
    std::vector<std::string> vec = {"wang", "wei", "ni", "hao"};
    std::copy(vec.begin(), vec.end(), std::back_inserter(test_map[1])); // one 后面插入vec中的值，即不覆盖插入
    for_each(test_map[1].begin(), test_map[1].end(), [](const std::string &elem){ std::cout << elem << " ";});
    std::cout << std::endl;
    std::cout << "copy back_inserter: " << test_map[1].size() << std::endl; // 5

    vector<string> vec1(6, "test");
    std::copy(test_map[1].cbegin(), test_map[1].cend(), vec1.begin()); // 覆盖原有vec中的内容
    std::copy(vec1.cbegin(), vec1.cend(), std::ostream_iterator<string>(std::cout, " ")); // 打印vec中的所有值: one wang wei ni hao test
    std::cout << std::endl;

    //partial_sum 求和
    vector<int> vec2 = {1, 5, 3, 6};
    
    // 求全量累加和: accumulate(first, last, extra_val) : 每个元素(elem)求和 + extra_val
    int sum = accumulate(vec2.begin(), vec2.end(), 1); // 16
    cout << "accumulate result: " << sum << endl;
    
    // 求部分累加和： {1, 1+5, 1+5+3, 1+5+3+6}
    std::partial_sum(vec2.begin(), vec2.end(), vec2.begin()); // 计算部分和，并把结果覆盖原来的vector中
    std::copy(vec2.cbegin(), vec2.cend(), std::ostream_iterator<int>(std::cout, ",")); // 1, 5, 9, 15
    std::cout << std::endl;

    // all_of ： vec中的元素全部满足条件
    std::vector<int> vec3 = {1, 3, 5};
    bool res = std::all_of(vec3.cbegin(), vec3.cend(), [](const int &elem){return (elem % 2 == 1);}); // 判断是否全部为奇数
    
    if (res) {
        std::cout << "all_of result is all odd" << std::endl;
    }

    // any_of ： vec中元素任何一个满足条件
    int val = 5;
    res = std::any_of(vec3.cbegin(), vec3.cend(), [val](const int &elem) {return elem == val;});

    if (res) {
        std::cout << "any_of result exsit VAL" << std::endl;
    }

}

void algorithm_use(){

    sort_algorithm_use();
    replace_str_use();
    container_algorithm_use();
}
