
#ifndef _7_H_
#define _7_H_

#include <iostream>
#include <vector>
#include <string>

#include <bitset>

#include "sales_data.h"

class Screen; //�����࣬�Ƕ���ʵ��
class Window_mgr;

extern std::ostream& storeOn(std::ostream &, Screen &);
extern std::bitset<32>& storeOn(std::bitset<32> &, Screen &);


class Window_mgr {

public:
//��������
using ScreenIndex = std::vector<Screen>::size_type;

public:

    Window_mgr() = default;
    //���ĳ��Screen
    void clear(ScreenIndex i); //�����������������Screen�����Ԫ��Ҫ������Screen��˽�г�Ա������ʵ�ַ���Screen�ඨ��֮��

    Screen& get(ScreenIndex i);//������

    ScreenIndex set(Screen &); //��window�����screen;ע�⣬�����ⶨ��ʱ����������

private:
    std::vector<Screen> screens;
    //std::vector<Screen> screens{Screen(3, 3, '#')}; //�������������ܵ���Screen�Ĺ��캯��

};



class Screen{

public:

    /*
     * ����һ�����ͳ�Ա�����£�
     * 1���ȼ��ڣ�using pos = std::string::size_type
     * 2������ʹ�����: ���ͳ�Ա��������������
     *
     */
    typedef std::string::size_type pos;

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;

    mutable size_t access_ctr = 0;//mutable���ɱ����ݳ�Ա��

public:
    //���캯��
    Screen(){};   //Ĭ�Ϲ��캯��
    Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(ht*wd, c){}

    /*
     * topic: inline ����
     * �ô��� Ч�ʣ�������Ҫֱ���滻���룻������С����
     *
     *
     * 1�����ڳ�Ա���������岢ʵ�ֵģ�Ĭ����inline��
     * 2������ʵ�ֵĳ�Ա������������ʽ�Ķ���Ϊinline
     *
     */

    char get() const{
        return contents[cursor];//Ĭ��inline
    }

    char get(pos ht, pos wd) const;

    /*
     * topic: mutable
     *
     */
    void some_memeber() const{
        ++access_ctr; //mutable��Ա����:��ʹ����ĳ�������Ҳ���Ըı�
        std::cout << "access_ctr: " << access_ctr << std::endl;
    }

    /*
     * topic: ���ض�������*this
     */

    Screen &set(char ch){

        //contents[cursor] = ch;
        contents.insert(cursor, 1, ch);
        return *this; //�����������
    }

    Screen &set(pos row, pos col, char ch){

        //contents[row * width + col] = ch;  //string ֱ��ĳ��λ�ø�ֵ���е����⡣��֪��ʲôԭ��
        contents.insert(row * width + col, 1, ch);
        return *this;
    }



    /*
     * topic: �ǳ�������const����������������������ٴε��ö����еķ�const������
     * ��ô���ʵ�֣�
     * ���ǰ�const�����������أ��Զ�����const���const�ĺ�����
     * ����������������С��������Ƴ�const,��֤��С���ķ��ʶ����Ա������
     *
     *  ���磺 Screen sce;
     *
     *  sce.display(os).set("#");
     *  һ��display����const��������ô��Ʋ��ܼ���constҲ�ɷ�constʵ�֣�
     *  ���ء�ʹ��constС����
     *
     */

private:
    //С����������������ͬʱ�ṩ��const�ͷ�const������
    void do_display(std::ostream &os) const{
        os << contents;
    }

public:
    /*
     * ˵��:
     * 1����const��Ա�������Ե���const��Ա������
     * 2��
     */
    Screen &display(std::ostream &os){
        do_display(os);
        return *this;

    }
    /* ˵����
     * 1������display, ���������Ҫ��const��������;
     * 2��const ��Ա�����ܵ��÷�const��Ա������ ��
     * 3�����ã������������displayʱ���Զ�����const����
     *
     *
     */

    const Screen &display(std::ostream &os) const{
        do_display(os);
        return *this;//��������ǳ�������

    }

    /*
     *  topic: ��Ԫ  ��̽��
     *  1��Ϊʲô��Ҫ��Ԫ�� ���Է�������������˽�г�Ա������
     *  2����Ԫ����ʽ����������ĳ����ģ�
     *     ��Ԫ����
     *     ��Ԫ��
     *     ��Ԫ��ĳ�Ա����
     *
     *     example ����
     *
     *  3����Ԫ�࣬��Ԫ��������Ҫ������������Ԫ���ͣ���Ԫ��������������ʱ��ֱ�Ӷ���ʵ�֣��������⻹��Ҫ������������
     *  4����Ԫ���߱�������
     *
     *
     */


//friend class Window_mgr;  //��Ԫ�࣬���г�Ա���������Է�����Screen�����˽�г�Ա����

friend std::ostream& stroeOn(std::ostream &, Screen &); //��Ԫ����������������������ǰ��������Ȼ��ͬ�����أ���ֻ������汾��Ȩ�޷�����Screen�����˽�г�Ա

 friend void Window_mgr::clear(Window_mgr::ScreenIndex i);
 /*
 * ��Ԫ���Ա������ ����һ�����⣿
 * Window_mgr::clear����Screen����Window_mgr::clear��û�ж��壬��ô�죿
 *��Window_mgr�������Screen֮ǰ��window_mgr��Ҫʹ��Screen�Ĺ��캯����˽�б����� ��֮���������Ҳ���clear����δ�������
 * �������⣺ ������������
 *
 * ���������
 * 1��window_mgr�࣬����Screen����������Ա�����Ȳ�Ҫ���壻��ҪScreen��Ļ����Ȱ�Screen�����ˣ�
 *
 * 2������ʵ����Screen
 *
 * 3��ʵ��window_mgr���г�Ա����
 *
 *
 */


};

