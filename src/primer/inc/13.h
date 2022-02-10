/*
 * 13.h
 *
 *  Created on: Feb 26, 2019
 *      Author: wangwei69
 */

#include <string>

using namespace std;

/*
 * ���壺��Ϊ��ֵ����
 *
 *    ÿ�����󣬶����Լ����ݵ�һ�ݿ���;
 *
 *    ��������������ʱ�����뿼�ǿ������ƣ��������졢������ֵ
 *
 *    �ؼ��ǣ�operator= ʵ��: ���� + ����
 *
 *
 *
 */

class hasPtr1 {

    friend void swap(hasPtr1 &l, hasPtr1 &r);

public:

    hasPtr1(const string &s = string()) :
            ps(new string(s)), i(0) {
        //Ĭ�Ϲ��캯����ÿ���������Լ�һ�ݿ���ֵ
    }

    hasPtr1(const hasPtr1 &hp) :
            ps(new string(*hp.ps)), i(hp.i) {
        //�������죬ÿ��ps�����Լ�һ�ݿ���
    }

    hasPtr1& operator=(const hasPtr1&); //����汾
    hasPtr1& operator=(hasPtr1); //����swap�Ŀ������������ģ��쳣��ȫ�İ汾

    ~hasPtr1() {
        delete ps;
    }

private:
    string *ps; //ÿ�������ps���ǲ�ͬ�ģ�����һ�ݿ���
    int i;

};

hasPtr1& hasPtr1::operator=(const hasPtr1& hp) {

    string *tmp = new string(*hp.ps); //�ȷ����¿ռ�

    delete ps; //�ͷ�ԭ��ָ��ռ�

    ps = tmp;
    i = hp.i;
    return *this;
}



/*
 * ���� : ��Ϊ��ָ�����   �е���������ָ��Ĺ���ʵ��
 *
 *   1����ʼ���������ʱ����Ҫ����һ�����ü�����
 *   2���������죺 �������ݳ�Ա���������ü�����
 *   3��������ֵ�� �����Ҳ����ü��������ݼ���������������Ϊ0�����ͷ�
 *   4������������ ���ü������ݼ���Ϊ0�ͷ���Դ��
 *
 *   ��������������ü������� �� �����֮����Ҫ�����������
 *
 *   �� ��Ƴ� static ��Ա���� �����У���������󣬶�����������ݣ��������ֻ�в��������֮�乲�����ݣ�
 *   �� ������ֵ���ͳ�Ա��ֻ���ǣ���̬����Ŀռ䣬ʵ�ֹ���
 *
 *
 *
 *
 *
 */



class hasPtr2{

private:
    string *ps;
    int i;
    std::size_t *cntPtr;

public:

    hasPtr2(const string &s = string()):ps(new string(s)), i(0),cntPtr(new size_t(1)){
    }

    hasPtr2(const hasPtr2& other): ps(other.ps),i(other.i),cntPtr(other.cntPtr){
        (*cntPtr)++;
    }


    //���������Ϳ�������˼·
    hasPtr2& operator=(const hasPtr2& other){

        if ((--*cntPtr) == 0){ //���ref�ݼ�
            delete ps;
            delete cntPtr; //ԭ�����ݺ�ref������������գ�
        }
        ps = other.ps;
        ++(*other.cntPtr); //�ұ�ref����
        cntPtr = other.cntPtr;
        i = other.i;

        return *this;
    }

    //��������
    ~hasPtr2(){

        if (--(*cntPtr) == 0){
            delete ps;
            delete cntPtr;
        }
    }

};


/*
 * topic : swap
 *
 *    swap��Ȼ����Ҫ��������������Ҫ���ǣ���һ����Ҫ���Ż��ֶΣ����ڷ�����Դ���ࣻ
 *
 *    ʹ��ע�⣺  using std::swap;
 *              swap(obj1, obj2); //�������󣬵�����������Լ������ص�swap��������ʹ�ö������ص�swap
 *
 *
 *              ʹ��swap������ʵ�֣�operator= �� �������������ļ������쳣��ȫ��ʵ�ֿ�����ֵ��
 *
 *
 */

//����ʵ�֣�hasPtr1ʹ�õ�swap����
inline void swap(hasPtr1 &l, hasPtr1 &r){
    using std::swap;
    swap(l.ps, r.ps);
    swap(l.i, r.i); //�������ͣ�û��swapʹ��std::swap; �������swap���࣬��ʹusing std::swap,Ҳ����ʹ�ö����ڲ��Լ���swap��
}


hasPtr1& hasPtr1::operator=(hasPtr1 other){ //������ֵ��������

    swap(*this, other); //����ʹ�ã���hasPtr1��swap�汾
    return *this; //�ⲽ���Զ�����,other�б��������

}















