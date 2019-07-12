/*
 * design_pattern.cpp
 *
 *  Created on: Mar 10, 2019
 *      Author: wangwei69
 */

#include <iostream>

//#include "design_pattern.h"
#include "design_model.h"


//int Singlton::objNum = 1;

void test_design_pattern(){

    //Singlton::instance().printTest();
    //Singlton::instance().printTest();
    //Singlton::instance().printTest();


    //重新写了一个singlton

    _Singlton &sgl1 = _Singlton::get_instance();

    _Singlton &sgl2 = _Singlton::get_instance2();

    //_Singlton ss("sss");






}




