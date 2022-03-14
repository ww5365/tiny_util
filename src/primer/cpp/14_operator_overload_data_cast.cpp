/*
 * 14.cpp
 *
 *  Created on: Mar 24, 2019
 *      Author: wangwei69
 */

#include <iostream>
#include <vector>
#include <string>
#include <functional>


using namespace std;



void test_14(){

    /* ��14.1�����ʣ�ʲô������� ^ , .* , ->*
     *
     * ^ : ����ǵģ��������
     *
     * .* : ? ɶ�����
     *
     * ->* :?
     *
     *
     */


    bool test1 = true, test2 = false, test3 = true;

    cout << " test operator ^: " << (test1^test2) << " : "  << (test1^test3) << endl;

    /*
     * ������������:  <<  >>
     *
     * 1�������Ա����
     * 2��ע������������Ĵ���ļ��:  ���Ϸ������룬Ҫ����
     *
     */


    /*
     * ���յ�һ����Ҫ�˽���������������������� -�� ��������
     *
     * greater<TYPE> less<TYPE> ... ��׼���ṩ�ģ����������� ��Ҳ����������()������ࣩ,��ҪӦ�õ㣺�����㷨
     *
     * plus  minus multiplies divides modules negate
     *
     * greater less  greater_equal less_equal equal_to not_equal_to
     *
     * logical_and logical_or logical_not
     *
     *   Ӧ�õķ����㷨��
     *
     *   for_each
     *   sort
     *   stable_sort
     *
     * lamda���ʽ�ı��ʣ���ʱ����������
     *
     *
     */


    vector<string> vec_str = {"wang", "wei", "ni", "hao"};

    stable_sort(vec_str.begin(), vec_str.end(), greater<string>());

    for_each(vec_str.begin(), vec_str.end(), [](string &s){cout << s << " ";});

    cout << endl;

    //�����lamda���ʽ���ȼ۵ĺ���������  : TMP();

    class TMP{

    public:
        TMP(){};
        void operator()(string &s){
            cout << s << " ";
        }
    };



    /*
     * ����ת���������first time to understand
     *
     * operator TYPE() const; //�޷����޲Σ���const  ��ʽ�Ķ��������������ת����ת���ɵĽ��������Ҫ��return���أ�
     * explicit operator TYPE() const; //��ʾ�Ķ��������������ת����static_cast<TYPE>(..)
     *
     * ���ף�while(cin >> str) ������ʲô��cin�����Զ������ˣ���������ת����ת��bool�� ���þ�������operator bool() const������
     *
     *  cin << value ; �ֻᷢ��ʲô�� value����λ���㣬����1��0λ
     *
     */


    class Test {
    private:
        string s;
    public:
        explicit operator bool()const{
            return (s.size() != 0 ? true : false);
        }
        Test(string str = ""):s(str){}
        string& content(){
            //��const����£��ǿ��Զ����˽�г�Աs���ó����ģ����ҿ����޸�����ֵ��
            return s;
        }
    };

    Test t1;
    if(!t1){//������ʲô������t1,����������ת����ת����bool�ͣ���Ȼ��explicit������ת�������������if��while�����У��������εĽ��У�
            // Ҳ����˵�� ���εĽ�������ʽ����������ת������

        cout << "t1 is an empty object!" << endl;
    }else{
        cout << "t1 is : " << t1.content() << endl;
    }

    Test t2("wangwei");
    if(!t2){
        cout << "t2 is an empty object!" << endl;
     }else{
         t2.content() += "nihao";
         cout << "t2 is : " << t2.content() << endl;
     }








}
