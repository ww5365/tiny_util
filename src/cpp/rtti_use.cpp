#include "../inc/com_use.h"
#include "../inc/rtti_use.h"


void rtti_use_test(){

    ClassDerived *elem = new ClassDerived(3);

    std::string name = elem->get_name();

    std::cout << "rtti name: " << name << std::endl;
}
