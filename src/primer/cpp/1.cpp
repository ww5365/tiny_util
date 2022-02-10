/*
 * 1.cpp
 *
 *  Created on: 2016年2月24日
 *      Author: wangwei69
 */

#include <iostream>
#include <limits>
#include <cwchar>
#include <string>
#include "1.h"
using namespace std;


char *get_str_1(){
    char str[] = "hello world"; //stack
    return str;
}

char *get_str_2(){
    char *str = "hello world"; //txt
    return str;
}

char *get_str_3(){
    char tmp[] = "hello world";
    char *str = new char[12];
    memcpy(str,tmp,12);
    return str;               //heap
}


/*
 * @brief
 *
 * 1、const
 * 2、constexpr:c++11
 * 3、auto:c++11
 * 4、decltype():c++11
 *
 */

//const 变量的作用范围？ 默认情况下文件内有效；定义时使用extern，其它文件中可以通用
extern int test_const =  random();

void primer_2_4_5(){

    //void指针：任意类型的指针赋值，再强制转换为想要指针类型
    void *ptr = nullptr;
    int a = 9;
    ptr = &a;
    cout <<"the result: " << (*(int*)ptr) <<endl;

    //const引用，初始化
    const int &aa = 10;  //可以使用字面值常量给引用赋初值，但缺少const是不行的
    const int &aa2 = 2 * test_const; //允许const常量引用，指向表达式；正常引用不可以；
    /*
     * 编译器实际过程：
     * int tmp = 2*test_const; //生成一个临时变量
     * const int &aa2 = tmp;
     */
    cout <<"aa value: " << aa <<endl;

    //指向常量的常量指针
    const int *const ptr_const = &a; //ptr_const不能改变；*ptr_const中的值也不能改变；

    //constexpr c++ 11 :常量表达式：编译阶段就确定了值；好处？编译阶段检查？更高的效率？
    //constexpr 用来申明一个变量是常量且必须用常量表达式初始化

    constexpr int  i = 32;  //必须用常量表示式赋值；
    const int ii = random(); // ii不是常量表达式

    //constexpr int iii = random();//不正确赋值；iii不是常量表示式；
    cout << "constexpr: " << i <<endl;

    constexpr char *str ="wangwei"; //str 是常量指针;*str中内容可变；constexpr直接修饰str变量；
    const char *str2 = "wangwei2";  //str2 是指向字符串常量的指针, 不是常量指针；const修饰数据类型
    cout <<"str:" << str <<endl;

    //c++ 11 using :别名的定义
    typedef char *string_c1;
    using string_c2 = char *;  //C++ 11 的新特性，等价于上面的写法
    const string_c1 test = "wangwei test ";   //test 是常量指针；基本类型是：char* 且const修饰的就是基本类型变量，所以变量test是常量。
    cout <<"c2: " <<test <<endl;

    // c++11 auto :不知道某个表达式的类型，想使用其返回值，可以使用auto定义类型，编译器自动计算变量类型；auto变量必须要初值；
    auto tt = test;  //tt 是const char * 类型，底层const保留；如果是上层const则不保留
    const auto t3 = 42 ;  //t3 是整形常量
    const auto &t4 = t3; //t4 是整型常量引用

    //c++ 11 decltype :想使用某个变量的类型，但不想使用这个变量，赋初值；使用decltype将变量的类型提取出来
    decltype(test) test2 = "szdd"; //test2 是const char*类型
    cout <<"test2: " <<test2 <<endl;

}



/*
 *@brief 使用说明
 *
 *1、引用的使用说明:
 *   必须初始化，且只能用变量初始化
 *   类型保持一直
 *
 *
 */

void primer_2_3_1(){

//    //引用
//    int &iref;  //错误，必须要初始化
    int i = 10;
//    int &iref1 = i; //ok
//    float &iref2 = i; //错误，类型不一致
//    int &iref3 = 10; //不能使用字面值

    int *ptr = &i;
    int *&r_ptr = ptr; //定义并初始化了指向指针的引用

    const int &iref4 = 10; //使用const限定之后，可以使用字面值初始化引用

}


/*
 * @brief
 * 1.变量初始化的几种形式
 * 2.变量命名
 */

void primer_2_2_1(){

    //变量初始化形式
    int t1 = 10;  //常见方式
    int t2 = (10);
    int t3{10}; //c++11中得到全面应用；与下面的括号相比，丢失精度情况下，错误不执行;初始化列表
    int t4(10); //类对象定义初始化，经常能看到；

    printf("initialization forms:%d %d %d %d",t1, t2, t3, t4);

    //命名，不建议情况
    int _Test = 10; //_+大写
    int __test = 10; //两个_开头

    printf("initialization forms:%d %d",_Test, __test);

}



