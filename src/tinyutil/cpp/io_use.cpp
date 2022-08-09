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



// cin、cin.get()、cin.getline()、getline()的区别

void cin_input_use() {

    // topic1: cin 标准输入流(键盘) cin直接从输入缓冲区取数据的，所以当缓冲区中有残留数据时，cin会直接取得这些残留数据而不会请求键盘输入

    // string str;
    // cout <<"input your name: " << endl;
    // cin >> str;   // wang  wei
    // cout << str << endl; // 输出：wang
    // // cin.sync();//  清空输入缓冲区
    // cout <<"input your ni hao: " << endl;
    // cin >> str; // ni hao
    // cout << str << endl;  // 输出： wei   解决？ 使用sync 清空缓冲区


    // topic2: cin >> var  

    /* 
    变量类型可以为int，float,char,char*,string等诸多类型
    输入结束条件：遇到Enter、Space、Tab键
    对结束符的处理：丢弃不保留在变量中
    */


    // topic3： cin.get(字符数组名, 接手长度，结束符)

    /*

    原型：
    
    istream& get(char& c);
    
    1.读取字符的情况：
    若要读取字符，直接cin.get(char ch)或ch=cin.get()即可。
    输入结束条件：Enter键
    对结束符处理：不丢弃缓冲区中的Enter
    
    原型：
    istream& get(char* s, streamsize n, char delim);
    istream& get(streambuf& sb);
    istream& get(streambuf& sb, char delim)
    2.读取字符串的说明：
    输入结束条件：默认Enter键（因此可接受空格，Tab键），可在第三个参数上自定义结束符
    对结束符处理：默认时Enter，不丢弃缓冲区中的结束符
    */

    //char ch1, ch2;

    //cout <<"please input character A [ENTER] !" << endl;
    //cin.get(ch1);
    //cin.get(ch2); // 输入： a 【enter键】

    //cout << "ch1: " << (int)ch1 << "  ch2: " << (int)ch2 << endl; // 输出a的assicc码  和  enter的asccii码 10

    //char ch3[10], ch4; 
    //cout << "please input abcde!" << endl;
    //cin.get(ch3, 5, 'd');  //  最多接受：5 - 1 = 4 个字符，最后 一个字符时\0； 结束符的标识使用d； 输入：abcde
    //cin.get(ch4);
    //cout << "ch3 result: " << ch3 << " ch4: " << ch4 << endl;

    // topic4: cin.getline(字符数组名, 接手长度，结束符)

    /*
    类似：cin.get   区别

    1、 cin.getline()当输入超长时，会引起cin函数的错误，后面的cin操作将不再执行
    2、cin.get()每次读取一整行并把由Enter键生成的换行符留在输入队列中，然而cin.getline()每次读取一整行并把由Enter键生成的换行符抛弃
    */

    //cin.sync();
    //char ch5, ch6[10];
    //cout << "please input less 5 characters: 1234" << endl;
    //cin.getline(ch6, 5, '3'); // 使用getline时，注意计算输入长度，最多：10- 1 = 9 个字符
    //cout << "ch6 result: "  << ch6 << endl;
    //cin.get(ch5);  // 分割符3被抛弃了
    //cout << "ch5 result: " << ch5 << " ch5 asscii: " << (int)ch5 << endl;


    // topic5: getline(istream is, string str, 结束符)

    /*
    1、它string库函数下，而非前面的istream流，所有调用前要在前面加入#include<string>
    2、方法也不是遇到空白字符(tab, space, enter(当结束符不是默认enter时))就结束输入的，且会丢弃最后一个换行符
    */

    cout <<"input string : abcde " <<endl;

    string str2;
    getline(cin, str2, 'd');

    char ch7 = cin.get();
    cout << "getline str result: " << str2 <<endl;  // 输出abc
    cout << "getline str ch7 : " << ch7 <<endl; // 输出：e  说明d 已经被抛弃了


}







// 输出数据一种新方法: 使用输出流的迭代器
// ostream_iterator( ostream_type& stream, const CharT* delim ) 和某个输出流stream关联,使用delim作为分割输出数据

void stream_output_use_iterator() {

    std::cout << "---stream_output_use_iterator--- " << std::endl;

    std::vector<int> vec = {1,2,3,4}; // 标准输入和输出，输出这个vec，分割符使用逗号

    // 输出到标准输出cout
    std::copy(vec.cbegin(), vec.cend(), std::ostream_iterator<int>(std::cout, ","));
    std::cout << std::endl;

    // 使用for_each
    for_each(vec.cbegin(), vec.cend(), [](const int &elem){ std::cout << elem << ",";});
    std::cout << std::endl;
   
    // 输出到ostringstream : 把int的vector转成字符串，使用逗号分割每个元素;使用输出流迭代器
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

    cin_input_use();



}
