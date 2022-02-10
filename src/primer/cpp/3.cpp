/*
 * 3.cpp
 *
 *  Created on: 2016��3��1��
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
     * stl��string ��ʹ��
     * ͷ�ļ���<string>
     */

    ////�ַ�����ʼ��
    string s1; //��ʼ��Ϊ���ַ���
    string s2 = "wangwei"; //������ʼ��,ʹ�õȺ�
    string s3 (s2); //ֱ�ӳ�ʼ��
    string s4 (10,'e'); //ֱ�ӳ�ʼ����10��c�������ַ���
    char *str = "wangweihao";
    string s5(str,1,3); //ֱ�ӳ�ʼ�����޶���ĳ��λ�ÿ�ʼ �� ����
    cout << "s5:" <<s5 <<endl;
    cout << "input string: "<<endl;

    //////string ��������Ͳ���
    //c_string �� stringת��
    char str1[] = "wangwei nihao";
    s1 = str1;  //c_string ֱ�Ӹ���string
    char cpy_str[20];
    const char *str2 = s1.c_str(); //��'\0' ��β
    const char *str3 = s1.data();  //û��'\0' ��β
    s1.copy(cpy_str,3,0);  //�����wan ������0��ʼ������Ϊ3���ַ���������cpy_str
    cout << "s1: " <<s1 <<endl;
    cout << "str2: " <<cpy_str <<endl;

    //Ԫ�ش�ȡ
    cout<<"s1[2] " <<s1[2] <<endl;
    cout<<"s1.at " <<s1.at(2) <<endl;  //��Խ����

    //�ַ����ıȽ�

    const char *str4 = "wangwei nihao";

    if(s1 == str4){  //���ԱȽ�string��c_string �����Ƿ����
        cout << "equal two string content" <<endl;
    }else{
        cout << "not equal two string content" <<endl;
    }

    if(s1.compare(str4) == 0 ){  //�ȼ��������== �Ƚ�
        cout << "equal two string content2" <<endl;
    }else{
        cout << "not equal two string content2" <<endl;
    }

    if(s1.compare(0,4,s2,0,4) == 0){  //s1:"wangwei nihao" s2:"wangwei"  ǰ4���ַ����бȽ�
        cout << "equal two string content ,just for 4 char" << endl;
    }

    //�ַ�������
    string::size_type ind = s1.find("nn"); //�������ͣ�string::size_type; ���Ҳ���������npos;
    if (ind != string::npos){
        cout << "find !" <<endl;
    }else{
        cout << "not find !" <<endl;
    }
    cout << "size_type value: " <<ind <<"  npos: " << string::npos<<endl; //����Ҳ�����npos��һ���Ƚϴ����

    s1.empty();    //�ַ����п�
    s1 = s2 + s4;  //�ַ�������
    string::size_type len = s1.size(); //�ַ������ֽڳ���,ע��ʹ��string::size_type ����
    len = s1.length();// length����Ϊ����C���Ե�ϰ�߶�����������, �� sizeû���κ�����

    cout <<"s1 and s1.length : " <<s1 << " : "<<s1.length()<<endl;

    //��Χfor ���
    cout <<"s4: " << s4 << endl;
    for (auto &ch :s4){
        ch = toupper(ch);  //���ȥ�����÷��ţ���Ϊc����s4��ÿ��Ԫ�أ�����s4��ֵ������Ϊ��д
        cout << ch <<" ";
    }
    cout <<endl;
    cout <<"s4_2: " <<s4 <<endl;

    //string��intת��,stringstream

    //int to str
    int aa = 30;
    stringstream ss1;  //������������
    ss1<<aa;
    string int2str_str1 = ss1.str();//��ʽ1
    string int2str_str2;
    ss1>> int2str_str2;  //���ַ�ʽ�ͷ�ʽ1����:�´��ٴ�ʹ��ss1ʱ��clear������Ч�����򣬷�ʽ1���´�ʹ��ss1������ԭ�������ݣ���ʹclear�ˣ�
    cout<<"int2str_str1: " <<int2str_str1<<endl; // 30
    cout<<"int2str_str1: " <<int2str_str1<<endl; // 30

    //str to int
    string str2int_str ="122";
    ss1.flush();
    ss1.clear();
    ss1<<str2int_str;
    int res = 0 ;
    ss1>>res;
    cout<<"str2int_res: "<< res <<endl; // 122

    //getline �ӱ�׼���룬��ȡһ���ַ�������,�ҿ����пո�
    //������std���ֿռ��ȫ�ֺ�������Ϊ���getline�����Ĳ���ʹ����string�ַ�����������������<string>ͷ�ļ�����

    cout<<"����һ���ַ�������10������������������:"<<endl;
    /*
    while(getline(std::cin,s1)){//�Ƿ����ļ������� ��ֹ
        if (s1.size() >10)
            cout << s1 <<endl;
    }
    */

    /////////////////////////////////////////////////////////////////////////////////////////////////////

    /*
     * stl��vector��ʹ��
     * ͷ�ļ���include <vector>
     * using std::vector
     */

    //vector�Ķ���ͳ�ʼ��
    vector<string> svec1; //����һ����vector��������ʹ��
    vector<string> svec2(10);  //���岢��ʼ������10��Ԫ�صĿ��ַ�����vector;���ַ�ʽԪ����Ҫ��Ĭ�Ϲ��캯��
    vector<string> svec3(10,"hi"); //���岢��ʼ������10��Ԫ�ص�hi��vector
    vector<string> svec4 = {"hello","world"}; //�б��ʼ��  C++11 ֧��
    vector<string> svec5 {"10","hi"};  //�б��ʼ��,�ȼ���svec4

    //���Ԫ�أ����������ò���
    for(int i = 0;i < 10;i++){
        //����תΪ�ַ���
       std::stringstream ss;
       ss<<i;
       string tmp1;
       //tmp1 = ss.str();//�����´���ssʱ�����б��εĽ��
       ss>>tmp1;
       svec1.push_back(tmp1);
       //���Ԫ�أ���Ч���������ܱ�֤��
       //�̺���̼ٶ��������÷���for�����Ԫ��
    }

    bool svec1_res = svec1.empty(); //�п�
    if (svec1 == svec2){ //�Ƚ�����, Ԫ�ظ�����Ԫ����ֵ������ͬ
        cout<< "equal" <<endl;
    }
    vector<string>::size_type c = svec1.size(); //Ԫ�ظ���
    cout<< "vec1 size:"<< c <<endl;

    if(c >0){
        cout << "vec1[0]:" <<svec1[0] <<endl;  //λ����������Ҫ���
    }

    //����Ԫ�� ��������
       //���±����𣺱�׼��������֧�ֵ�������ֻ�в���֧���±�
       //���ܱ���������push_back���󣬻���ɵ�����ʧЧ

    //��������ʹ��
    vector<string>::iterator it1 = svec1.begin();
    vector<string>::iterator it2 = svec1.end(); //β�����������ʵ�ʺ��壬����ʶ����������Ԫ��
    vector<string>::const_iterator it3 = svec1.begin();//ֻ�ܶ�������дԪ��

    auto it4 = svec1.begin();  //c++ 11  ��it1��ͬ
    //auto it5 = svec1.cbegin(); // c++ 11 ,��it3 ��ͬ

    for ( ;it1 != it2;++it1){
        if (!(*it1).empty()){
            cout << *it1 << endl; // * ������
        }

        if (!(it1->empty())){ //��ͷ�������Ԫ�ض������г�Ա���Է���
            cout << *it1 <<endl;
        }
    }

    //�����������㣬it+n ,it+=n ,it-=n,it1-it2


    string search_for_str = "2";
    it1 = svec1.begin();
    it2 = svec1.end();
    vector<string>::iterator mid = it1 + (it2-it1)/2;//�������ʾ�������м���Ԫ����
    //����������ʵ��: ʵ�ֶ��ֲ���
    while (mid != it2){  //��һ��������mid������end
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

    //����

    //����ʱ��ȷ�����ͺ�Ԫ�ظ���
    const int SIZE = 10;
    string str_arr[SIZE];
    char ch1[] = "nihao"; //���⣬��6���ֽ�,�Զ����'\0'
    char ch2[] ={'n','i','h','a','o'}; //��5���ֽ� ���б��ʼ��

    int *ptr_arr[10];// �������ָ������飬���ҵ��󣬴�С10��������ptr����ŵ�����int *

    int *(*pArr)[10]; //����ָ�������ָ�룬���ڶ��⣬pArr�Ǹ�ָ�룬ָ�����10������ָ��Ԫ�ص�ָ��

    int *(&pArr2)[10] = ptr_arr; //������������ã����ڶ��⣬pArr2�Ǹ����ã����õ��Ǻ���10������ָ�������

    pArr = &ptr_arr;  //pArr һ���Ƕ�ά������ʹ��

    cout << "finished!" <<endl;


    //��������㣬�Ƚ�����ĵط�

    int array [] = {2,3,5,8,1,9};

    // c++ 11
    //int *pbegin = begin(array);  //��ֵ��ָ��
    //int *pend = end(array);  //����βָ�룬���һ��Ԫ�ص���һλ��

    //����ͱ�׼��string ,vector�� []�����в�ͬ�ĵط�; ����ֵ����Ϊ��ֵ��

    int *ptr_test = array + 4;

    cout << "array access test[0]: " << ptr_test[0] << endl;
    cout << "array access test[-1]: " << ptr_test[-1] << endl;  //����ֵΪ��

    //c�����ַ������漰�����㣬strlen,strcmp,strcat,�ȣ�����ʹ��string��

    //string��C����ת��

    const char *const_str = "wangwei nihao";
    string str1_test = const_str; //string �������Կ��ַ�����β���ַ����飬����ֵ
    const char *str_2_cstr = str1_test.c_str(); //ʹ��c_str����









}
