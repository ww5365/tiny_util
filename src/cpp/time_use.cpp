/*
 * time_use.cpp
 *
 *  Created on: May 25, 2018
 *      Author: wangwei69
 *
 * @ 处理时间，日期相关的c/c++ 接口
 */

#include "com_use.h"
#include "time_cal.h"
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <sys/time.h>
#include <unistd.h>

using std::cout;

int get_current_idx(int, int);
time_t get_next_time();
void utc_to_localtime();

void accurate_time();

void time_use_test(){

    //
    get_current_idx(4, 20);
    //get_current_idx(4, 120);
    //get_next_time();
    utc_to_localtime();

    accurate_time();

    Timer timer;

    sleep(1);

    cout << "the program run time: " << timer.elapse() << " us "<<std::endl;

}


time_t get_next_time(){
    int period  = 1;
    int delay = 50;
    int sec_interval = 60 * period;
    //time_t now = time(NULL);

    unsigned int now = 51;
    unsigned int next_time = 1;
    while (now < 1000){
        cout << "---------------" << std::endl;
        cout << "next_time now: " << now << std::endl;
        time_t next_time = (now / sec_interval + 1) * sec_interval + delay;
        cout << "next_time1: " << next_time << std::endl;
        if (next_time - now > sec_interval) {
            next_time -= sec_interval;
        }

        cout << "next_time: " << next_time << std::endl;
        now++;
    }

    return next_time;
}

int get_current_idx(int period, int delay){


    time_t now = time(NULL);//从1970到现在秒数；long int

    cout << "now: " << now << std::endl;
    struct tm ptm;
    /*
     * 结构体：struct tm
     int tm_sec;   秒 – 取值区间为[0,59]
     int tm_min;        分 - 取值区间为[0,59]
     int tm_hour;       时 - 取值区间为[0,23]
     int tm_mday;      一个月中的日期 - 取值区间为[1,31]
     int tm_mon;       月份（从一月开始，0代表一月） - 取值区间为[0,11]
     int tm_year;       年份，其值等于实际年份减去1900
     int tm_wday;      星期 – 取值区间为[0,6]，其中0代表星期天，1代表星期一，以此类推
     int tm_yday;      从每年的1月1日开始的天数 – 取值区间为[0,365]，其中0代表1月1日，1代表1月2日，以此类推
     int tm_isdst;      夏令时标识符，实行夏令时的时候，tm_isdst为正。不实行夏令时为0；不了解情况时，tm_isdst()为负。
     *
     */
    localtime_r(&now, &ptm);//获取当前时间now（日期）

    cout << "sec: " << ptm.tm_sec << " "
         << "min: " << ptm.tm_min << " "
         << "hour: " << ptm.tm_hour << " "
         << "year:" << 1900+ptm.tm_year << " "
         << "month: " << ptm.tm_mon + 1 << " "
         << "day: " << ptm.tm_mday << " "
         << "days from yuandan:" << ptm.tm_yday << " "
         << "xialing: " << ptm.tm_isdst << std::endl;


    now = ptm.tm_hour * 3600 + ptm.tm_min * 60 + ptm.tm_sec;
    int sec = now - delay;
    if (sec < 0) {
        sec += 3600 * 24;
    }
    int idx = sec / (period * 60) + 1;

    cout << "indx: " << idx << std::endl;
    return idx;
}

/*
 * @brief 将iso8601时间：2018-06-04T07:13:31Z 转换成本地时间
 *
 * ISO8601的时间，其实就是UTC时间的表示方式；
 *
 */

//这个diff_tm计算是什么意思？两个tm相差的秒数？

long long diff_tm(struct tm *a, struct tm *b) {
 return a->tm_sec - b->tm_sec
      + 60LL * (a->tm_min - b->tm_min)
      + 3600LL * (a->tm_hour - b->tm_hour)
      + 86400LL * (a->tm_yday - b->tm_yday)
      + (a->tm_year - 70) * 31536000LL
      - (a->tm_year - 69) / 4 * 86400LL
      + (a->tm_year - 1) / 100 * 86400LL
      - (a->tm_year + 299) / 400 * 86400LL
      - (b->tm_year - 70) * 31536000LL
      + (b->tm_year - 69) / 4 * 86400LL
      - (b->tm_year - 1) / 100 * 86400LL
      + (b->tm_year + 299) /400 * 86400LL;
}

