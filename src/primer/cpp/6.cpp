/*
 * 6.cpp
 *
 *  Created on: 2016��8��20��
 *      Author: wangwei69
 *
 *  ͨ�����ѧ���ԣ�c++
 *
 *  �൱�ڷ�������һ��˼·��ȥѧϰ������ԡ�
 *
 *  ���������£�������������
 *
 *  chapter 6: ����
 *  �������磺
 *  ��������(��ֵ��ʵ�Ρ��β�)->
 *
 *
 */

#include "all.hpp"
#include <initializer_list>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>

#include <stdarg.h>

void error_msg(int err_code, std::initializer_list<std::string> para);

void sum_int(const int len,...);
void print_msg(char *buf,const char *format,...);

int (*fun_ret_2(int arr[][4],int))[4];//����ָ����4���е�����ָ��
auto fun3(int len) ->int (*)[10]; //c++11 β�õķ�����������


constexpr int fun_test(){return 42;} //���س������ʽ������׶ξ���ȷ�����ʽ�ӵ�ֵ��
int &get(int *arr, int idx);

int calc(char *,char*){return 1;}  // int calc(char* const,char* const );  �ظ�����
int calc(const char* ,const char* ){return 2;}


//��������

bool str_cmp_test(const std::string &s1, const std::string &s2){
    std::cout << "test function pointer use!" << std::endl;
    return false;
}

//���庯�����ͱ���
typedef bool str_cmp(const std::string &, const std::string &); //������str_cmpΪ���ຯ�������ͱ���
using str_cmp2 = bool (const std::string &, const std::string&);//ʹ��using�����˺������͵ı�����Ч��ͬ�ϣ�����Ķ����������

//���庯������ָ��
typedef bool (*str_cmp_ptr) (const std::string &s1, const std::string &s2);//str_cmp_ptr��������ָ��
str_cmp2 *str_cmp_ptr2; //ʹ�ú������ͱ����������庯������ָ��

//��������ָ����Ϊ�β���ʹ��

void my_sort(std::vector<int>&,  bool (*str_cmp_ptr)(std::string &, std::string &)); //��������ָ����Ϊ�βΣ��ܷ�򻯶��壿

void my_sort(std::vector<int>& vec,  str_cmp_ptr fun){ //�򻯶��壬ֱ��ʹ�ú�������ָ��

    std::cout << "test function pointer as parameters!" << std::endl;

    std::string s1,s2;
    fun(s1, s2);
}

//����ָ����Ϊ��������ֵ��ʹ��
auto get_fun_ptr() -> bool (*)(const std::string &, const std::string &){
    str_cmp2 *fun = str_cmp_test;
    return fun;
}

decltype(str_cmp_test)* get_fun_ptr2(){
    //�ڶ��ֶ��巽ʽ��ʹ��decltype
    str_cmp_ptr fun = str_cmp_test;
    return fun;
}

void get_fun_ptr_use(){

    std::string s1,s2;
    std::cout << "test function pointer as return value!" << std::endl;
    //����ָ����Ϊ����ֵ����ʵ�ֵ��ô˺���
    get_fun_ptr()(s1, s2);

}



