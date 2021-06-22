/*
 * cmpare_file_use.cpp
 *
 *  Created on: Jun 11, 2019
 *      Author: wangwei69
 */


#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include "com_use.h"
#include "string_using.h"
using namespace std;

bool read_file(string file_name, vector<string> & content){

    std::ifstream ifs;
    ifs.open(file_name);

    if (!ifs.good()){
        cout << "open file failed! " << file_name << endl;
        return false;
    }

    string line;

    while(getline(ifs, line)){
        content.push_back(line);
    }

    return true;
}

void vec_to_map(vector<string> & content, multimap<string, string> &mf){

    vector<string>  fields;
    string key ="";
    for (size_t i = 0; i < content.size(); ++i){

        size_t len = split_string(content[i], "\t",  fields);
        if (fields.size() > 0 && fields[0] != ""){
            key = fields[0];
            cout << "the key is : " << key << endl;
        }
        mf.insert(std::make_pair(key, content[i]));
    }
}



void cmpare_file_use_test(){


    string file1 = "/Users/wangwei69/workspace/github/tiny_util/file/online_res";
    string file2 = "/Users/wangwei69/workspace/github/tiny_util/file/test_res";

    string out_file = "/Users/wangwei69/workspace/github/tiny_util/file/outfile_res";

    ofstream ofs;
    ofs.open(out_file);

    if (!ofs.good()){

        cout << "outfile failed !" << endl;
        return ;
    }


    vector<string> file1_content;
    vector<string> file2_content;

    bool res1 = read_file(file1, file1_content);
    bool res2 = read_file(file2, file2_content);

    multimap<string, string> mf1;
    multimap<string, string> mf2;

    if (res1 && res2){

        vec_to_map(file1_content, mf1);
        vec_to_map(file2_content, mf2);

    }

    //以mf1的key为纬度，来merge两个文件

    for (auto it = mf1.begin(); it != mf1.end(); it = mf1.upper_bound(it->first)){

        auto range1 = mf1.equal_range(it->first);

        size_t len1 = std::distance(range1.first, range1.second);

        auto range2 = mf2.equal_range(it->first);

        size_t len2 = std::distance(range2.first, range2.second);

        size_t min_len = (len1 <= len2 ? len1 : len2);

        for(size_t i = 0; i < min_len && (range1.first != range1.second) && (range2.first != range2.second); ++i){
            ofs<< range1.first->second << "\t" << range2.first->second << endl;
            ++range1.first;
            ++range2.first;
        }

        while (range1.first != range1.second){
            ofs<< range1.first->second << "\t" << "" << "\t" << ""<< "\t" << ""<< "\t" << ""<< "\t" << ""<< "\t" << ""<< "\t" << ""<< "\t" << ""<< endl;
            ++range1.first;
        }

        while (range2.first != range2.second){
            ofs << "" << "\t" << ""<< "\t" << ""<< "\t" << ""<< "\t" << ""<< "\t" << ""<< "\t" << ""<< "\t" << ""<< "\t" << range2.first->second << endl;
            ++range2.first;
        }


    }

   cout << "output finished!" << endl;

}










