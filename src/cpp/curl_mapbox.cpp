/*
 * curl_mapbox.cpp
 *
 *  Created on: 2016年3月10日
 *      Author: wangwei69
 *  说明：使用libcurl获取mapbox的geocoding服务返回的数据，并解析返回的json数据串
 *
 *  访问：
 *  curl https://api.mapbox.com/geocoding/v5/mapbox.places/-73.989,40.733.json?access_token=sk.eyJ1Ijoid3c1MzY1IiwiYSI6ImNpbGx5aGhqdDY0czd1dW1jaTA1eWVrdGUifQ.L66B41d7fz0x6iKjb93tjQ
 *  返回：json 数据串
 *
 */

/*
 * libcurl库的使用;
 * 调用mapbox服务；

#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>
#include <stdio.h>
#include <string.h>


int curl_mapbox() {
    //char buff[102400];
    //memset(buff,0,102400);

    const char *get_url = "https://api.mapbox.com/geocoding/v5/mapbox.places/-73.989,40.733.json?access_token=sk.eyJ1Ijoid3c1MzY1IiwiYSI6ImNpbGx5aGhqdDY0czd1dW1jaTA1eWVrdGUifQ.L66B41d7fz0x6iKjb93tjQ";
    CURL *curl;
    CURLcode res;
    FILE *fp;
    if((fp = fopen("res.txt","w")) == NULL){
        printf("open file failed!\n");
        return -1;
    }
    curl = curl_easy_init();
    if (curl){
        curl_easy_setopt(curl, CURLOPT_URL, get_url);// 设置server的URL
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); //不使用SA认证
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); //返回的主体数据输出到fp所指向的文件
       // curl_easy_setopt(curl, CURLOPT_HEADERDATA, fp); //返回的头部数据输出到fp所指向的文件

        res = curl_easy_perform(curl); //执行
        printf("get curl res: %d \n",res);
        curl_easy_cleanup(curl);

    }
    //printf("\nbuff : %s\n", buff);
    fclose(fp);
    return 0;
}

*/
