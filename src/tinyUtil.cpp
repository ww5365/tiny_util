//============================================================================
// Name        : tinyUtil.cpp
// Author      : wangwei
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include "cmd_option.h"
#include "com_use.h"
#include "macro_study.h"
#include  "stl_use.h"

#include <cstdlib>
#include <ctime>

#include <string>

using namespace std;

typedef struct test_struct{
    int a;
    char *str;
}test_struct;


#define MAMA(x...)  p_##x;

#define QT_LEN 2

#define IP_SIZE 2



template<typename T1,typename T2>struct CustomType
{
    typedef T1 RAW;
    typedef T2 ATOMIC; //必须保证是2*RAW大小,同时放在OdictSnode中必须对齐..
    //并且这个atomic只在64位下面才有效.....

};


//#define TEST(fmt,arg...) do{\
//    printf("function:[%s]"fmt,__FUNCTION__,##arg);\
//}while(0)


int is_alpha(const char c)
{
    if((const unsigned char)c >= 'A' &&  (const unsigned char)c <= 'Z'
        || (const unsigned char)c >= 'a' && (const unsigned char)c <= 'z')
        return 1;
    return 0;
}


//去掉字符串中的所有空格,返回字符串的长度
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



int main(int argc, char* argv[]) {


    //动态分配内存

    int *a_ptr = new int[10](); //分配10个空间，同时赋初值为0

    for(int i = 0 ;i < 10; i++){
        cout << a_ptr[i] << " ";
    }

    cout << endl;



    //字符串截取
    string test_str_se = "东京$美食";

    string::size_type pos_se =  test_str_se.find("$");

    cout << "pos :"  << pos_se <<endl;
    cout << "first: " << test_str_se.substr(0,pos_se) << "second:" << test_str_se.substr(pos_se+1) <<endl;




    string trim_str = "王伟 nihao ! ";
    cout << "before trim_all:" <<trim_str <<endl;
    int len = trim_all(trim_str);
    cout << "after trim_all:" <<trim_str << "len:"<< len <<endl;
    //test stl

    stl_use stlUse;
    stlUse.vector_use();

    //
    printf("test percernt:%% \n");
    string test2 = "wangwei:9";
    int pos_tag = test2.find(":");
    string sep1 = test2.substr(0,pos_tag);
    string sep2 = test2.substr(pos_tag+1);
    int credit;
    sscanf(sep2.c_str(),"%d",&credit);
    cout <<"pos: " << pos_tag << " sep1: " <<sep1 << " sep2: " <<credit <<endl;

    char buff[10];

    const char *ptr=test2.c_str();
    int index2 = 0;
    while((*ptr) != NULL){
        buff[index2] = *ptr;
        ptr++;
        index2++;
    }

    buff[index2] = '\0'; //buff已经溢出了，再拷贝到buff2中

    cout <<"test buff overflow:" << buff <<endl;
    char buff2[10];

    memset(buff2,0,10);

    strncpy(buff2,buff,10);

    cout <<"test overflow:" << buff2 <<endl;

    //stable_sort使用

    cout << "algorithm use: sort and stable_sort" <<endl;
    algorithm_use();


    //特定类型数据的最大，最小值
    std::cout << "the max int:"  << std::numeric_limits<float>::max() <<std::endl;
    std::cout << "the max uint:"  << std::numeric_limits<unsigned int>::max() <<std::endl;

    //TEST("this is a test name:%s,num:%d\n","wangwei",4);
    int MAMA(x,y);

    string test = "nih王伟";

    const char *ch = test.c_str();
    while(*ch){
        if(is_alpha(*ch)){
            cout << "alpha:" << *ch << std::endl;
        }else{

            cout << "not alpha:"  << *ch <<std::endl;
        }
        ch++;
    }



    cout<<endl;
    //CustomType<unsigned int,unsigned long long> Test;

    std::cout << "bytes:" << sizeof(CustomType<unsigned int,unsigned long long>) <<std::endl;
    std::cout << "bytes2:" << sizeof(CustomType<unsigned int,unsigned long long>::RAW) <<std::endl;
    std::cout << "bytes3:" << sizeof(CustomType<unsigned int,unsigned long long>::ATOMIC) <<std::endl;

    //CustomType<string,int> test;
    //test.RAW = "wangwei";
    //std::cout <<"test.Raw:" <<test.RAW<<std::endl;

    CustomType<string,int>::RAW test_str2;
    test_str2="weiwang";

    std::cout <<"test_str2.Raw:" <<test_str2<<std::endl;




    static const int MAX_HASH_NUM = (1ULL<<31) -1;

    std::cout << "the hash num:" << MAX_HASH_NUM <<std::endl;

    string_using_test();

	string query = "北京市海淀区";
	string sub = "市qu";
	string sub2 = "";
	string sub3 = "";

	string sub_tmp;
	string::size_type pos = query.find(sub);
	string::size_type pos2 = query.find(sub2);

	if (pos != string::npos){
		//query.erase(pos,sub.size());
		query = query.substr(0,pos);
	}




	cout << "the final query: " << query <<endl;
	cout << "the final substr: " << sub_tmp <<endl;

	cout << "pos res: " << pos <<" : " <<pos2 << " : "<<string::npos <<endl;


	//锟芥本锟脚比较达拷小锟斤拷 9.8.0
	const char *sv = "9.8.1";
	if (strcmp(sv,"9.8.0") >= 0){
		std::cout << "version:" << sv <<std::endl;
	}else{
		std::cout << "version2:" << sv <<std::endl;
	}

    //c锟斤拷锟斤拷锟斤拷使锟斤拷时锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷

    std::cout << time(NULL)<<std::endl;

    srand((unsigned int)time(NULL));

    int ran = rand();
    int index = ran%IP_SIZE;

    std::cout << "ran: index: " <<ran <<":"<<index <<std::endl;


    //锟斤拷维锟街凤拷锟斤拷锟斤拷锟介长锟斤拷
    char *test_str[QT_LEN]={
            "qt=s",
            "qt=nb"
    };

    int qt_num = QT_LEN;

    std::cout << "test_str len: " <<qt_num <<std::endl;




    //锟斤拷锟斤拷锟斤拷C锟斤拷锟皆结构锟斤拷母锟街�

    test_struct cv[]={
            {2,NULL},
            {3,NULL}
    };//使锟矫达拷锟斤拷锟脚革拷锟斤拷值

    std::cout << cv[0].a << std::endl;
    std::cout << cv[1].a << std::endl;


    //锟斤拷锟斤拷

    std::string qt = "\"qt\":\"s\"";
    const char *bound = "(123,323.2211111;2121,33.33)";

    std::stringstream ss;
    ss<<"\""<<"b"<<"\""<<":"<<"\""<<bound<<"\"";

    std::string query2;
    ss>>query2;

    cout <<"query res: " <<query2 <<std::endl;


    float x1,x2,y1,y2;

    sscanf(bound,"(%f,%f;%f,%f)",&x1,&y1,&x2,&y2);

    char buf[256];
    buf[0] = '\0';

    double xx = (x1 + x2)/2;
    double yy = (y1 + y2)/2;

    snprintf(buf,256,"(%.2f,%.2f;%.2f,%.2f)",xx,yy,xx,yy);

    printf("res: %f , %f ,%f ,%f  bound:%s \n",x1,y1,x2,y2,buf);


    //cpp read write file demo

    cpp_r_w_demo();

    //test macro
    macro_study();

    //c read_write_demo
    read_write_demo();

    cout << "!!!Hello World!!!" << endl;
    cout << "args num :" << argc << endl;
    for (int i = 0; i < argc; i++) {
        cout << "args:" << i << " value:" << argv[i] << endl;
    }
    cout << "finished!" << endl;
    char *p = argv[argc-1];
    cout << "argv:" << *p <<endl;

    util::CmdOption opt;

    opt.init(argc,argv,"d:c:h");

    if (opt.has_option("d")){
        cout << "d option exist" <<endl;
        cout <<"d option is: " <<opt["d"] <<endl;

    }else{
        cout << "d option not exist" <<endl;
    }

    if (opt.has_option("f")){
        cout << "f option exist" <<endl;
        cout <<"f option is: " <<opt["f"] <<endl;

    }else{
        cout << "f option not exist" <<endl;
    }

    printf("program is over!\n");
    return 0;
}