void test_6(){


    std::cout << "-------------test chapter6----------------" << std::endl;

    //����ָ��

    std::vector<int> test_vec(2, 0);
    test_vec.reserve(10);
    my_sort(test_vec, str_cmp_test);
    get_fun_ptr_use();


    /*
     * ��������
     */

    //����ʹ�ó�������
    //������Ϊ�β�

    ///�ɱ�����ĺ���
    ///ʡ�ԺŲ���:�ɱ����

     //error_msg(0, {"this", "error", "msg1"}); //mac eclipse��û�����ӳɹ�
    //error_msg(1, {"this", "error", "msg1", "msg2"});

    sum_int(4,344,4,5,6);

    char buf[256];
    buf[0]='\0';

    print_msg(buf,"this is %s test and result is %d","wangwei",1);

    printf("the buf content: %s",buf);

    /*
     * �����ķ���ֵ
     */

    //��������ָ��,��Զ�ά��������

    int array_test[][4] ={
            {1,2,3,4},
            {4,3,2,1},
            {5,6,7,8}
    };

    int (*ptr) [4] ;
    int size_test = sizeof(array_test)/sizeof(array_test[0]);
    ptr = fun_ret_2(array_test,size_test);

    int *ptr2 = array_test[1];

    for(auto i =0 ;i<4;i++){
        std::cout << std::endl
        <<"two dimension:" << (ptr2)[i] <<" ";
    }

    std::cout << std::endl;

    int (*ptr3)[10];
    ptr3 = fun3(1);

    std::cout << "ptr3 content: " << std::endl;
    for(auto i = 0;i< 10 ; i++){
        std::cout << i << " " << *ptr3[i] << std::endl;
    }

    std::cout <<std::endl;

    int *arr = *ptr3;
    //������ֵ
    get(arr, 1) = 11;

    std::cout << "after change ptr3 content: " << std::endl;
    for(auto i = 0; i< 10; i++){
        std::cout << i << " " << arr[i] << std::endl;
    }



    //���������������;����������  ����


    //constexpr ����   ��;��    ���磺 constexpr int fun_test(){return 42;} �������ǳ�������������

    int array[fun_test()]; //constexpr: ������������ʱ��constexpr���������滻�ɽ��ֵ

    const int val2 = 10;

    int array2[val2];

    //�����ĵ��Լ����� ˼�룺����ʱʹ�ã����ߺ�Ҫ���ε����Դ���

    ///assert Ԥ����꣬ͷ�ļ�cassert;���ԣ���ʲô������ʹ�ã�
    // ���Ե�ʱ����Ϊʹ��NDEBUG����ʹ��ʧЧ��ͬʱ���϶������Ƿ���������������������������ˡ�
    assert(1 < 3); //����Ϊ�棬����ִ������Ĵ��룻����Ϊ��0�������Ϣ����ֹ����

    ///NDEBUG :
    ////1. gcc -D NDEBUG main.c  : �ӱ���������NDEBUG����ִ�е��Գ����൱����main��ʼ������ #define NDEBUG��ͬʱassertҲ������Ч��
    ////2. #ifndef NDEBUG ...#endif  : û�ж��岻���е��Ա�ʶ��Ҳ���ǽ��е��ԣ�ִ�е��Դ���

    #ifndef NDEBUG

    std::cout <<"function:" << __func__  //������Ϊÿ����������ģ���ź�������
         <<" at file:"  << __FILE__   //Ԥ���������壬�����õ�����4����Ϣ
         <<" at line:"  << __LINE__
         <<" on date:"  << __DATE__
         <<" at time:"  << __TIME__
         <<std::endl;

    #endif




    std::cout <<"this is programmer end"<<std::endl;


}

/*
 *  ����
 */

//������Ϊ�β�

///�������������ȼۣ�
void print1(const int *); //�βζ���Ϊconst int* ������
void print2(const int[]);  //�β�������һ�����飬��ͼ����
void print3(const int[10]); // �����βδ�С10�ģ���ֹԽ�磬��ι���ָ���βΣ�

///��������ָ�볤�ȵļ���
void print(const int[],const int size); //���ã�ֱ��ָ������
void print(const int [],const int *beg,const int *end);//���飬��ʼԪ��ָ�룬��βԪ�غ�һ��ָ��

///����������Ϊ�βΣ� �ܴﵽ�ı������ڲ�Ԫ�ص�Ŀ�ģ���ζ���,�����Ǹ��ǣ�

//void print(int &arr[10]);  //arr��һ����10���������õ�����
void print(int (&arr)[10]);//yes,not lose parathesis

///��ά������Ϊ��������άʵ����C++û��ʵ�֣���ʵ�����������

void print(int arr[][10]);
void print(int (*arr)[10]);//arr��ָ�룬ָ����10��Ԫ�ص�����

//�ɱ����

///initializer_list�β�

void error_msg(int &err_code, std::initializer_list<std::string> para){

    //initializer_list ��ģ����
    for(auto it = para.begin(); it != para.end(); it++){
        std::cout << "para: " << *it << std::endl;
    }

    //�����֧�ֵ�����������Ҳ�����÷�Χfor
    for(auto &e: para){
        std::cout << "para2: " << e << std::endl;
    }
    err_code = 0;
}

