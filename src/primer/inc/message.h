/*
 * message.h
 *
 *  Created on: Mar 25, 2019
 *      Author: wangwei69
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>
#include <set>

#include <utility>
#include <algorithm>

using namespace std;

/*
 *
 * 定义实现类： Message
 *
 * 功能梳理：
 *
 * 1、数据
 *   string content 保存信息的内容
 *   set <Folder> folders 保存这个消息属于哪些folder
 *
 *   也就是说一个Message可以属于多个Folder;一个Folder也可以有多个message;
 *
 *
 *
 * 2、功能
 *
 *    新建一个消息：默认的初始构造
 *
 *    消息能支持所有的拷贝控制，如下：
 *
 *    拷贝构造
 *    拷贝赋值运算
 *    析构
 *
 *    移动构造
 *    移动赋值运算  :  这两个是实现的难点。要释放两次指向；
 *
 *
 *    在folder中新加一个message
 *    在folder种删除一个message
 *
 *
 *
 */

class Message;

class Folder{

private:
    string name;
    set<Message*> messages;

public:

    bool delMsg(Message*); //把message从这个folder中删除
    bool addMsg(Message*); //把这个message加入此folder

};

bool Folder::delMsg(Message*){

    return true;

}
bool Folder::addMsg(Message*){

    return true;
}


//void swap(Message& l, Message& r);

class Message{

    friend void swap(Message& l, Message& r);//友元函数

private:

    string content;
    set<Folder*> folders;

    //把此message更新到所有folders中
    void add_to_folders(){
        for (auto f : folders){
            f->addMsg(this);
        }
    }

    //把这个message从所有的folder中删除
    void free_from_folders(){
        for (auto f : folders){
            f->delMsg(this);
        }
    }



public:

    explicit Message(string m = ""):content(m){} //默认构造函数；folders会默认初始化为空; 加上explicit是个好的习惯？

    ~Message(){
        free_from_folders();  //为什么要抽取出来，形成private的成员函数？ 设计考虑
        //清除这个message所属于的folders
        //string set 自动析构
    }

    //正常的拷贝构造函数
    Message(const Message& m):content(m.content), folders(m.folders){

        //free_from_folders();//先将自身message从folder中删除；抽取出来成函数的好处就可见了。
        /* 这步多余了。。。因为是拷贝构造，原来的对象是空的；不用删除 */

        //将本message加入到新的folders列表中
        for (auto f: folders){
            f->addMsg(this);
        }
    }

    //正常的赋值运算
    Message& operator=(const Message& m) {

        if (this != &m) {
            //这次需要先删除，此message在原来所有folder中的记录
            free_from_folders();

            //接受新赋值

            content = m.content;
            folders = m.folders;

            //更新message在新对象folder中的记录

            //for (auto f: folders){
            //    f->addMsg(this);
            //}

            add_to_folders();  //上面这个3句亦可以抽像出来小函数
        }

        return *this;
    }


    //拷贝交换 赋值构造

    Message& operator=(Message m){
       //先是形参-》m需要发生拷贝构造 m 是一个独立的临时对象
        using std::swap;
        swap(*this, m); //将最新的值，放入到this了

        add_to_folders();
        //出来之后，自动析构m， 释放原来的对象所属于的folders；

        return *this;
    }


    //移动构造函数 : 使用右值m进行构造, 也就是在原有对象的内存空间的基础上构造，不发生拷贝，只发生移动

    Message(Message &&m): content(std::move(m.content)){ //使用string的移动赋值运算，原来的内存区域的content

        //和普通的拷贝构造不同的是：m中的folders指向的message(m),需要被清除；同时，将本message加入到folders中；

        for(auto f : m.folders){
            f->delMsg(&m);  //清除m在原folders中记录
            f->addMsg(this); //加入自身message到folders
        }

        folders = std::move(m.folders);
        m.folders.clear(); //确保销毁m无害

    }

    // 移动赋值运算： 注意两次释放  注意： m自身也要消失。。。

    Message& operator=(Message &&m){

        if(this != &m){
            free_from_folders(); //先释放自身在folders中记录
            content = std::move(m.content);

            for(auto f : m.folders){
                f->delMsg(&m); //释放m在folder中记录
                f->addMsg(this); //
            }

            folders = std::move(m.folders);
        }

        return *this;
    }

    //类的功能性函数：保存一个消息到一个folder中

    bool save_to_folder(const Message);

};


void swap(Message &lmsg, Message& rmsg){

    std::swap(lmsg.content, rmsg.content);

    for (auto f : lmsg.folders){
        f->delMsg(&lmsg);
        f->addMsg(&rmsg);
    }

    for (auto f : rmsg.folders){
        f->delMsg(&rmsg);
        f->addMsg(&lmsg);
    }
    //摆正自己的位置。。
    std::swap(lmsg.folders, rmsg.folders);

}


#endif /* MESSAGE_H_ */
