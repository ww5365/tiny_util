#include "../inc/com_use.h"
#include <iostream>
#include <vector>

/* 
 * 强类型的枚举 c++11
 * 
 * 1、元素不会自动转化为int类型了
 * 2、可以指定底层的数据存储类型： char 
 * 
 */

enum class Color : char {
    RED,
    YELLOW = 10,
    BLUE,
    WHITE
};

std::ostream& operator << (std::ostream& os, const Color &cl)
{
    return os << static_cast<int>(cl);

}

void enum_use_test(){

    Color cl = Color::BLUE;
    std::cout << "test enum use: " << cl << std::endl;
    return;
}



