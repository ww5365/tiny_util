/*
 * 8.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: wangwei69
 */


#include <fstream>  //�ļ���д��ͷ�ļ�
#include <iostream>
#include <sstream>

#include <string>
#include <vector>

/*
 * topic: IO
 *
 *    ���������������״̬��
 *      s.good(): ��״̬û����
 *      s.fail(): ����failed bad
 *      s.eof():  �����ļ���β
 *
 *    �����������ˢ�£�
 *
 *      std::endl  : ˢ��+����
 *      std::flush : ˢ��
 *      std::ends  : ˢ�� + �ո�
 *
 *
 *
 *    fstream: ͷ�ļ�������һ�µ���
 *      ifstream
 *      ofstream
 *      fstream
 *
 *    �ļ���ģʽ��
 *      out
 *      in
 *      app
 *      trunc
 *      binary
 *      ate
 *
 *
 *    sstream: �ַ�����
 *
 *      istringstream
 *      ostringstream
 *      stringstream
 *
 */


void test_file_io(){

   /*
    * ��ĳ��ģʽ����������д�뵽�ļ�test�У�
    */

    //�����
    std::ofstream ofs;
    ofs.open("./test", std::ofstream::out | std::ofstream::trunc | std::ofstream::binary); //Ĭ�Ͼ���out��app�ģ�

    if (ofs.good()){
        //�ж�������Ƿ��д����޴�����TRUE������ʧ�ܣ�failed bit �ᱻֵ
        ofs << "# this is a test file input!"  << std::endl;//ˢ�»���������������з�
    }else{
        std::cerr << "open file failed!" << std::endl;
    }

    ofs << "wangwei 123 456" << std::endl;
    ofs << std::flush ; //�����ˢ�»���������������κζ����ַ�
    ofs << "nihao   234 324 122" << std::endl;
    ofs << std::unitbuf; //���в��������������ˢ�»�����
    ofs.close();
}


struct PersonInfo{
    std::string name;
    std::vector<std::string> phones;
};

void test_string_io(){

    /*
     * ���ļ�test�ж����ʽ�������ݣ�
     * ʹ���ַ����������ַ������ݣ��������ݴ���ṹ��PersonInfo�У�
     *
     */
    std::ifstream ifs;
    ifs.open("./test");
    if (!ifs.good()){

        std::cout << "open file failed!" << std::endl;
        return;
    }

    std::string line;
    std::vector<PersonInfo> personinfo;

    while(getline(ifs, line)){
        PersonInfo info;
        std::istringstream iss(line);  //���ַ���line�е����ݣ����뵽�ַ�����������<sstream>
        iss >> info.name;  //���������Կո�tab���ָ����������д�뵽������
        std::string phone;
        while(iss >> phone){
            info.phones.push_back(phone);
        }
        personinfo.push_back(info);
    }

    //��Χrange����ʽ����vector
    for(auto e : personinfo){
        std::cout << "name:"  << e.name << "phone list:" << e.phones.size() << std::endl;
    }

    std::ostringstream oss; //�ַ�������������ַ��������֣��ȵȶ�������ַ���������У�����ת�ַ�����ʵ�ֿ��Կ���

    oss << 123456789 << " nihao 12333";
    std::string int_2_str = oss.str();

    std::cout << "oss test: " << int_2_str << std::endl;
    oss.clear(); //����������״̬λ
    oss.str(""); //���������е���������
    std::cout << "oss test: " << oss.str() << std::endl;


}


void test_8(){

    test_file_io();

    test_string_io();


}

