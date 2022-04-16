
# volatile


## volatile 基础

volatile : 修饰的变量，编译器不会对变量进行优化; 每次读取都会从内存中读取变量值，不会从寄存器中读取。 牺牲一定效率，来保证数据一致性的。

volatile char *s;  // 修饰由指针指向的对象、数据是 const 或 volatile 

char* volatile pchv; // 指针自身的值——一个代表地址的整数变量，是 const 或 volatile 的


## volatile与多线程


volatile 不能解决多线程中的问题。只能解决多线程中某些问题。

按照 Hans Boehm & Nick Maclaren 的总结，volatile 只在三种场合下是合适的。
* 和信号处理（signal handler）相关的场合；
* 和内存映射硬件（memory mapped hardware）相关的场合；
* 和非本地跳转（setjmp 和 longjmp）相关的场合。


尝试来用volatile关键字解决多线程同步的一个基本问题：happens-before  ??







## 参考
![知乎上的一篇技术博文](https://zhuanlan.zhihu.com/p/62060524)
