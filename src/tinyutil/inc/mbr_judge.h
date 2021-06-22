/*
 * mbr_judge.h
 *
 *      Author: wangwei69
 */

#ifndef INC_MBR_JUDGE_H_
#define INC_MBR_JUDGE_H_

typedef struct __point_t {
    int x;
    int y;
} point_t;



typedef struct __bound_t {
    point_t *pts;
    unsigned int max_num;
    int count;
} bound_t;


typedef struct __rect_t {
    int xmin;
    int ymin;
    int xmax;
    int ymax;
} rect_t;

/*
 * just for country mbr judge
 * add on 2016.04.27
 */

typedef struct __mbr_t {
    int xmin;
    int xmax;
    int ymin;
    int ymax;
    int cityid;
    int sugto;
} mbr_t;

typedef struct __country_t {
    mbr_t *mbrs;
    unsigned int max_num;
    int count;
} country_t;



#endif /* INC_MBR_JUDGE_H_ */
