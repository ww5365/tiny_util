/*
 * 7.cpp
 *
 *  Created on: Dec 14, 2018
 *      Author: wangwei69
 */


#include "all.hpp"
#include "7.h"



/*
 * thisָ��
 * ����������������ָ�룬ֻ�ܷ��ʳ�����Ա������Ϊʲô��
 *
 * 1��������⣺��Ϊ�ǳ���������������ָ�룬��ô���������������ǲ��ܱ��ı�ģ�������ʷ�const�ĳ�Ա���������п��ܸı���������ݵģ�
 *
 * 2��������⣺ÿ��������������ָ�������thisָ�룬������ʽ��ͨ��this���������ݳ�Ա�����ͣ�TYPE *const this������ָ��ǳ������ĳ���ָ�룻
 *            �������������const�ģ����������ָ�뻹��ָ��ǳ�������ģ���������Ͳ�ƥ���ˡ�
 *            ������ô��this��ɣ�const TYPE *const this�������ͣ�
 *            ͨ����Ա����������const����this����Ϊָ��const�����ָ�룬����Ϳ���ͨ��this���������ݳ�Ա�ˣ�
 *            û������Ϊconst�ĳ�Ա�������ǲ��ܱ�����������õģ�
 *
 *            const����������أ�*this ���ǳ�����������ã�
 *
 *            �ܽ᣺Ϊ�˱�����ļ����ԣ�������Ϊconst��Ա�����ģ��;�������Ϊconst����֤���const���󣬾����ܶ�ķ��ʳ�Ա������
 *
 */



void test_7(){

    const Sales_data sa;

    //sa.addCount(); //���ܷ��ʷ�const�ĳ�Ա����

    sa.getCount();

    const Screen screen;
    screen.some_memeber(); //��ȡmutable��Ա��������

    Screen screen2;

    screen2.display(std::cout).set('w'); //�Զ��������صķ�const��display����
    screen2.display(std::cout); //����const��display����
    std::cout << std::endl << "screen2 some member: " << std::endl;
    screen2.some_memeber();

    std::cout << std::endl;

    //������Ԫ��

    Window_mgr wm;
    wm.set(screen2);

    std::cout << std::endl << "in wm screen's some member: " << std::endl;

    Screen &s = wm.get(0);
    s.display(std::cout);

    std::cout << std::endl;
    screen2.display(std::cout);
    std::cout << std::endl;
    wm.clear(0);

    s.display(std::cout);

    std::cout << std::endl << "test finished!" << std::endl;

    //Ĭ�Ϲ��캯��
    Test_class test; //����Ĭ�Ϲ��캯��
    //test.add(std::string("999-999")); // ��Ϊ����һ��string�����Ĺ��캯����exlicit�ģ����ܽ�����ʽ����ת����
    test.add(Test_class(std::string("999-999"))); //"999-999" ��ʽ����ת����string��������һ�������Ĺ��캯������ʽ������һ����ʱTest_class����;





}




