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
#include <unordered_set>
#include <unordered_map>

/*
 * priority_queue使用范例
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

    // 内部重载运算符号<
    bool operator<(const Student &s) const
    {
        if (score == s.get_score()) {
            return name < s.get_name();
        }
        return score > s.get_score(); //score的小顶堆, 成绩从小到大出队
    }


};

// 重写仿函数: 比较类，重载()运算符号
class CompareClass{
public:
    bool operator() (const Student &lf,const Student &rg) const {
        if (lf.get_score() == rg.get_score()){
            return lf.get_name() < rg.get_name(); //大顶堆：x1 < x2 < x3(队头) 从大到小出队
        }
        return lf.get_score() > rg.get_score();// 小顶堆： x1 > x2 > x3(队头)  队头是最小的元素，出队顺序从小到大
    }
};


class stl_use{
public:


    static void priority_queue_use();
    static void deque_use();
    static void vector_use();

    static void map_use();

    static void unordered_set_use();

    static void set_use();

    static void list_use();

    static void iterator_use();

};



#endif /* SRC_INC_STL_USE_H_ */
