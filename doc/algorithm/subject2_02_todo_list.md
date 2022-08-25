# subject 2 待深入的topic

* 原子操作  第7题
  atomic_bool  
  memory_order

  3.9 -> G.CON.03-CPP 使用C++语言和标准库的机制实现线程安全的单例初始化

  实现double check的单例，使用了atomic变量  +  memory_order   可以参考


* set: set_intersection


* new/delete placement 操作  15题切入


* 什么是functor?  11, 21 为依托
  

* 完美转发 ？

完美转发（perfect forwarding）问题是指函数模板在向其他函数传递参数时该如何保留该参数的左右值属性的问题?

引用折叠规则:

T& &变为T&
T& &&变为T&
T&& &变为T&
T&& &&变为T&&

ref : https://blog.csdn.net/Stranger_CJHan/article/details/69830916

```c++
template <typename ...Args>      // 多个参数模板,可以有多个数据类型
void forward_ref(Args&& ...args) // 多个数据类型，相对应多个可变参数
{
    foo(std::forward<Args>(args)...); //参数包中每个参数的const属性和左值/右值属性都被保持
}
```



```c++
#include <utility>
template <typename ...Args>
void forward_ref(Args&& ...args)
{
    foo(std::forward<Args>(args)...);
}

// 可变参数模板

```
* std::forward  std::move 说明和区别？

std::forward<T>()不仅可以保持左值或者右值不变，同时还可以保持const、Lreference、Rreference、validate等属性不变；

ref: https://www.cnblogs.com/shadow-lr/p/Introduce_Std-move.html



* std::optional<TYPE> 

应用场景：函数返回多个值时    错误的情况下可以返回： std::nullopt;   最终可以返回：0个或多个参数



* std::lock_guard<Mutex> lock(mutexData) 使用？

安全锁机制，lock unlock 不是通过mutexData.lock() 实现， 通过lock_guard<std::Mutex> 来实现
参考规范：3.9  -》 G.CON.02-CPP 不要直接调用mutex的方法


* 自定义类型转换函数


operator 目标类型()
{
函数体
}

该函数没有返回类型，因为返回类型，就是目标类型。

注：
1、类型转换函数只能定义为一个类的成员函数，而不能定义为类的友元函数，可以定义在类内部，也可以定义在类外部
2、类型转换函数既没有参数，也不能在函数名前面指定函数类型。
3、类型函数中必须有return 语句。
4、一个类可以定义多个类型转换函数。


```c++
class Foo {
public:
    
    Foo(string name): myName(name){
        //不加exlicit, string str = "wang";Foo foo = str; 会隐式的把str转化为Foo对象;
        cout << "constructor single parameter" << endl;
    } 
    explicit operator std::string() const {
        cout << "conversation function!" << endl;
        return myName; // 可以把Foo对象转换为string对象: static_cast<string>(foo);
    }
private:
    std::string myName;
};

```


* enum 使用规范

enum class TestEnum {
RED,
YELLOW,
BLUE
};

标准： 建议使用enum class  或  enum  struct   类型安全的枚举类

细节规范参考：enum_use.cpp 

* namespace 使用规范

G.INC.12-CPP 对于cpp文件中不需要导出的变量、常量或函数，应使用匿名namespace封装或者使用static修饰 ，更建议:namespace

G.INC.09-CPP 头文件中禁止向全局命名空间中导入符号, 可以在模块自定义命名空间中以及类、函数等局部作用域中使用它们.


```
// Foo.h
#include <mylib/string>
using namespace mylib; // 不符合：禁止向全局命名空间导入
using mylib::string; // 不符合：禁止向全局命名空间导入符号


// Foo.h
namespace Foo {
using mylib::string; // 符合：可以在模块自定义命名空间中导入符号
void Foo()
{
using namespace mylib; // 符合：在函数作用域内使用using-directive
...
}
}
```

* vector<int> 中标准库的使用

remove, remove_if, remove_copy, remove_copy_if
erease, erease_if


* strdup  

* 线程安全同步
  promise 
  future
  



## gdb


* gdb查看内存数据
  格式: x /nfu  ADDR


## 测试

* 地址消毒 ？

地址消毒技术，一种兼顾性能和功能的新型工具。 地址消毒技术可以找到越界错误（关于堆，栈，全局变量）以及释放后使用错误，仅降低系统73%的运行速度和消耗3.4倍的内存。 这使得它是个全面测试C/C++应用程序的好的选择。 地址消毒技术由两部分组成：一个模块和一个运行时库。


ASAN/KASan，也即地址消毒技术，通过编译插桩，能够发现此3类型问题：内存泄露，堆/栈/全局变量读写溢出，将问题直接打印出来；
ASCan：检测用户态堆，栈，全局变量读写溢出等20多种类错误
KASan：
即Kernel中的ASAN，Kernel Address Sanitizer，是内核中动态检测内存非法访问的工具，可以检测常见的内存访问错误，如：释放后访问（use-after-free），访问越界（out-of-bounds）

LSAN是ASAN的一部分，只做内存泄漏检测。
TSAN：
Thread Sanitizer，即线程消毒，针对C/C++数据竞争检测工具。数据竞争是多线程系统中最常见和最难调试的问题；与ASAN冲突，需单独编译版本；

http://3ms.huawei.com/hi/group/2029293/thread_8461144.html?mapId=10280992

http://3ms.huawei.com/km/groups/2705403/blogs/details/10488871


