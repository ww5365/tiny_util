/*
 * read_write.cpp
 *
 *  Created on: 2016年3月23日
 *      Author: wangwei69
 */

#include<stdio.h>
#include "../inc/com_use.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>

using namespace std;


// 输出数据一种新方法: 使用输出流的迭代器

void stream_output_use_iterator() {

    std::cout << "---stream_output_use_iterator--- " << std::endl;

    std::vector<int> vec = {1,2,3,4}; // 标准输入和输出，输出这个vec，分割符使用逗号

    // 输出到标准输出cout
    std::copy(vec.cbegin(), vec.cend(), std::ostream_iterator<int>(std::cout, ","));
    std::cout << std::endl;

    // 使用for_each
    for_each(vec.cbegin(), vec.cend(), [](const int &elem){ std::cout << elem << ",";});
    std::cout << std::endl;
   
    // 输出到ostringstream
    std::ostringstream oStrStream;
    std::ostream_iterator<int> itOss(oStrStream, ",");
    std::copy(vec.cbegin(), vec.cend(), itOss);
    string vec2String = oStrStream.str();
    std::cout << "ostringstream result: " << vec2String << std::endl;
}




/*
 * 使用 STL 的copy实现输入输出？？
 * 靠：。。 老子都看不懂。。
 *
 * 障碍点： 不同的 iterator ？？
 *
 */

int copy_read_write_demo()
{
     typedef vector<int> IntVector;
     typedef istream_iterator<int> IstreamItr;
     typedef ostream_iterator<int> OstreamItr;
     typedef back_insert_iterator< IntVector > BackInsItr;

     IntVector myvector;

     // 从标准输入设备读入整数
     // 直到输入的是非整型数据为止 请输入整数序列，按任意非数字键并回车结束输入
     cout << "Please input element：" << endl;
     copy(IstreamItr(cin), IstreamItr(), BackInsItr(myvector));

     //输出容器里的所有元素，元素之间用空格隔开
     cout << "Output : " << endl;
     copy(myvector.begin(), myvector.end(), OstreamItr(cout, " "));
     cout << endl;

    return 0;
}


/*
 * 使用 c 文件风格进行二进制文件的读写
 *
 * fopen fclose
 * fwrite
 * fread
 * ftell fseek
 *
 */

class PbIO{
public:
    // Constructor
    explicit PbIO(const char* filepath);
    // Destructor
    ~PbIO(){
        if (fp){
            fclose(fp);
        }
        fp = NULL;
    }

    void Rewind() {
        fseek(fp, 0, SEEK_END); //相对于第3个参数的偏移量 SEEK_SET, SEEK_CUR
        m_file_left_byte = ftell(fp);  //返回当前文件指针的位置
        rewind(fp);  //恢复文件指针的位置到开始
    }

    //读入二进制文件
    int WriteMessage(){



    }

    //读入二进制文件
    int ReadMessag(){

        // Check End of File
        if (m_file_left_byte <= sizeof(int) + 1) {
            //ul_writelog(UL_LOG_NOTICE, "[suggestion][End of pb file!]");
            return 0;
        }
       //message->Clear();

        int siz = 0;
        int ret = fread(&siz, sizeof(int), 1, fp);
        if (ret != 1) {
            //ul_writelog(UL_LOG_FATAL, "[suggestion][Failed to read message size]");
            return -1;
        }
        m_file_left_byte -= sizeof(int);

        // Pay attention to buff size.
        char buff[8192];
        ret = fread(buff, sizeof(char), siz, fp);
        if (ret != siz) {
            //ul_writelog(UL_LOG_FATAL, "[suggestion][Failed to read message]");
            return -1;
        }
        m_file_left_byte -= siz;
        //message->ParseFromArray(buff, siz);
        return 1;
}

private:
    //Disallow
    PbIO() {}

private:
    FILE* fp;
    int64_t m_file_left_byte;
};


void read_write_demo(){

    //c 风格： sscanf读入格式化的数字字符串到变量中
    const char *geo = "(123.22,456.33;234.11,567.22)";
    double x1=0,y1=0,x2=0,y2=0;
    sscanf(geo,"(%lf,%lf;%lf,%lf)",&x1,&y1,&x2,&y2);  //读入形如：(1,2;1,2)  这样的数字字符串到变量中
    printf("geo str: %s\n",geo);
    printf("the res is: %f,%f,%f,%f \n",x1,y1,x2,y2);
    
    stream_output_use_iterator();



}
