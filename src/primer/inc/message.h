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
 * ����ʵ���ࣺ Message
 *
 * ��������
 *
 * 1������
 *   string content ������Ϣ������
 *   set <Folder> folders ���������Ϣ������Щfolder
 *
 *   Ҳ����˵һ��Message�������ڶ��Folder;һ��FolderҲ�����ж��message;
 *
 *
 *
 * 2������
 *
 *    �½�һ����Ϣ��Ĭ�ϵĳ�ʼ����
 *
 *    ��Ϣ��֧�����еĿ������ƣ����£�
 *
 *    ��������
 *    ������ֵ����
 *    ����
 *
 *    �ƶ�����
 *    �ƶ���ֵ����  :  ��������ʵ�ֵ��ѵ㡣Ҫ�ͷ�����ָ��
 *
 *
 *    ��folder���¼�һ��message
 *    ��folder��ɾ��һ��message
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

    bool delMsg(Message*); //��message�����folder��ɾ��
    bool addMsg(Message*); //�����message�����folder

};

bool Folder::delMsg(Message*){

    return true;

}
bool Folder::addMsg(Message*){

    return true;
}


//void swap(Message& l, Message& r);

class Message{

    friend void swap(Message& l, Message& r);//��Ԫ����

private:

    string content;
    set<Folder*> folders;

    //�Ѵ�message���µ�����folders��
    void add_to_folders(){
        for (auto f : folders){
            f->addMsg(this);
        }
    }

    //�����message�����е�folder��ɾ��
    void free_from_folders(){
        for (auto f : folders){
            f->delMsg(this);
        }
    }



public:

    explicit Message(string m = ""):content(m){} //Ĭ�Ϲ��캯����folders��Ĭ�ϳ�ʼ��Ϊ��; ����explicit�Ǹ��õ�ϰ�ߣ�

    ~Message(){
        free_from_folders();  //ΪʲôҪ��ȡ�������γ�private�ĳ�Ա������ ��ƿ���
        //������message�����ڵ�folders
        //string set �Զ�����
    }

    //�����Ŀ������캯��
    Message(const Message& m):content(m.content), folders(m.folders){

        //free_from_folders();//�Ƚ�����message��folder��ɾ������ȡ�����ɺ����ĺô��Ϳɼ��ˡ�
        /* �ⲽ�����ˡ�������Ϊ�ǿ������죬ԭ���Ķ����ǿյģ�����ɾ�� */

        //����message���뵽�µ�folders�б���
        for (auto f: folders){
            f->addMsg(this);
        }
    }

    //�����ĸ�ֵ����
    Message& operator=(const Message& m) {

        if (this != &m) {
            //�����Ҫ��ɾ������message��ԭ������folder�еļ�¼
            free_from_folders();

            //�����¸�ֵ

            content = m.content;
            folders = m.folders;

            //����message���¶���folder�еļ�¼

            //for (auto f: folders){
            //    f->addMsg(this);
            //}

            add_to_folders();  //�������3������Գ������С����
        }

        return *this;
    }


    //�������� ��ֵ����

    Message& operator=(Message m){
       //�����β�-��m��Ҫ������������ m ��һ����������ʱ����
        using std::swap;
        swap(*this, m); //�����µ�ֵ�����뵽this��

        add_to_folders();
        //����֮���Զ�����m�� �ͷ�ԭ���Ķ��������ڵ�folders��

        return *this;
    }


    //�ƶ����캯�� : ʹ����ֵm���й���, Ҳ������ԭ�ж�����ڴ�ռ�Ļ����Ϲ��죬������������ֻ�����ƶ�

    Message(Message &&m): content(std::move(m.content)){ //ʹ��string���ƶ���ֵ���㣬ԭ�����ڴ������content

        //����ͨ�Ŀ������첻ͬ���ǣ�m�е�foldersָ���message(m),��Ҫ�������ͬʱ������message���뵽folders�У�

        for(auto f : m.folders){
            f->delMsg(&m);  //���m��ԭfolders�м�¼
            f->addMsg(this); //��������message��folders
        }

        folders = std::move(m.folders);
        m.folders.clear(); //ȷ������m�޺�

    }

    // �ƶ���ֵ���㣺 ע�������ͷ�  ע�⣺ m����ҲҪ��ʧ������

    Message& operator=(Message &&m){

        if(this != &m){
            free_from_folders(); //���ͷ�������folders�м�¼
            content = std::move(m.content);

            for(auto f : m.folders){
                f->delMsg(&m); //�ͷ�m��folder�м�¼
                f->addMsg(this); //
            }

            folders = std::move(m.folders);
        }

        return *this;
    }

    //��Ĺ����Ժ���������һ����Ϣ��һ��folder��

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
    //�����Լ���λ�á���
    std::swap(lmsg.folders, rmsg.folders);

}


#endif /* MESSAGE_H_ */
