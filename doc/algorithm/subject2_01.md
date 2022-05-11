# subject 2 



##


1、如果想要定义Rational类的乘法操作符重载，且要求支持连乘操作，以下实现方法中正确的是（）

```  c++

A.
const Rational& operator*(const Rational& lhs, const Rational& rhs)
{
　　Rational result(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
　　return result;  //返回局部变量的地址：返回类型是对象的引用，局部变量释放导致返回引用悬空
}
B.
Rational operator*(const Rational& lhs, const Rational& rhs)
{
　　return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
} // ok   

//性能的讨论：主流的编译器几乎都会在打开了优化选项的情况下对其进行优化，使得返回时不发生对象拷贝。

C.
const Rational& operator*(const Rational& lhs, const Rational& rhs)
{
　　Rational* result = new Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
　　return *result; // 返回new创建的对象但未保证释放：返回类型是对象的引用，heap上对象不会悬空；但Rational c = a * b 会导致a*b的临时对象的指针丢失，造成内存泄漏；同时，禁止将局部变量的地址返回到其作用域以外。
}
D.
const Rational& operator*(const Rational& lhs, const Rational& rhs)
{
　　std::shared_ptr result = std::make_shared(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
　　return *(result.get()); //误用智能指针: get 返回对象的原始指针，返回类型是引用，管理指针计数器不会增加1，导致函数结束后，指向悬空了。 
　　// 使用智能指针时，应当尽量避免取出原始指针或取出内部保管的对象的引用，同时还要避免使用智能指针类型的引用。只有这样才能充分发挥智能指针自动管理生命周期的作用，减少编码错误. 
　　//同时不能支持连乘的实现
}

```
>>  1、智能指针：shared_ptr<TYPE> ptr = shared_ptr<TYPE>(new TYPE(..));  ptr.get() //获取原始指针，计数器不加1



## subject 2真题 

1、使用rand()产生随机数适用的场景，类似的还有random()和/dev/urandom()也是不安全的。

因为rand()生成的随机数是**可预测的**。

比如如果随机数的种子是一样的，那么rand()产生的随机数的顺序和数值都是一摸一样的涉及安全性和要求具有不确定性的场景都不能使用该函数来产生随机数，如：

* SessionID的生成
* 挑战算法中的随机数生成
* 验证码的随机数生成
* 生成重要随机文件（存有系统信息等的文件）的随机文件名
* 和生成密钥相关的随机数生成

而对于随机性测试如**随机路由、网卡驱动随机丢包算法**等场景则可以使用。

安全的随机数方式包括：

Unix/Linux下采取建议读取/dev/random文件来获取真随机数
Windows推荐使用随机数生成函数CryptGenRandom()
对于可靠性要求很严格的产品可以使用开源组件openssl或我司中研封装的iPSI组件
硬件随机数

>>> 补充： 
>>> /dev/random 与 /dev/urandom 的区别
>>> * /dev/random 是真随机数生成器，它会消耗熵值来产生随机数，同时在熵耗尽的情况下会阻塞，直到有新的熵生成.
>>> * /dev/urandom 是伪随机数生成器，它根据一个初始的随机种子(这个种子来源就是熵池中的熵)来产生一系列的伪随机数，而并不会在熵耗尽的情况下阻塞。
>>> 熵的说明：
>>> * cat /proc/sys/kernel/random/poolsize  # 查看系统熵池的容量
>>> * cat /proc/sys/kernel/random/entropy_avail  # 查看系统熵池中拥有的熵数
>>> * cat /proc/sys/kernel/random/read_wakeup_threshold  # 查看从熵池中读取熵的阀值
>>> linux是根据系统的熵池来产生随机数的。熵池就是系统当前的环境噪音,环境噪音的来源很多，键盘的输入、鼠标的移动、内存的使用、文件的使用量、进程数量等等

  

2、 代码语义准确

* 尽量不使用非bool变量来做bool判断，会造成语义不准确
* 有符号整数运算要保证结果不出现溢出，无符号整数运算时要保证结果不出现反转
* 无符号数左移右移都是填0，有符号数左移填0，右移看符号，正号填0，负号填1。
* 应当避免对有符号整数使用位操作符运算，对有符号数做左移操作，其结果是不确定的，禁止进行此操作

>>> 补充：
>>> 思考下为什么对有符号的数做<<操作，是需要禁止的？ 首位可能是1，被移掉了


3、代码命名风格

![name regular](../img/name_regular.png)

>>关注：枚举类型 枚举值
>> 枚举类型： 大驼峰
>> 枚举值：  全大写，下划线分割；  


4、静态成员变量

静态成语变量的初始化需要放到类外进行，在类的作用域之外进行初始化，如在include对应的头文件之后进行初始化，再进行类方法的实现

