# GCC 使用


## fPIC


### 基本介绍

在生成动态库时，常常习惯性的加上fPIC选项，fPIC有什么作用和意义，加不加有什么区别，这里做下小结：

fPIC的全称是 Position Independent Code， 用于生成位置无关代码。什么是位置无关代码，个人理解是代码无绝对跳转，跳转都为相对跳转。

### 不加fPIC选项

即使不加fPIC也可以生成.so文件，但是对于源文件有要求，例如
因为不加fPIC编译的so必须要在加载到用户程序的地址空间时重定向所有表目，所以在它里面不能引用其它地方的代码。

如下：
``` c++
#include <stdio.h>

int func1(int a)
{
    printf("haha a=%d\n", 2);
    a++;
    return a;
}
```

使用 gcc  -shared -o libb3.so c.c 编译将报错

/usr/bin/ld: /tmp/ccCViivC.o: relocation R_X86_64_32 against `.rodata' can not be used when making a shared object; recompile with -fPIC
/tmp/ccCViivC.o: could not read symbols: Bad value

将上述代码改为：

```c++
int func1(int a)
{
//    printf("haha a=%d\n", 2);
    a++;
    return a;
}
```

则可以编译通过。

对于不加 -fPIC生成的动态库，“生成动态库时假定它被加载在地址0处。加载时它会被加载到一个地址（base），这时要进行一次重定位（relocation），把代码、数据段中所有的地址加上这个 base 的值。这样代码运行时就能使用正确的地址了。”

 

### 加fPIC选项

加上fPIC选项生成的动态库，显然是位置无关的

“这样的代码本身就能被放到线性地址空间的任意位置，无需修改就能正确执行。通常的方法是获取指令指针的值，加上一个偏移得到全局变量/函数的地址。”

加fPIC选项的 源文件对于，它引用的函数头文件编写有很宽松的尺度。

比如只需要包含个声明的函数的头文件，即使没有相应的C文件来实现，编译成so库照样可以通过。

 

在内存引用上，加不加fPIC的异同：

加了fPIC实现真正意义上的多个进程共享so文件。

多个进程引用同一个 PIC 动态库时，可以共用内存。这一个库在不同进程中的虚拟地址不同，但操作系统显然会把它们映射到同一块物理内存上。

对于不加-fPIC的

不加fPIC，则加载so文件时，需要对代码段引用的数据对象需要重定位，重定位会修改代码段的内容,这就造成每个使用这个.so文件代码段的进程在内核里都会生成这个.so文件代码段的copy.每个copy都不一样,取决于这个.so文件代码段和数据段内存映射的位置。

可见，这种方式更消耗内存。

但是不加fPIC编译的 so文件的优点是加载速度比较快。

### fPIC 参考

1、[linux编译动态库 fPIC作用](https://www.cnblogs.com/fengliu-/p/10216878.html)


## .a 和 .so 库生成和使用