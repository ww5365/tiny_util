/*
 * thread_use_demo.cpp
 *
 *  Created on: Mar 28, 2018
 *      Author: wangwei69
 */

#include "com_use.h"
#include <pthread.h>
#include <iostream>

#include <unistd.h>

using namespace std;

void* thread_stub(void *args){

    pthread_detach(pthread_self());//在stub中detach子线程，这样主线程不会阻塞；即使再调join也不会生效，主线程继续执行；
    cout << "this is thread num: " << *(int*)args <<endl;
    while(1){

    }
    return nullptr;

}

void* thread_stub2(void* args){


    cout << "this is thread2!!" << endl;

    while(true){

    }
}


/*
 * 1、线程间的互斥与同步？
 *    典型应用：双buffer的热加载数据；
 *
 */


/*
 * 1、测试创建线程
 * 2、线程间互斥访问
 */

void thread_use_test(){

    //创建10个线程
    pthread_t *tid;//线程id的数组
    tid = (pthread_t*)malloc(sizeof(pthread_t)*10);//分配线程id数组空间
    for(int i = 0;i < 10;i++){
        //pthread_create参数全部是指针
        pthread_create(&tid[i],NULL,thread_stub,(void*)(&i));

        usleep(1000);
    }


    sleep(1);
    cout << "this is main thread111!" << endl;

    //pthread_exit(NULL);

    pthread_t tid2;
    pthread_create(&tid2, NULL, thread_stub2, NULL);

    for (int i = 0; i < 10; i++){
        pthread_join(tid[i],NULL); //因为在子线程中已经detach了，所以这里即使join，也不会再阻塞主线程了
    }

    //pthread_join(tid2, NULL); //这里会把主线程阻塞掉

    cout << "this is main thread222!" << endl;




}



