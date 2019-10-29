/*
 * string_using.cpp
 *
 *  Created on: Apr 28, 2017
 *      Author: wangwei69
 */

#include <cctype>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <regex>  //c11正则表达式
#include "./com_use.h"
#include "string_using.h"

using namespace std;
using std::string;



void split_string2();

void first_charactor_upper(char *str);



/*
 * @desc 字符串是否全部是数字
 */
bool is_pure_digits(const char *str, unsigned int len);

int string_using_test(){

    string upper_str("AbCADDD1234");
    transform(upper_str.begin(), upper_str.end(), upper_str.begin(), ::tolower);
    cout << "transform result: " << upper_str << endl;

    const string str("dir/test.txt");

    //长度不足的情况下，起始地址过长，直接substr，会抛出out of range异常
    try{
    string sub_str = str.substr(5,3);
    }catch(std::exception const &e){
        cout << "err: " << e.what() << endl;
    }catch (...){
        cout << "unknown err!" << endl;
    }

    //find 和 rfind的用法: 截取目录名和文件文名
    /*
     * rfind(string match, pos)
     * 第2个参数代表：从某个位置开始，从后往前查找; 如果pos>=len(string)，npos 相当于整个字符串；
     * 返回值：
     * 第一次出现的下标位置,正着字符串数； 如果没找到？
     * pos+strlen(match)-1;
     *
     */
    string sub_str = "/t";
    string::size_type sz = str.rfind(sub_str, string::npos);

    if (sz != string::npos){
        cout << "size type: " << sz << " dir: " << str.substr(0,sz) << " file: " << str.substr(sz + sub_str.size()) << endl;
    }else{
        cout << "not find size type: " << sz << endl;
    }





    //是否全部是字符串
    string str_d = "12345678990 ";


    if (is_pure_digits(str_d.c_str(), str_d.size()))
        cout << "this is all digitals string :"  << str_d << endl;
    else
        cout << "this is not all digitals string :"  << str_d << endl;


    //tag字符串的分割
    split_string2();

    //字符串分割

    string string_src = "wangwei\t\tnihao\t";
    std::vector<std::string> res;
    res.clear();
    size_t res_size = split_string(string_src,"\t",res);

    cout << "string use test size: " << res_size << " " << "res[0]:" << res[0] << endl;
    if (res[res_size -1] == ""){
        cout << "empty string!" << endl;
    }

    //常见的string使用方式
    string_com_use();

    //模式匹配
    string_match_way();

    //判断中英文
    is_chinese_english();

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
   vector<string>(vec1).swap(vec1);//前半部分相当于tmp变量；函数结束，也就随之析构；
   cout << "swap capacity:size: " <<vec1.capacity() <<" :" <<vec1.size()<<endl;

}

bool  is_pure_digits(const char *str, unsigned int len){
    unsigned int index = 0;
    for(const char *ptr = str; (*ptr) && index < len; ++index, ++ptr){
        if (!isdigit(*ptr)){
            return false;
        }
    }
    return true;
}


/*
 * 解析tag字符串：Traffic facilities:10 Gas station:10 Gas station:10
 *
 * 把其中英文tag解析出来？
 *
 * 使用冒号分割；去除字符串中数字字符
 *
 */

void split_string2(){

    string test_str = "Traffic facilities:10 Gas station:10 Gas station:10";

    std::vector<string> res;
    res.clear();
    split_string(test_str,":",res);

    for (size_t idx = 0; idx < res.size();idx++){

        string tmp = res[idx];
        string tag;
        tag.clear();

        size_t pos = 0;
        for (; pos < tmp.size(); pos++){
            if(!std::isdigit(tmp[pos])){
                tag.push_back(tmp[pos]);
            }
        }

        for (pos = 0; pos < tmp.size(); pos++){
            if(!std::isspace(tag[pos])){
                break;
            }
        }

        string tag_res = tag.substr(pos);

        cout << "tag split: " << tag_res << "pos:"<< pos << std::endl;

        if(tag.empty()){

        }


    }




}



/*
 * @breif string 标准库 常见使用
 */

