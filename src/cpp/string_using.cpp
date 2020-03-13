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

    //前缀截取

    string str_j1 = "北京大学";
    string str_j2 = "北京";
    str_j1 = str_j1.substr(str_j2.size());

    cout << "string jiequ: " << str_j1 << endl;


    //18/12 Tryon Rd, Lindfield NSW 2070澳大利亚

    string address_str = "18/12 Tryon Rd, Lindfield NSW 2070, 澳大利亚";

    size_t pos2 = address_str.find_last_of(",");

    string address_str2 = address_str.substr(0, pos2);

    std::transform(address_str2.begin(), address_str2.end(), address_str2.begin(), ::tolower);

    std::replace(address_str2.begin(), address_str2.end(), ',', ' ');

    cout << "last sep pos: " << pos2 << " str: " << address_str2 << endl;


    //复杂门址数据格式解析
    string address = "[北京市(110000)|CITY|1|][东城区(110101)|AREA|1|][故宫东门外()|ROAD|0|]景山前街4号故宫博物院[宁寿宫(10275688963131648896)|POI_PARENT|1|]内";

    parse_address_norm(address);

    cout << "normal address: " << address << endl;

    //判断第一个数字字符出现的位置

    //string str_dig = "王伟12";
    string str_dig(address);
    int pos_digital = get_first_digit_pos(str_dig.c_str());
    cout << "first digital pos: " << pos_digital << endl;



    //判断一行数据是否为空行
    string line = " ";
    size_t pos1 = line.find_first_not_of(" \t\r\n");  //寻找第1个不是" \t\r\n"子串中任一字符的下标位置；如果空行，一直到行尾；
    if (pos1 == string::npos){
        //一直到最后都是" \t\r\n"，说明是空行
        cout << "line is empty string "  << line  << endl;
    }

    /*
     * 测试中文处理：unsinged short  两个字节标识一个中文？
     *
     * 与源码文件的编码有关：
     * 源码：gbk     标识两个字节的 gbk 码值
     * 源码 utf8    会有问题，只能打印出两个字节的码值
     *
     */

    const char *ch_num[12] = {"零","一","二","三","四","五","六","七","八","九","十","百"};

    unsigned short value = 0;
    cout << "chinese charactors encoding value: " << endl;
    for (int i = 0; i < 12; ++i){
        value = *(unsigned short*)ch_num[i];
        cout << hex << value << " ";
    }

    cout << endl;

    //测试中文的长度
    std::string chinese_str = "王伟";
    int query_len = 0;
    for (size_t ix = 0; ix < chinese_str.size(); ++ix) {
        if (chinese_str[ix] == ' ') {
            continue;
        }
        query_len++;
    }

    cout << "chinese str size: " << query_len << endl;

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

    string brand_name{"肯德基(test)"};
    string query{"肯德"};

    int pos = 0;
    if ((pos = brand_name.find_last_of('(')) != string::npos){
        brand_name.assign(brand_name, 0, pos);
    }


    cout << "brand name: " << brand_name << endl;



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

   return 1;
}



// 是否是双字节字符, 只针对GBK/GB18030编码进行判断
bool is_gb18030_double_bytes(const char* src, size_t len) {
    if (len < 2) {
        return false;
    }
    unsigned char ch_1 = src[0];
    unsigned char ch_2 = src[1];
    if (ch_1 >= 0x81 && ch_1 <= 0xFE
            && ((ch_2 >= 0x40 && ch_2 <= 0x7E) ||
                (ch_2 >= 0x80 && ch_2 <= 0xFE))) {
        return true;
    }
    return false;
}

// 是否是四字节字符, 只针对GB18030编码进行判断
bool is_gb18030_four_bytes(const char* src, size_t len) {
    if (len < 4) {
        return false;
    }

    unsigned char ch_1 = src[0];
    unsigned char ch_2 = src[1];
    unsigned char ch_3 = src[2];
    unsigned char ch_4 = src[3];
    if (ch_1 >= 0x81 && ch_1 <= 0xFE
            && ch_2 >= 0x30 && ch_2 <= 0x39
            && ch_3 >= 0x81 && ch_3 <= 0xFE
            && ch_4 >= 0x30 && ch_4 <= 0x39) {
        return true;
    }

    return false;
}


/*
 * 复杂门址字符串的解析
 */

