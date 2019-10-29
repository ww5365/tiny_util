/*
 * time_cal.h
 *
 *  Created on: Oct 21, 2019
 *      Author: wangwei69
 */

#ifndef SRC_INC_TIME_CAL_H_
#define SRC_INC_TIME_CAL_H_

#include <sys/time.h>


/*
 * 1、实现一个类： 计算两个时间的时间差，单位是us
 *    1s = 10^6 us
 *
 */


class Timer{
public:
    explicit Timer():diff(0){
        gettimeofday(&start, nullptr);
    }

    time_t elapse(){
        gettimeofday(&end, nullptr);
        diff = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        return diff;
    }
private:
    timeval end;
    timeval start;
    time_t diff;
};


#endif /* SRC_INC_TIME_CAL_H_ */