/*
 * @brief
 * 1、字面值常量的表示
 * 2、不同进制表示，打印
 * 3、转移序列
 */

void primer_2_1_3(){

    //进制，整型和浮点字面值常量
    int l_int = 0x17;//16进制,标识:0x
    int o_int = 010; //8进制,标识:0 也就是说，不能随便以0开头表示一个数据，会被看做8进制的。
    double l_double = 12.30E4F; //双精度浮点，E标识指数，F标识是浮点类型
    long double l_double2 = 12.223e9F;

    printf("int literal : %o,%d,%x,%lf\n", l_int,l_int,l_int,l_double);
    printf("int literal : %o,%d,%x,%.5Lf\n", o_int,o_int,o_int,l_double2);
    //转义序列
    bool literal_bool = true;
    char liter_char1 = 'M';
    char liter_char2 = '\115';  //泛转义，八进制最多3个数字标识一个字符；
    char liter_char3 = '\x4d';   //十六进制
    char *ptr = NULL;  //空指针赋初值使用：0 ，NULL，来初始化为空指针；
    char *ptr2 = nullptr;   // c++ 11 中引入了：nullptr 来初始化空指针，新标准下推荐使用；
    const char *liter_str = u8"hello world";   //指定了字符串的字面常量值编码格式，是utf8

    cout << "result:" << liter_char1 << liter_char2 << liter_char3  << liter_str <<endl;

    /*
     * 技术topic：
     *
     * 1、编译c++ 11 标准的程序？ -std=c++0x
     *    g++ -std=c++0x -I "D:\workspace\primer_5\inc" -O0 -g3 -Wall -c -fmessage-length=0
     *
     * 2、字面值常量，存储在进程运行空间中哪个部分？
     *    .txt,.data,.bss,heap,stack
     *    存放在代码段(.txt),比如"hello world";但liter_str这个变量本身放在stack段；
     *    liter_str[1] = 'a';  //会报段错误
     */

    //扩展进程运行空间的理解

    char *str1 = get_str_1();// 出错，Stack段中的数据在函数退出时就销毁了
    char *str2 = get_str_2();//正确，指向Text段中的字符直接量，退出程序后才会回收
    char *str3 = get_str_3();//正确，指向Heap段中的数据，还没free()/delete

    cout <<"str3:" <<str3 <<endl;
    if (str3!=NULL){
        delete str3;
    }
}

/*
 * @brief signed、unsigned 区别
 */
void primer_2_1_2(){


    //1、误用unsigned,导致死循环case。

    /*
    cout << "endless loop case, illustration" << endl;
    for (unsigned int i = 3; i >= 0; i--){
        cout << "integer i: " << i << endl;
        //为啥会死？
    }
    */


    //2、编译器隐式数据类型转换：signed -> unsigned  导致数据溢出

    unsigned int i = -6;
    cout << "i + 5 = " << i + 5 << endl; //会得到-1的结果吗？

    cout << "the max unsigned int: " << INT_MAX << endl;

}

/*
 * @biref c++11内置数据类型,占用字节和表示范围
 *
 * numeric_limits<TYTPE> c++11模板类表示基本数据类型范围:<limits>
 *
 */

