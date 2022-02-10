/*
 * 15_textquery_example.h
 *
 *  Created on: Jun 21, 2019
 *      Author: wangwei69
 */

#ifndef _15_TEXTQUERY_EXAMPLE_H_
#define _15_TEXTQUERY_EXAMPLE_H_

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/*
 * �ı���ѯ�������汾���ܣ�
 *
 * 1����һ���ı�
 * 2�������ؼ��֣�key ���أ����key���ִ������Լ����ֵ��е�����
 *
 * ˼·������
 * 1�����ȣ������ı����ݣ�������Ҫ�Ĳ�����ѡ��ʲô�������ݽṹ�����棿
 *
 * 2��Ԥ��ʹ�ã�
 *   TextQuery tq("input_file_stream");
 *   TextResult tr = tq.query("KEY");
 *   print(tr);
 *
 *   eg��
 *
 *   "KEY" occurs 5 times:
 *   line3:  ... KEY ...
 *   line5:  ... KEY ...
 *
 *
 * 3����ƣ�
 *   �������ݱ��棺vector<string>
 *   ÿ�������Լ����ֵ��кţ� map<string��set<line_no>>
 *
 *
 */

class TextResult;


class TextQuery{

public:
    using line_no = std::vector<string>::size_type;
    TextQuery(ifstream &ifs);
    TextResult query(string key) const;

private:
    //Ϊʲôʹ��shared_ptr���棿
    shared_ptr<vector<string>> content;
    map<string, shared_ptr<multiset<line_no>>> wordmap;
};


TextQuery::TextQuery(ifstream &ifs): content(make_shared<vector<string>>()){

    //�����ı��ļ������γɲ�ѯ��Ҫ�����ݽṹ;
    string line;
    while(getline(ifs, line)){
        if (line.empty()){
            line = " ";
        }
        content->push_back(line);
        istringstream iss(line); //�ַ�����, �ո�ִ�
        string word;

        while (iss >> word){
            shared_ptr<multiset<line_no>> &mset = wordmap[word];

            if (!mset){
                mset.reset(new multiset<line_no>());
                //mset = make_shared<multiset<line_no>>();  //ֱ�Ӹ�ֵ������ΪҲ����
            }
            mset->insert(content->size());
        }
    }
}


class TextResult{

    using line_no = TextQuery::line_no;
private:
    string query;
    shared_ptr<vector<string>> content_query;
    shared_ptr<multiset<TextQuery::line_no>> line_query;

public:

    TextResult(string q,
            shared_ptr<vector<string>> cq,
            shared_ptr<multiset<TextQuery::line_no>> lq) : query(q),content_query(cq), line_query(lq){

        //��֮�䣬ʵ�����ݹ���ͨ������ָ�롣
        //Ϊʲô������Ԫ�ࣿ�������⣬TextQuery�����ͷţ�TextResult�����ڣ�
        //ʹ��shared_ptr���������ݣ�ԭ����û���ˣ�ֻҪ�������������������ݣ�heap�����ݾͲ����ͷţ�
    }

    shared_ptr<vector<string>> get_file(){
        return content_query;
    }

    multiset<line_no>::iterator begin(){
        return line_query->begin();
    }

    multiset<line_no>::iterator end(){
        return line_query->end();
    }

    friend ostream& print(ostream& os, const TextResult &result);

};


//�ټ�������TextQuery���е�query����
TextResult TextQuery::query(string key) const{

    auto it = wordmap.find(key);

    cout << "find key:" << key << " result size: " <<it->second->size() << endl;
    static shared_ptr<multiset<line_no>> nodata(new multiset<line_no>()); //Ϊʲôstatic? ����ÿ�����󶼷���ɡ���
    if (it !=  wordmap.end()){
        return TextResult(key, content, it->second);
    }else{
        return TextResult(key, content, nodata);
    }

}

ostream& print(ostream &os, const TextResult &result){

    //multiset�ı���

    std::size_t occur_times = 0;

    for(auto it = result.line_query->begin(); it != result.line_query->end(); it = result.line_query->upper_bound(*it)){
        //����ÿ������ͬ��Ԫ��
        std::size_t pos = *it;
        //������ִ���
        auto pair_res = result.line_query->equal_range(*it);
        occur_times +=  distance(pair_res.first, pair_res.second);
        os << "line " << pos << " : " << result.content_query->at(pos - 1) << endl;
    }

    os << "key: \"" << result.query << "\" occur times: " << occur_times << endl;

    return os;

}

