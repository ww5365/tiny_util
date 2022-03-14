/*
 * 3.cpp
 *
 *  Created on: 2016年3月1日
 *      Author: wangwei69
 */

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include <cstddef>

using namespace std;

void test_3(){

    /*
     * stl库string 的使用
     * 头文件：<string>
     */

    ////字符串初始化
    string s1; //初始化为空字符串
    string s2 = "wangwei"; //拷贝初始化,使用等号
    string s3 (s2); //直接初始化
    string s4 (10,'e'); //直接初始化，10个c，构成字符串
    char *str = "wangweihao";
    string s5(str,1,3); //直接初始化，限定从某个位置开始 和 长度
    cout << "s5:" <<s5 <<endl;
    cout << "input string: "<<endl;

    //////string 类型运算和操作
    //c_string 和 string转换
    char str1[] = "wangwei nihao";
    s1 = str1;  //c_string 直接赋给string
    char cpy_str[20];
    const char *str2 = s1.c_str(); //以'\0' 结尾
    const char *str3 = s1.data();  //没有'\0' 结尾
    s1.copy(cpy_str,3,0);  //结果：wan 从索引0开始，长度为3的字符串拷贝给cpy_str
    cout << "s1: " <<s1 <<endl;
    cout << "str2: " <<cpy_str <<endl;

    //元素存取
    cout<<"s1[2] " <<s1[2] <<endl;
    cout<<"s1.at " <<s1.at(2) <<endl;  //有越界检查

    //字符串的比较

    const char *str4 = "wangwei nihao";

    if(s1 == str4){  //可以比较string和c_string 内容是否相等
        cout << "equal two string content" <<endl;
    }else{
        cout << "not equal two string content" <<endl;
    }

    if(s1.compare(str4) == 0 ){  //等价于上面的== 比较
        cout << "equal two string content2" <<endl;
    }else{
        cout << "not equal two string content2" <<endl;
    }

    if(s1.compare(0,4,s2,0,4) == 0){  //s1:"wangwei nihao" s2:"wangwei"  前4个字符进行比较
        cout << "equal two string content ,just for 4 char" << endl;
    }

    //字符串查找
    string::size_type ind = s1.find("nn"); //返回类型：string::size_type; 查找不到，返回npos;
    if (ind != string::npos){
        cout << "find !" <<endl;
    }else{
        cout << "not find !" <<endl;
    }
    cout << "size_type value: " <<ind <<"  npos: " << string::npos<<endl; //如果找不到，npos是一个比较大的数

    s1.empty();    //字符串判空
    s1 = s2 + s4;  //字符串连接
    string::size_type len = s1.size(); //字符串的字节长度,注意使用string::size_type 类型
    len = s1.length();// length是因为沿用C语言的习惯而保留下来的, 和 size没有任何区别

    cout <<"s1 and s1.length : " <<s1 << " : "<<s1.length()<<endl;

    //范围for 语句
    cout <<"s4: " << s4 << endl;
    for (auto &ch :s4){
        ch = toupper(ch);  //如果去掉引用符号？因为c引用s4中每个元素，所以s4的值，都变为大写
        cout << ch <<" ";
    }
    cout <<endl;
    cout <<"s4_2: " <<s4 <<endl;

    //string和int转换,stringstream

    //int to str : stringstream 方式  另外：to_string(val) -> string
    int aa = 30;
    stringstream ss1;  //串流输入和输出
    ss1<<aa;
    string int2str_str1 = ss1.str();//方式1
    string int2str_str2;
    ss1>> int2str_str2;  //这种方式和方式1区别:下次再次使用ss1时，clear函数生效；否则，方式1，下次使用ss1，还有原来的数据，即使clear了；
    cout<<"int2str_str1: " <<int2str_str1<<endl; // 30
    cout<<"int2str_str1: " <<int2str_str1<<endl; // 30

    //str to int  另外方式: std::stoi(string, &pos, 进制) std::stoi/stol/stoll等等函数
    string str2int_str ="122";
    ss1.flush();
    ss1.clear();
    ss1<<str2int_str;
    int res = 0 ;
    ss1>>res;
    cout<<"str2int_res: "<< res <<endl; // 122

    //getline 从标准输入，读取一行字符串数据,且可以有空格
    //它是在std名字空间的全局函数，因为这个getline函数的参数使用了string字符串，所以声明在了<string>头文件中了

    cout<<"输入一行字符，大于10个，遇到结束符结束:"<<endl;
    /*
    while(getline(std::cin,s1)){//非法或文件结束符 终止
        if (s1.size() >10)
            cout << s1 <<endl;
    }
    */

    /////////////////////////////////////////////////////////////////////////////////////////////////////

    /*
     * stl库vector的使用
     * 头文件：include <vector>
     * using std::vector
     */

    //vector的定义和初始化
    vector<string> svec1; //定义一个空vector来备后续使用
    vector<string> svec2(10);  //定义并初始化含有10个元素的空字符串的vector;这种方式元素需要有默认构造函数
    vector<string> svec3(10,"hi"); //定义并初始化含有10个元素的hi的vector
    vector<string> svec4 = {"hello","world"}; //列表初始化  C++11 支持
    vector<string> svec5 {"10","hi"};  //列表初始化,等价于svec4

    //添加元素，及其他常用操作
    for(int i = 0;i < 10;i++){
        //整形转为字符串
       std::stringstream ss;
       ss<<i;
       string tmp1;
       //tmp1 = ss.str();//区别，下次用ss时，还有本次的结果
       ss>>tmp1;
       svec1.push_back(tmp1);
       //添加元素，高效增长，性能保证？
       //蕴含编程假定：不能用返回for，添加元素
    }

    bool svec1_res = svec1.empty(); //判空
    if (svec1 == svec2){ //比较运算, 元素个数和元素数值，都相同
        cout<< "equal" <<endl;
    }
    vector<string>::size_type c = svec1.size(); //元素个数
    cout<< "vec1 size:"<< c <<endl;

    if(c >0){
        cout << "vec1[0]:" <<svec1[0] <<endl;  //位置索引，不要溢出
    }

    //遍历元素 ：迭代器
       //和下标区别：标准库容器都支持迭代器，只有部分支持下标
       //不能遍历，还在push_back对象，会造成迭代器失效

    //迭代器的使用
    vector<string>::iterator it1 = svec1.begin();
    vector<string>::iterator it2 = svec1.end(); //尾后迭代器，无实际含义，但标识处理完所有元素
    vector<string>::const_iterator it3 = svec1.begin();//只能读，不能写元素

    auto it4 = svec1.begin();  //c++ 11  和it1相同
    //auto it5 = svec1.cbegin(); // c++ 11 ,和it3 相同

    for ( ;it1 != it2;++it1){
        if (!(*it1).empty()){
            cout << *it1 << endl; // * 解引用
        }

        if (!(it1->empty())){ //箭头运算符，元素对象中有成员可以访问
            cout << *it1 <<endl;
        }
    }

    //迭代器的运算，it+n ,it+=n ,it-=n,it1-it2


    string search_for_str = "2";
    it1 = svec1.begin();
    it2 = svec1.end();
    vector<string>::iterator mid = it1 + (it2-it1)/2;//相减，表示迭代器中间差的元算数
    //迭代器运算实例: 实现二分查找
    while (mid != it2){  //就一个条件，mid不等于end
        if(*mid == search_for_str){
            cout <<"find just i want : " << *mid <<endl;
            break;
        }else if(*mid > search_for_str){
            it2 = mid;
        }else{
            it1 = mid + 1;
        }
        mid = it1 + (it2-it1)/2;
    }

    //数组

    //定义时，确定类型和元素个数
    const int SIZE = 10;
    string str_arr[SIZE];
    char ch1[] = "nihao"; //特殊，有6个字节,自动多个'\0'
    char ch2[] ={'n','i','h','a','o'}; //有5个字节 ，列表初始化

    int *ptr_arr[10];// 存放整形指针的数组，从右到左，大小10，数组名ptr，存放的类型int *

    int *(*pArr)[10]; //定义指向数组的指针，从内而外，pArr是个指针，指向包含10个整型指针元素的指针

    int *(&pArr2)[10] = ptr_arr; //定义数组的引用，从内而外，pArr2是个引用，引用的是含有10个整形指针的数组

    pArr = &ptr_arr;  //pArr 一般是二维数据在使用

    cout << "finished!" <<endl;


    //数组的运算，比较特殊的地方

    int array [] = {2,3,5,8,1,9};

    // c++ 11
    //int *pbegin = begin(array);  //数值首指针
    //int *pend = end(array);  //数组尾指针，最后一个元素的下一位置

    //数组和标准库string ,vector， []运算有不同的地方; 索引值可以为负值；

    int *ptr_test = array + 4;

    cout << "array access test[0]: " << ptr_test[0] << endl;
    cout << "array access test[-1]: " << ptr_test[-1] << endl;  //索引值为负

    //c风格的字符串：涉及的运算，strlen,strcmp,strcat,等，建议使用string库

    //string与C风格的转换

    const char *const_str = "wangwei nihao";
    string str1_test = const_str; //string 可以用以空字符串结尾的字符数组，来赋值
    const char *str_2_cstr = str1_test.c_str(); //使用c_str函数









}
