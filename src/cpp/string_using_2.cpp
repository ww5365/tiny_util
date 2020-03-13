/*
 * string_using_2.cpp
 *
 *  Created on: Feb 26, 2020
 *      Author: wangwei69
 */

#include "com_use.h"
#include <string>

using namespace std;

void string_use_test2(){

    /*
     * wstring和string 区别 ？
     *
     * 1、wstring : 基本类型是wchar_t，每个字符最多占用4个字节；(32bit)
     *    string : 基本类型是 char, 每个字符占用1个字节；
     *
     * 2、wstring: 可以按照用户语义的长度来处理；比如："宽字符" 处理长度是：3
     *             如果用string，处理长度，就是实际占用字节长度：9 (utf-8 ：使用3个字节)
     */
    const wstring wstr= L"宽字符";
    wcout << "wstring size : " << wstr.size(); //大小是3

    for (wchar_t e : wstr){
        wcout << "wchar_t: " << e << endl;  //mac wcout没有输出
    }

    cout << endl;
    wcout << "wchar size : " << sizeof(wchar_t) << endl;

    cout << endl;
    const string str = "正常字符";
    cout << "string size:" << str.size() << endl;
    cout << endl;


    /*
     * 部分匹配是否能用find()匹配到，并返回部分匹配的第一个下标？
     *
     */

    wstring poi_name = L"王伟你好";
    wstring query = L"伟";

    size_t pos = poi_name.find(query);

    if (pos != string::npos){
        cout << "find the match pos: " << pos << endl;
    } else {
        cout << "not find the match  " << endl;
    }



}