静态常量成员可以放在类内定义并进行初始化，static const

>>补充 : 实例演示

```

class Test {
private:
    static int a;  // 静态成员变量； 类体外进行初始化
    static const int b; //  静态常量整型成员变量声明
    static const int c = 3; //  静态常量整型成员变量定义
}

// 类体外进行初始化
int Test::a = 1;
const int Test::b = 2;

```


5、类型转换

结论：dynamic_cast上行转换一定成功，下行转换需要派生类有基类的虚函数，否则将转换失败。
在进行上行转换时，dynamic_cast和static_cast的效果是一样的；在进行下行转换时，dynamic_cast具有类型检查的功能，比static_cast更安全
派生类中需要检测有虚函数的原因：类中存在虚函数，就说明它有想要让基类指针或引用指向派生类对象的情况，此时转换才有意义。

C++常用转换的总结：

dynamic_cast ：主要用于继承体系下行转换，该转换具有类型检查的功能。应做好基类和派生类的设计，合理使用dynamic_cast:
dynamic_cast 的出现一般说明基类和派生类设计出现了问题，派生类破坏了基类的契约，不得不通过 dynamic_cast 转换到派生类进行特殊处理，这个时候更希望来改善类的设计，而不是通过 dynamic_cast 来解决问题。
如果强制转换不可避免，则应优先使用 dynamic_cast ，而不是使用 static_cast ，因为编译器将在运行时检查强制转换的有效性。
static_cast ：和C风格转换相似可做值的强制转换，或上行转换(把派生类的指针或引用转换成基类的指针或引用)。如果是纯粹的算数转换，那么可以使用大括号初始化方式转换。
reinterpret_cast ：用于转换不相关的类型，是一种不安全的转换，应尽量少用。
const_cast ：用于移除对象的 const 属性，使对象变得可修改，这样会破坏数据的不变性，应尽量少用。

>> 补充：
>> 上行转换：基类 <- 派生类      下行转换：基类 -》 派生类 


6、类型转换的性质

* dynamic_cast的出现一般说明我们的基类和派生类设计出现了问题，派生类破坏了基类的契约
* reinterpret_cast用于转换不相关指针类型，不同指针类型之间应尽量避免转换
* const_cast用于移除对象的const性质，不保留volatile性质
* static_cast可以将void指针转换为任意其他类型指针

>> 补充： 了解下 cons_cast  会把变量的: const 和  volatile 属性都拿掉


7、原子操作

* bool操作并非是不可分割的，它不是原子操作，若需要使用原子操作，可以用std::atomic_bool
* 原子操作通常比加锁性能要高，它是实现无锁算法的基础
* 使用原子操作需要使用合适的memory_order

8、运算符重载

1.C++中不能被重载的运算符有：
* 类属关系运算符"."
* 成员指针运算符".*"
* 作用域运算符"::"
* sizeof运算符
* 三目运算符"?:"
  
2.运算符函数重载一般有两种形式：重载为类的成员函数和重载为类的非成员函数。非成员函数通常是友元。
* 注意：也可以把一个运算符作为一个非成员、非友元函数重载，但此时运算符无法直接访问类的私有和保护成员。
* 当运算符重载为类的成员函数时，函数的参数个数比原来的操作数要少一个（后置单目运算符除外），这是因为成员函数用this指针隐式地访问了类的一个对象，它充当了运算符函数最左边的操作数。
* 当运算符重载为类的友元函数时，由于没有隐含的this指针，因此操作数的个数没有变化，所有的操作数都必须通过函数的形参进行传递，函数的参数与操作数自左至右一一对应。

3.成员函数运算符与友元函数运算符自的特点
* 一般情况下，单目运算符最好重载为类的成员函数；双目运算符则最好重载为类的友元函数。
* 不能重载为类的友元函数的双目运算符： = 、()、[]、 ->
* 类型转换函数只能定义为一个类的成员函数而不能定义为类的友元函数
* 若一个运算符的操作需要修改对象的状态，选择重载为成员函数较好
* 若运算符所需的操作数（尤其是第一个操作数）希望有隐式类型转换，则只能选用友元函数
* 当运算符函数是一个成员函数时，最左边的操作数（或者只有最左边的操作数）必须是运算符类的一个类对象（或者是对该类对象的引用）。如果左边的操作数必须是一个不同类的对象，或者是一个内部类型的对象，该运算符函数必须作为一个友元函数来实现
* 当需要重载运算符具有可交换性时，选择重载为友元函数

>>> 运算符重载： 重载为成员函数 或  非成员函数 (友元)


9、初始化列表的初始化顺序

1.成员是按照他们在类中声明的顺序进行初始化的，而不是按照他们在初始化列表出现的顺序初始化的
2.内置类型变量是否自动初始化取决于变量定义的位置。函数体外定义的变量初始成0；函数体内定义的变量不进行自动初始化。类的成员变量会调用类的默认构造函数来进行初始化，若显式定义了构造函数，则编译会报错。



