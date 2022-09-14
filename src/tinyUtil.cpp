//============================================================================
// Name        : tinyUtil.cpp
// Author      : wangwei
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include "./tinyutil/inc/cmd_option.h"
#include "./tinyutil/inc/com_use.h"
#include "./tinyutil/inc/macro_study.h"
#include  "./tinyutil/inc/stl_use.h"
#include  "./tinyutil/inc/design_model.h"
#include "./leetcode/inc/01_all.h"
#include "./leetcode/cpp/chapater_nine/chapater_nine.h"

#include <cstdlib>
#include <ctime>
#include <string>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <memory>

#include "./primer/inc/all.hpp"

typedef struct test_struct{
    int a;
    char *str;
}test_struct;

#define QT_LEN 2
#define IP_SIZE 2

#define MAMA(x...)  p_##x;

#define TEST_MACRO(TYPE)  \
do{\
    cout << "TEST MACRO para name: " << #TYPE << endl;  \
    cout << "TEST MACRO Para content: " << TYPE << endl; \
}while(0)

//禁止拷贝的构造函数；放在private中
#define DISABALE(C)\
    C(const C&);\
    C& operator=(const C&);

//#define TEST(fmt,arg...) do{\
//    printf("function:[%s]"fmt,__FUNCTION__,##arg);\
//}while(0)

template<typename T1,typename T2>struct CustomType
{
    typedef T1 RAW;
    typedef T2 ATOMIC;

};

int is_alpha(const char c)
{
    if((const unsigned char)c >= 'A' &&  (const unsigned char)c <= 'Z'
        || (const unsigned char)c >= 'a' && (const unsigned char)c <= 'z')
        return 1;
    return 0;
}


int trim_all(string &str){
    if (str.size() <= 0){
        return 0;
    }
    size_t index = 0;
    for (size_t i = 0; i < str.size(); i++){
        if (str[i] != ' '){
            str[index++] = str[i];
        }
    }//end for
    str = str.substr(0, index);
    return index;
}


struct cmp{
    bool operator() (const int left, const int right){
        return left < right; //后进来的（right）越大，返回true，优先级越高；
    }
};

struct link_acc_traffic_t {
    uint64_t       linkid;
    float           orispeed;
    float           speed;
    int   status;
    time_t          update_time;
    uint8_t         rewrite_info;
    uint8_t         confidence_status;
};


class Comp{
public:
    bool operator()(const int left, const int right){

        if (left >= right){
            return true;//返回true，前面的大，说明已经位置正确，不用交换了。
        }else{
            return false;
        }
    }
};

int *g_int_ptr = nullptr;

struct DisplayItem {
    //多少人访问过
    //uint32_t pv;
    //星级评分
    //uint8_t rating;

    //char ch[3];
    char *data;
    char data2[0]; //这个占多少空间？验证

};


void fun1(void *ptr) {
    std::cout << "1111" <<std::endl;
}


void fun1(int i) {
    std::cout <<"2222" << std::endl;;
}



