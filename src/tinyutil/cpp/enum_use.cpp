#include "../inc/com_use.h"
#include <iostream>
#include <vector>

/* 
 * 强类型的枚举 c++11
 * 
 * 1、元素不会自动转化为int类型了
 * 2、可以指定底层的数据存储类型： char 

规范的建议：
1、使用scoped enum 类型安全的， 避免使用c语言中unscoped enum， 会自动隐式进行数据类型转换int类型；

2、enum class  和  c 语言的 enum的区别

自动类型转换：enum 会自动类型转换成int类型, enum class 编译时会有类型检查的，不允许自动转成int类型
作用域：  enum  中枚举类和枚举项是有相同的作用域，容易造成命名空间的污染；  enum class 是类作用域的；
潜在类型： enum 没有潜在的类型； enum class 默认的潜在类型是int

 
 */


// 定义时指定了： underlying type
enum class Color : char {
    RED,
    YELLOW = 10,
    BLUE
};

enum Color2 : int{
    BLACK,
    WHITE
};

std::ostream& operator << (std::ostream& os, const Color &cl)
{
    return os << static_cast<int>(cl);

}

void enum_use_test(){

    Color cl = Color::BLUE;
    std::cout << "test enum use: " << cl << std::endl;

    
    // enum 类型 会自动转成int； enum class 必须要static_cast；
    // int t1 = Color::RED;   // 编译错误
    int t1 = static_cast<int>(Color::RED);
    int t2 = BLACK;

    std::cout << "enum type conversation: "  << t1  <<  "  " << t2 << std::endl;

    // 命名空间的污染
    constexpr int WHITE = 0;  // Color2中也有WHITE
    std::cout << "name pollution: " << WHITE << std::endl;




    return;
}