void parse_address_norm(std::string &address_norm) {
    /* 大概有以下几种格式
    "[北京市(110000)|CITY|1|][东城区(110101)|AREA|1|][故宫东门外()|ROAD|0|]景山前街4号故宫博物院[宁寿宫(10275688963131648896)|POI_PARENT|1|]内";
    "[新疆维吾尔自治区(650000)|PROV|1|][石河子市(659001)|CITY|1|]银燕路"
    "[广东省(440000)|PROV|0|][东莞市(441900)|CITY|0|][新竹路()|ROAD|0|]康河路东200米"
    "[北京市(110000)|CITY|1|][东城区(110101)|AREA|1|]天坛东路甲1号[天坛公园(11168662261122746086)|POI_PARENT|1|]附近"
    "[云南省(530000)|PROV|0|][曲靖市(530300)|CITY|1|][麒麟区(530302)|AREA|1|][麒麟南路()|ROAD|1|][中天购物中心(8022519126727589108)|POI_PARENT|1|1层$]"
    "[广东省(440000)|PROV|0|][中山市(442000)|CITY|0|][中山四路()|ROAD|1|63号$][华凯商务大厦(18010431063507075071)|POI_PARENT|1|3层307$]"
    "[广东省(440000)|PROV|0|][东莞市(441900)|CITY|1|]厚街镇汀山村[村前路()|ROAD|1|77号$](博览大道旁)"
    */
    int start = 0;
    int end = 0;

    std::vector<std::string> items;
    bool is_in_item = false; //是否在[]内的标记位
    int len = address_norm.length();
    const char* ptr = address_norm.c_str();
    int offset = 0;
    for (int i = 0; i < len; i += offset) {
        if (is_gb18030_double_bytes(ptr + i, len - i)) {
            offset = 2;
        } else if (is_gb18030_four_bytes(ptr + i, len - i)) {
            offset = 4;
        } else {
            offset = 1;
        }
        if (address_norm[i] == '[') {
            if (is_in_item) {
                end = i;
                std::string item = address_norm.substr(start, end - start);
                items.push_back(item);
                //start = i + 1  ;
                //is_in_item = false;
            }
            start = i;
            is_in_item = true;
            continue;
        }
        if (address_norm[i] == ']') {
            end = i;
            std::string item = address_norm.substr(start + 1, end - start - 1);
            items.push_back(item);
            start = end;
            is_in_item = false;
            continue;
        }
        if (address_norm[i] != '[' && address_norm[i] != ']' && !is_in_item) {
            start = i;
            is_in_item = true;
            //continue;
        }
        if (i == len - offset) {    // 以中文结束,i不会走到len - 1的位置
            end = i + offset;       // end == len
            std::string item = address_norm.substr(start, end - start);
            items.push_back(item);
        }
    }
    std::string address = "";
    for (int i = 0; i < items.size(); ++i) {
        std::string item = items[i];
        int prov_index = item.find("PROV");
        int city_index = item.find("CITY");
        int area_index = item.find("AREA");
        int road_index = item.find("ROAD");
        int parent_index = item.find("POI_PARENT");
        if (prov_index != std::string::npos || city_index != std::string::npos ||
                area_index != std::string::npos) {
            continue;
        }

        std::vector<std::string> infos;

        //boost::split(infos, item, boost::is_any_of("|"));  //按照字符"|"来切分字符串，结果保存在 infos 中


        split_string(item, "|", infos);

        if (infos.size() == 1) {
            address = address + item;
        }
        if (infos.size() != 4) {
            continue;
        }
        //此处只剩下 ROAD 和 POI_PARENT，以及游离的没切出来的
        //[信息路()|ROAD|1|甲9号$]  （道路中增加了门牌号）
        //[中天购物中心(8022519126727589108)|POI_PARENT|1|1层$]  （增加了父点POI分段）
        if (road_index != std::string::npos ||
                parent_index != std::string::npos) {
            int left_parenthesis = infos[0].find("(");
            int dollar_symbol = infos[3].find("$");
            int flag = atoi(infos[2].c_str()); //标志位，标记该片段在地址中是否存在，0不存在，1存在
            if (flag == 0) {
                continue;
            }
            if (left_parenthesis != std::string::npos) {
                address = address + infos[0].substr(0, left_parenthesis);
            }
            if (dollar_symbol != std::string::npos) {
                address = address + infos[3].substr(0, dollar_symbol);
            }
            continue;
        }
    }
    address_norm = address;
}


/*
 * 识别第1个是数字的字符的位置
 */
bool is_digit(const char ch){

    if ((const unsigned char)ch >= '0' && (const unsigned char)ch <= '9'){
        return true;
    }
    return false;
}

int get_first_digit_pos(const char *str){
    const char *p = str;
    int pos = 0;
    while (*p){
        if (is_digit(*p)){
            return pos;
        }
        cout << "digital str ch: " << *p << endl;
        p++;
        pos++;

    }
    return -1;
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
 *
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





