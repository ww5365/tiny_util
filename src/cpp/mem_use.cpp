/*
 * mem_use.cpp
 *
 *  Created on: Sep 3, 2018
 *      Author: wangwei69
 *  @brief 描述了与内存使用的功能
 */

#include "com_use.h"
#include <string>
#include <map>


/*
 * 如何释放容器中，new出来的数据？
 */

void del_new_data_container(){

    std::map<int, std::string*> map_test;
    std::string *str = new std::string("wang");
    map_test.insert(std::make_pair(1,str));

    //如何释放str指向




}

void mem_use_test(){



}