10、C++11关键字

* 使用auto来避免冗长的类型名，但是auto会忽略引用，此外还会忽略顶层const（但保留底层const），若希望保留顶层const，则需要指出：
  `const auto value = historyValue;`

* decltype，C++的第二种类型说明符，与auto的区别是通过表达式解析要使用的类型，但不会实际进行表达式的计算。此外保留了const与引用特性。

* decltype(f()) sum = x;// sum的类型就是函数f的返回值类型。  
* override需要紧跟在函数名之后，分号之前
  >> 作用：在成员函数声明或定义中， override 确保该函数为虚函数并覆写来自基类的虚函数。
  >> 1．可以当注释用,方便阅读;告诉阅读你代码的人，这是方法的复写
  >> 2．编译器可以给你验证 override 对应的方法名是否是你父类中所有的，如果没有则报错．
* 空指针应该使用nullptr而不是NULL


11. 模板与静态变量

``` c++

	template<typename T, typename F>
	T Use(T v, F f)
	{
	    static int count = 0;
	    count++;
	    std::cout << "now count = " << count << std::endl;
	    return f(v);
	}
	 
	class Fp {
	private:
	    double z_;
	public:
	    Fp(double z = 1.0)  :  z_(z) {}
	    double operator()(double p) { return z_*p; }
	};
	 
	double Dub(double x) { return 2.0 * x; }
	double Square(double x) {return x * x;}
	 
	int main()
	{
	    double y = 1.0;
	    cout << "Function Dub”;
	    Use(y, Dub);
	    cout << "Function Square";
	    Use(y, Square);
	    cout << "object Fp";
	    Use(y, Fp(5.0));
	    cout << "Lambda Fp";
	    Use(y, [](double u) { return u * u; });
	    cout << "Lambda Fp";
	    Use(y, [](double u) { return u * u; });
	}
// 输出

	Function Dubnow count =1
	Function Squarenow count =2
	Object Fpnow count =1
	Object Fpnow count =2
	Lambda Fpnow count =1
	Lambda Fpnow count =1

```

这题考察的主要知识点是函数模板实例化。即：若在**模板中定义静态变量，相同类型的模板共享同一个静态变量**。

* Dub和Square都属于函数指针，且函数签名相同，所以Use(y, Dub)和Use(y, Square)调用的是模板实例化出的同一个函数。

* 而Fp是一个functor，它和函数指针不是一个类型，Use(y, Fp)调用的和上面的不是同一个函数。
  >> 什么是functor? https://marquistj13.github.io/MyBlog/ReadingNotes/ProgrammingSkills/cplusplus/basic%20concepts%20%20functor

  >> 定义一个函数之后，函数名就是函数指针；而functor只是一个object（对象）。
  >> functor可以有状态，而普通的函数没有状态的概念.

* 最后是lambda表达式，lambda表达式是一个匿名类型，即使完全相同的代码写两次，编译器都会为你生成出2个不同的闭包类型。


12.对象不能多态

多态的原理，当基类成员函数用virtual修饰时：

* 基类大小多出来4个字节，即一个指针，指向虚函数表（函数指针数组，元素为函数地址）
* 派生类会继承基类的虚函数表
* 如果派生类有重写，那么重写的函数地址会覆盖虚函数表中基类的该函数的地址。
* 调用函数时，回去虚函数表中找到函数。
* 但类对象的虚函数指针永不会变，永远都指向所属类的虚函数表
* 只有当使用指针或引用时，虚函数指针才会指向继承类的虚函数表
  
  >> 1. 对象无法多态，指针或引用才能多态
  >> 2. 依赖虚函数表来实现多态，同时基类中有virtual函数，那么至少占用了4个字节

多态的动态调用：

```c++
	class Base {
	public:
	    virtual void Func(){ cout << "Base" << endl; }
	};
	 
	class Derived : public Base{
	public:
	    virtual void Func(){ cout << "Derived" << endl; }
	};
	 
	typedef void (Base::*Pfunc)();
	 
	int main()
	{
	    Base* rb = new Derived;
	    rb->Func(); // 指向派生类对象的基类指针，调用派生类的方法
	    rb->Base::Func(); // 使用基类类名修饰，则调用基类的方法
	    Pfunc pfn = &Base::Func;
	    (rb->*pfn)(); //同样可以多态？ 这个我的理解是：印证了【如果派生类有重写，那么重写的函数地址会覆盖虚函数表中基类的该函数的地址】 这个条规则
	    delete rb;
	    return 0;
	}
	// 输出：Derived Base Derived
```

