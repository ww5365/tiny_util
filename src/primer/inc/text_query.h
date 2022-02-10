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

    shared_ptr<vector<string>> text;  //Ҫʵ�ֲ�ͬ�����ļ��Ĺ�������ʹ��shared_ptr;���������ļ���
    map<string, shared_ptr<set<lineNo>>> str_dict; //ÿ�����ʣ������ڲ�ͬ�еļ���;һ�п��Գ��ֶ�Σ���һ�Σ�

public:
    TextQuery(ifstream &ifs):text(new vector<string>){

        string line;
        while (getline(ifs, line)){
            text->push_back(line);
            istringstream iss(line);

            string word;
            while (iss >> word){

                shared_ptr<set<lineNo>> &set_ptr = str_dict[word]; //��map��set������ָ���ó���ʹ�����ã�������shared_ptr�ļ���ֵ
                if (!set_ptr){
                    set_ptr.reset(new set<lineNo>);//����ռ䣬������shared_ptr��ֵ
                }

                set_ptr->insert(text->size()); //vector��size��������Ϊ�кţ��ٶ���һ��������
            }//while
        }//while

    }

    TextQueryRes query(string key);

};


class TextQueryRes{
    friend ostream& print(ostream &os, const TextQueryRes &res);
private:
    shared_ptr<set<TextQuery::lineNo>> ln;  //ÿ��word��Ӧ���ֵ��кż���
    shared_ptr<vector<string>> text;
    string word;

public:

    TextQueryRes(string w, shared_ptr<vector<string>> txt, shared_ptr<set<TextQuery::lineNo>> line):ln(line), text(txt), word(w){}
};


//��ѯ���е�query����
TextQueryRes TextQuery::query(string key){

    //�ɲ����Բ���new�������ԣ���Ϊ��ѯʧ��ʱ��printҪ����nodata��ʼ����lnֵ�������new��ln->size()����
    static shared_ptr<set<lineNo>> nodata(new set<lineNo>);
    auto it = str_dict.find(key);
    if (it == str_dict.end()){
        //û��ѯ��
        //return TextQueryRes(key, text, shared_ptr<set<lineNo>>(new set<lineNo>));

        //Ϊʲô��һ���ֲ�static����nodata������д����������������������䣬ÿ�β�ѯʧ�ܶ���new�ն���,�˷ѿռ䡣
        //�����Ƴ�static����������ֻ����һ���յĿռ䡣

        return TextQueryRes(key, text, nodata);

    }else{
        //�鵽��Ӧ��word
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
