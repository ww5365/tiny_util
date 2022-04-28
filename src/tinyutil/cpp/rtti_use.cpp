#include "../inc/com_use.h"
#include "../inc/rtti_use.h"

#define OUTPUT(f)	cout << #f << "\t: " << typeid(f).name() << endl;

using namespace std;


void rtti_use_test(){

    ClassDerived *elem = new ClassDerived(3);
    std::string name = elem->get_name();
    std::cout << "rtti name: " << name << std::endl;


    
	cout << endl << "---base class has virtual function---" << endl;
 
	BaseB baseB;
	DeriveB deriveB;
    BaseB* pb;
	pb = &baseB; // 基类赋值给基类指针
	OUTPUT(*pb); // 打印基类的类型名称 BaseB
	OUTPUT(pb);  // 打印基类的指针类型名称: BaseB *
	pb = &deriveB; // 把派生类赋值给基类指针，会有运行时多态
	OUTPUT(*pb); // 打印派生类的类型名: DeriveB, 如果BaseB中没有虚函数，这里还是打印基类类名

    std::cout << " real class name: " << typeid(*pb).name() << std::endl; // 真实的类名，字符串不一定和类名完全一致，主要和编译器有关

    if (typeid(*pb) == typeid(DeriveB) ) {
        // 主要可以通过 == 来判断某个对象，是否属于某个类
        std::cout <<"object *pb  class type: " << "DeriveB" << std::endl; 
    }

}
