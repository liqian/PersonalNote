# 简介
## 什么是Docker
- Docker 是一个开源的应用容器引擎，基于 Go 语言并遵从 Apache2.0 协议开源；
- Docker 可以让开发者打包他们的应用以及依赖包到一个轻量级、可移植的容器中，然后发布到任何流行的 Linux 机器上，也可以实现虚拟化；
- 容器是完全使用沙箱机制，相互之间不会有任何接口，更重要的是容器性能开销极低；
- Docker 从 17.03 版本之后分为 CE（Community Edition-社区版）和 EE（Enterprise Edition-企业版）。
## Docker的应用场景
- Web应用的自动化打包和发布，自动化测试和持续集成、发布；
- 在服务型环境中部署和调整数据库或其他的后台应用；
- 从头编译或者扩展现有的 OpenShift 或 Cloud Foundry 平台来搭建自己的 PaaS 环境。
## 友情链接
- [Docker官网](https://www.docker.com/)
- [Docker中文社区](https://www.docker.org.cn/)
- [Docker Hub](https://hub.docker.com/)

# Command
## docler --help
帮助文档，说明。

# Docker 镜像使用
当运行容器时，使用的镜像如果在本地中不存在，docker 就会自动从 docker 镜像仓库中下载，默认是从 Docker Hub 公共镜像源下载。

## 列出镜像列表
使用命令 `sudo docker images`列出本机上已经安装的所有的镜像
```
liqian@ubuntu:~$ sudo docker images
[sudo] password for liqian: 
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
hello-world         latest              bf756fb1ae65        10 months ago       13.3kB

```

各个选项说明:
* _**REPOSITORY**_：表示镜像的仓库源
* _**TAG**_：镜像的标签
* _**IMAGE ID**_：镜像ID
* _**CREATED**_：镜像创建时间
* _**SIZE**_：镜像大小

同一仓库源可以有多个 TAG，代表这个仓库源的不同个版本，如 ubuntu 仓库源里，有 15.10、14.04 等多个不同的版本，我们使用 REPOSITORY:TAG 来定义不同的镜像。  
_**如果你不指定一个镜像的版本标签，例如你只使用 ubuntu，docker 将默认使用 ubuntu:latest 镜像。**_

## 获取一个新的镜像
当我们在本地主机上使用一个不存在的镜像时 Docker 就会自动下载这个镜像。如果我们想预先下载这个镜像，我们可以使用 `docker pull` 命令来下载它。

```
liqian@ubuntu:~$ sudo docker pull ubuntu:16.04
[sudo] password for liqian: 
16.04: Pulling from library/ubuntu
2c11b7cecaa5: Pull complete 
04637fa56252: Pull complete 
d6e6af23a0f3: Pull complete 
b4a424de92ad: Pull complete 
Digest: sha256:bb69f1a2b6c840b01eeffef07386e95a74ecac8bfa52d35c32fb526c85e00678
Status: Downloaded newer image for ubuntu:16.04
docker.io/library/ubuntu:16.04

```
下载完成后，我们可以直接使用这个镜像来运行容器。


## 查找镜像
我们可以从 Docker Hub 网站来搜索镜像，Docker Hub 网址为： https://hub.docker.com/

我们也可以使用 `docker search name` 命令来搜索镜像。比如我们需要一个 httpd 的镜像来作为我们的 web 服务。我们可以通过 `docker search` 命令搜索 httpd 来寻找适合我们的镜像。 
```
liqian@ubuntu:~$ sudo docker search ubuntu
NAME                                   DESCRIPTION                                     STARS               OFFICIAL            AUTOMATED
ubuntu                                 Ubuntu is a Debian-based Linux operating sys…   11504               [OK]                
dorowu/ubuntu-desktop-lxde-vnc         Docker image to provide HTML5 VNC interface …   474                                     [OK]
rastasheep/ubuntu-sshd                 Dockerized SSH service, built on top of offi…   249                                     [OK]
```
各个选项的含义:
* _**NAME**_: 镜像仓库源的名称
* _**DESCRIPTION**_: 镜像的描述
* _**OFFICIAL**_: 是否 docker 官方发布
* _**stars**_: 类似 Github 里面的 star，表示点赞、喜欢的意思。
* _**AUTOMATED**_: 自动构建。

查找docker镜像库是否有我们想要的Images。

## 删除镜像
镜像删除使用 `docker rmi` 命令，比如我们删除 hello-world 镜像：
```
liqian@ubuntu:~$ sudo docker rmi hello-world
Untagged: hello-world:latest
Untagged: hello-world@sha256:8c5aeeb6a5f3ba4883347d3747a7249f491766ca1caa47e5da5dfcf6b9b717c0
Deleted: sha256:bf756fb1ae65adf866bd8c456593cd24beb6a0a061dedf42b26a993176745f6b
Deleted: sha256:9c27e219663c25e0f28493790cc0b88bc973ba3b1686355f221c38a36978ac63
```

# Docker 容器使用
## 查看容器
命令: `docker ps`
参数说明:
* -a:查看所有容器，包含启动的 未启动的
* -q:只显示container id

```
liqian@ubuntu:~$ docker ps -a
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
43865fe958b1        ubuntu              "/bin/bash"         32 minutes ago      Up 5 minutes                            C1
```
各个选项含义:
* CONTAINER ID:容器的ID
* IMAGE: 创建容器时使用的镜像
* COMMAND: 创建容器时的命令
* CREATED: 容器创建时间
* STATUS: 当前容器状态
* PORTS: 映射端口号
* NAMES: 容器的名字。(创建是使用 --name参数设定的名字)
## 创建运行容器
使用命令`docker run`.

参数说明：
* -i:交互式操作
* -t:终端
* -d:启动守护进程
* -P:将容器内部使用的网络端口随机映射到我们使用的主机上。docker默认开放5000端口，随机映射到主机端口号。
* -p:映射容器端口 到 主机端口
* --name:给启动的容器设定名字，不能重复; 如果不指定，默认随机生成名字。为了方便使用最好是自己起个名字。e.g. C1
 C2  
* ImageName:tag: tag如果省略，默认使用least。  
e.g. ubuntu就是使用ubutun镜像。  
可以使用ubuntu:20.04指定Image的名字。  
如果本地没有镜像，或默认取网上获取，获取不到会报错。
* /bin/bash：放在镜像名后的是命令，这里我们希望有个交互式 Shell，因此用的是 /bin/bash。

### 交互式模式启动容器
以下命令使用 ubuntu 镜像启动一个容器，参数为以命令行模式进入该容器：  
```
docker run -i -t --name C1 ubuntu /bin/bash
```
自动进入容器。  
一旦使用`exit`退出这个容器，容器停止运行。

### 后台运行容器
以下命令使用 ubuntu 镜像启动一个容器，参数为以命令行模式进入该容器：  
```
docker run -i -t -d --name C2 ubuntu /bin/bash
```
**注**：加了 -d 参数默认不会进入容器，想要进入容器需要使用指令 docker exec（下面会介绍到）。

## 启动已停止的容器
使用命令`docker start containerId/name`:

使用命令`docker restart containerId/name`:

- 不管是交互式(-i)还是后台式(-d)启动后，都不会自动进入容器，需要手动进入。

## 进入容器
在使用 -d 参数时，容器启动后会进入后台。此时想要进入容器，可以通过以下指令进入：
* docker attach
* docker exec：推荐大家使用 docker exec 命令，因为此退出容器终端，不会导致容器的停止。

### attach 命令

下面使用 `docker attach containerId/name` 命令
```
$ docker attach 1e560fca3906
```
**注意**： 如果从这个容器退出，会导致容器的停止,不管是否是以 -d 参数启动的容器。

### exec 命令
下面使用`docker exec containerId/name` 命令
```
docker exec -it 243c32535da7 /bin/bash
```
**注意**： 如果从这个容器退出，不会导致容器的停止，这就是为什么推荐大家使用 docker exec 的原因。

更多参数说明请使用 docker exec --help 命令查看。

## 删除容器
使用命令 `docker rm containerId/name`

- 删除所有容器
```
docker rm 'docker ps -a -q'
```
**注意**: 如果有容器还处于运行状态会报错，要先停掉。

- 删除所有处于终止状态的容器。
```
docker container prune
```
## 导出和导入容器