虚函数绑定: 
* 两个层面的绑定： 运行时函数绑定 -- 动态绑定;  虚函数参数的绑定 -- 静态绑定，编译期间。

``` c++
	class Fruit {
	public:
	    Fruit() {}
	    virtual ~Fruit() {}
	    virtual void Foo(int value = 1) {
	        std::cout << "Fruit:" << value << endl;
	    };
	};
	 
	 class Apple : public Fruit {
	     public:
	     Apple() {}
	     virtual ~Apple() {}
	     virtual void Foo(int value = 2)
	    {
	        std::cout << "Apple:" << value << endl;
	    };
	 };
	 
	 int main()
	 {
	     Apple oneApple;
	     Fruit *fruit = &oneApple;
	     Apple *apple = &oneApple;
	     fruit->Foo();
	     apple->Foo();
	     return 0;
	 }
    //  输出： Apple: 1  Apple: 2
	// fruit的静态类型是Fruit的引用，而动态类型是Apple的引用，因此，当fruit调用虚函数Foo()时，根据动态绑定规则，它调用的是Apple的成员函数Foo()；而对于虚函数的缺省参数，根据静态绑定规则，它将value确定为Fruit中给出的缺省值1。

```

虚函数定义规则：
派生类的函数需要与基类的函数定义相同，能够满足override关系。包括以下几种不符合的情况：
* 是否有const。有const则多态失效。
* 函数返回值不同
* 函数参数列表不同等都是判断条件

12.  智能指针引用计数

1).智能指针引用计数: shared_ptr
每个shared_ptr所指向的对象都有一个引用计数，它记录了有多少个shared_ptr指向自己
shared_ptr的析构函数：递减它所指向的对象的引用计数，如果引用计数变为0，就会销毁对象并释放相应的内存
引用计数的变化：决定权在shared_ptr，而与对象本身无关

引用计数增加的情况
拷贝一个shared_ptr，其所指对象的引用计数会递增，如：
* 用一个shared_ptr初始化另一个shared_ptr
* 用一个shared_ptr给另一个shared_ptr赋值
* 将shared_ptr作为参数传递给一个函数
* shared_ptr作为函数的返回值

引用计数减少的情况
给shared_ptr赋予一个新值
shared_ptr被销毁（如离开作用域）

2). unique_ptr

std::unique_ptr 是 c++11中用来取代 std::auto_ptr 指针的指针容器。 它不能与其他unique_ptr类型的指针对象共享所指对象的内存。这种所有权仅能够通过std::move函数来转移。unique_ptr是一个删除了拷贝构造函数、保留了移动构造函数的指针封装类型。

* 调用release 会切断unique_ptr 和它原来管理的对象的联系。
* release 返回的指针通常被用来初始化另一个智能指针或给另一个智能指针赋值。
* 如果不用另一个智能指针来保存release返回的指针，程序就要负责资源的释放。

``` c++
#include <memory>
int main() {
        std::unique_ptr<int> uptr(new int(10));  //绑定动态对象
        //std::unique_ptr<int> uptr2 = uptr;  //不能賦值
        //std::unique_ptr<int> uptr2(uptr);  //不能拷内
        std::unique_ptr<int> uptr2 = std::move(uptr); //轉換所有權

        if(uptr == nullptr)
            printf("uptr give up *int\n");

        int * p = uptr2.release(); //uptr2释放对指针的控制权，返回指针，并将uptr2置为空
        if(uptr2 == nullptr)
          printf("uptr2 give up *int\n");
        printf("%d\n", *p);
        delete p;
        return 0;
}

```

13.  tuple

tuple是一个固定大小的不同类型值的集合，是泛化的std::pair，比pair功能更强大，不但可以存储和pair相同的2个元素，也可以存储三个及三个以上的不同类型的元素

``` c++
	std::tuple<T1, T2, TN> t1;            //创建一个空的tuple对象（使用默认构造），它对应的元素分别是T1和T2...Tn类型，采用值初始化。
	std::tuple<T1, T2, TN> t2(v1, v2, ... TN);    //创建一个tuple对象，它的两个元素分别是T1和T2 ...Tn类型; 要获取元素的值需要通过tuple的成员get<Ith>(obj)进行获取(Ith是指获取在tuple中的第几个元素，请看后面具体实例)。
	std::tuple<T1&> t3(ref&); // tuple的元素类型可以是一个引用
	std::make_tuple(v1, v2); // 像pair一样也可以通过make_tuple进行创建一个tuple对象
	 
	// tuple的元素为引用
	std::string name;
	std::tuple<string &, int> tpRef(name, 30);
	// 对tpRef第一个元素赋值，同时name也被赋值 - 引用
	std::get<0>(tpRef) = "Sven";
	 
	// name输出也是Sven
	std::cout << "name: " << name << '\n';


    // 和结构体的使用方法相同
   	struct person {
	    char *m_name;
	    char *m_addr;
	    int  *m_ages;
	};
	 
	//可以用tuple来表示这样的一个结构类型，作用是一样的。
	std::tuple<const char *, const char *, int *>

    // get<TYPE/Ith>(tuple_var_name)
    std::tuple<int, std::string> tl{ 1, "qwer" };
    constexpr std::tuple<int, void*> t2{ 10, nullptr };
    std::tuple<int, char, std::string> t3{ 1, 't', "qwer" };
    std::cout << std::get<0>(tl) << std::endl;
    constexpr int n2 = std::get<0>(t2);
    auto s = std::get<char>(t3);

```
>> tuple：定义，初始化， 访问


