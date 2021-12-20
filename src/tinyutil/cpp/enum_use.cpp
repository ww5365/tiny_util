#include "../inc/com_use.h"
#include <iostream>
#include <vector>

enum class Color {
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



