/*
 * thread_use_demo.h
 *
 *  Created on: May 28, 2019
 *      Author: wangwei69
 */

#ifndef SRC_INC_THREAD_USE_DEMO_H_
#define SRC_INC_THREAD_USE_DEMO_H_

#include <stdio.h>
#include <pthread.h>

void print_msg(const char* msg, int error);

/*
 * 类实现功能：？
 *
 * 1、类定义的对象可以自动对：临界区进行加锁；同时，超过类对象的作用域后，利用自动析构的功能，把加的锁释放掉；
 *
 */

class Lock{

public:
    Lock(){
        int ret = pthread_mutex_init(&mutex, nullptr);
        fprintf(stderr, "init mutex!ret:[%d][%s]\n", ret, strerror(ret));//抽像出来，这种重复的代码

        print_msg("mutxt_lock", pthread_mutex_lock(&mutex));
    }

    virtual ~Lock(){
        print_msg("mutex_unlock", pthread_mutex_unlock(&mutex));

        int ret = pthread_mutex_destroy(&mutex);
        fprintf(stderr, "mutex destory! ret:[%d][%s]\n", ret, strerror(ret));
    }
private:
    pthread_mutex_t mutex;
};








#endif /* SRC_INC_THREAD_USE_DEMO_H_ */
