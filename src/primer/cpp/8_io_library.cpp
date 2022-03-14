/*
 * 8.cpp
 *
 *  Created on: Jan 21, 2019
 *      Author: wangwei69
 */


#include <fstream>  //文件读写的头文件
#include <iostream>
#include <sstream>

#include <string>
#include <vector>

/*
 * topic: IO
 *
 *    输出输入流的条件状态：
 *      s.good(): 流状态没问题
 *      s.fail(): 包括failed bad
 *      s.eof():  到达文件结尾
 *
 *    输出缓冲区的刷新：
 *
 *      std::endl  : 刷新+换行
 *      std::flush : 刷新
 *      std::ends  : 刷新 + 空格
 *
 *
 *
 *    fstream: 头文件，包含一下的类
 *      ifstream
 *      ofstream
 *      fstream
 *
 *    文件打开模式：
 *      out
 *      in
 *      app
 *      trunc
 *      binary
 *      ate
 *
 *
 *    sstream: 字符串流
 *
 *      istringstream
 *      ostringstream
 *      stringstream
 *
 */


void test_file_io(){

   /*
    * 以某种模式将三行数据写入到文件test中；
    */

    //输出流
    std::ofstream ofs;
    ofs.open("./test", std::ofstream::out | std::ofstream::trunc | std::ofstream::binary); //默认就是out和app的；

    if (ofs.good()){
        //判断输出流是否有错误，无错，返回TRUE；开打失败，failed bit 会被值
        ofs << "# this is a test file input!"  << std::endl;//刷新缓冲区，并输出换行符
    }else{
        std::cerr << "open file failed!" << std::endl;
    }

    ofs << "wangwei 123 456" << std::endl;
    ofs << std::flush ; //输出后刷新缓冲区，并不添加任何额外字符
    ofs << "nihao   234 324 122" << std::endl;
    ofs << std::unitbuf; //所有操作，输出后立即刷新缓冲区
    ofs.close();
}


struct PersonInfo{
    std::string name;
    std::vector<std::string> phones;
};

void test_string_io(){

    /*
     * 从文件test中读入格式化的数据；
     * 使用字符串流保存字符串数据，并将数据存入结构体PersonInfo中；
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
        std::istringstream iss(line);  //将字符串line中的内容，读入到字符串输入流；<sstream>
        iss >> info.name;  //输入流，以空格、tab键分割；将流中数据写入到变量；
        std::string phone;
        while(iss >> phone){
            info.phones.push_back(phone);
        }
        personinfo.push_back(info);
    }

    //范围range的形式访问vector
    for(auto e : personinfo){
        std::cout << "name:"  << e.name << "phone list:" << e.phones.size() << std::endl;
    }

    std::ostringstream oss; //字符串输出流；把字符串，数字，等等都输出到字符串输出流中；数字转字符串，实现可以考虑

    oss << 123456789 << " nihao 12333";
    std::string int_2_str = oss.str();

    std::cout << "oss test: " << int_2_str << std::endl;
    oss.clear(); //清除输出流的状态位
    oss.str(""); //清空输出流中的数据内容
    std::cout << "oss test: " << oss.str() << std::endl;


}


void test_8(){

    test_file_io();

    test_string_io();


}

