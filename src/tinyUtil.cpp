//============================================================================
// Name        : tinyUtil.cpp
// Author      : wangwei
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "cmd_option.h"
using namespace std;

int main(int argc, char* argv[]) {
    cout << "!!!Hello World!!!" << endl;
    cout << "args num :" << argc << endl;
    for (int i = 0; i < argc; i++) {
        cout << "args:" << i << " value:" << argv[i] << endl;
    }
    cout << "finished!" << endl;

    char *p = argv[argc-1];


    cout << "argv:" << *p <<endl;

    util::CmdOption opt;

    opt.init(argc,argv,"d:c:h");

    if (opt.has_option("d")){
        cout << "d option exist" <<endl;
        cout <<"d option is: " <<opt["d"] <<endl;

    }else{
        cout << "d option not exist" <<endl;
    }

    if (opt.has_option("f")){
        cout << "f option exist" <<endl;
        cout <<"f option is: " <<opt["f"] <<endl;

    }else{
        cout << "f option not exist" <<endl;
    }


    return 0;
}
