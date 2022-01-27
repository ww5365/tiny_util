/*
 * macro_study.h
 *
 * Created on: 2016年3月23日
 * Author: wangwei69
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
 */


// ## 宏可变变量(原值)形成参数列表

#define LOG(fmt, name, arg...)                                \
    do {                                                      \
        printf("[%s] [%d] :" fmt, __FILE__, __LINE__, ##arg); \
    } while (0);


/*
 * ## 符号连接操作符, 宏定义的参数符号连接在一起,形成一个实际参数
 * #  字符串化操作符 将宏定义中的传入参数名转换成用双引号括起来参数名字符串。只能用于有传入参数的宏定义中，且必须置于宏定义体中的参数名前。
 */

#define FACTORY(seg1, seg2)                          \
    do {                                             \
        int seg1##seg2 = 10;                         \
        string name(#seg1);                          \
        std::cout << "name : #seg1 : " << name << std::endl; \
        std::cout << "int para seg1##seg2 : " << seg1##seg2 << std::endl; \
    } while (0);

// FACTORY(te, st) => int test = 10; string name("te")

/*
 * 宏定义：实现常用的位运算
 */
#define BIT_MSK(bit) (1 << (bit))
#define BIT_SET(x, bit) ((x) |= BIT_MSK(bit))
#define BIT_CLR(x, bit) ((x) &= ~BIT_MSK(bit))
#define BIT_TST(x, bit) ((x) >> (bit)&1) // 判断某个bit 位是否为1


void macro_study();


#endif /* INC_MACRO_STUDY_H_ */
