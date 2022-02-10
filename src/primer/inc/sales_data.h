/*
 * sales_data.h
 *
 *  Created on: Mar 25, 2019
 *      Author: wangwei69
 */

#ifndef SALES_DATA_H_
#define SALES_DATA_H_

#include <string>
using namespace std;


class  Sales_data{

public:
/*topic ��Ԫ������
 * 1���ǳ�Ա�����������Ԫ����������;
 * 2��ΪʲôҪ����Ԫ����Щ�������Է���������˽�г�Ա����
 */

friend Sales_data add(const Sales_data&, const Sales_data&);
friend std::ostream& print(std::ostream& os, const Sales_data&);
friend std::istream& read(std::istream& is, const Sales_data&);

/*
 * ��14��
 * 1������������ȶ�������ȡ���������س��������������ʹ��
 *
 */

//���룬��� �����
friend Sales_data operator<< (std::ostream &os, const Sales_data& data);
friend Sales_data operator>> (std::istream &is, Sales_data& data);


//��� �����

friend bool operator==(const Sales_data &l, const Sales_data &r);


private:
    /*
     * ��Ա������˵����
     * 1����ʼ����˳�򣬺Ͷ���˳����ͬ���ͳ�ʼ���б��˳���޹أ�
     * 2��������Ա��������ʼ��ֻ��ͨ����ʼ���б�Ҳ����˵����ʼ���б��������ȡconst����ǰ��ֵ��
     */
    std::string isbn; //���Ψһ���
    unsigned int units_sold = 0; //������
    double revenue = 0.0 ;  //����Ĭ��ֵ�����۶�

public:

    /* topic��Ĭ�Ϲ��캯����
     * 1��û�в�����û���Ļ������������Զ��ϳ�Ĭ�Ϲ��캯��
     * 2��ʹ��=default�����������Զ��ϳɵĹ��캯����û��ʵ�֣�=default����ʵ�֣�
     * 3��Ϊʲô��Ҫ=default����Ϊ�������������汾�Ĺ��캯������Ͳ���������Ĭ�Ϲ��캯���ˣ�
     * �������������ҪĬ�Ϲ��캯���ģ���ʱ=defaultһ�¡���
     * 4�����ܶ��壬Ĭ�ϲ�����const���͵Ķ���
     */

    //Sales_data() = default;

    //Ĭ�Ϲ��캯����ʹ��Ĭ��ֵ�ͳ�ʼ���б�,���г�ʼ����
    Sales_data():isbn(""),revenue(0.0),units_sold(0){

        /* topic����ʼ���б�͸�ֵ������
        * ����const����ʱ��������ó�ʼ���б�Ҳ����˵����Ķ����ȡconst���ԣ����ڳ�ʼ���б�֮��ġ�
        */

        //isbn = "";
        //revenue = 0.0;
        //units_sold = 0;
    }

    Sales_data(std::istream &is);

    /*
     * topic������const��Ա����˵����
     * 1���ǳ�������������ͨ�����������ָ�������������������ΪҪ�ı�����Ա������ֵ��
     * 2������ԭ���ǣ�������ʹ����thisָ�룬���ָ���ǣ�TYPE *const this�������͵ģ�
     *
     */
    void addCount(){
        units_sold ++;
    }
    /* topic: thisָ��
     * const���������� ��thisָ����Ϊ��const TYPE *const this��
     * ���Դ��ඨ��ĳ��������ָ�룬�����÷��ʷ�const�ĳ�Ա������ֻ�ܷ���const��Ա������
     * tips��
     * ���ı����Ա�����ĺ����������������const��Ա��������֤�ඨ���const����ͷ�const���󶼿��Է��ʴ˺�����
     */
    unsigned int getCount() const{
        return units_sold;
    }


};














#endif /* SALES_DATA_H_ */