//��ʽ����������
inline char Screen::get(pos ht, pos wd) const{
    return contents[ht * wd];
}

void Window_mgr::clear(ScreenIndex i){

    Screen &s = screens[i];
    s.contents = std::string(s.height * s.width, ' '); //��Ϊ����Screen����Ԫ�࣬���Կ��Է���Screen������˽�г�Ա

    if (s.contents.empty()){
        std::cout << "screen : " << i << " clear!" << std::endl;
    }
}


Screen& Window_mgr::get(ScreenIndex i){
    return screens[i];
}

Window_mgr::ScreenIndex Window_mgr::set(Screen &s){
    screens.emplace_back(s); //˼��������������s�������¹��죿����ԭ���ģ�
    //screens.push_back(s);
    //std::cout << "make use of s construct screens in window_mgr" << std::endl;
    //screens[0].some_memeber();
    return screens.size() - 1;
}


/*
 * topic: ���캯����̽
 *
 * 1�����캯���Գ�Ա������ʼ����ʱ����
 *   �ں�����տ�ʼִ��ʱ����Ա�����ĳ�ʼ�����Ѿ���ɣ� ���ԣ�����const��Ա���������͵ĳ�Ա���Ͳ���ʹ�ø�ֵ��ʽ���г�ʼ��������ʹ�ó�ʼ���б�
 *
 * 2��������ݳ�Ա�ĳ�ʼ����˳��
 *    �������ڶ����˳�������г�ʼ����
 *
 * 3�������캯����delegating constructor   ??
 *
 *    ���캯�����ñ�Ĺ��캯�������г�Ա�����ĳ�ʼ����
 *
 *    ִ��˳�򣺳�ʼ���б��е��õĹ��캯�� -�� �������ڴ���
 *
 * 4��Ĭ�Ϲ��캯��
 *
 *    4.1 ����һ���������Ĺ��캯���������T�ڶ������ʱ�� T test, �����ǲ��еġ�û��Ĭ�Ϲ��캯����������Ҳ�������ɣ��ϳɵ�Ĭ�Ϲ��캯��;
 *    4.2 ʲôʱ������ʹ��Ĭ�Ϲ��캯���� ���ڳ�Ա������Ҳ��ĳ����Ķ���
 *
 *
 *  5���ؼ��֣�explicit
 *
 *    ��ֹ��Ĺ������ʱ��������ʽ��������ת����
 *    ��ԣ�һ�������Ĺ��캯�����ᷢ����ʽ����ת���������������ֱ�ӹ��죬���Ǹ�ֵ=����
 *
 *  6������ֵ������
 *
 *    constexpr ���캯���� ����������ֵ������
 *
 *    û�����͸������ֵ�����ࣿΪʲôҪ��constexpr �� ����ֵ������ʵ�����Ĳ��Ǻ�͸��
 *
 *    �����������˽�ɡ���
 *
 */


class Test_class {

private:
    std::string isdn;
    double price;
    unsigned int units_sold;
    double revenue;

public:

    Test_class(std::string s, unsigned int cnt, double p): isdn(s), price(p),units_sold(cnt){
        revenue = price * units_sold;
    }

    //������
    //һ�������Ĺ��캯��,ʹ���������������Ĺ��캯������ʵ��һ�������Ĺ��캯��
    Test_class(double pr):Test_class("", 0, pr){}

    //Ĭ�Ϲ��캯��
    Test_class():Test_class("", 0, 0){}

    //explict ֻ������ʾ����;ʹ��Test_class����ֻ����ʾ�Ĺ��죬���ܽ�����ʽת���ˣ�
    //���磺test.add(Test_class(std::string("999-999"))); ��ȷ
    //     test.add(std::string("999-999")); //����ȷ string������ʽת��Test_class����ʱ����

     explicit Test_class(std::string s):Test_class(s, 0, 0){}
     void add(Test_class t){}

};


/*
 * topic: ��ľ�̬����
 *
 *  1��Ϊʲô��Ҫstatic��Ա��
 *     ������������ж���
 *     �������пռ䣺��̬������
 *
 *  2�����������壺
 *  static ���Ա(����������)�����������ڣ����帳ֵ�������⣻ͬʱ�����ⶨ�帳ֵʱ�����ټ�static�ؼ���;
 *  static��Ա��������ʱ�������ڳ�ʼ������Ҳ��Ҫ������в���ֵ�Ķ���;
 *
 *  �ྲ̬���ݳ�Ա�������Լ����͵Ķ��� ţ�ƣ� ͻȻ�뵽��resource������Դ����ģʽ��ʵ�֣���ʹ����static�������Ա����ʵ�֣�
 *
 *  3��ʹ�ã�
 *
 *
 *
 *
 *
 */


class Account {

private:
    static constexpr int period = 30; //��̬���������ʽ�����ڳ�ʼ��

    double daily_tbl[period];  //periodʵ���Ǿ�̬����

    static Account other_acc;  //������Ա���������Լ����͵ġ������ֳ��������������ù��� ����ģʽ��resource����ʵ��

    std::string owner;
    double amount;
    static double interestRate;
    static double initRate();

public:
    static double rate(){ return interestRate; }

    static void rate(double);
    void calculate(){
        amount += amount * interestRate;
    }

};







#endif /* 7_H_ */