void string_com_use(){

    //string初始化方式
    string str1{"wangwei1"};  //直接初始化；c++11对花括号初始化全面支持。
    string str2("wang_wei-2,nihao + tahao");  //传统的直接初始化操作
    string str3(10,'w'); //使用10个w字符初始化
    string str4 = str3; //使用=的拷贝构造
    cout << str1 <<" "<<str2 <<" " << str3 << " " << str4 << endl;

    //读入标准输入上数据，放入str4；遇到空白符结束
    cout << "please input string value:" << endl;
    //cin >> str4;
    cout << "standard input stream str:" << str4 <<endl;

    //读入文件中的一行数据，以换行符结束
    std::ifstream ifs("/Users/wangwei69/workspace/github/tiny_util/test.txt");
    uint32_t line_num = 1;
    if (ifs.is_open()){
        while (getline(ifs,str4)){ //string类库提供的getline函数,一行数据放入string；返回istream&;
            cout << "line" << line_num << ": " <<str4;
            line_num++;
        }
    }else{
        cout << "file not open!" <<endl;
    }

    //将字符串中的字符换成大写；标点符号换成空格；数字保持不变
    for (auto &e : str2){ //使用范围for来便利strig
        if (isalpha(e)){ //判断是否为字母,包含在字符处理头文件：cctype 中
            e = toupper(e);
        }else if (ispunct(e)){ //判断是否为标点符号（+-_等等）
            e =' ';
        }
    }

    cout << "str2 transfer to: " << str2 << endl;

     //查找并截取字符串中字符子串；取出仅是数字部分的子串；

    std::string str5 = "123344F";

    //rfind从后往前查找，返回指定字符的位置；值为正数，从0开始下标和find一样；
    string::size_type pos = (str5.rfind('F') != std::string::npos) ? str5.rfind('F') : str5.rfind('T');
    string str6 = "";
    if (pos != std::string::npos){
        str5 = str5.substr(0,pos);
    }

    //字符串转转换成unsigned long值
    unsigned long linkid = 0;
    sscanf(str6.c_str(),"%lu", &linkid);


    cout << "replace test: " << str5  << " pos:" << pos << endl;

    cout << "linkid test: " << linkid << endl;


    unordered_map<unsigned long, std::vector<std::string> > maptest = {
            {123,{"s1","s2","s3"}},
            {124,{"ss1","ss2","ss3"}}

    };

    auto it = maptest.find(123);

    it ->second[0] = "sss1";
    it ->second[1] = "sss2";
    it ->second[2] = "sss3";


    cout << "map test : " << maptest.find(123) ->second[2] << endl;

    //prd_two_dimesion();

}


/*
 * @brief 字符串分割  比如，123\twang\twei\tni   每行以tab键分割
 * 主要涉及string的操作：？
 *
 * 1、字符串的查找：find
 *    find(substr,pos):从某个位置开始查找子串substr；返回第一个出现位置的下标；否则返回npos；
 * 2、字符串取子串：substr
 *    substr(pos,len):从某个位置开始取子串，长度为len；返回子串；或nullptr
 */
size_t split_string(const std::string& src,
                    const std::string& delimiter,
                    std::vector<std::string>& fields){

    fields.clear();
    size_t previous_pos = 0;
    size_t current_pos = 0;
    while ((current_pos = src.find(delimiter, previous_pos)) != std::string::npos) {
        fields.push_back(src.substr(previous_pos, current_pos - previous_pos));
        previous_pos = current_pos + delimiter.length();
    }

    // Add the last string
    // If the last string is delimiter, add emyty string to fields too.
    if (previous_pos <= src.length()) {
        fields.push_back(src.substr(previous_pos));
    }

    return fields.size();


}

/*
 * brief ： gbrank代码中提供的一版本，行分割的代码实现
 *
 * items:是string指针，保存的分割出来的每行数据；传入vector<string> vec; &vec[0]是可以的；
 * 分隔符:sep1 sep2是或的关系
 *
 * 返回：分割出来的字符串行数
 *
 */

int splitline(string line, string* items, int items_num, const char separator1,
        const char separator2)
{
    if (items == NULL || items_num <= 0)
    {
        return -1;
    }

    int n = line.length();
    int j = 0;
    int start = 0;

    for (int i = 0; i < n; i++)
    {
        if (line[i] == separator1 || line[i] == separator2)
        {
            if (j < items_num && start < n)
            {
                items[j++] = line.substr(start, i - start);
                start = ++i;
            }
        }
    }

    if (j < items_num && start < n)
    {
        items[j++] = line.substr(start, n - start);
    }

    return j;
}


/*
 * @字符串的模式匹配
 * 1、正则表达式：匹配所有以beijing开头的字符串；
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


}


/*
 * @brief 判断gbk编码的字符串，包含中文字符，还是英文字符，还是中英文混合的字符；
 * 中文：0
 * 英文：1
 * 中英文：2
 *
 * 详细参考：《字符编码问题--gbk,utf8》
 */

int is_chinese_english() {
    //gbk
    string str_gbk = "王伟2a";
    char* p_ch = const_cast<char*>(str_gbk.c_str());
    uint16_t label = 0; //中文gbk编码使用两个字节表示
    bool ch_flag = false;
    bool en_flag = false;
    while (*p_ch) {
        if (*p_ch < 0) { //为什么小余0？gbk汉字码位：8140~FEFE p_ch：是有符号的，能标识的范围：-128~+127
            label = *((uint16_t*) p_ch); //标识1个汉字
            printf("*p_ch:%d\t%c\n", *p_ch, label);
            cout << *p_ch << " : " << label << endl;
            p_ch += 2;
            ch_flag = true;
        } else {
            label = *p_ch;
            cout << *p_ch << " : " << label << endl;
            p_ch++;
            en_flag = true;
        }
    }//end while

    //返回结果
    if (ch_flag&&en_flag){
        return 2;
    }else if(ch_flag){
        return 0;
    }else{
        return 1;
    }
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