int main(int argc, char* argv[]) {

    
    // mem_use_test();

    // move_use_test();

    // tuple_use_test();
    
    // primer_all_test();

    // enum_use_test();
    // map_use_test();

    //leetcode 目录下testcase
    leetcode_all_test();


    //nlohmann使用
    // json_test();

    //predicate : 谓词
    // predicate_use_test();


    //rtti : run time type info
    // rtti_use_test();

    //c类型子串的使用

    //charaters_use_test();
    //double大小比较和与0比较
    //double a = 1e-10;
    //double b = 1e-11;
    //const double EPSION = 1e-13;

    //if (a > 0){
    //    cout << "a greater than b" << endl;
    //} else {
    //    cout << "a smaller than b" << endl;
    //}

    //if (fabs(a - b) < EPSION){
    //    cout << "a is equal b" << endl;
    //} else {
    //    cout << "a not equal b !" << endl;
    //}

    string test_macro = "wangwei";
    TEST_MACRO(test_macro);

    //vector的使用测试

    //vector_use_test();


    //字符串相关的测试使用

    // string_use_test2();
    
    // //字符串测试
    // string_using_test();

    //double feature[4];
    //fill_n(feature, 4, 19);//快速赋初始值
    //feature[0] = 20;
    //std::swap(feature[0], feature[1]); //可以直接交换两个数组元素的值

    //for (auto elem: feature){
    //    cout << "fill_n: " << elem << endl;
    //}


    // //unsigned short

    // string cid_str = "80500";

    // unsigned short  test_cid = (unsigned short)atoi(cid_str.c_str());

    // cout << "test test cid: " << test_cid << endl;


    // class Base{
    // private:
    //     int a;
    //     virtual int get_value() = 0;
    // public:
    //     Base(int x): a(x){}
    //     virtual ~Base(){}
    // };

    // class Derived: public Base{
    // private:
    //     int b;
    //     int get_value(){
    //         return b;
    //     }
    // public:
    //     Derived(int x = 0, int y = 0): Base(x),b(y){}

    // };


    // stl_use::vector_use();
    // stl_use::deque_use();
    // stl_use::priority_queue_use();

    // std::shared_ptr<vector<string> > content;
    // cout << "test shared_ptr use cnt1: " << content.use_count() << endl;
    // content = std::make_shared<vector<string> >(10,"test string");
    // //content = make_shared<vector<string>>();
    // //content = shared_ptr<vector<string>> (new vector<string>(10, "test"));
    // cout << "test shared_ptr use cnt2: " << content.use_count()  << " size: " <<content->size()<< endl;

    // for (auto it = content->begin(); it != content->end(); ++it){

    //     cout << "content: " << *it << endl;
    // }

    // //测试文件处理:compare

    // //cmpare_file_use_test();


    // bool test_stoi = stoi("1.5");
    // cout << "test_stoi" << test_stoi << endl;

    // bool test_priority_logic = false || true && false;  //先与后或；结果是false

    // cout << "logic priority res: " << test_priority_logic << endl;
    // //assign: 1、不同容器相互赋值；2、清空原容器中内容

    // vector<string> vec_str;
    // vec_str.reserve(5);
    // vec_str.push_back("test");
    // list<string> l_str = {"wang", "wei", "nihao"};
    // vec_str.assign(l_str.begin(), l_str.end());
    // for_each(vec_str.begin(), vec_str.end(), [](const string &s){cout << s << endl;});

    // size_t test = 1.4;

    // cout << "test size_t: " << test << endl;

    // cout << "11<<1: " << (1<<11) << endl;

    // const char *str_test = "abc";

    // str_test = "abcd";

    // cout << "str_test: " << str_test << endl;


    // //gbk c++11

    // //cout << "gbk 内码: " << BOOK_GBK_STR.c_str() << std::endl;

    // //设计模式相关疑问点的验证

    // test_design_pattern();

    // algorithm_use();

    // //size 大小计算

    // cout << "size struct: " << sizeof(DisplayItem) << endl;
    // //多线程相关
    // thread_use_test();

    // //
    // //ml_use_test();


    // //c11新特性测试

    // new_feature_c11_use_test();


    // //模板使用

    // template_use_test();

    // cout << "begin to test!" << endl;
    
    // //数学计算
    //  math_use_test();

    // //com 使用
    // com_use_test();

    // //文件读写
    // cpp_r_w_demo();

    // //类型转换
    // data_type_convert_test();

    // //
    // cout << "sizeof:" << sizeof(struct link_acc_traffic_t) << endl;
    // std::string str1 = "7.8962";
    // float f_test = 0;
    // sscanf(str1.c_str(), "%f", &f_test);

    // cout << "sscanf float test : " << f_test << endl;

    // //时间的测试

    // time_use_test();

    // //直接delete null指针，会不会core？
    // char *ptr = NULL;
    // delete ptr;

    // //set使用测试
    // stl_use::set_use();
    // stl_use::list_use();
    // stl_use::iterator_use();
    // stl_use::map_use();
    // stl_use::unordered_set_use();


    // //正则表达式

    // regex_test();


    // //测试排序使用的比较函数,返回true/false的对排序结果的影响

    // std::vector<int> test_vec = {12,3,4,67,29};

    // std::sort(test_vec.begin(), test_vec.end(), Comp());

    // for (size_t idx = 0;idx < test_vec.size(); idx++){

    //     std::cout << test_vec[idx] << " " ;
    // }

    // std::cout << std::endl;

//
//    char buff_2[256];
//    memset(buff_2,0,256);
//    int test1 = 100;
//
//    snprintf(buff_2,sizeof(buff_2),"%d",test1); //
//
//    cout << "buff2 value:" << buff_2 <<endl;
//
//
//    int *a_ptr = new int[10](); //
//
//    for(int i = 0 ;i < 10; i++){
//        cout << a_ptr[i] << " ";
//    }
//
//    cout << endl;
//
//
//
//    //
//    string test_str_se = "han$";
//
//    string::size_type pos_se =  test_str_se.find("$");
//
//    cout << "pos :"  << pos_se <<endl;
//    cout << "first: " << test_str_se.substr(0,pos_se) << "second:" << test_str_se.substr(pos_se+1) <<endl;
//
//
//
//
//    string trim_str = "鐜嬩紵 nihao ! ";
//    cout << "before trim_all:" <<trim_str <<endl;
//    int len = trim_all(trim_str);
//    cout << "after trim_all:" <<trim_str << "len:"<< len <<endl;
//    //test stl
//
//    stl_use stlUse;
//    stlUse.vector_use();
//    stlUse.priority_queue_use();
//
//    //
//    printf("test percernt:%% \n");
//    string test2 = "wangwei:9";
//    int pos_tag = test2.find(":");
//    string sep1 = test2.substr(0,pos_tag);
//    string sep2 = test2.substr(pos_tag+1);
//    int credit;
//    sscanf(sep2.c_str(),"%d",&credit);
//    cout <<"pos: " << pos_tag << " sep1: " <<sep1 << " sep2: " <<credit <<endl;
//
//    char buff[10];
//
//    const char *ptr=test2.c_str();
//    int index2 = 0;
//    while((*ptr) != NULL){
//        buff[index2] = *ptr;
//        ptr++;
//        index2++;
//    }
//
//    buff[index2] = '\0'; //buff
//
//    cout <<"test buff overflow:" << buff <<endl;
//    char buff2[10];
//
//    memset(buff2,0,10);
//
//    strncpy(buff2,buff,10);
//
//    cout <<"test overflow:" << buff2 <<endl;
//
//    //stable_sort
//
//    cout << "algorithm use: sort and stable_sort" <<endl;
//    algorithm_use();
//
//
//    //
//    std::cout << "the max int:"  << std::numeric_limits<float>::max() <<std::endl;
//    std::cout << "the max uint:"  << std::numeric_limits<unsigned int>::max() <<std::endl;
//
//    //TEST("this is a test name:%s,num:%d\n","wangwei",4);
//    int MAMA(x,y);
//
//    string test = "nih鐜嬩紵";
//
//    const char *ch = test.c_str();
//    while(*ch){
//        if(is_alpha(*ch)){
//            cout << "alpha:" << *ch << std::endl;
//        }else{
//
//            cout << "not alpha:"  << *ch <<std::endl;
//        }
//        ch++;
//    }
//
//
//
//    cout<<endl;
//    //CustomType<unsigned int,unsigned long long> Test;
//
//    std::cout << "bytes:" << sizeof(CustomType<unsigned int,unsigned long long>) <<std::endl;
//    std::cout << "bytes2:" << sizeof(CustomType<unsigned int,unsigned long long>::RAW) <<std::endl;
//    std::cout << "bytes3:" << sizeof(CustomType<unsigned int,unsigned long long>::ATOMIC) <<std::endl;
//
//    //CustomType<string,int> test;
//    //test.RAW = "wangwei";
//    //std::cout <<"test.Raw:" <<test.RAW<<std::endl;
//
////    CustomType<string,int>::RAW test_str2;
////    test_str2="weiwang";
////    std::cout <<"test_str2.Raw:" <<test_str2<<std::endl;
////
////    static const int MAX_HASH_NUM = (1ULL<<31) -1;
////
////    std::cout << "the hash num:" << MAX_HASH_NUM <<std::endl;
////
////    string_using_test();
////
////	string query = "中国";
////	string sub = "";
////	string sub2 = "";
////	string sub3 = "";
////
////	string sub_tmp;
////	string::size_type pos = query.find(sub);
////	string::size_type pos2 = query.find(sub2);
////
////	if (pos != string::npos){
////		//query.erase(pos,sub.size());
////		query = query.substr(0,pos);
////	}
//
//
//
//
////	cout << "the final query: " << query <<endl;
////	cout << "the final substr: " << sub_tmp <<endl;
////
////	cout << "pos res: " << pos <<" : " <<pos2 << " : "<<string::npos <<endl;
//
//
//	// 9.8.0
//	const char *sv = "9.8.1";
//	if (strcmp(sv,"9.8.0") >= 0){
//		std::cout << "version:" << sv <<std::endl;
//	}else{
//		std::cout << "version2:" << sv <<std::endl;
//	}
//
//    //c
//
//    std::cout << time(NULL)<<std::endl;
//
//    srand((unsigned int)time(NULL));
//
//    int ran = rand();
//    int index = ran%IP_SIZE;
//
//    std::cout << "ran: index: " <<ran <<":"<<index <<std::endl;
//
//
//    //
//    char *test_str[QT_LEN]={
//            "qt=s",
//            "qt=nb"
//    };
//
//    int qt_num = QT_LEN;
//
//    std::cout << "test_str len: " <<qt_num <<std::endl;
//
//
//
//
//    //
//
//    test_struct cv[]={
//            {2,NULL},
//            {3,NULL}
//    };//
//
//    std::cout << cv[0].a << std::endl;
//    std::cout << cv[1].a << std::endl;
//
//
//    //
//
//    std::string qt = "\"qt\":\"s\"";
//    const char *bound = "(123,323.2211111;2121,33.33)";
//
//    std::stringstream ss;
//    ss<<"\""<<"b"<<"\""<<":"<<"\""<<bound<<"\"";
//
//    std::string query2;
//    ss>>query2;
//
//    cout <<"query res: " <<query2 <<std::endl;
//
//
//    float x1,x2,y1,y2;
//
//    sscanf(bound,"(%f,%f;%f,%f)",&x1,&y1,&x2,&y2);
//
//    char buf[256];
//    buf[0] = '\0';
//
//    double xx = (x1 + x2)/2;
//    double yy = (y1 + y2)/2;
//
//    snprintf(buf,256,"(%.2f,%.2f;%.2f,%.2f)",xx,yy,xx,yy);
//
//    printf("res: %f , %f ,%f ,%f  bound:%s \n",x1,y1,x2,y2,buf);
//
//
//    //cpp read write file demo
//
//    cpp_r_w_demo();
//
//    //test macro
    // macro_study();
//
//    //c read_write_demo
//    read_write_demo();
//
//    cout << "!!!Hello World!!!" << endl;
//    cout << "args num :" << argc << endl;
//    for (int i = 0; i < argc; i++) {
//        cout << "args:" << i << " value:" << argv[i] << endl;
//    }
//    cout << "finished!" << endl;
//    char *p = argv[argc-1];
//    cout << "argv:" << *p <<endl;
//
//    util::CmdOption opt;
//
//    opt.init(argc,argv,"d:c:h");
//
//    if (opt.has_option("d")){
//        cout << "d option exist" <<endl;
//        cout <<"d option is: " <<opt["d"] <<endl;
//
//    }else{
//        cout << "d option not exist" <<endl;
//    }
//
//    if (opt.has_option("f")){
//        cout << "f option exist" <<endl;
//        cout <<"f option is: " <<opt["f"] <<endl;
//
//    }else{
//        cout << "f option not exist" <<endl;
//    }

    printf("program is over!\n");
    return 0;
}