14. 函数重载

函数重载的定义：只有参数列表不同（参数个数、参数类型、参数顺序），其它都保持一致，其中参数命名以及参数是否有默认值的区别不算在内

>> 返回值可以相同也可以不同； 仅仅只有返回值不同，不是函数重载；

>> 注意：函数返回值不同，对多态，特别是override修饰的接口有影响



15.new/delete

* new和delete操作符是对堆中的内存进行申请和释放，而这两个都是不能被重载的。要实现不同的内存分配行为，需要重载operator new函数和operator delete函数，而不是new和delete

* 使用new实例化一个过象，涉及三个步骤：调用operator new()函数分配内存; 调用类对应的构造函数;返回指向新分配并构造的对象的指针

* 在已分配的缓冲区上new对象，C++称之为placement new，如下代码：

```c++
class Task;
char buf[sizeof(Task)]; // 缓存提前分配
Task *task = new (buf) Task; //在已分配内存上new对象，并不会申请内存; 感觉上，只有new操作的后两步隐含操作
task->suspend(); // 按照普通方式使用分配的对象
...
task->~Task(); //调用外在的析构函数来销毁对象
delete [] buff; //若需要反复利用缓存则重复以上步骤，否则就调用该语句来释放缓存
```
其中，第三行的new并未申请内存，只是调用了构造函数，返回一个指向已分配好的内存的一个指针，因此销毁时不必delete释放空间，但必须调用析构函数来销毁对象。若不再使用就释放缓存，否则重复分配缓存创建对象、使用对象及销毁对象即可。

* malloc/free只是动态分配内存空间/释放空间，而new/delete除了分配空间还会调用构造函数和析构函数进行初始化与清理

>> 1、不了解placement new 机制？ 不了解 operator new / operator delete ?
>> 用定位放置new操作，既可以在栈(stack)上生成对象，也可以在堆（heap）上生成对象。如本例就是在栈上生成一个对象。
>> new 运算符，对应了后面的多步动作


16.线程

* detach:将当前线程对象所代表的执行实例与该线程对象分离，使得线程的执行可以单独进行。一旦线程执行完毕，它所分配的资源将会被释放。
* join：调用该函数会阻塞当前线程，阻塞调用者所在的线程直至被join的std::thread对象//标识的线程执行结束
* std::thread是可移动的，不可拷贝。在std::thread对象之间转移线程所有权使用sd::move函数
* RAII 是 resource acquisition is initialization 的缩写，意为“资源获取即初始化”。它是 C++ 之父 Bjarne Stroustrup 提出的设计理念，其核心是把资源和对象的生命周期绑定，对象创建获取资源，对象销毁释放资源。在 RAII 的指导下，C++ 把底层的资源管理问题提升到了对象生命周期管理的更高层次。

以下关于std::thread线程使用，描述正确的是C
A．一个已经被detach的线程对象可以再次被detach。（无法重复detach。已经脱离管控了，没法再脱离一次。）
B．一个已经被join的线程对象可以再次被join。（无法重复join，join一次之后，正在执行的线程已经不是当前调用join的线程了，无法再腾出资源了。）
C．为了防止忘记调用join或detach，我们可以使用RAll技法管理线程的回收。
D．在对线程std::thread对象进行管理时，可以通过std::copy和std::move实现。（可移动，不可拷贝）


17.fopen与open的区别:

* fread是带缓冲的,read不带缓冲.
* fopen是标准c里定义的,open是POSIX中定义的.
* fread可以读一个结构.read在linux/unix中读二进制与普通文件没有区别.
* fopen不能指定要创建文件的权限.**open可以指定权限. **（对于权限敏感的文件，需要给定一个具体的权限范围）
* fopen返回文件指针,open返回文件描述符(整数).
* linux/unix中任何设备都是文件,都可以用open,read.


18. 数组指针

```c++
#include <stdio.h>
int main()
{
    int a[5] = { 1, 2, 3, 4, 5 };
    int *p = (int*)(&a + 1);
    printf("%d, %d", *(a + 1), *(p - 1));
    return 0;
}
```

