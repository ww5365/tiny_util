# git 使用


-- 一
git stash: 暂时贮存本地文件/某个特定文件

``` shell
git stash push -m "this is my test" ./test.java   
```

git rebase -i [startpoint] [endpoint]

有点像剪切功能，把某个区间分支，剪切接到master分支之后

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


代码提交过程

git clone ssh://git@codehub-g.xxx.com:2222/ww/poissonsitekit.git

git remote add public ssh://git@codehub-dg-g.xxx.com:2222/PoissonSearch/poissonsitekit.git  //增加远程分支，方便从上面pull数据，同步到本地代码仓

同步public的分支数据到本地分支，并同步到自己origin仓：先fetch，再checkout 再pull public ，再push origin
  git fetch public Br_release_11.0.4.300SP15
  git checkout Br_release_11.0.4.300SP15
  git status
  git pull public Br_release_11.0.4.300SP15
  git push origin Br_release_11.0.4.300SP15


git remote -v
origin  ssh://git@git.xxx.com:2222/ww/poissonsitekit.git (fetch)  // 自己的远程代码仓
public  ssh://git@git.xxx.com:2222/PoissonSearch/poissonsitekit.git (fetch) //主远程代码仓


git pull public dev  //更新远端dev分支的代码到本地

git pull public release/5.2.0.300

git push origin dev //把本地代码提交

git reset 

git clean -fd //删除当前目录下没有被track过的文件和文件夹

git checkout -b release/5.0.5.310  //新建一个本地代码仓

git reset --hard 0d446ef3b884a61bfaefa14f89a04ab82d89fe16  //回退代码到日志id版本

git cherry-pick 2ae4b3cd822841f1e1d886712301c31cfb58db86  //已更新到别的分支上的代码，同步更新到现在的分支

git push -f origin release/5.0.5.310  //表示将目前自己本机的代码库推送到远端，并覆盖；慎用

git commit

git
3.切换本地master分支，合并远端和本地代码；
git checkout dev
git merge public/dev

5.git基于public创建分支： 参考：http://3ms.xxx.com/km/blogs/details/9651657
拉去远端代码：git fetch public
查看远端分支：git branch -r
切换到远端分支：git checkout public/br_release_520
基于远端分支新建本地：git checkout -b br_release_520
将本地分支推送到个人fork仓库：git push origin br_release_520


我运行了一下 git lfs install --skip-smudge 就可以pull代码了

1 Git Bash commit 无法提交，出现 Aborting commit due to empty commit message 错误提示

使用指令：
• cd .git
• ls -al
• rm .COMMIT_EDITMSG.swp
• 重新 git commit -a 正常操作即可

  git status
  pwd
  ls
  cd poissonsitekit/
  ls
  git status
  git remote -v
  git fetch public master
  git pull public
  git status
  git branch -v
  git remote -v
  git pull public master
  git pull public
  git reset
  git status
  git checkout .
  git status
  git clean -fd
  git status
  git pull public de
  git pull public dev
  git push origin dev
  git remote -v
  git branch -a
  git status
  git add .
  git status
  git commit
  git push origin dev
  git checkout -b release/5.0.5.310
  git log
  git reset --hard 0d446ef3b884a61bfaefa14f89a04ab82d89fe16
  git pull public release/5.0.5.310
  git checkout dev
  git log
  git checkout release/5.0.5.310
  git cherry-pick 2ae4b3cd822841f1e1d886712301c31cfb58db86
  git push -f origin release/5.0.5.310   
  git checkout release/5.0.5.300           
  
  
  git cherry-pick :
  
  当我们需要在某个分支合并其他分支的某一次提交时，同时并不希望对整个分支进行合并，而是只希望将某一次提交合入到本地当前分支上，
  那么git cherry-pick commitId就派上用场了:
    git branch  # 当前分支为 test
    git log     # 此时会出现test分支的提交记录，假设此时你想要将test分支的commitId为123456的提交合并到sprint分支
    git checkout sprint
    git cherry-pick 123456 # 此时便已经将这个commit合并到sprint分支了
    git log  # 通过git log 便可以看到
  
  新建和删除分支：
  
    查看所有分支： git branch -a
    在本地新建一个分支： git branch BranchName   或者基于某个分支创建分支  git checkout -b BranchName origin/oldBranchName
    
    切换到你的新分支: git checkout BranchName
    将新分支发布在github上： git push origin BranchName
    在本地删除一个分支： git branch -d BranchName
    在github远程端删除一个分支： git push origin :BranchName (分支名前的冒号代表删除)

  submodule使用：参考： https://www.codenong.com/cs109239897/
  
  #添加submodule
  git submodule add url path    eg : git submodule add https://github.com/hwx0000/imgui.git imgui
  

	# pull主仓时，不会下载子仓的代码的，所以需要专门更新下载子仓代码
	git submodule update --init   # 更新所有子仓
	 
	git submodule init sub1 sub2  #更新特定子仓：sub1 sub2                    
  git submodule update          #update所有被init过的submodule
 
 
  # 更新子仓代码
  git submodule update --remote  <path to submodule>        
  
  git submodule update 过程中断，再次执行，会报错fatal: could not get a repository handle for submodule
  解决方案：把对应submodule路径的.git文件删掉，再重新git submodule update








