# git 使用



git stash: 暂时贮存本地文件/某个特定文件

``` shell
git stash push -m "this is my test" ./test.java   
```





git rebase -i [startpoint] [endpoint]


>> -i 的含义是：--interactive, 即弹出交互式的界面让用户编辑完成合并操作
>> [startpoint] 指的是合并区间的起点。
>> [endpoint] 指的是合并区间的终点，默认是当前分支 HEAD 所指向的 commit。
>> 注意：这里的区间是一个前开后闭的区间。

* 功能
commit多次，不够直观，不能比较清晰查看那些 commit 是对应的那个功能。
所以，在这种情况下。我们需要整理一下 commit 的记录，让我们更好的管理提交记录

* 示例

```shell
git rebase -i ID1 ID2   #进入临时分支
git checkout -b feature/tmp_branch  #新建临时分支feature/tmp_branch
git checkout dev  # 切回dev分支

git rebase feature/tmp_branch  # 在dev分支上，rebase这个临时分支


```







