/*
 * string_using_2.cpp
 *
 * Created on: Feb 26, 2020
 * Author: wangwei69
 */

#include "com_use.h"
#include <string>
#include <vector>
#include <map>
#include <string>

#include <algorithm>

using namespace std;


// 参数是vector的常量引用，可以往里面添加数据？

int fun(vector<string> &str)
{
    str.push_back("wang");
    str.push_back("wei");
    return 0;
}
std::string VecToStr(const std::vector<std::int32_t> &vec)
{
    std::string res = "";
    for (auto e : vec) {
        res += (std::to_string(e) + ",");
    }
    return res;
}

void wchar_using() {

        /*
     * wstring和string 区别 ？
     *
     * 1、wstring : 基本类型是wchar_t，每个字符最多占用4个字节；(32bit)  常用来出来国际化字符
     * string : 基本类型是 char, 每个字符占用1个字节；
     *
     * 2、wstring: 可以按照用户语义的长度来处理；比如："宽字符" 处理长度是：3
     * 如果用string，处理长度，就是实际占用字节长度：9 (utf-8 ：使用3个字节)

     * 3、wstring 《-》 string 的相互转换： 
        使用boost库中接口：utf_to_utf<wchar_t>(str.c_str(), str.c_str() + str.size());
     */
    const wstring wstr = L"宽字符";
    std::wcout << "wstring size : " << wstr.size() << std::endl; // 大小是3

    for (wchar_t e : wstr) {
        std::wcout << "wchar_t char: " << e << std::endl; // mac wcout没有输出
    }

    std::cout << std::endl;
    std::wcout << "wchar_t bytes : " << sizeof(wchar_t) << std::endl; // wchar_t占用的字节数
    std::cout << std::endl;

    const string str = "正常字符";
    std::cout << "string size:" << str.size() << std::endl;  // 实际占用的字节数，utf8 : 12 bytes

    // wstring 保存英文是什么情况？
    wstring wstr2 = L"ni hao";
    for (size_t i = 0; i < wstr2.size(); ++i) {
        std::wcout << "wstr2: " << wstr2[i] << std::endl;
    }

    // 部分匹配是否能用find()匹配到，并返回部分匹配的第一个下标？
    wstring poi_name = L"王伟你好伟大";
    wstring query = L"王伟";

    size_t pos = poi_name.find(query);

    if (pos != string::npos) {
        std::cout << "find the match pos: " << pos << std::endl;
    } else {
        std::cout << "not find the match  " << std::endl;
    }

    // wchar_t作为key构成map
    std::map<wchar_t, int> w_map;
    for (wchar_t word : poi_name) {
        auto it = w_map.find(word);
        if (it == w_map.end()) {
            w_map.insert(make_pair(word, 1));
            std::cout << "w_word: " << word << std::endl;
        } else {
            it->second++;
            std::cout << "w_word2: " << word << " val: " << it->second << std::endl;
        }
    }
    std::cout << "w_map size: " << w_map.size() << std::endl;

    // hashcode 转64bit的base64编码
    int64_t res = 0;
    for (auto e : str) {
        // 循环12次，每次一个字节
        res = 31 * (0xFFFFFFFF & res) + e;
    }
    std::cout << "chinese base64: " << static_cast<int32_t>(res) << std::endl;

}

void string_use_test2()
{
    std::cout << "-----------string_use_test2------------" << std::endl;
    // string 赋初值
    string str1(5, '.'); // string初始化，5个相同的字符.给到字符串str1
    std::cout << "inital string : " << str1 << std::endl; //  str1 = "....."

    // 字符串进行翻转 : Reverse 可以翻转容器内 [first,last) 指向的内容 <algorithm>
    string str2 = "abcde";
    std::reverse(str2.begin(), str2.end());
    std::cout <<"reverse str2: " << str2  << std::endl;

    //  字符串查找 和 截取substr()
    size_t pos = 1; // 下标从0开始；在下标1处截取长度为n的子串: edcba 即从d开始
    size_t n  = 3;
    string subStr2 = str2.substr(pos, n);  // 如果n大于字符串长度，截取到最后; 这里是：dcb  如果pos大于字符串长度，抛出异常:out of range
    std::cout << "subStr2 : " << subStr2 << std::endl;

    size_t idx = str2.find(subStr2);  // 返回字符串第一次出现的下标位置, 从0 开始; 这里是1
    
    string subStr3 = str2.substr(idx, n);  // 如果n大于字符串长度，截取到最后; 这里是：dcb  如果pos大于字符串长度，抛出异常:out of range
    std::cout << "subStr3 : " << subStr3 << std::endl;



    
    // wchar 相关的测试
    wchar_using();
    



    // 整数vec<int>转成字符串
    std::vector<int32_t> vec = { 1, 2, 3, 4, 112 };
    std::cout << VecToStr(vec) << std::endl;

    // test
    std::vector<std::string> vec_str;
    fun(vec_str);
    cout << "const str len: " << vec_str.size() << endl;
    
    std::cout << "-----------string_use_test2 finished------------" << std::endl;
}
