/*
 * stl_use.h
 *
 *  Created on: Jun 16, 2017
 *      Author: wangwei69
 */

#ifndef SRC_INC_STL_USE_H_
#define SRC_INC_STL_USE_H_

#include <string>
#include <queue>
#include <map>
#include <set>
#include <list>

/*
 * priority_queue使用范例
 * 需求：有5个同学随意入队；他们都有成绩和姓名；请按照成绩从低到高出队列，如果成绩相等，按照名字字母逆顺序出队；
 */

class Student{
private:
    std::string name;
    short score;
public:
    Student():name(""),score(0){}
    Student(std::string name,short score):name(name),score(score){}
    short get_score() const{
        return score;
    }
    std::string get_name() const{
        return name;
    }


};

class CompareFun{
public:
    bool operator() (const Student &lf,const Student &rg) const {
        if (lf.get_score() == rg.get_score()){
            return lf.get_name() < rg.get_name(); //返回1的时机？后面的大，返回1，进行调整；把大的调整到前面
        }
        return lf.get_score() > rg.get_score();//左边大于右边，返回1；入队时，之前入队的元素大于后入队的，返回1，进行调整；
    }
};


class stl_use{
public:


    void priority_queue_use();
    void vector_use();

    static void map_use();

    static void set_use();

    static void list_use();

    static void iterator_use();

};



#endif /* SRC_INC_STL_USE_H_ */
