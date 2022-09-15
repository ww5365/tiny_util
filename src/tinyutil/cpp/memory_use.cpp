/*
 * mem_use.cpp
 *
 * Created on: Sep 3, 2018
 * Author: wangwei69
 * @brief 描述了与内存使用的功能
 */

#include "com_use.h"
#include <string>
#include <map>
#include <memory>
#include <fstream>
#include <vector>


/*
 * 如何释放容器中，new出来的数据？
 */

void del_new_data_container()
{
    std::map<int, std::string *> map_test;
    std::string *str = new std::string("wang");
    map_test.insert(std::make_pair(1, str));

    // 如何释放str指向
}


/*
RAII : 使用RAII技术管理资源
*/


void ReadFile(const char *fileName)
{
    FILE *fp = std::fopen(fileName, "r");
    if (fp == nullptr) {
        std::cout << "failed to open " << fileName << std::endl;
        return;
    }
    // DoSomething(fp); // 如果抛异常，则文件没有被正确关闭
    fclose(fp);

    // 下面这种方式更好
    std::ifstream ifs(fileName); //file 会在函数结束的时候自动关闭
    if (ifs.fail()) {
        std::cout << "failed to open" << fileName << std::endl;
        return;
    }
    // dosomethin(fp);
}


/*
new 分配内存错误时的处理方式：

当new 操作符以返回nullptr 表示错误时，必须对返回值做空指针检查，否则不要对返回值做空指针检查
当new 操作符可能抛出异常时，按照通常的异常处理方法处理

*/


void Fun()
{
    constexpr int BUFFER_SIZE = 10;
    char* p = new(std::nothrow) char[BUFFER_SIZE];  // new 操作符传入两个参数：不抛异常版本，返回的nullptr,
    if (p == nullptr) { // 如果不加std::nothrow new 抛异常，这里是执行不到的
        std::cout << "failed" << std::endl;
    }
}






/*
动态内存管理：

独享unique_ptr

unique_ptr<T> (new T())

template<class T,     class... Types>
unique_ptr<T> make_unique(Types&&... Args)
{
    return (unique_ptr<T>(new T(forward<Types>(Args)...)));
}

unique_ptr 是可以作为函数的返回值的，控制权发生转移； 也可以作为函数形参，代表这个资源的所有权是从外部移动进来的

相对于先 new 出裸指针再构造 unique_ptr ，直接使用 make_unique 的优点：更明确的避免裸指针和智能指针混用

*/

std::unique_ptr<int> fun(std::unique_ptr<int> para)
{
    return para;
}

void unique_ptr_use()
{
    int *p = new int(4);
    std::unique_ptr<int> p1(p); // 不建议先new，再构造unique；建议使用make_unique；
    std::unique_ptr<int> p2 = std::make_unique<int>(5);

    // std::unique_ptr<int> p3 = fun(p1); // 编译报错，需要使用move发生所有权的转移
    std::unique_ptr<int> p3 = fun(std::move(p1));

    std::cout << "unique_ptr test p3:  " << p3.get() << " p1:  " << p1.get() << std::endl; // p1 为空了
}

void shared_ptr_use()
{

    // 定义一个指向：vector<int> 类型的指针,类似vector<int> *ptr = new vector<int>(3); 定义指向一个vector<int>的指针，并且这个vector<int> 大小初始化为3
    std::shared_ptr<std::vector<int> > ptr(new std::vector<int>(10, 2)); 
    std::cout << "shared ptr point vector<int> size: " << ptr->size() << std::endl;
    std::cout << "shared ptr point vector<int> first elem: " << ptr->at(0)<< std::endl;

    // 定义指向： vector<int> [4] 类型的指针, 类似vector<int> *ptr2 = new vector<int>[3]

    std::shared_ptr<std::vector<int>> ptr2 (new std::vector<int>[3], [](std::vector<int> *p){delete []p;});
    //类似指针使用
    auto realPtr2 = ptr2.get();
    realPtr2[0].push_back(1);
    realPtr2[1].push_back(2);

    std::cout << "ptr2 size---"<< realPtr2[0].size()  << std::endl;

}

void mem_use_test()
{
    unique_ptr_use();
    shared_ptr_use();
}