void primer_2_1_1(){

    //boolean
    cout << "bool bytes: " << sizeof(bool) << endl;

    //字符类型
    char ch_1 = 'A';
    wchar_t wch_1 = L'w';//宽字符类型：L
    char16_t ch16_1 = u'w'; //支持unicode扩展编码，u
    char32_t ch32_1 = U'w'; //支持unicode扩展编码，U

    std::cout <<"char bytes:"  << sizeof(ch_1) << " rang:" << static_cast<int>(numeric_limits<char>::min()) << "~" << static_cast<int>(numeric_limits<char>::max()) << endl;
    std::cout << "wchar_t bytes: " << sizeof(wch_1) << " rang:" << numeric_limits<wchar_t>::min() << "~" << numeric_limits<wchar_t>::max() << endl;
    std::cout << "char16_t bytes: " << sizeof(ch16_1) << " rang:" << numeric_limits<char16_t>::min() << "~" << numeric_limits<char16_t>::max() << endl;
    std::cout << "char32_t bytes: " << sizeof(ch32_1) << " rang:" << numeric_limits<char32_t>::min() << "~" << numeric_limits<char32_t>::max() << endl;

    //unsigned short、short

    cout << "unsigned int bytes: " << sizeof(unsigned int) << " rang:"<< numeric_limits<unsigned int>::min() << "~" << numeric_limits<unsigned int>::max() << endl;
    cout << "int bytes: " << sizeof(int) << " rang:"<< numeric_limits<int>::min() << "~" << numeric_limits<int>::max() << endl;


    //unsigned int、int
    cout << "unsigned int bytes: " << sizeof(unsigned int) << " rang:"<< numeric_limits<unsigned int>::min() << "~" << numeric_limits<unsigned int>::max() << endl;
    cout << "int bytes: " << sizeof(int) << " rang:"<< numeric_limits<int>::min() << "~" << numeric_limits<int>::max() << endl;

    //long
    cout << "unsigned long bytes: " << sizeof(unsigned long) << " rang:"<< numeric_limits<unsigned long>::min() << "~" << numeric_limits<unsigned long>::max() << endl;
    cout << "long bytes: " << sizeof(long) << " rang:"<< numeric_limits<long>::min() << "~" << numeric_limits<long>::max() << endl;

    //long long
    cout << "unsigned long bytes: " << sizeof(unsigned long long) << " rang:"<< numeric_limits<unsigned long long>::min() << "~" << numeric_limits<unsigned long long>::max() << endl;
    cout << "long long bytes: " << sizeof(long long) << " rang:"<< numeric_limits<long long >::min() << "~" << numeric_limits<long long>::max() << endl;

    //float,double,long double
    cout << "float bytes: " << sizeof(float) << " rang:"<< numeric_limits<float>::min() << "~" << numeric_limits<float>::max() << " epsilon: " << numeric_limits<float>::epsilon()<< " digits: " <<numeric_limits<float>::digits << endl;
    cout << "double bytes: " << sizeof(double) << " rang:"<< numeric_limits<double>::min() << "~" << numeric_limits<double>::max() << " epsilon: " << numeric_limits<double>::epsilon()<< " digits: " <<numeric_limits<double>::digits << endl;
    cout << "long double bytes: " << sizeof(long double) << " rang:"<< numeric_limits<long double>::min() << "~" << numeric_limits<long double>::max() << " epsilon: " << numeric_limits<long double>::epsilon()<< " digits: " <<numeric_limits<long double>::digits << endl;


}

/*
 * 扩展：
 * 宽字符类型：wchar_t  -》  wstring
 *
 * 区别： wstring  string
 *
 * wstring : 每个元素占2个字节，循环时1个单位就是跨越两个字节
 *
 *
 */

#define tab "\t";

void primer_2_extend() {

    locale def;
    cout << def.name() << endl;
    locale current = cout.getloc();
    cout << current.name() << endl;

    float val = 1234.56;
    cout << val << endl;

    //chage to french/france
    cout.imbue(locale("chs"));
    current = cout.getloc();
    cout << current.name() << endl;
    cout << val << endl;

    //上面是说明locale的用法，下面才是本例的内容，因为其中用到了imbue函数
    cout << "*********************************" << endl;

    //为了保证本地化输出（文字/时间/货币等），chs表示中国，wcout必须使用本地化解析编码
    wcout.imbue(std::locale("chs"));

    //string 英文，正确颠倒位置，显示第二个字符正确
    string str1("ABCabc");
    string str11(str1.rbegin(), str1.rend());
    cout << "UK\ts1\t:" << str1 << "\t" << str1[1] << "\t" << str11 << endl;

    //wstring 英文，正确颠倒位置，显示第二个字符正确
    wstring str2 = L"ABCabc";
    wstring str22(str2.rbegin(), str2.rend());
    wcout << "UK\tws4\t:" << str2 << "\t" << str2[1] << "\t" << str22 << endl;

    //string 中文，颠倒后，变成乱码，第二个字符读取也错误
    string str3("你好么？");
    string str33(str3.rbegin(), str3.rend());
    cout << "CHN\ts3\t:" << str3 << "\t" << str3[1] << "\t" << str33 << endl;

    //正确的打印第二个字符的方法
    cout << "CHN\ts3\t:RIGHT\t" << str3[2] << str3[3] << endl;

    //中文，正确颠倒位置，显示第二个字符正确
    //std::wstring str4=L"你好";
    //wstring str44(str4.rbegin(),str4.rend());
    //wcout<<"CHN\tws4\t:"<<str4<<"\t"<<str4[1]<<"\t"<<str44<<endl;

    //只有char类型的string时才可以如此构造
    wstring str5(str1.begin(), str1.end());
    wstring str55(str5.rbegin(), str5.rend());
    wcout << "CHN\tws5\t:" << str5 << "\t" << str5[1] << "\t" << str55 << endl;

    //如此构造将失败!!!!
    wstring str6(str3.begin(), str3.end());
    wstring str66(str6.rbegin(), str6.rend());
    wcout << "CHN\tws6\t:" << str6 << "\t" << str6[1] << "\t" << str66 << endl;

}


