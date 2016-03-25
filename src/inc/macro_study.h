/*
 * macro_study.h
 *
 *  Created on: 2016年3月23日
 *      Author: wangwei69
 */

#ifndef INC_MACRO_STUDY_H_
#define INC_MACRO_STUDY_H_

#include <stdio.h>

/*
 * 可变参数的宏定义
 * arg...:可变的参数》=0
 * ##arg：计算参数，形成参数列表或者去掉之前的逗号(参数为空时)
 */



#define LOG(fmt, arg...) do {printf(\
        "[%s] [%d] : "fmt, __FILE__, __LINE__, ##arg);} while(0);


void macro_study();







#endif /* INC_MACRO_STUDY_H_ */
