# linux shell常用命令学习


## 查看系统版本信息

lsb_release -a
cat /etc/os-release

##  压缩和解压

解压tar.gz命令是
tar -zxvf xx.tar.gz

解压tar.bz2的命令是
tar -jxvf xx.tar.bz2

## 文件

### readlink

Linux中的readlink命令用于打印解析的符号链接或规范文件名。用简单的话来说，有符号链接，想知道它代表什么路径。然后，在这种情况下，将使用readlink命令显示符号链接的实际路径。

readlink -f：通过递归跟随给定名称的每个组件中的每个符号链接，此选项可以规范化；除最后一个组件外，所有组件都必须存在。

```shell
readlink -f "$0"  # $0 代表当前运行的shell(命令)的名称；这句得到当前运行脚本的全路径
```
### dirname

用法：dirname 名称 或：dirname 选项
输出：已经去除了尾部的"/"字符部分的名称；如果名称中不包含"/"，则显示"."(表示当前目录)。

``` shell
dirname $(readlink -f "$0")  # 得到正在执行shell(命令)的目录
dirname /usr/bin/sort  # 输出"/usr/bin"
dirname stdio.h      # 输出"."
```


## 信号量
### ipcs
ipcs命令是Linux下显示进程间通信设施状态的工具。 我们知道，系统进行进程间通信（IPC）的时候，可用的方式包括信号量、共享内存、消息队列、管道、信号（signal）、套接字等形式[2]。 使用IPCS可以查看共享内存、信号量、消息队列的状态。 id 对应shmid、semid、msgid等

``` shell
ipcs -a #显示所有的IPC设施
ipcs -s #显示所有的信号量
ipcs -m #显示所有的共享内存

```

### ipcrm
ipcrm 命令用于删除指定 ID 的 IPC（Inter-Process Communication，进程间通信）对象，包括消息队列（message queue）、共享内存（shared memory）和信号量（semaphore），同时将与 IPC 对象关联的数据一并删除，只有超级用户或 IPC 对象创建者能够删除。

``` shell
ipcrm {shm | msg | sem} ID

eg:
ipcrm  -a

```





