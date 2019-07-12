/*
 * algorithm_use.cpp
 *
 *  Created on: Jul 31, 2017
 *      Author: wangwei69
 */

#include <vector>
#include <algorithm>

#include <map>

#include <iostream>
using namespace std;


/*
 * @biref 排序接口的使用：sort，stable_sort
 *
 *
 */

/*
 * 比较函数，注意参数是：const 类型的引用
 * 比较函数：可以设计成
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
 *
 */
void test_container_algorithm_use(){

    //将vector中字符串，尾插的方法拷贝到map对应的某个key中
    std::map<uint32_t, std::vector<std::string>> test_map;
    std::vector<std::string> vec = {"wang", "wei", "ni", "hao"};

    std::copy(vec.begin(), vec.end(), std::back_inserter(test_map[1]));

    std::cout << "copy back_inserter: " << test_map[1].size() << std::endl;




}

void algorithm_use(){

    sort_algorithm_use();
    replace_str_use();

    test_container_algorithm_use();
}