/*
 * �ı���ѯ�ĸ߼��汾��
 *
 * ֧��query��ѯ���߼����㣺 & | ��
 *
 * 1������query
 *   Query q = query("key1") & query("key2") | query("key3")
 *
 *   ���壺ͬʱ����key1��key2��ֻ����key3����
 *
 * 2��ִ�в�ѯ
 *   TextQuery tq("infile");
 *   TextResult tr = q.eval(tq); //�õ��Ľ����������Ҫ���������߼������Լ�����
 *
 *
 * ������
 *  query �����������װ�ˣ����������˾���ʵ�֣�
 *
 *  �����ʵ���ࣺһԪ���㣬��Ԫ���� ��������  ʹ��ͳһ�Ľӿ�����ͳ��
 *
 *
 */


/*
 * implement the real query action's Interface
 */

class Query_base{

    friend class Query; //���Է��������private˽�г�Ա������eval get_rep
protected:
    using line_no = TextQuery::line_no;
    Query_base() = default;
    virtual ~Query_base() = default; //����������

private:  //��Ա��Ƴ�private �� �����ǽӿڣ�������������ʵ�֣���ʹ�á�����
    virtual TextResult eval(const TextQuery &tq) const = 0;
    virtual string get_rep() const = 0;

};


class Query{

public:
    Query(const string &s); //����1��string�������캯��������������������Ǹ��Լ�private��Ա������ʼ�����õ�

    TextResult eval(const TextQuery &tq) const{
        return qu->eval(tq); //ʵ��ʹ�ýӿ�Query_baseʵ��ָ���������������в�ѯ��ע��qu->eval��private�ġ�Ҫ��Query���Query_base��Ԫ�ࣻ
    }

    string get_rep() const{
        return qu->get_rep();
    }

private:
    shared_ptr<Query_base> qu; // ָ��ʵ�ʽ��в�ѯ��������������󣬳������c++ polymorphsim
    Query(shared_ptr<Query_base> query): qu(query){}
    //Ϊʲô��˽�еģ��û����������þ����ʵ����������query�ģ�
    //˽�й��캯��Ҳ�ܸ����õ�ʱ��ɣ�

    friend Query operator~(const Query &q);
    friend Query operator&(const Query &l, const Query &r);
    friend Query operator|(const Query &l, const Query &r);

};

/*
 * ʵ�ֵ����ʲ�ѯ�����漰�������Ҳ�����յ�ִ��ʵ�ʲ�ѯ��ʵ���ࣻ
 *
 * 1��ȫ����private�ġ�
 * 2�������У��ӿ� ��private ����������Ȼ���Լ̳У���ʵ�֡���
 *
 */

class WordQuery: public Query_base{
    string query_word;
    WordQuery(const string& s):query_word(s){} //˽�й��캯����ͨ����Ԫ��������

    TextResult eval(const TextQuery &tq) const{
        return tq.query(query_word);
    }
    string get_rep() const{
        return query_word; //ֱ�ӷ��ز�ѯ��
    }
    friend class Query; //�����Query���캯����Ҫ����˽�е�WordQuery�Ĺ��캯��
};

//��ʼ�����캯��
inline Query::Query(const string& s): qu(new WordQuery(s)){}


/*
 *  ����NotQuery�֧࣬��һԪ���㣺~query
 *
 */

class NotQuery: public Query_base{

    friend Query operator~(const Query& q);
private:
    Query query;
    NotQuery(const Query& q): query(q){}
    TextResult eval(const TextQuery &tq) const;
    string get_rep() const{
        return "~" + query.get_rep();
    }

};

Query operator~(const Query &q){
    shared_ptr<Query_base> tmp = shared_ptr<Query_base>(new NotQuery(q));  //ʹ��Query������ָ��NotQuery�Ļ���ָ�룻����NotQuery˽�й��캯��
    return Query(tmp); //ʹ��ָ��NotQuery�Ļ���ָ�룬������һ��Query;����Query˽�й��캯��

    //���������ʵ������˼�� Query -> NotQuery -> ����ָ�� -> �ٴι���һ��Query
}

