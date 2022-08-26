# linux shell 使用



## linux shell 常用命令

### cp

* 参数
  -a, --archive    等于-dR --preserve=all

    --backup[=CONTROL    为每个已存在的目标文件创建备份

-b                类似--backup 但不接受参数

   --copy-contents        在递归处理是复制特殊文件内容

-d                等于--no-dereference --preserve=links

-f, --force        如果目标文件无法打开则将其移除并重试(当 -n 选项

                    存在时则不需再选此项)

-i, --interactive        覆盖前询问(使前面的 -n 选项失效)

-H                跟随源文件中的命令行符号链接

-l, --link            链接文件而不复制

-L, --dereference   总是跟随符号链接

-n, --no-clobber   不要覆盖已存在的文件(使前面的 -i 选项失效)

-P, --no-dereference   不跟随源文件中的符号链接

-p                等于--preserve=模式,所有权,时间戳

    --preserve[=属性列表   保持指定的属性(默认：模式,所有权,时间戳)，如果

               可能保持附加属性：环境、链接、xattr 等

-R, -r, --recursive  复制目录及目录内的所有项目

* 实例


``` shell

# 拷贝软连文件

cp -d  soft_file.txt file.txt    ## 保留了软连接的属性, file.txt就是个软链

cp -L soft_file.txt file.txt  ## 跟随符号链接，将soft_file.txt指向的实际的文件，拷贝给fille.txt  硬拷贝

```


### pushd 和 popd

pushd、popd和dirs : 在linux中可以用来方便地在多个目录之间切换.

#### dirs

-p	每行显示一条记录
-v	每行显示一条记录，同时展示该记录在栈中的index
-c	清空目录栈

``` shell

dirs -v   # 显示当前的目录栈的情况：栈顶 就是当前所在的目录； 当切换目录之后，栈中的目录也随之改变;

```

#### pushd

``` shell

pushd /opt/data  # 将目录/opt/data入目录栈，同时当前的工作目录是：/opt/data
pushd   # 不带任何参数：将目录栈中0~1号索引目录栈进行交换
pushd +2  # 切换到目录栈中的第n个目录(这里的n就是dirs -v命令展示的index)，并将该目录以栈循环的方式推到栈顶

```
#### popd

``` shell

popd # 将当前的目录栈的栈顶弹出，同时工作目录变化
popd +2  # 将目录栈中第n个元素弹出

```


### /dev/null 

常见的shell脚本： >/dev/null 2>&1 

将标准输出送到空设备，即不显示输出内容； 同时将标准错误输出也输出到标注输出，即空设备

说明如下：
1：> 代表重定向到哪里，例如：echo "123" > /home/123.txt
2：/dev/null 代表空设备文件
3：2  表示stderr标准错误
4：& 表示等同于的意思，2>&1，表示2的输出重定向等同于1
5：1 表示stdout标准输出，系统默认值是1，所以">/dev/null"等同于 "1>/dev/null"

说明2：
command > file 2>file  与command > file 2>&1

它们有什么不同的地方吗？
首先command > file 2>file 的意思是将命令所产生的标准输出信息,和错误的输出信息送到file 中.command  > file 2>file 这样的写法,stdout和stderr都直接送到file中, file会被打开两次,这样stdout和stderr会互相覆盖,这样写相当使用了FD1和FD2两个同时去抢占file 的管道。
command >file 2>&1 这条命令就将stdout直接送向file, stderr 继承了FD1管道后,再被送往file,此时,file 只被打开了一次,也只使用了一个管道FD1,它包括了stdout和stderr的内容。
从IO效率上,前一条命令的效率要比后面一条的命令效率要低,所以在编写shell脚本的时候,较多的时候我们会command > file 2>&1 这样的写法。

* 示例程序：

``` shell

libstdcname=$(ls /usr/lib64/libstdc++.so.6.0.*)
for libstdcversion in ${libstdcname}
do
    if [[ "${libstdcversion}" =~ "25" ]]; then
        cp /usr/lib64/libstdc++.so.6.0.25 ${CURR_PATH}/../tmp/deep-match/so/
        pushd ${CURR_PATH}/../tmp/deep-match/so > /dev/null 2>&1
        ln -snf libstdc++.so.6.0.25 libstdc++.so.6
        ln -snf libstdc++.so.6 libstdc++.so
        popd > /dev/null 2>&1
    elif [[ "${libstdcversion}" =~ "28" ]]; then
        cp /usr/lib64/libstdc++.so.6.0.28 ${CURR_PATH}/../tmp/deep-match/so/
        pushd ${CURR_PATH}/../tmp/deep-match/so > /dev/null 2>&1
        ln -snf libstdc++.so.6.0.28 libstdc++.so.6
        ln -snf libstdc++.so.6 libstdc++.so
        popd > /dev/null 2>&1
fi
done
```






## 参考

1. evernote 笔记
2. 

