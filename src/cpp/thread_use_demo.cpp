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

    cout << "this is thread num: " << *(int*)args <<endl;
    return nullptr;

}

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





}



