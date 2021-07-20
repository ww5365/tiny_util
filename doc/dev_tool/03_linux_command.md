# linux 常用命令学习



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