TextResult NotQuery::eval(const TextQuery &tq) const{

    TextResult  result = query.eval(tq);
    shared_ptr<multiset<line_no>> ret_lines = make_shared<multiset<line_no>>();

    //get_file ���ر��������������ļ��Ĺ���ָ��
    vector<string>::size_type n = result.get_file()->size();

    auto begin = result.begin();
    auto end = result.end();

    cout << "NotQuery result size: " << distance(begin, end) << endl;

    for (auto it = begin ;it != end; ++it){
        cout << "NotQuery result elm: " << *it << endl;
    }


    for (std::size_t i = 0; i < n; ++i){
        //�ж��ļ���ÿ�У��Ƿ���multiset�У�û��find; ����multiset�������ԱȽ�;��Ҫ�����ظ�Ԫ�أ�
        if (begin == end || *begin != (i+1)){
            ret_lines->insert(i+1);
        }else{
            auto cur = begin;
            auto next = ++begin;
            while (next != end && *cur == *next){
                cur = next;
                next = ++begin;
            }
        }//end else
    }//end for

    cout << "NotQuery ret_lines size: " << ret_lines->size() << endl;
    //���췵�ؽ����
    return TextResult(get_rep(), result.get_file(), ret_lines);
}


/*
 * ��Ԫ�����ࣺ�ֶ���һ��ӿڣ�BinaryQuery; ͨ�����ӿڣ���������� ��Ԫ����
 *
 */

class BinaryQuery: public Query_base{

protected:
    Query left ,right;
    string operand;
    BinaryQuery(const Query& l, const Query& r, string opr): left(l), right(r), operand(opr){}
    string get_rep() const{
        return left.get_rep() + " " +  operand + " " + right.get_rep();
    }
};

/*
 * AndQuery: & ��Ԫ����
 */

class AndQuery: public BinaryQuery{

private:
    AndQuery(const Query &l, const Query &r): BinaryQuery(l, r, "&"){}
    TextResult eval(const TextQuery &tq) const;
    friend Query operator&(const Query &l, const Query &r);
};

Query operator&(const Query &l, const Query &r){
    shared_ptr<Query_base> tmp = shared_ptr<Query_base>(new AndQuery(l,r));
    return Query(tmp); //˽�й��캯�������������ΪQuery����Ԫ
}

TextResult AndQuery::eval(const TextQuery &tq)const{

    TextResult ltr = left.eval(tq);
    TextResult rtr = right.eval(tq);


    shared_ptr<multiset<line_no>> ret_lines = make_shared<multiset<line_no>>();

    //�󼯺ϵĽ���: set_intersection(s1.begin, s1.end(), s2.begin(), s2.end(), inserter(new_set, set.begin()))
    //����ظ�multiset���ظ�����ȥ����inserter ����֮������ݼ��ϣ����������

    set_intersection(ltr.begin(), ltr.end(),
                     rtr.begin(), rtr.end(),
                     inserter(*ret_lines, ret_lines->begin()));


    return TextResult(get_rep(), ltr.get_file(), ret_lines);
}

/*
 * OrQuery: | ��Ԫ����
 */
class OrQuery: public BinaryQuery{
private:
    OrQuery(const Query &l, const Query &r): BinaryQuery(l, r, "|"){}
    TextResult eval(const TextQuery &tq) const;
    friend Query operator|(const Query &l, const Query &r);
};

Query operator| (const Query &l, const Query &r){
    shared_ptr<Query_base> tmp = shared_ptr<Query_base>(new OrQuery(l, r));
    return Query(tmp);
}

TextResult OrQuery::eval(const TextQuery &tq) const{

    TextResult ltr = left.eval(tq);
    TextResult rtr = right.eval(tq);

    shared_ptr<multiset<line_no>> ret_lines =
            make_shared<multiset<line_no>>(ltr.begin(), ltr.end());    //��һ��set��ʼ����һ��set����

    for (auto it = rtr.begin(); it != rtr.end(); ++it){
        ret_lines ->insert(*it);
    }
    //ret_lines -> insert(rtr.begin(), rtr.end());
    return TextResult(get_rep(), ltr.get_file(), ret_lines);

}

























#endif /* 15_TEXTQUERY_EXAMPLE_H_ */
