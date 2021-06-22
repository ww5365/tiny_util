#include "../inc/com_use.h"
#include <algorithm>
#include <cstring>
#include <cstdio>
#define MAX_LEN 10

void charaters_use_test(){

    /*
    * 字符串拷贝函数的使用建议：尽量不用
    * strcpy ,strcat, strdup,sprintf : 无越界检查
    * strncpy(dest, src, LEN) : 不保证以\0结束，当src的长度大于dest的LEN时，就出问题了,小于长度时造成浪费；同时效率也不高；
    * 
    * 建议：snprintf() 来统一处理以上问题
    * 
    * snprintf(dest, src, LEN); 
    */

   const char *str = "this is test character lib!";

   char buf[MAX_LEN];

   //批量给字符数组赋值,字符串中的处理函数；c中常用 
   //memset(buf, 0, MAX_LEN);  //string.h

   /*
   * c++11 支持了更通用的方式:
   * void fill(ForwardIt first, ForwardIt last, const T& value);
   * OutputIterator fill_n(OutputIt first, size n, const T& value);
   * 功能：
   * fill给迭代器范围[first, last)内元素均赋值为value。无返回值。
   * fill_n将first指向范围内的前n个元素赋值为value。返回first+n(c++11)
   */

  std::fill_n(buf, MAX_LEN, 0);  //algorithm

  std::cout << "fill_n success! " << "buf:" << buf << std::endl;

  snprintf(buf, MAX_LEN, "%s", str);
  //strncpy(buf, str, MAX_LEN); //不会保证以\0结尾
  std::cout << "after copy charaters buf: " << buf << std::endl;

  /*
  * 内存拷贝：都是string.h中使用内存拷贝的函数，区别？
  * void* memcpy(dst, src, count) ： 不保证内存重叠情况下的正确性,但效率要高些
  * void* memmove(dst, src, count) ： 其实包含了memcpy，考虑内存重叠的情况; 
  * 建议：？ 使用memmove：
  * 
  */

  char buf2[MAX_LEN];
  memset(buf2, 0, MAX_LEN);
  memmove(buf2, buf, 3);
  std::cout << "after copy charaters buf2: " << buf2 << std::endl;





}