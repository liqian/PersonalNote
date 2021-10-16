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

## git
```shell
    sudo apt install git -y
```

## gcc/g++/gdb
- 这个是开发C++的必备组件，一般情况下我们都会安装
```shell
    sudo apt install gcc g++ gdb -y
```
## docker

## auto install
- git 库管理安装脚本
- JFrog存储本地安装包
- 如有特殊情况，如下进行说明。

### OpenGL
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