///ʡ�Ժ��βΣ�����ͨ������c��c++ͨ�����ͣ������ͨ������ȷ��������

/// <stdarg.h> va_list,va_start(),va_arg(),va_end()
/// ������һϵ�еĺ궨�壻���ݽ������пռ䣬�����ķֲ��������������������ĵ�ַ��
/// ��������������ջ�����Ըߵ�ַ->�͵�ַ����n��->��1��������

void sum_int(const int len,...){ //�������Ͳ����ĺ�,���ȿɱ�

    va_list para;
    va_start(para,len); //len�����һ���̶���������; para ָ���һ�ɱ��������ʼλ��
    int para_value = va_arg(para,int);  //��ȡ��һ��int���Ͳ�����ֵ�� ע��va_arg�ĵڶ����������������ͣ�int

    std::cout << "param:" << 1 << ": "<<para_value <<std::endl;

    for (int i = 1 ;i < len;i++){
        para_value = va_arg(para,int);
        std::cout << "param:" << i+1 << ": "<<para_value <<std::endl;
    }
    va_end(para);
}

///vsnprintf��ӡva_list�����������ܴ�ӡ���ɱ����,�������buf;

void print_msg(char *buf,const char *format,...){
    va_list va_par;
    va_start(va_par,format);
    vsnprintf(buf,256,format,va_par);  //ר�Ÿ�ʽ����ӡva_list����
    va_end(va_par);
}


/*
 * �����ķ���ֵ
 */

//��ֵ����

///��α����أ�������ֵ���ص����õ�

///���ܷ��ؾֲ�������ָ�������

const std::string &fun_p(){
    std::string ret;
    if (!ret.empty())
        return ret;  // ���󣺾ֲ�����
    else
        return "empty"; //���󣺾ֲ�����
}

///���طǳ������ã���Ϊ��ֵ�� ������

char &get_first_char(std::string str){
    if(!str.empty())
        return str[0];
}
void test(){
    std::string tt = "hangwei";
    get_first_char(tt) = 'w'; //��һ���ַ���Ϊw
    std::cout << tt <<std::endl;
}

int &get(int *arr, int idx){
    return arr[idx];
}


//��������ֵ����������ָ��

typedef int arr1[10];  //arr1��int[10]���ͱ���
using arr2 = int [10]; //ͬ�ϣ�c++11

arr1 *fun1(int len);//��������ֵ��ָ��int[10]��һ��ָ��

int (*fun2(int len))[10]; //ͬ�ϣ������Ķ��巽ʽ

//int *fun2_1(int len)[10]; //����ֵ��һ������10��ָ��Ԫ�ص�����

auto fun3(int len) ->int (*)[10]{
    //�����ά�����ڴ�ռ�
    int **ptr2 = new int*[3];
    for(int i = 0; i < 3; i++){
        ptr2[i] = new int[10];
    }
    //ǿ������ת���������Ļ�������Ҫ����
    int (*ptr)[10] = reinterpret_cast<int(*)[10]>(ptr2[1]);

    for (int i = 0; i< 10;i++){
        *ptr[i] = i + 1;
    }
    return ptr;
}


int (*fun_ret_2(int arr[][4] ,int size))[4]{
    //���ض�ά�����еڶ��е���ָ��
    if(size>=2){
        int (*ptr)[4] ;
        ptr = &arr[1];
        return ptr;
    }
    return 0;
}


//���������������;����������

///Ĭ��ʵ�Σ��ӵ�һ��Ĭ�Ͽ�ʼ���������������Ĭ��
std::string screen(size_t h = 24, size_t w = 80, char back_grd = 'a'){return NULL;}

///�������� inline  ע�������ͺ궨�������  �׶Σ����룬Ԥ����  ������飺�У���  ��

inline int fun_test(int a, int b){
    return a > b ? a : b; //�����������������ڵ��õ�ֱ��չ���ñ��ʽ
}














