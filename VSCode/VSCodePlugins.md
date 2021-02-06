# Python 插件

# Remote 插件
## **Remote SSH** : 
是一个通过ssh远程连接的插件，例如Linux  


## **Remote WSL** :  
是一个连接win10下WSL子系统的工具  
## **Remote Development**：
是一个支持远程开发的插件，它会需要Remote SSH的支持，会一同安装

## 
- 在 settings.json中加入下面内容，每次需要输入密码时，会在终端出现 terminal中，用起来比较顺手
"remote.SSH.showLoginTerminal": true,
"remote.SSH.useLocalServer": false

## Setting up the SSH Agent#
If you are connecting to an SSH host using a key with a passphrase, you should ensure that the SSH Agent is running locally. VS Code will automatically add your key to the agent so you don't have to enter your passphrase every time you open a remote VS Code window.

To verify that the agent is running and is reachable from VS Code's environment, run ssh-add -l in the terminal of a local VS Code window. You should see a listing of the keys in the agent (or a message that it has no keys). If the agent is not running, follow these instructions to start it. After starting the agent, be sure to restart VS Code.
## **VSCode连接linux免密登录**
可以复用git的，id_rsd.pub是公钥。将 id_rsd.pub 复制到远程linux的 ~/.ssh下，命名为authorized_keys

## 远程开发
- 连接上服务器后，发开 VSCode的Terminal，等同于PUTTY，XShell等工具，命令行操作
- File-> Open File :可以打开远程文件。
- 开启远程编码

# Common 
## Git Graph
- 图形界面查看git log的插件，有点类似于小乌龟的，比较好用。

## GitLens
- 在查看源码的时候，直接在每行形式最新的提交/修改log
- 
## Bracket Pair Colorizer
- 彩虹括弧，显示配对信息，方便阅读源码

## Bookmarks
- 书签
- Ctrl + Alt + K 添加/删除书签
- 
## Live Server
- 预览Html

## CODEIF
- https://unbug.github.io/codelf/



# C++
- Cmake/Cmake Tool 如果没有必要，不推荐使用，太耗性能了

# Java
## Maven for Java
- 自动刷新工程和编译，导致机器卡
