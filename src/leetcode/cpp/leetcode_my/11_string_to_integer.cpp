/*
 * 11_string_to_integer.cpp
 *
 *  Created on: Jan 2, 2018
 *      Author: wangwei69
 */

/*
 *
 * 问题：Implement atoi to convert a string to an integer.
 *
 * 考虑：一些特殊case。
 * 1、涉及数字变动，首先考虑到：overflow的情况：INT_MIN: -21,4748,3648 INT_MAX:+2147483647
 * 2、有效的字符？ +-0~9
 * 3、出现多个+，- 情况处理：++1 --c ？无效输入？
 *
 */


#include <string>
#include <climits>

using namespace std;


class Solution{

public:

    /*
     * 自己实现的代码
     */
    int myatoi(const string str){

        bool first_valid = false;
        bool first_signal = false;
        int signal = 1;

        int result = 0;
        int len = str.size();

        for (int i = 0; i < str.size(); i++){

            if (!first_valid && is_validate_ch(str[i]) >= 0){
                first_valid = true; //找到第一个有效字符
                if (str[i] == '-'){
                    signal = -1;
                }
                if (is_signal_ch(str[i])){
                    continue;//第一个有效字符是=-，不计数
                }
            }else if (!first_valid){
                continue; //过滤掉之前的特殊字符
            }

            if (first_valid && is_number_ch(str[i])){
                //找到有效字符，同时是number类型char
                result = result * 10 + (str[i] - '0');  // ??? 未考虑溢出啊。
            }else{
                break;
            }

        }//end for

        return result * signal;

    }


    /*
     * 参考别人写的代码，学习溢出的判断技巧
     */

    int myatoi2(const string str){
        int num = 0;
        int sign = 1;
        const int n = str.length();
        if (n == 0) return 0;
        int i = 0;
        while (str[i] == ' ' && i < n) i++;
        if (str[i] == '+') {
            i++;
        } else if (str[i] == '-') {
            sign = -1;
            i++;
        }

        for (; i < n; i++) {
            if (str[i] < '0' || str[i] > '9')
                break;
            if (num > INT_MAX / 10 || (num == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10)) {
                //溢出判断 INT_MAX = 2147483647  INT_MIN = -2147483648
                return sign == -1 ? INT_MIN : INT_MAX;
            }
            num = num * 10 + str[i] - '0';
        }

        return num * sign;

    }



private:
    int is_number_ch(const char ch){

        if (ch >= '0' && ch <= '9'){
            return 1;
        }
        return 0;
    }

    int is_signal_ch(const char ch){

        if (ch == '+' || ch == '-'){
            return 1;
        }
        return 0;
    }

    int is_validate_ch(const char ch){
        if (ch >= '0' && ch <= '9'){
            return 0;
        }else if(ch == '+' || ch == '-'){
            return 1;
        }
        return -1;
    }





};

