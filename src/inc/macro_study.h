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
 * 双井号就是用于连接
 * 单井号就是将后面的宏参数变成一个字符串；就是将后面的参数用双引号引起来
 *
 *
 *
 */


// ## 宏可变变量(原值)形成参数列表

#define LOG(fmt, name, arg...) do \
{\
    printf("[%s] [%d] :" fmt, __FILE__, __LINE__, ##arg); \
} while(0);


//## 宏变量(原值)连接在一起
#define FACTORY(seg1, seg2) do \
{\
   int seg1##seg2 = 10; \
}while(0);


/*
 * 宏定义：实现常用的位运算
 */
#define  BIT_MSK(bit)     (1 << (bit))
#define  BIT_SET(x, bit)  ((x) |= BIT_MSK(bit))
#define  BIT_CLR(x, bit)  ((x) &= ~BIT_MSK(bit))
#define  BIT_TST(x, bit)  ((x) >> (bit) & 1)   //判断某个bit 位是否为1


void macro_study();







#endif /* INC_MACRO_STUDY_H_ */
