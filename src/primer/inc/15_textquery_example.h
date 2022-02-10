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
 * 文本查询：初级版本功能：
 *
 * 1、有一段文本
 * 2、给出关键字：key 返回：这个key出现次数，以及出现的行的内容
 *
 * 思路分析：
 * 1、首先，读入文本数据；基于想要的操作，选用什么样的数据结构来保存？
 *
 * 2、预想使用：
 *   TextQuery tq("input_file_stream");
 *   TextResult tr = tq.query("KEY");
 *   print(tr);
 *
 *   eg：
 *
 *   "KEY" occurs 5 times:
 *   line3:  ... KEY ...
 *   line5:  ... KEY ...
 *
 *
 * 3、设计：
 *   数据内容保存：vector<string>
 *   每个单词以及出现的行号： map<string，set<line_no>>
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
    //为什么使用shared_ptr保存？
    shared_ptr<vector<string>> content;
    map<string, shared_ptr<multiset<line_no>>> wordmap;
};


TextQuery::TextQuery(ifstream &ifs): content(make_shared<vector<string>>()){

    //读入文本文件，并形成查询需要的数据结构;
    string line;
    while(getline(ifs, line)){
        if (line.empty()){
            line = " ";
        }
        content->push_back(line);
        istringstream iss(line); //字符串流, 空格分词
        string word;

        while (iss >> word){
            shared_ptr<multiset<line_no>> &mset = wordmap[word];

            if (!mset){
                mset.reset(new multiset<line_no>());
                //mset = make_shared<multiset<line_no>>();  //直接赋值，我认为也可以
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

        //类之间，实现数据共享；通过共享指针。
        //为什么不用友元类？存在问题，TextQuery对象释放，TextResult对象还在；
        //使用shared_ptr来共享数据，原来的没有了，只要还有其它对象在用数据，heap区数据就不会释放；
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


//再继续定义TextQuery类中的query函数
TextResult TextQuery::query(string key) const{

    auto it = wordmap.find(key);

    cout << "find key:" << key << " result size: " <<it->second->size() << endl;
    static shared_ptr<multiset<line_no>> nodata(new multiset<line_no>()); //为什么static? 不用每个对象都分配吧。。
    if (it !=  wordmap.end()){
        return TextResult(key, content, it->second);
    }else{
        return TextResult(key, content, nodata);
    }

}

ostream& print(ostream &os, const TextResult &result){

    //multiset的遍历

    std::size_t occur_times = 0;

    for(auto it = result.line_query->begin(); it != result.line_query->end(); it = result.line_query->upper_bound(*it)){
        //遍历每个不相同的元素
        std::size_t pos = *it;
        //计算出现次数
        auto pair_res = result.line_query->equal_range(*it);
        occur_times +=  distance(pair_res.first, pair_res.second);
        os << "line " << pos << " : " << result.content_query->at(pos - 1) << endl;
    }

    os << "key: \"" << result.query << "\" occur times: " << occur_times << endl;

    return os;

}

/*
 * 文本查询的高级版本：
 *
 * 支持query查询的逻辑运算： & | ！
 *
 * 1、构建query
 *   Query q = query("key1") & query("key2") | query("key3")
 *
 *   含义：同时出现key1和key2或只出现key3的行
 *
 * 2、执行查询
 *   TextQuery tq("infile");
 *   TextResult tr = q.eval(tq); //得到的结果，就是想要符合运算逻辑的行以及内容
 *
 *
 * 分析：
 *  query 把所有情况封装了，对外隐藏了具体实现；
 *
 *  具体的实现类：一元运算，二元运算 。。。等  使用统一的接口类来统领
 *
 *
 */


/*
 * implement the real query action's Interface
 */

class Query_base{

    friend class Query; //可以访问下面的private私有成员函数：eval get_rep
protected:
    using line_no = TextQuery::line_no;
    Query_base() = default;
    virtual ~Query_base() = default; //虚析构函数

private:  //成员设计成private ？ 但它是接口，可以在子类中实现，并使用。。。
    virtual TextResult eval(const TextQuery &tq) const = 0;
    virtual string get_rep() const = 0;

};


class Query{

public:
    Query(const string &s); //接受1个string参数构造函数，但是这个参数并不是给自己private成员变量初始化来用的

    TextResult eval(const TextQuery &tq) const{
        return qu->eval(tq); //实际使用接口Query_base实际指向的运算对象来进行查询；注意qu->eval是private的。要把Query设成Query_base友元类；
    }

    string get_rep() const{
        return qu->get_rep();
    }

private:
    shared_ptr<Query_base> qu; // 指向实际进行查询操作的派生类对象，充分利用c++ polymorphsim
    Query(shared_ptr<Query_base> query): qu(query){}
    //为什么是私有的？用户不能随意用具体的实现类来构造query的；
    //私有构造函数也总该有用的时候吧？

    friend Query operator~(const Query &q);
    friend Query operator&(const Query &l, const Query &r);
    friend Query operator|(const Query &l, const Query &r);

};

/*
 * 实现单个词查询，不涉及运算符；也是最终的执行实际查询的实现类；
 *
 * 1、全部是private的。
 * 2、父类中：接口 是private 但子类中依然可以继承，并实现。。
 *
 */

class WordQuery: public Query_base{
    string query_word;
    WordQuery(const string& s):query_word(s){} //私有构造函数：通过友元类来访问

    TextResult eval(const TextQuery &tq) const{
        return tq.query(query_word);
    }
    string get_rep() const{
        return query_word; //直接返回查询词
    }
    friend class Query; //下面的Query构造函数需要访问私有的WordQuery的构造函数
};

//初始化构造函数
inline Query::Query(const string& s): qu(new WordQuery(s)){}


/*
 *  定义NotQuery类，支持一元运算：~query
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
    shared_ptr<Query_base> tmp = shared_ptr<Query_base>(new NotQuery(q));  //使用Query来构造指向NotQuery的基类指针；访问NotQuery私有构造函数
    return Query(tmp); //使用指向NotQuery的基类指针，构造另一个Query;访问Query私有构造函数

    //这个过程其实很有意思： Query -> NotQuery -> 基类指针 -> 再次构造一个Query
}

TextResult NotQuery::eval(const TextQuery &tq) const{

    TextResult  result = query.eval(tq);
    shared_ptr<multiset<line_no>> ret_lines = make_shared<multiset<line_no>>();

    //get_file 返回保存整个待搜索文件的共享指针
    vector<string>::size_type n = result.get_file()->size();

    auto begin = result.begin();
    auto end = result.end();

    cout << "NotQuery result size: " << distance(begin, end) << endl;

    for (auto it = begin ;it != end; ++it){
        cout << "NotQuery result elm: " << *it << endl;
    }


    for (std::size_t i = 0; i < n; ++i){
        //判断文件的每行，是否在multiset中，没用find; 利用multiset的有序性比较;但要考虑重复元素；
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
    //构造返回结果类
    return TextResult(get_rep(), result.get_file(), ret_lines);
}


/*
 * 二元运算类：又定义一层接口，BinaryQuery; 通过这层接口，再派生与或 二元运算
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
 * AndQuery: & 二元操作
 */

class AndQuery: public BinaryQuery{

private:
    AndQuery(const Query &l, const Query &r): BinaryQuery(l, r, "&"){}
    TextResult eval(const TextQuery &tq) const;
    friend Query operator&(const Query &l, const Query &r);
};

Query operator&(const Query &l, const Query &r){
    shared_ptr<Query_base> tmp = shared_ptr<Query_base>(new AndQuery(l,r));
    return Query(tmp); //私有构造函数，重载运算符为Query的友元
}

TextResult AndQuery::eval(const TextQuery &tq)const{

    TextResult ltr = left.eval(tq);
    TextResult rtr = right.eval(tq);


    shared_ptr<multiset<line_no>> ret_lines = make_shared<multiset<line_no>>();

    //求集合的交集: set_intersection(s1.begin, s1.end(), s2.begin(), s2.end(), inserter(new_set, set.begin()))
    //会把重复multiset中重复的行去掉；inserter 插入之后的数据集合，都是有序的

    set_intersection(ltr.begin(), ltr.end(),
                     rtr.begin(), rtr.end(),
                     inserter(*ret_lines, ret_lines->begin()));


    return TextResult(get_rep(), ltr.get_file(), ret_lines);
}

/*
 * OrQuery: | 二元操作
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
            make_shared<multiset<line_no>>(ltr.begin(), ltr.end());    //用一个set初始化另一个set。。

    for (auto it = rtr.begin(); it != rtr.end(); ++it){
        ret_lines ->insert(*it);
    }
    //ret_lines -> insert(rtr.begin(), rtr.end());
    return TextResult(get_rep(), ltr.get_file(), ret_lines);

}

























#endif /* 15_TEXTQUERY_EXAMPLE_H_ */
