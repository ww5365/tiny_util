/*
 * mbr_judge.c
 *
 *  Created on: 2016年7月18日
 *      Author: wangwei69
 */

#define MAX_POINTS_NUM 10000

#include "mbr_judge.h"
#include<stdio.h>
#include<stdlib.h>



static int is_digital_str(char *buf, unsigned int len)
{
    unsigned int i = 0;
    for (i = 0; i < len; ++i) {
        if (buf[i] == '-') {
            continue;
        }
        if (buf[i] >= '0' && buf[i] <= '9') {
            continue;
        } else {
            return 0;
        }
    }
    return 1;
}


static int parse_xy(char *str, point_t* pt)
{
    //buffer sample "12109378.4,3606455.5"
    if (!str || !pt) {
        return -1;
    }
    char *ptr, *buf, tmp[32];
    memset(tmp, 0 , sizeof(tmp));
    buf = str;
    ptr = strpbrk(buf, ",");
    if (ptr) {
        *ptr = '\0';
    } else {
        //WARNING("bad request bound  format in request string[%s]", str);
        return -1;
    }
    pt->x = atoi(buf);
    pt->y = atoi(ptr + 1);
    return 0;
}

static int parse_request_bound(char *str, point_t *pt)
{
    //buffer sample(12109378.4,3606455.5;13397570.4,5390263.5)
    //解析bound，格式如下，得到bound的中心点
    if (!str || !pt) {
        return -1;
    }
    char *ptr, *buf ;
    point_t plb, pru;
    int ret = 0;
    buf = str;
    if (*buf == '(') {
        buf++;
    }
    if (buf[strlen(buf) - 1] == ')') {
        buf[strlen(buf) - 1] = '\0';
    }
    ptr = strpbrk(buf, ";");
    if (ptr) {
        *ptr = '\0';
    } else {
        ("bad request bound  format in request string[%s]", str);
        return -1;
    }
    ret = parse_xy(buf, &plb);

    if (ret == -1) {
        return -1;
    }
    ret = parse_xy(ptr + 1, &pru);
    if (ret == -1) {
        return -1;
    }
    pt->x = plb.x + (pru.x - plb.x) / 2;
    pt->y = plb.y + (pru.y - plb.y) / 2;

    return 0;
}


country_t *mod_rewrite_country_init(unsigned int mbr_max_num)
{
    country_t *ct = (country_t*)malloc(sizeof(country_t));
    if (NULL == ct) {
        ("in %s malloc failed!", __FUNCTION__);
        return NULL;
    }
    ct->max_num = mbr_max_num;
    ct->count = 0;
    ct->mbrs = calloc(ct->max_num, sizeof(mbr_t));
    if (NULL == ct->mbrs) {
        ("in %s calloc failed!", __FUNCTION__);
        return NULL;
    }
    return ct;
}


void *mod_rewrite_country_destroy(country_t *ct)
{
    if (ct->mbrs != NULL) {
        free(ct->mbrs);
        ct->mbrs = NULL;
    }
    if (ct != NULL) {
        free(ct);
        ct = NULL;
    }
}


int mod_rewrite_country_load(const char *filename, country_t *ct)
{
    FILE *fp;
    char buf[256], *ptr, *p;
    int c;
    ("sug conf mbrlist load begin ! fun:%s", __FUNCTION__);

    if (!(fp = fopen(filename, "r"))) {
        ("can not open file [%s]", filename);
        return -1;
    }
    c = 0;
    if (NULL == ct->mbrs) {
        ("in %s, ct->mbrs is null", __FUNCTION__);
        fclose(fp);
        return -1;
    }
    while (fgets(buf, sizeof(buf), fp)) {
        if (strchr("\n\r#", *buf)) {//判断是否为空行的
            continue;
        }

        if (c > MAX_POINTS_NUM) {
            ("the number of mbr in file [%s] exceeds max number [max:%d]", filename, MAX_POINTS_NUM);
            break;
        }
        ptr = strpbrk(buf, "\n\r");
        if (ptr) {
            *ptr = '\0';
        }
        p = strtok(buf, "\t");
        if (!p || !is_digital_str(p, strlen(p))) {
            ("bad file format in file[%s], around line[%d]", filename, c + 1);
            continue;
        }

        ct->mbrs[c].cityid = atoi(p);
        int times = 1;
        while (p) {
            p = strtok(NULL, "\t");

            if (times == 1 && p) {
                ct->mbrs[c].xmin = atoi(p);
            }

            if (times == 2 && p) {
                ct->mbrs[c].xmax = atoi(p);
            }

            if (times == 3 && p) {
                ct->mbrs[c].ymin = atoi(p);
            }

            if (times == 4 && p) {
                ct->mbrs[c].ymax = atoi(p);
            }

            if (times == 6 && p) {
                ct->mbrs[c].sugto = atoi(p);
            }
            times++;
        }

        c++;
    }
    fclose(fp);
    ct->count = c;
    ("sug conf mbrlist load finished ! num: %d", c);
    return 0;
}


int mod_rewrite_point_in_country(country_t *ct, point_t center)
{

    int idx = 0;
    int xmin, ymin, xmax, ymax;
    for (; idx < ct->count; ++idx) {
        mbr_t mt = ct->mbrs[idx];
        xmin = mt.xmin;
        ymin = mt.ymin;
        xmax = mt.xmax;
        ymax = mt.ymax;
        if (center.x <= xmax && center.x >= xmin && center.y <= ymax && center.y >= ymin) {
            printf("target: find mbr:%d \n",idx);
            return mt.sugto;    //中心点落在mbr的范围内
        }
    }

    return -1;

}


int main_process(int argv, char *args[]){

    //读入各个国家的mbr值
    country_t *country_mbr = mod_rewrite_country_init(MAX_POINTS_NUM);
    char *file_name = "mbrlist";
    mod_rewrite_country_load(file_name,country_mbr);

    if (argv < 1){
        printf("error: input parameter less 1\n");
        return -1;
    }

    char bound[256];
    snprintf(bound,sizeof(bound),"%s",args[1]);
    point_t center_point;

    int ret = parse_request_bound(bound,&center_point);

    if(ret != 0 ){
        printf("error: parse bound error\n");
        return -1;
    }

    mod_rewrite_point_in_country(country_mbr,center_point);

    mod_rewrite_country_destroy(country_mbr);


}


