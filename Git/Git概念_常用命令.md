
# 基本概念
## 基本的 Git 工作流程如下

- 在工作目录中修改文件。
- 暂存文件，将文件的快照放入暂存区域。
- 提交更新，找到暂存区域的文件，将快照永久性存储到 Git 仓库目录。

## Git 自带一个 git config 的工具来帮助设置控制 Git 外观和行为的配置变量
- 如果添加 --system 命令，对所有用户的git配置起作用
- 如果添加 --global 明亮，对当前用户 所有项目配置起作用
- 如果在单个工程目录下，不添加上面2个命令，只是对当前用户 当前项目起作用

## Git工作流，生命周期

- 工作目录下的每一个文件都不外乎这两种状态：<font color=red>已跟踪</font>或<font color=red>未跟踪</font>。    

- 已跟踪的文件是指那些被纳入了版本控制的文件，在上一次快照中有它们的记录，在工作一段时间后，它们的状态可能处于未修改，已修改或已放入暂存区。 
- 工作目录中除已跟踪文件以外的所有其它文件都属于未跟踪文件，它们既不存在于上次快照的记录中，也没有放入暂存区。 
- 初次克隆某个仓库的时候，工作目录中的所有文件都属于已跟踪文件，并处于未修改状态。
- 编辑过某些文件之后，由于自上次提交后你对它们做了修改，Git 将它们标记为已修改文件。 我们逐步将这些修改过的文件放入暂存区，然后提交所有暂存了的修改，如此反复。所以使用 Git 时文件的生命周期如下：
    ![Git文件的生命周期](resources/GitWorkFlow.png)

- Git Status 查看当前分支状态。已修改的，已提交 未被跟踪等信息。  
    1. 工作空间同服务器一致，干净.  
        `On branch master`  
        `Your branch is up to date with 'origin/master'.`  
        `nothing to commit, working tree clean`
    2. 未跟踪   
        `On branch master`  
        `Your branch is up to date with 'origin/master'.`  

        `Untracked files:`  
        `(use "git add <file>..." to include in what will be committed)`  
            `test.txt`

        `nothing added to commit but untracked files present (use "git add" to track)`
    3. 已修改，未放入 暂存区  
        `On branch master`
        `Your branch is up to date with 'origin/master'.`  

        `Changes not staged for commit:`  
        `    (use "git add <file>..." to update what will be committed)`  
        `    (use "git restore <file>..." to discard changes in working directory)`  
        `    modified:   make_packes.py`  

        `no changes added to commit (use "git add" and/or "git commit -a")`  
    4. 放入 暂存区，未提交  
        `On branch master`  
        `Your branch is up to date with 'origin/master'.`  

        `Changes to be committed:`  
            `(use "git restore --staged <file>..." to unstage)`  
            `modified:   make_packes.py`  
            `new file:   test.txt`  
    5. 本地提交  
        `On branch master`  
        `Your branch is ahead of 'origin/master' by 1 commit.`  
            `(use "git push" to publish your local commits)`  

        `nothing to commit, working tree clean` 
    6. 提交到服务器上
    状态同1. 

# 常用命令含义和简单说明
## Clone代码
    git clone 'url/ssh path'
## 查看本地分支
    git branch
## 查看远程分支
    git branch -a

## 切换并下载远程分支
    git checkout -b xx_local_branch_name xx_remote_branch_name
## 切换本地分支
    git checkout local_branch_name
    e.g.  
    git checkout master

## 查看当前信息
    git status
## git使用前的配置
    git config [options] [options] 
- 配置用户名
    git config --global user.name "your name"
- 配置邮箱
    git config --global user.email "you@meixing.com"
- 配置log模板
    git config commit.template .gitmessage
- 配置文本编辑器
    git config --global core.editor vim

## git submodule组合初始化更新 递归
    gir submodue add rul path/name
    git submodule update --progress --init --recursive
## git rm 删除文件
## git rm -r 删除目录
## git mv 移动文件
## git log 查看日志
## git commit --amend  撤销提交，也叫合并提交。
- 本次提交同上次提交信息合并，用于修改漏提交文件或者写错log信息等情况
## 回退本地代码

```bash
git reset --hard commit-id：回滚到commit-id，将commit-id后的提交全移出
git reset --hard HEAD~3:将最近3次提交回滚
```

## git reset HEAD <file> 取消暂存区文件
- 相当于`git add <file>`命令逆操作。
## git checkout -- <file> 撤销对文件的修改
- 相当于我们在Win GUi界面下的revert操作。 

## 关于win和linux 跨平台开发是的编码问题
- 一般情况最好不要启用git的自动转换字符的功能，如下配置
   1. 提交检出均不转换  
        `git config --global core.autocrlf false`
   2. 拒绝提交包含混合换行符的文件  
        `git config --global core.safecrlf true`

