/*
 * 15_textquery_example.cpp
 *
 *  Created on: Jun 21, 2019
 *      Author: wangwei69
 */

#include <iostream>

#include "15_textquery_example.h"


void test_15_textquery(){


    ifstream ifs("test");
    if (!ifs.is_open()){
        cout << "open file failed! " << endl;
    }

    TextQuery tq(ifs);

    TextResult tr = tq.query("what");

    print(cout, tr);


    Query qu1("hello");
    Query qu2("what");
    Query qu = qu1&qu2;

    TextResult tr2 = qu.eval(tq);
    print(cout, tr2);

    Query qu3("what");
    TextResult tr4 = (~qu3).eval(tq);
    print(cout, tr4);


}


