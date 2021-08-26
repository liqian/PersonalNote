# 软件安装列表
- ubuntu20.04
- ububtu18.04
- ubuntu16.04

## VSCode
1. 安装

2. 插件配置
## IDEA

## tmux

## Vim

## SSH

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
