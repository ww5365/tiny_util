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


/*
* 使用标准的库函数实现计算程序的运行时间
* 
* std::chrono::duration<double, std::milli> duration
* double: Rep参数代表了可以传入的时间单位的类型，可以为float, int, int64等等，如果为float表示可以传入时间单位的一部分，比如传入1.2表示1.2倍个时间单位。
* std::milli: Period参数代表了时间单位，可以为微秒，毫秒，秒，分钟，小时等（或者其它自定义的单位，类型为std::ratio）。
*/
class Timer2 {
    public:
    explicit Timer2():diff(0) {
        start  = std::chrono::system_clock::now();
    }

    void reset() {
        start = std::chrono::system_clock::now();
    }

    long long elapse() {
        // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        end = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        diff = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
        return diff;
    }
    

private:

    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
    long long diff;

};

#endif /* SRC_INC_TIME_CAL_H_ */
