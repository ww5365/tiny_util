/*
 * test_query.h
 *
 *  Created on: Feb 25, 2019
 *      Author: wangwei69
 */

#ifndef TEXT_QUERY_H_
#define TEXT_QUERY_H_

#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <set>
#include <sstream>

using namespace std;

class TextQueryRes;

class TextQuery{
public:
using lineNo = size_t;

private:

    shared_ptr<vector<string>> text;  //要实现不同对象，文件的共享，所以使用shared_ptr;读入整个文件；
    map<string, shared_ptr<set<lineNo>>> str_dict; //每个单词，出现在不同行的集合;一行可以出现多次，算一次；

public:
    TextQuery(ifstream &ifs):text(new vector<string>){

        string line;
        while (getline(ifs, line)){
            text->push_back(line);
            istringstream iss(line);

            string word;
            while (iss >> word){

                shared_ptr<set<lineNo>> &set_ptr = str_dict[word]; //把map中set的智能指针拿出，使用引用，不增加shared_ptr的计数值
                if (!set_ptr){
                    set_ptr.reset(new set<lineNo>);//分配空间，并重置shared_ptr的值
                }

                set_ptr->insert(text->size()); //vector的size，可以作为行号；少定义一个变量；
            }//while
        }//while

    }

    TextQueryRes query(string key);

};


class TextQueryRes{
    friend ostream& print(ostream &os, const TextQueryRes &res);
private:
    shared_ptr<set<TextQuery::lineNo>> ln;  //每个word对应出现的行号集合
    shared_ptr<vector<string>> text;
    string word;

public:

    TextQueryRes(string w, shared_ptr<vector<string>> txt, shared_ptr<set<TextQuery::lineNo>> line):ln(line), text(txt), word(w){}
};


//查询类中的query动作
TextQueryRes TextQuery::query(string key){

    //可不可以不用new？不可以，因为查询失败时，print要访问nodata初始化的ln值；如果不new，ln->size()报错。
    static shared_ptr<set<lineNo>> nodata(new set<lineNo>);
    auto it = str_dict.find(key);
    if (it == str_dict.end()){
        //没查询到
        //return TextQueryRes(key, text, shared_ptr<set<lineNo>>(new set<lineNo>));

        //为什么用一个局部static变量nodata？而不写成上面这样。。上面这语句，每次查询失败都会new空对象,浪费空间。
        //如果设计成static，整个程序只分配一个空的空间。

        return TextQueryRes(key, text, nodata);

    }else{
        //查到相应的word
        return TextQueryRes(key, text, it->second);
    }
}


ostream& print(ostream &os, const TextQueryRes &res){

    os << res.word << " occurs " << res.ln->size() << " times in this file!" << endl;

    for (auto num : *res.ln){
        os << "\t" << "(line: " << num << " ): " << (*res.text)[num-1] << endl;
    }

    return os;
}








#endif /* TEXT_QUERY_H_ */
