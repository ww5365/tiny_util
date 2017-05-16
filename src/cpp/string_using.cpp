/*
 * string_using.cpp
 *
 *  Created on: Apr 28, 2017
 *      Author: wangwei69
 */

#include <vector>
#include <string>
#include <iostream>
#include "./com_use.h"

using namespace std;

bool verify_unicode(const char *str);
int string_unicode_utf8(const char *src,string &des);

int string_using_test(){

    //测试函数：string_unicode_utf8

    const char *src = "\"name\":\"\\ufy1c\\u56fd\\ufa19\\ufa4c \\u9752\\u7a7a\\u53e4\\u5e0\"";

    //const char *src = "\\u2";

    string str_src(src);
    string str_des;

    cout <<"src:" <<str_src<<endl;
    string_unicode_utf8(src,str_des);
    cout <<"des:" <<str_des<<endl;

    //测试如何消除，臃肿的容器？capcity 很大，但size很小的情况。
    vector<string> vec1;
    for (int i =0 ;i< 1000 ;i++){
        vec1.push_back("wan");
    }//添加1000个字符串
    cout << "origin capacity:size: " <<vec1.capacity() <<" :" <<vec1.size()<<endl;
    vec1.clear();
    vec1.push_back("wangwei");//1024 capacity : 1 size
    cout << "clear capacity:size: " <<vec1.capacity() <<" :" <<vec1.size()<<endl;

    //消除臃肿技巧swap
   vector<string>(vec1).swap(vec1);
   cout << "swap capacity:size: " <<vec1.capacity() <<" :" <<vec1.size()<<endl;

}

/*
 *功能：将字符串（\u23ab unicode编码），转为utf8的中文。同时把源字符串的结果拷贝至目标字符串。
 * 比如：
 *  "name":"\ufa1c\u56fd\ufa19\ufa4c \u9752\u7a7a\u53e4\u5e02"
 *  转为：
 *  "name":"靖国神社 青空古市"
 */

int string_unicode_utf8(const char *src,string &des){


    des.clear();
    const char *cur = src;

    int len = strlen(src);

    try{
        while(*cur != '\0' && cur < (src+len)){
              //判断出现\u这种情况
              if (*cur == '\\' && *(cur+1) != '\0'){
                  const char *begin = cur;
                  int cnt = 0;
                  //const char *end = cur;
                  cnt++;
                  cur++;
                  if (*cur == 'u' && *(cur+1) != '\0'){
                      char unicode[5];
                      unicode[0]='\0';
                      //cur ++;
                      cnt ++;
                      if ((cur+4)<(src+len)){
                          //后面4个字符是否非法判断
                          if(verify_unicode(cur+1)){
                              strncpy(unicode,cur+1,4*sizeof(char));//取出\ufa1c中的fa1c
                              unsigned short unicode_value;
                              sscanf(unicode,"%4x",&unicode_value);
                              printf("unicode:%x\n",unicode_value);
                              char test[128];
                              sprintf(test,"%s","靖");
                              des.append(test);
                              cur += 5;
                              continue;
                          }else{
                              //处理\u123y后面4个字符有非法字符的情况
                              des.append(begin,cnt);
                              printf("test 111111\n");
                          }
                      }else{
                          //处理\u123且是字符串尾情况
                          des.append(begin,src+len-begin);
                          printf("test 222222\n");
                          break;
                      }
                  }else{
                      //处理\x 或 0这种情况
                      if(*cur != '\0'){
                          cnt++;
                      }
                      des.append(begin,cnt);
                  }
              }else{
                  //处理正常情况下的字符
                  des.append(1,*cur);
              }

              cur++;
          }

    }catch(...){
        return -1;
    }

    return 0;

}

bool verify_unicode(const char *str){

    bool first = false;
    bool second = false;
    bool third = false;
    bool fourth = false;


    if (str == NULL){
        return false;
    }

    cout << *str <<endl;
    cout << *(str+1) <<endl;
    if( (*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'F')||(*str >= 'a' && *str <= 'f') ){
        first = true;
    }

    if( (*(str+1) >= '0' && *(str+1) <= '9') || (*(str+1) >= 'A' && *(str+1) <= 'F')||(*(str+1) >= 'a' && *(str+1) <= 'f') ){
        second = true;
    }

    if( (*(str+2) >= '0' && *(str+2) <= '9') || (*(str+2) >= 'A' && *(str+2) <= 'F')||(*(str+2) >= 'a' && *(str+2) <= 'f') ){
        third = true;
    }
    if( (*(str+3) >= '0' && *(str+3) <= '9') || (*(str+3) >= 'A' && *(str+3) <= 'F')||(*(str+3) >= 'a' && *(str+3) <= 'f') ){
        fourth = true;
    }


    return (first&second&third&fourth);
}

