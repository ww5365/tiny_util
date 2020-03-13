/*
 * thread_use_demo.cpp
 *
 *  Created on: Mar 28, 2018
 *      Author: wangwei69
 */

#include "com_use.h"
#include "thread_use_demo.h"
#include <pthread.h>
#include <iostream>

#include <unistd.h>
#include <utility>
#include <functional>


using namespace std;


void print_msg(const char* msg, int error){

    fprintf(stderr, "error msg: [%d][%s][%s]\n", error, strerror(error), msg);
}

void* thread_stub(void *args){

    pthread_detach(pthread_self());//在stub中detach子线程，这样主线程不会阻塞；即使再调join也不会生效，主线程继续执行；
    //cout << "this is thread num: " << *(int*)args <<endl;

    int pa = *(int*)args;
    while(1){
        //cout << "thread num: " << *(int*)args << endl; //有问题，运行平稳后，输出全部为：thread num : 2 ?想想为什么？因为 主进行中参数i变为2，*(int*)args相当于引用方式使用啊。
        cout << "this is thread num: " << pa << endl;
        usleep(1000000);
    }
    return nullptr;
}

void* thread_stub2(void* args){
    cout << "this is thread2!!" << endl;
    while(true){
    }
}

class CallBackHandle{
public:
    //typedef int(*CallBackFun)(string &name);

    typedef function <int(string)> CallBackFun;  //回调函数：函数指针类型

    CallBackHandle(CallBackFun f, string name):_fun(f), _name(name){}
    ~CallBackHandle(){}

    bool run(){

        cout << "call back handle invoke function!" << endl;
        _fun(_name);
        return true;
    }

private:
    CallBackFun _fun;
    string _name;
};


class Process{
private:
    string _name;
    int _id;

public:
    Process(string name = " ", int id  = 0):_name(name), _id(id){}

    int handle(string name, int seqid){
        cout << "invoke function name: " << name << " seqid: " << seqid << endl;
        return _id;
    }

};


static void* stub3(void* args){

    CallBackHandle* handle = reinterpret_cast<CallBackHandle*>(args);

    handle->run();

    return (void*)nullptr;

}


/*
 * 线程池的简单设计和实现：？
 *
 * 参考：sudata 建库中SimpleThreadPool设计和实现。。
 *
 *
 *
 */









/*
 * 1、先测试如何不把主线程阻塞？
 *
 */

void thread_use_test(){

    //验证自动加锁，解锁类

    {
        Lock lock_obj;
    }

    //只测试上面内容
    return ;

    /*
     * 验证：子线程从主线程中detach出来，即使join，也不再阻塞主线程的运行；
     */

    //创建2个线程
    static const int THREAD_NUM = 2;
    pthread_t *tid;//线程id的数组
    tid = (pthread_t*)malloc(sizeof(pthread_t) * THREAD_NUM);//分配线程id数组空间
    for(int i = 0;i < THREAD_NUM;i++){
        //pthread_create参数全部是指针
        pthread_create(&tid[i],NULL,thread_stub,(void*)(&i));
        usleep(1000);
    }
    sleep(1);
    cout << "this is main thread, over create stub1!" << endl;

    //pthread_exit(NULL);
    pthread_t tid2;
    pthread_create(&tid2, NULL, thread_stub2, NULL);

    for (int i = 0; i < THREAD_NUM; i++){
        pthread_join(tid[i],NULL); //因为在子线程中已经detach了，所以这里即使join，也不会再阻塞主线程了
    }

    //pthread_join(tid2, NULL); //这里会把主线程阻; 如果这里不阻塞，主线程会继续执行，并结束；
    cout << "this is main thread222!" << endl;


    /*
     * 验证：设计方式： callbackhandle对象指针作为参数，传递给桩函数,实际使用对象中定义的函数run；
     *               同时在，主线程中实现对callbackhandle的设置。
     *               主要的目的是：通过函数回调机制，来使用自定义的函数;
     *
     */


    int seqid = 1;
    Process pro("test", seqid);
    CallBackHandle::CallBackFun fun = std::bind(&Process::handle, &pro,std::placeholders::_1, seqid); //fun(str) <=> pro.handle(str,seqid)

    //使用自定义的回调函数来处理事务
    CallBackHandle cbh(fun, "Process::handle"); //通过handler对象，设置了回调函数；也就是把回调函数封装到一个对象里面了
    pthread_t tid3;
    pthread_create(&tid3, nullptr, stub3, &cbh); //将cbh作为参数，传到桩函数中；桩函数通过cbh来调用回调函数；




}