a：指向数组第一个元素的指针，a + 1则指向第二个元素，即为2
&a：指向数组的指针，即p指向包含5个int元素的数组，p+1后p的偏移量相当于p+sizeof(int)*5
将p转为int*后，p-1就是p – sizeof(int)，因此最后得到的是数组最后一个元素5

输出：2， 5

19. 枚举

```c++

	// 普通枚举：隐式转换为int，同一作用域下，元素不允许重复
	enum State { DEFAULT, RUNNING, STOP };
	constexpr int DEFAULT = 1; // 编译错误：'DEFAULT' already declared in this scope
	// 枚举类：不允许隐式转换为int，同一作用域下，元素允许重复;类作用域
	enum class State { DEFAULT, RUNNING, STOP };
	constexpr int DEFAULT = 1;

```
>> 类作用域；不允许隐式类型转化


20.数组拷贝

```c++
	A、
	void ParseMsg(unsigned char *msg)
	{
	    (void)strcpy_s(msg, str1en(msg) + 1, "world");
	}
	B、
	void ParseMsg(unsigned char *msg， size_t msgLen)
	{
	    ...
	}
	C、
	void SaveName(char *name, size_t len, const char *inputName)
	{
	    int ret = strcpy_s(name, len, inputName);
	    ...
	}
	D、
	void SearchName(const char *name)
	{
	   ...
	}
```
按照规范：
1） 涉及到数组拷贝的，都需要在参数中传入数组长度
2） 若不涉及字符串拷贝，只使用该字符串，可以不需要传数组长度


21.函数对象

函数对象也叫函数符(是不是就是functor)，**函数符**是可以以函数方式与()结合使用的任意对象。这包括 **函数名、指向函数的指针和重载了()运算符的类对象**。即函数名、指向函数的指针和重载了括号运算符的类对象与括号结合，从而以函数方式实现某种功能。

包括以下几种：

重载了括号操作符()的函数类

``` c++
class FuncObjType
{
public:
    void operator() ()
    {
        cout<<"Hello C++!"<<endl;
    }
};
```
对于该类的对象，可以和函数完全一样的调用方式，相比较函数，函数对象有以下优势：

* 函数对象可以有自己的状态。我们可以在类中定义状态变量，这样一个函数对象在多次的调用中可以共享这个状态。但是函数调用没这种优势，除非它使用全局变量来保存状态。
* 函数对象有自己特有的类型，而普通函数无类型可言。这种特性对于使用C++标准库来说是至关重要的。这样我们在使用STL中的函数时，可以传递相应的类型作为参数来实例化相应的模板，从而实现我们自己定义的规则。
>> 比如：sort(vec.begin(), vec.end(), less<int>()); // 指定某种类型到模板类中

Lambda表达式

代码在编译时，lambda表达式会自动转变成一个类——它每一个成员变量都对应着一个捕获的变量。这个类根据lambda表达式的参数列表重载了operator()

std::function类
当你需要一个非模板函数对象作为类的成员或者函数参数时，你必须指定函数对象的具体类型。C++中的函数对象并没有一个基类，但是标准库提供了一个模板类std::function来代表所有的函数对象。

从一般的函数回调意义上来说，函数对象和函数指针是相同的，但是函数对象却具有许多函数指针不具有的有点，

函数对象使程序设计更加灵活
能够实现函数的内联（inline）调用，使整个程序实现性能加速
函数对象可以在几次调用之间保持状态


>> function: 这个类来代表所有的函数对象..



22.内联函数

内联函数和模板的声明、定义都放在头文件中
在class/struct/union定义内定义的成员函数，为隐式的inline函数。如：

```c++
class Person {
...
   int GetAge() const { return age_; }  
};
```
关键词inline的含义是非强制的，编译器拥有对标记为inline的函数生成函数体的自由；也有对不标记为inline的函数使用内联替换的自由
内联函数中static修饰的对象，不同cpp文件中并不共享


23.迭代器失效

* vector和deque是序列式容器，进行元素的增删操作（erase insert push_back）之后，迭代器将失效
* 对于关联式容器，删除当前的iterator仅会使当前的iterator失效，在erase时递增当前的iterator即可
>> 对应了之前的:如何循环的删除：vector 或  map中的元素 ?


24. constexpr  常量表达式

constexpr： 主要是给编译器用的，明确告诉编译器可以把变量认为是：字面长量   
* 编译期间就可以确定值；
* 编译时就能得出常量值的表达式去优化

const： 编译或运行期间确定值

```c++
constexpr int Foo(int i)
{
	return i + 5; // 这种状态，不会报错，编译器不完全相信用户，传参一定是字面常量； 参数是一个常量字面值的时候，编译器才会去对其做优化，否则，依然会将计算任务留给运行时。
}

std::array<int, Foo(5)> arr; // ok
int i = 5;
std::array<int, Foo(i)> arr; // 不可以，因为array<T, N>必须在编译期间就要确定其大小N
```




