#include <iostream>
#include <map>

using namespace std;

/*
c++ 编程标准示例 : 命名规范

类别    命名    风格形式

* 文件  C++的头文件和源文件名应该和类名保持一致，可以使用大驼峰或者小写下划线风格  AaBb.cpp aa_bb.cpp 
* 命名空间，类类型，结构体类型，联合体类型，枚举类型，typedef 定义的类型      大驼峰      AaaBbb
* 函数（包括全局函数，作用域内函数，成员函数） 大驼峰     AaaBbb
* 宏，枚举值，goto 标签       全大写，下划线分割      AAA_BBB
* 常量（以constexpr或const修饰的，在全局、文件以及namespace域中的对象，或者类的静态成员）   全大写，下划线分  AAA_BBB
* 全局变量（包括全局、文件、namespace域下的变量以及相应作用域下的静态变量）   带 'g_' 前缀的小驼峰    g_aaaBbb
* 类成员变量  在三种小驼峰命名风格中，选择并统一使用一种风格  aaaBbb,m_aaaBbb,aaaBbb_
* 局部变量，函数参数，宏参数，结构体和联合体中的成员变量  小驼峰  aaaBbb

 */

 namespace TestNameSapce{
    // 常量命名示例
    const int NAME_MAX_LEN = 10; // 基本数据类型 大写 + _
    const char* const VERSION = "V100"; // 指向字符串字面量的常量指针
    const char C_STR[] = "c string"; // C字符串常量
    enum class Color { RED, GREEN, BLUE }; // 枚举类型是大驼峰，枚举常量使用全大写下划线分割
    const Color TABLE_COLOR = Color::GREEN;

    namespace Utils { //命名空间是用大驼峰
        const unsigned int DEFAULT_FILE_SIZE_KB = 200; // 全局常量
    }

    class Foo {
        public:
        static const unsigned int DEFAULT_VALUE = 0x55aa; // 静态成员常量
    };

    //类名，结构
    class UrlTable {}; // 类名， 大驼峰
    struct UrlTableProperties {}; //结构体，大驼峰
    union Packet {}; //联合体， 大驼峰
    enum class UrlTableErrors {}; //枚举，大驼峰； 元素是全大写；
    typedef std::map<std::string, UrlTableProperties*> PropertiesMap;  //类型别名，大驼峰命名

    //函数命名：动宾结构  大驼峰

    class List {
    public:
        void AddElement(const Foo& element); //大驼峰，类成员函数名
        Foo GetElement(const unsigned int index) const;
        bool IsEmpty() const;
    };

    //全局变量  g_ + 小驼峰
    int g_activeConnectCount = 0; // 全局变量
    Foo g_someObject{}; // 全局对象
    static int g_blockCount = 0; // 文件作用域中的全局变量
    namespace Utils {
        int g_fileCount = 0; // 命名空间中的全局变量
    }

    //类成员变量   小驼峰 三种 都ok
    class Foo2 {
    private:
        std::string fileName_; //小驼峰 + _
        static int objCount_;
        
        std::string fileName;  //小驼峰

        std::string m_fileName; //m_小驼峰
    };

    //局部变量，函数参数， 宏参数， 结构体和联合体中成员变量   小驼峰

    void Fun(const std::string& fileName) // 符合：函数参数使用小驼峰命名风格
    {
        std::string tableName; // 符合: 小驼峰命名风格
        std::string tablename; // 不符合: name首字母应大写
        std::string path; // 符合: 只有一个单词时，小驼峰为全小写
        static int packetCount = 0; // 符合： 函数局部静态变量，使用小驼峰命名风格
        const unsigned int bufferSize = 100; // 符合： 函数局部常量，使用小驼峰命名风格
    }

 }