void utc_to_localtime(){

    std::string iso_time = "2018-06-04T07:13:31Z"; //iso8601标准的utc时间表示
    struct tm tm_v;
    //std::istringstream is(iso_time);
    //is >> std::get_time(&tm_v,"%Y-%m-%dT%H:%M:%SZ"); //c++11支持，读入utc特定格式的时间到tm中；必须有输入流；

    int year,month,day;
    int hour,min,second;
    sscanf(iso_time.c_str(), "%d-%d-%dT%d:%d:%d", &year, &month, &day, &hour, &min, &second);

    tm_v.tm_year = year-1900;
    tm_v.tm_mon = month -1;
    tm_v.tm_mday = day;
    tm_v.tm_hour = hour;
    tm_v.tm_min = min;
    tm_v.tm_sec = second;
    tm_v.tm_isdst = -1;

    cout << "sec: " << tm_v.tm_sec << " "
         << "min: " << tm_v.tm_min << " "
         << "hour: " << tm_v.tm_hour << " "
         << "year:" << 1900+tm_v.tm_year << " "
         << "month: " << tm_v.tm_mon + 1 << " "
         << "day: " << tm_v.tm_mday << " "
         << "days from yuandan:" << tm_v.tm_yday << " "
         << "xialing: " << tm_v.tm_isdst << std::endl;

    //获取tm结构数据，对应的utc的时间戳：time_t
    time_t utc = std::mktime(&tm_v);

    struct tm tm_tmp0 = { .tm_year = tm_v.tm_year,
                     .tm_mday = tm_v.tm_mday,
                     .tm_mon = tm_v.tm_mon,
                     .tm_hour = tm_v.tm_hour,
                     .tm_isdst = -1 }; //sec 和 min 这两个数据都是0

    cout << "sec: " << tm_tmp0.tm_sec << " "
         << "min: " << tm_tmp0.tm_min << " "
         << "hour: " << tm_tmp0.tm_hour << " "
         << "year:" << 1900+tm_tmp0.tm_year << " "
         << "month: " << tm_tmp0.tm_mon + 1 << " "
         << "day: " << tm_tmp0.tm_mday << " "
         << "days from yuandan:" << tm_tmp0.tm_yday << " "
         << "xialing: " << tm_tmp0.tm_isdst << std::endl;


    //获取本地时间戳？
    time_t pseudo = mktime(&tm_tmp0);

    //获取utc时区的tm结构
    struct tm tm_tmp1 = *gmtime(&pseudo);

    tm_tmp0.tm_sec += utc - diff_tm(&tm_tmp1, &tm_tmp0);
    time_t local = tm_tmp0.tm_sec;
    struct tm tm_local = *localtime(&local); //通过time_t获取本地时间
    char local_time[32];
    strftime(local_time, sizeof(local_time), "%Y-%m-%d %H:%M:%S", &tm_local);

    cout << "time res:"  << local_time << std::endl;

}

/*
 * @brief 精确的时间处理；精确到毫秒
 */


void accurate_time(){

    /* 两个数据结构：

     //时间戳
    struct  timeval{
        long  tv_sec;  //秒
        long  tv_usec; //微妙
    };

    //时区
    struct  timezone{
        int tz_minuteswest;  //和greenwich 时间差了多少分钟
        int tz_dsttime; //type of DST correction
    };

    */

    struct timeval tv;
    struct timezone tz;

    //获取当前系统的时间戳(从1970开始)和时区
    gettimeofday(&tv,&tz);

    cout << "timeval: " << tv.tv_sec << " : " << tv.tv_usec << std::endl;

    cout << "timezone: " << tz.tz_dsttime << " : " << tz.tz_minuteswest << std::endl;

    //从1970到现在为止的毫秒数

    uint64_t m_seconds = (uint64_t)tv.tv_sec* 1000 + tv.tv_usec/1000;

    cout << "mill seconds form 1970: " << m_seconds << std::endl;

}

