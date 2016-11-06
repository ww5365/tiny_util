
/*
#include "curl_mapbox.h"
#include <curl/curl.h>
#include <pthread.h>
#include <string>
#include <iostream>


CHttpClient::CHttpClient(void) :_m_bDebug(false)
{
}

CHttpClient::~CHttpClient(void)
{
}

static int on_debug(CURL *, curl_infotype itype, char * pData, size_t size, void *)
{
    if(itype == CURLINFO_TEXT)
    {
        //printf("[TEXT]%s\n", pData);
    }
    else if(itype == CURLINFO_HEADER_IN)
    {
        printf("[HEADER_IN]%s\n", pData);
    }
    else if(itype == CURLINFO_HEADER_OUT)
    {
        printf("[HEADER_OUT]%s\n", pData);
    }
    else if(itype == CURLINFO_DATA_IN)
    {
        printf("[DATA_IN]%s\n", pData);
    }
    else if(itype == CURLINFO_DATA_OUT)
    {
        printf("[DATA_OUT]%s\n", pData);
    }
    return 0;
}

static size_t on_write_data(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
    std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);  //两次数据类型转换？
    if( NULL == str || NULL == buffer )
    {
        return -1;
    }

    char* pData = (char*)buffer;
    str->append(pData, size * nmemb);
    return nmemb;
}

int CHttpClient::post_http(const std::string &strUrl, const std::string &strPost, std::string &strResponse)
{
    CURLcode res;
    CURL* curl = curl_easy_init();
    if(NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }
    if(_m_bDebug)
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, on_debug);
    }
    curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPost.c_str());
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, on_write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}

int CHttpClient::get_http(const std::string &strUrl, std::string &strResponse)
{
    CURLcode res;
    CURL* curl = curl_easy_init();
    if(NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }
    if(_m_bDebug)
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, on_debug);
    }
    curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, on_write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);


    //当多个线程都使用超时处理的时候，同时主线程中有sleep或是wait等操作。
    //如果不设置这个选项，libcurl将会发信号打断这个wait从而导致程序退出。


    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}

int CHttpClient::post_https(const std::string & strUrl, const std::string & strPost, std::string & strResponse, const char * pCaPath)
{
    CURLcode res;
    CURL* curl = curl_easy_init();
    if(NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }
    if(_m_bDebug)
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, on_debug);
    }

    curl_easy_setopt(curl, CURLOPT_PROXY, "10.242.95.15:8088"); //设置代理
    curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPost.c_str());
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, on_write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    if(NULL == pCaPath)
    {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    }
    else
    {
        //缺省情况就是PEM，所以无需设置，另外支持DER
        //curl_easy_setopt(curl,CURLOPT_SSLCERTTYPE,"PEM");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
        curl_easy_setopt(curl, CURLOPT_CAINFO, pCaPath);
    }
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}

int CHttpClient::get_https(const std::string &strUrl, std::string &strResponse, const char *pCaPath)
{
    CURLcode res;
    CURL *curl = curl_easy_init();  //得到 easy interface型指针
    if(NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }
    if(_m_bDebug)
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, on_debug);
    }
    curl_easy_setopt(curl, CURLOPT_PROXY, "10.242.95.15:8088"); //设置代理,使用代理访问
    curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, on_write_data); //设置传回数据的处理回调函数
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    if(NULL == pCaPath)
    {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    }
    else{
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
        curl_easy_setopt(curl, CURLOPT_CAINFO, pCaPath);
    }
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3L); //设置连接等待时间,单位：秒
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3L);  //设置传输时间
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);  //释放内存
    return res;
}


void CHttpClient::set_debug(bool bDebug)
{
    _m_bDebug = bDebug;
}

#define NUM 4

const char *urls[NUM] = {
        "http://api.mapbox.com/geocoding/v5/mapbox.places/%E5%8C%97%E4%BA%AC%E5%A5%8E%E7%A7%91%E7%A7%91%E6%8A%80%E5%A4%A7%E5%8E%A6.json?access_token=sk.eyJ1Ijoid3c1MzY1IiwiYSI6ImNpbGx5aGhqdDY0czd1dW1jaTA1eWVrdGUifQ.L66B41d7fz0x6iKjb93tjQ",
        "http://api.mapbox.com/v4/directions/mapbox.driving/99.948462,13.798207;100.159599,13.814642.json?access_token=pk.eyJ1IjoiZmVuZ3hpYW9rZSIsImEiOiJjaWxsdmp2OXI2MjYydnJtMHpsOGNzZ2xlIn0.1JWShDIuGXTlvnqTYnJbtw",
        "http://api.mapbox.com/v4/directions/mapbox.walking/99.948462,13.798207;100.159599,13.814642.json?access_token=pk.eyJ1IjoiZmVuZ3hpYW9rZSIsImEiOiJjaWxsdmp2OXI2MjYydnJtMHpsOGNzZ2xlIn0.1JWShDIuGXTlvnqTYnJbtw",
        "http://api.mapbox.com/v4/directions/mapbox.driving/-122.42,37.78;-75.03,38.00;-77.03,38.91.json?alternatives=false&access_token=pk.eyJ1IjoiY2FybGd1byIsImEiOiJjaWxtMDFnNDE2NWppdm5tYzgya25kcm5sIn0.d4ipm_OLrXhvjSSyF45C_A"
};

static void * pull_one_url(void *url){

    CHttpClient client;
    std::string res;
    std::string str_url((const char *)url);
    client.get_https(str_url,res);

    std::cout << "------------------------------https access result --------------------------------------"<<std::endl;
    std::cout << res <<std::endl;
}



int main(int argc,char*argv[]){

    //多线程的访问？
    pthread_t tid[NUM];
    int i ,error;
    curl_global_init(CURL_GLOBAL_ALL);

    for(i=0; i<NUM; i++){
        error = pthread_create(&tid[i],
                               NULL,
                               pull_one_url,
                               (void *)urls[i]);

        if(0 != error){
            fprintf(stdout,"can not run thread:%d\n",i);
        }else{
            fprintf(stdout,"thread %d,gets %s\n",i,urls[i]);
        }
    }

    for(i=0; i<NUM; i++){
        error = pthread_join(tid[i],NULL);
        fprintf(stderr,"thread %d terminated",i);
    }

    curl_global_cleanup();

    return 0;

}


*/























