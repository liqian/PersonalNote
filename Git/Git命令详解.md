https://www.yiibai.com/git/git_reset.html

# git config 
    git config [-–local|-–global|-–system] .....
默认是local，可以不用加 --local参数。
local: 工程目录/.git/config
global:~/.gitconfig
system:

可以直接修改这几个文件，可以达到如下命令的目的。


## 1. git config 帮助命令
    git help config

## 2. 配置用户名 和邮箱
    git config --global user.name "your name"
    git config --global user.email "you@meixing.com"
每次安装git后，首先需要配置这项，否则无法提交代码。  
git的每次提交都会将该信息嵌入到提交log中。

    git config user.name "your name"
    git config user.email "you@meixing.com"
如果去掉 --global ,name只是对当前的项目设置 用户名。  
需要在项目的路径下执行这个命令。

## 3. 配置文本编辑器
    git config --global core.editor vim
如果不配置，git使用系统默认的编辑器。  
在 git commit后会调出这个编辑器，进行编写提交log信息。

推荐是用vim, 大家也可以根据自己的习惯进行更换。例如 Emacs 等
## 4. 配置比较工具
    git config --global merge.tool vimdiff
需要配置的有用的选项是缺省的比较工具它用来解决合并时的冲突。

Git可以接受 kdiff3, tkdiff, meld, xxdiff, emerge, vimdiff, gvimdiff, ecmerge, 和 opendiff 作为有效的合并工具。

## 5. 检查配置信息
    git config --list

如果是在非工程目录下运行该命令，显示的是 --global 的配置信息
如果是在工程目录下运行该命令，显示该工程的全部config信息。

## 6. 添加/删除 配置项
    git config --add section.key value
    git config --unset section.key

--add：添加配置， section key value 一个不能少，否则执行失败. 添加的时候并不会判断section.key是否存在，如果存在 将会重复添加。所有最好少用 或者使用前先查看下是否有 section.key值。
--unset：删除配置项，只需要 section key

    git config section.key value
这个命令也是添加配置，如果没有section.key 会进行添加，如果存在，会修改成新的值。推荐使用这个。

## 7. 添加log模板
    git config commit.template .gitmessage
由于不同工程存在不同的模板，所以这个推荐设置单个工程的
## 8. 自动转换换行符的配置：AutoCRLF
- 提交时转换为LF，检出时转换为CRLF   
    `git config --global core.autocrlf true`  

- 提交时转换为LF，检出时不转换   
    `git config --global core.autocrlf input`   

- <font color=red>提交检出均不转换 [推荐]</font>  
    `git config --global core.autocrlf false`
## 9. 提交时检查换行符问题：SafeCRLF
- <font color=red>拒绝提交包含混合换行符的文件 [推荐]</font>  
    `git config --global core.safecrlf true`  

- 允许提交包含混合换行符的文件  
    `git config --global core.safecrlf false`   

- 提交包含混合换行符的文件时给出警告  
    `git config --global core.safecrlf warn`

## 10. 支持long path
下载是可能会遇到Filename too long错误，在git bash下执行一下
    git config --global core.longpaths true 
命令就能正常下载了    

# git clone
    git clone url
    git clone url localname
## git 协议
支持http ssh等协议
- http 协议  
    `git clone git@192.168.2.34:liq/PyProject2.git`
- ssh 协议  
    `git clone git@192.168.2.34:liq/PyProject2.git`

# git init
    git init
不克隆项目，只是对当前的项目文件使用Git进行管理.  
例如当前有个目录D:/MyProject,运行如下命令：  
    `git init`

该命令将创建一个名为 .git 的子目录，这个子目录含有初始化的 Git 仓库中所有的必须文件，这些文件是 Git 仓库的骨干。
  
但是，在这个时候，我们仅仅是做了一个初始化的操作，项目里的文件还没有被跟踪。  

如果是在一个已经存在文件的文件夹(而不是空文件夹)中初始化 Git 仓库来进行版本控制的话，应该开始跟踪这些文件并提交。可通过 git add 命令来实现对指定文件的跟踪，然后执行 git commit 提交.



# git stash

## git stash list: 显示stash中的内容
```bash
git stash list
# stash@{0}: On master: clean crur cache
# stash@{1}: On master: MxDefault
# stash@{2}: On master: project
```
## git stash drop: 删除stash中的缓存内容
```bash
git stash drop stash@{0}
# Dropped stash@{0} (380ffaa2f41b4e91cc065755c7bea056e02e7bcd)
```
## git stash apply :命令时可以通过名字指定使用哪个stash，默认使用最近的stash（即stash@{0}）
## git stash pop : 将缓存中的第一个缓存内容恢复到工作区
## git stash branch branch_name: 从缓存区创建个分支，创建成功，会将存在内容丢弃。


# git format-patch
* git打patch
* 需要先要在本地提交，然后才能打patch
## 某次提交（含）之前的几次提交
```
git format-patch [commit sha1 id] -n
```
n指从sha1 id对应的commit开始算起n个提交。
eg：
```
git format-patch  2a2fb4539925bfa4a141fe492d9828d030f7c8a8 -2
```

## 某个提交的patch
```
git format-patch 【commit sha1 id】 -1
```
eg

```
git format-patch  2a2fb4539925bfa4a141fe492d9828d030f7c8a8 -1
```

## 某两次提交之间的所有patch
```
git format-patch 【commit sha1 id】..【commit sha1 id】 
```
e.g:
```
git format-patch  2a2fb4539925bfa4a141fe492d9828d030f7c8a8..89aebfcc73bdac8054be1a242598610d8ed5f3c8
```

## 应用patch
- 检查patch/diff是否能正常打入
```
git apply --check 【path/to/xxx.patch】
git apply --check 【path/to/xxx.diff】
```

- 打入patch/diff
```
git apply 【path/to/xxx.patch】
git apply 【path/to/xxx.diff】
```

或者

```
git  am 【path/to/xxx.patch】
```

# git branch

## 创建分支
```
git branch branch_name
```
在本地创建一个分支名字为 branch_name.

## 分支提交到远程
```
git push origin remote_branch_name
```

一般我们会将branch_name 和remote_branch_name 保持一样，方便理解。

这时候，如果`git pull` 会报错，参考如下说明

## 建立本地分支和远程分支的关联
```
git branch --set-upstream-to=origin/remote_branch_name branch_name
```

如果不运行，会报如下错误：
```
There is no tracking information for the current branch.
See git-pull(1) for details.

    git pull <remote> <branch>

If you wish to set tracking information for this branch you can do so with:

    git branch --set-upstream-to=origin/<branch> branch_name
```