24. 完美转发  ??
 
（单选）模板函数，下列哪个选项是错误的
template <typename …Args>
void ForwardRef(Args&& …args)
{
    Foo(std::forward<Args>(args)…);
}
A.	如果参数中有const T&，则Foo接受的参数类型为const T&
B.	如果参数中有T&&，则Foo接受的参数类型为T&&
C.	如果参数中有T，则Foo接受的参数类型为T&
D.	如果参数中有T&，则Foo接受的参数类型为T&&

（多选）模板函数，下列哪个选项是正确的
template <typename …Args>
void ForwardRef(Args&& …args)
{
    Foo(std::forward<Args>(args)…);
}
A.	将入参T解释为T
B.	将入参T&&解释为T&&
C.	将入参T解释为T&
D.	将入参T&解释为T&&


补充：规范：

要被完美转发的参数使用“转发引用”类型，并在函数内使用std::forward
如果一个函数参数类型为T&& 并且T 是模板的类型参数，则该参数传递时将会保持调用者所传参数类型
的 const 属性和左值/右值属性。这种类型应当只被用于完美转发——即函数需要保留入参的 const 属
性和左值/右值属性，并且将入参用std::forward 转给需要区分这些属性的另一个函数。


要被移动的参数，应使用右值引用类型，并在函数内使用std::move;
对于只能被移动，并且移动的代价很小的类型，如std::unique_ptr，可以按值传递，这样写起来更简单
而且效果相同。


``` c++
void Fun(std::vector<int>&& v) // 获取入参的所有权
{
StoreSomewhere(std::move(v));
// v已被移动走，不能再使用
...
}

// unique_ptr不能被复制，只能被移动，并且移动代价小，
// 因此可以使用“std::unique_ptr<SomeClass>”或“std::unique_ptr<SomeClass>&&”作为参数类型
void Fun1(std::unique_ptr<SomeClass> p)
{
...
}
void Fun2(std::unique_ptr<SomeClass>&& p)
{
...
}

```

25. （多选）using typedef数组指针，指向数组的指针是
A.	typedef int (Array*)[10]
B.	using Array = int(*)[10]
C.	typedef int (*Array)[10]
D.	using *Array = int[10]

答案：BC
A申明方式不对
D两边类型不对等



26. （多选）假设函数Foo返回类型为const A&，下列语句与 const A& r = Foo(); 等价的有
A.	auto r = Foo();
B.	auto& r = Foo();
C.	const auto& r = Foo();
D.	decltype(Foo()) r = Foo();

答案： BCD
当有&的时候，const会默认复制过来；auto 的const属性保留。


27. 函数匹配：

```c++
void fun1(void *ptr) {
    std::cout << "1111";
}

void fun1(int i) {
    std::cout <<"2222";
}

    fun1(1); //输出：1111
    fun1(nullptr); // 输出： 2222
```

28. 类型变换后的溢出

```c++
    unsigned int a = 10;
    int b = -20;
    std::cout << (a + b) << std::endl; // 输出：4294967286 溢出
```





## 编码规范


1. 使用标准的头文件包含顺序可增强可读性，避免隐藏依赖，建议的头文件包含顺序为：

	cpp对应的头文件,C/C++标准库, 系统库的.h, 其他库的.h, 本项目内其他的.h


2.（多选）以下标识符的申明或定义，错误的有
A.	undef _LINE__   // 规范要求，不能undef任何在标准库头文件中声明的标识符
B.	define MODULE_INCLUDE  // 规范要求不能定义空的宏
C.	void *malloc(size_t nbytes);
D.	define SIZE_MAX 80 // 

规范：

#undef __LINE__ // 不符合：__LINE__为保留宏，不允许#undef保留宏
#define _MODULE_INCLUDE_ // 不符合：下划线开头
enum { MAX_SIZE = 80 }; // 不符合：MAX_SIZE是<cstdint>中保留宏
int errno; // 不符合：errno是标准库中的保留标识符
void* malloc(size_t nbytes); // 不符合：malloc是标准库中的保留标识符

>> 规范：不要声明或定义保留标识符

3. 可以在extern “C” 中包含头文件 ： 错误

 在 extern "C" 中包含头文件，有可能会导致 extern "C" 嵌套，部分编译器对 extern "C" 嵌套层次有限制，嵌套层次太多会编译错误。在C，C++混合编程的情况下，在extern "C"中包含头文件，可能会导致被包含头文件的原有意图遭到破坏，例如链接规范被不正确地更改。

>> 规范：禁止在extern "C"中包含头文件


