/*
 * str_vec.h
 *
 *  Created on: Mar 25, 2019
 *      Author: wangwei69
 */

#ifndef STR_VEC_H_
#define STR_VEC_H_

#include <memory>
#include <string>

using namespace std;


/*
 * ����ʵ��strvec��: ���� vector<string> ���ܣ��洢������string�ַ���
 *
 *
 */


class StrVec{


private:

    string *element;
    string *first_free; //��һ������λ��
    string *cap;   //����

    static allocator<string> alloc;  //ΪʲôҪ��Ƴ�static?

public:

    StrVec(const string &s){
        alloc.allocate(1);
        //alloc.construct()
    }



    /*
     * ��14�£���������½ڣ�����������
     *
     * 1. operator=
     * 2. operator[]
     *
     * 3.
     *
     *
     */


    //��ֵ���㣬֧�ֳ�ʼ���б����ʽ��StrVec test = {"ab", "cde"}

    StrVec& operator= (std::initializer_list<string> li);


    //�±����㣬 StrVec test[0]  Ϊʲô�������汾��

    StrVec& operator[] (std::size_t n);
    const StrVec& operator[] (std::size_t n) const;






};






#endif /* STR_VEC_H_ */
