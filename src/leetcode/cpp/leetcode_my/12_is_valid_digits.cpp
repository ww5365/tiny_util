/*
 * 12_is_valid_digits.cpp
 *
 *  Created on: Jan 9, 2018
 *      Author: wangwei69
 */


/*
 * 问题： 判定给定字符串是否为数字？
 * Validate if a given string is numeric.
 *
 * Some examples:
 *"0" => true
 *" 0.1 " => true
 *"abc" => false
 *"1 a" => false
 *"2e10" => true
 *
 *
 *目的： 开开眼？ 有限自动机是什么？怎么使用以及代码实现？
 *
 */

#include "test_main.h"
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

class Solution {

public:
   bool isNumber(const string & s){

       enum InputType{
           INVALID = 0,
           NUM,
           SIGN,
           DOT,
           EXP,
           InputTypeNum  //定义数组方便，可扩展性
       };

       short status[][InputTypeNum] = {
               {-1,1,2,3,-1}, //status 0 and input some ch lead to next status
               {-1,1,-1,4,5},
               {-1,1,-1,3,-1},
               {-1,6,-1,-1,-1},
               {-1,6,-1,-1,5},//status 4
               {-1,7,8,-1,6},
               {-1,6,-1,-1,5},
               {-1,7,-1,-1,-1},
               {-1,7,-1,-1,-1}
       };//先手绘状态转移有向图，再得出此表更方便

       std::string str(s);
       auto itor = str.begin();

       //去掉所有空格？
       //暂时没考虑好，用string怎么elegant实现？好吧，找到了；remove + erase:  two line code enough

       /*
        * remove是algorithm中;移除字符串中指定字符；但字符串长度不变;
        * 返回: 移除指定字符后，尾后迭代器；（此迭代器以及后面的元素是不确定的，使用erase清理）
       */

       string::iterator new_str_end =  remove(str.begin(),str.end(),' ');
       str.erase(new_str_end, str.end()); //移除后面多余字符

       int next_status = 0;
       for (auto ch:str){
           InputType input_type = INVALID;
           if (isdigit(ch)){
               input_type = NUM;
           }else if (ch == '+' || ch == '-'){
               input_type = SIGN;
           }else if (ch == '.'){
               input_type = DOT;
           }else if (ch == 'e' || ch == 'E'){
               input_type = EXP;
           }

           next_status = status[next_status][input_type];

           if (next_status == -1){
               cout << "invalid num status: " << next_status << endl;
               return false;
           }
       }//end for

       //最终的状态达到1，6，7 都是有效输入的状态
       switch (next_status){
       case 1:
       case 6:
       case 7:
           cout << "valid num status: " << next_status << endl;
           return true;
       default:
           cout << "invalid num status: " << next_status << endl;
           return false;
       }
    }//end is_Number

};//end class



void is_valid_number_test(){

    Solution s;

    string str1 = " -123.55";
    string str2 = "12.3 e-3";
    string str3 = "123e.23";

    s.isNumber(str1);
    s.isNumber(str2);
    s.isNumber(str3);


}


