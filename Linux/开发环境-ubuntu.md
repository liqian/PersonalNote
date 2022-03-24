# 软件安装列表
- ubuntu20.04
- ububtu18.04
- ubuntu16.04

## VSCode
1. 安装

2. 插件配置
## IDEA


## SSH
```shell
    sudo apt install openssh-server -y
    sudo service ssh start
```
## vim
```bash
    sudo apt install vim -y
```
## git
```shell
    sudo apt install git -y
```

## gcc/g++/gdb
- 这个是开发C++的必备组件，一般情况下我们都会安装
```shell
    sudo apt install gcc g++ gdb -y
```

## x-terminator-emulator 终端分屏工具
1. 安装 x-terminator-emulator
```
    sudo apt install terminator -y
```

2. 切换回自带的终端

对于Ubuntu系统，如果安装了terminator，那么快捷键Ctrl+Alt+T将不会启动自带的terminal，而是启动安装的terminator。

如果想恢复回来，可以执行以下命令：

```
sudo update-alternatives --config x-terminal-emulator
```
然后选择：
    gnome-terminal.wrapper


## OpenGL
OpenGL 有好几种安装办法：下面列出二种，GLUT 和 GLFW
GLUT 方法:
```shell
sudo apt-get install build-essential
sudo apt-get install libgl1-mesa-dev
sudo apt-get install libglu1-mesa-dev
sudo apt-get install libglut-dev
```

如果上一步出现报错：

```
Reading package lists... Done
Building dependency tree
Reading state information... Done
E: Unable to locate package libglut-dev
```

将上述
```
sudo apt-get install libglut-dev
```

命令改成：
```
sudo apt-get install freeglut3-dev
```

## Cmake 
- 可以使用系统
```
sudo apt install cmake
```
- 也可以使用压缩包进行安装



## docker

# auto install
- git 库管理安装脚本
- JFrog存储本地安装包
- 如有特殊情况，如下进行说明。