4.（单选）以下移位操作中符合编程规范的是
A.	int lhs = 180;
int a = lhs >> 3;
B.	int lhs = 10;
int a = 3 >> lhs;
C.	unsigned char lhs = 80
unsigned int a = (~lhs) >> 3;
D.	constexpr int lhs = 10;
unsigned int a = 3u >> lhs;

答案：D
AB整型不推荐用移位
C中对char型求反时会自动提升类型，不符合预期逻辑

5.（单选）以下说法中不符合编程规范的选项
A.	基类的虚构函数应该声明为virtual 
B.	虚函数可以使用缺省参数值 
C.	禁止重新定义继承而来的非虚函数
D.	为避免隐式转换，可以将单参数构造函数声明为explict

答案：B
规范：
G.CLS.10-CPP 通过基类指针释放派生类时，必须将基类中析构函数声明为虚函数
G.CLS.11-CPP 在派生类中重写虚函数时禁止重新定义缺省参数值
G.CLS.12-CPP 在重写虚函数时应明确指定override或final
G.CLS.13-CPP 禁止重新定义继承而来的非虚函数

G.CLS.03-CPP 单参数构造函数声明为explicit: 建议


6.（单选）以下描述符合C++语言编程规范的是
A.	为了适应不定数量参数的要求，优先定义C风格的变参函数
B.	可以使用可变参数模板替代一部分C风格变参函数
C.	优先使用void* 类型参数来实现泛型
D.	设计函数是，优先使用输出参数而非返回值

答案：B

设计函数时，优先使用返回值而不是输出参数

7. （单选）以下代码符合规范的是
A.	void Log_func()
{
    printf(“%s %s”, __LINE__, __func__, “exaval”);
}
B.	inline void Log_func()
{
    printf(“%s %s”, __LINE__, __func__, “exaval”);
}
C.	#define Log_func printf(“%s %s”, __LINE__, __func__, “exaval”);
D.	class Log_func {
void Log_func()
{
        printf(“%s %s”, __LINE__, __func__, “exaval”);
}
}
规范：
函数和内联函数不能完全替代函数式宏，函数式宏在某些场景更适合。例如：在日志记录场景中，只有
宏可以保持调用点的文件名（__FILE__）、行号（__LINE__）等信息。




6.以下均为涉及动态内存管理的C++11代码，分配的内存都只在局部使用，return之前要保证释放。其中符合公司C++通用编程规范的规则和建议的是（）
A.
Image* imageA = new Image;
Image* imageB = new Image;
// …
if (ProcFail()) {
delete imageA;
delete imageB;
return;
}
// …
delete imageA;
delete imageB;
return;

B.
auto imageA = std::make_unique();
auto imageB = std::make_unique();
if (ProcFail()) {
return;
}
return;

C.
auto imageA = std::make_shared();
auto imageB = std::make_shared();
// …
if (ProcFail()) {
return;
}
//…
return;

D.
std::auto_ptr imageA(new image);
std::auto_ptr imageB(new image);
// …
if (ProcFail()) {
return;
}
// …
return;

参考答案：B  

B的小问题，c++14才提供make_unique;  保证释放的话，这个最合适。 为什么？


使用RAII技术管理资源的生命周期
使用std::make_unique而不是new创建std::unique_ptr
使用std::make_shared而不是new创建std::shared_ptr
new和delete配对使用，new[]和delete[]配对使用
自定义new/delete操作符需要配对定义，且行为与被替换的操作符一致


```c++
// 使用std::make_unique而不是new创建std::unique_ptr
void Foo()
{
C* p = new C();
std::unique_ptr<C> sp = std::unique_ptr<C>(p); // 不符合
... // 代码中既可以使用 p 也可以使用 sp
}

void Foo()
{
std::unique_ptr<C> sp = std::make_unique<C>(); // 符合
... // 代码中只能使用 sp
}

```


```c++

// 下面的例子适用于无法使用异常的工程。工厂函数Foo::Create 使用C++17的std::optional 型作为返回值，表示可能出错的情形。有可能出错的操作被提出构造函数之外。
Foo {
public:
static std::optional<Foo> Create(const std::string& fileName)
{
std::ifstream file(fileName); // RAII会自动关闭文件
if (file.fail()) {
return {}; // 返回特殊值
}
std::unique_ptr<Data> resource = std::make_unique<Data>(); // 使用智能指针保证释放
if (DoMoreInitialization() == FAILED) {
return {}; // 返回特殊值
}
return Foo(std::move(file), std::move(resource));
}
private:
Foo(std::ifstream file, std::unique_ptr<Data> resource)
: file(std::move(file)), resource(std::move(resource))
{
// 这样的构造函数只设置成员值，不会出错
}
std::ifstream file;
std::unique_ptr<Data> resource;
};

```


## 调试与开发者自测

1. GDB 条件断点

break TestCase.cpp:100 if (isInit  ！= 0)








