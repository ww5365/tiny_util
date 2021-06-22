/*
 * regex_test.cpp
 *
 *  Created on: 2019年12月18日
 *      Author: wangwei69
 */

#include "com_use.h"

#include <regex>
#include <string>
#include <vector>

using namespace std;



/*
 * @字符串的模式匹配
 * std::regex  pattern("模式子串串", std::regex_constraints::icase);  //模式串可以忽略大小写
 *
 * std::regex_match(str, pattern);  //str是否符合模式匹配 pattern，返回 true/false;
 *
 */

void string_match_way(){

    std::vector<string> test;
    test.push_back("bei hai1");
    test.push_back("beijing university");
    test.push_back("beijing人民");
    std::regex pattern("beijing.*");//.匹配任意字符；*匹配之前出现的>=0个字符
    std::regex pattern2("[A-Za-z0-9 ]+");//字母，数字，空格
    for (auto it = test.begin();it != test.end(); it++){

        if (std::regex_match(*it, pattern)){//参数1：要匹配的字符串 参数2：通配模式
            std::cout << "match pattern: " << *it << std::endl;
        }
        if (std::regex_match(*it, pattern2)){
            std::cout << "match pattern2: " << *it << std::endl;
        }
        //模式匹配成功，将匹配成功的字符串全部替换成replace，并返回新串;未成功，直接返回待匹配的字符串；
        std::string replace_str = "good person";
        string new_str = std::regex_replace( *it, pattern, replace_str);
        std::cout << "repalce: " << new_str << std::endl;
    }//end for


    //匹配：自助银行 或 ATM

    std::string str("招商银行ATM(上海新田360广场华侨城店)");

    string substr("自助银行");
    string::size_type idx = str.find(substr);

    if (idx != string::npos){
        cout << "self bank match str: " << str << " substr: " <<  substr << endl;
        cout << "self bank match: " << str.substr(0, idx) << endl;
    }else {
        cout << "self bank not match! " << str << " : " <<  substr << endl;
    }

    string  pat_str = ".*自助银行.*|.*ATM.*";
    std::regex pat(pat_str, std::regex_constants::icase);

    bool res = std::regex_match(str, pat);

    if (res){
        cout << "self bank regex match" << endl;
    } else {
        cout << "self bank regex not match" << endl;
    }

    const char *str_ch = "招商银行atm(上海)";

    res = std::regex_match(str_ch, pat);

    if (res){
        cout << "self bank regex match2" << endl;
    } else {
        cout << "self bank regex not match2" << endl;
    }
}



void regex_test(){

    string_match_way();


}


