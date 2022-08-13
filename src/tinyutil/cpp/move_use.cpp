/*
 * mem_use.cpp
 *
 * Created on: Sep 3, 2018
 * Author: wangwei69
 * @brief 描述了与内存使用的功能
 */

#include "com_use.h"
#include <string>
#include <cstring>

using namespace std;


class MyString {
private:
    char *buffer; // 存储字符串
    int s_size;

public:
    MyString() : buffer(nullptr)
    { // 默认的构造函数
        cout << "Default constructor called" << endl;
    }

    MyString(const char *initialInput)
    { // 从一个字符串常量初始化
        cout << "Const constructor called: " << initialInput << endl;

        if (initialInput != nullptr) {
            buffer = new char[strlen(initialInput) + 1];
            strcpy(buffer, initialInput);
        } else
            buffer = nullptr;
    }

    MyString(const MyString &copySrc)
    { // 从另一个对象开始初始化
        cout << "Copy constructor called, copy from: " << copySrc.buffer << endl;

        if (copySrc.buffer != nullptr) {
            buffer = new char[strlen(copySrc.buffer) + 1];
            strcpy(buffer, copySrc.buffer);
        } else
            buffer = nullptr;
    }

    ~MyString()
    {
        cout << "Destroy object:" << (buffer == nullptr ? "nullptr" : buffer) << endl;
        if (buffer != nullptr) {
            delete[] buffer;
        }
    }

    MyString operator + (const MyString &addThis)
    {
        cout << "Operator + called: " << buffer << " + " << addThis.buffer << endl;
        MyString newStr;

        if (addThis.buffer != nullptr) {
            newStr.buffer = new char[strlen(buffer) + strlen(addThis.buffer) + 1];
            strcpy(newStr.buffer, buffer);
            strcat(newStr.buffer, addThis.buffer);
        }
        // cout << "Operator + Get newStr: " << newStr.buffer << endl;
        return newStr;
    }

    MyString &operator = (const MyString &copySrc)
    { // copy assignment op
        cout << "Copy assignment op. copies: " << copySrc.buffer << endl;
        if ((this != &copySrc) && (copySrc.buffer != nullptr)) {
            if (buffer != nullptr)
                delete[] buffer;
            buffer = new char[strlen(copySrc.buffer) + 1];
            strcpy(buffer, copySrc.buffer);
        }

        return *this;
    }

    // 移动构造函数
    MyString(MyString &&moveSrc)
    {
        cout << "Move constructor called, move from: " << moveSrc.buffer << endl;

        if (moveSrc.buffer != nullptr) {
            buffer = moveSrc.buffer;
            moveSrc.buffer = nullptr;
        }
    }

    MyString &operator = (MyString &&moveSrc)
    {
        cout << "Move assignment op. move: " << moveSrc.buffer << endl;
        if ((moveSrc.buffer != nullptr) && (this != &moveSrc)) {
            delete[] buffer;
            buffer = moveSrc.buffer;
            moveSrc.buffer = nullptr;
        }

        return *this;
    }
};


void move_use_test()
{
    // 如果没有右值引用，构造函数被调用的次数

    cout << "begin test mem_use_test --------" << endl;
    MyString strsDefault; // 仅仅创建一个对象
    MyString strsHello = "Hello";
    MyString strsWorld = " World";
    MyString strsCPP = " CPP!";

    strsDefault = strsHello + strsWorld + strsCPP;
    // 没有move构造函时， 构造的次数？
    // hello + word ： 默认构造 + return之前的copy构造(可能会被编译器优化，直接作为上层调用函数的临时变量)
    //  hello word + cpp : 默认构造 +  return之前的copy构造 (如上)
    //  使用 = 的赋值运算

    
    cout << "--------trigger move constructor function -------" << endl;
    MyString g_str("test");
    MyString s = std::move(g_str);

    MyString s2 = MyString("test2");
    MyString s3 = "test3";


    cout << "finish test mem_use_test --------" << endl;

    return;
}
