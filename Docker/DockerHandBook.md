# 简介
- [OfficalWebsite](https://docs.docker.com/)
## 什么是Docker
- Docker 是一个开源的应用容器引擎，基于 Go 语言并遵从 Apache2.0 协议开源；
- Docker 可以让开发者打包他们的应用以及依赖包到一个轻量级、可移植的容器中，然后发布到任何流行的 Linux 机器上，也可以实现虚拟化；
- 容器是完全使用沙箱机制，相互之间不会有任何接口，更重要的是容器性能开销极低；
- Docker 从 17.03 版本之后分为 CE（Community Edition-社区版）和 EE（Enterprise Edition-企业版）。
## Docker的应用场景
- Web应用的自动化打包和发布，自动化测试和持续集成、发布；
- 在服务型环境中部署和调整数据库或其他的后台应用；
- 从头编译或者扩展现有的 OpenShift 或 Cloud Foundry 平台来搭建自己的 PaaS 环境。
## Docker 资源
- [Docker官网](https://www.docker.com/)
- [Docker中文社区](https://www.docker.org.cn/)
- [Docker 官方博客](https://blog.docker.com/)
- [Docker 官方文档](https://docs.docker.com/)
- [Docker Store](https://store.docker.com)
- [Docker Cloud](https://cloud.docker.com)
- [Docker Hub](https://hub.docker.com)
- [Docker菜鸟教程](https://www.runoob.com/docker/docker-tutorial.html)

- [Docker 的源代码仓库](https://github.com/moby/moby)
- [Docker 发布版本历史](https://docs.docker.com/release-notes/)
- [Docker 常见问题](https://docs.docker.com/engine/faq/)
- [Docker 远端应用 API](https://docs.docker.com/develop/sdk/)
- [Docker技术入门与实战  第3版] 是不错的入门数据。（第二章安装部分，最好参考官网，时间有点老了）
## Docker 国内镜像
- 阿里云的加速器：https://help.aliyun.com/document_detail/60750.html
- 网易加速器：http://hub-mirror.c.163.com
- 官方中国加速器：https://registry.docker-cn.com
- ustc 的镜像：https://docker.mirrors.ustc.edu.cn

# Install
- [Ubuntu安装说明]( Install&Run_ubuntu.md)
- [Window安装说明]( Install&Run_win.md)

# 配置

Docker有两处可以配置参数：
-  一个是 docker.service 服务配置文件,
- 一个是Docker daemon配置文件  daemon.json 。

建议所有修改都在 daemon.json 中进行。

若没有 daemon.json ，自行创建 /etc/docker/daemon.json，官方 daemon.json配置说明。这里对一些常用的配置进行说明。

更改daemon.json后，使用如下命令生效:
```
sudo systemctl daemon-reload
sudo systemctl restart docker
```

使用`docker info`查看是否修改成功。


## 镜像下载和上传并发数
从 Docker1.12 开始，支持自定义下载和上传镜像的并发数，默认值上传为5个并发，下载为3个并发。

通过添加 max-concurrent-downloads 和 max-concurrent-uploads 参数对其修改：
```json
{
 "max-concurrent-downloads": 3,
 "max-concurrent-uploads": 5 
}
```

## 镜像加速地址
国内直接拉取镜像会有些缓慢，为了加速镜像的下载，可以给Docker配置国内的镜像地址。
```json
{
  "registry-mirrors": ["http://hub-mirror.c.163.com"],
  "registry-mirrors": ["https://cr.console.aliyun.com"],
  "registry-mirrors": ["https://docker.mirrors.ustc.edu.cn"]
}
```

国内的镜像源
   >* 网易
   >http://hub-mirror.c.163.com

   >* Docker中国区官方镜像 -- 速度还有有点慢，公司网络
   >https://registry.docker-cn.com

   >* 中国科技大学 -- 
   >https://docker.mirrors.ustc.edu.cn

   >* 阿里云容器  服务 -- 速度还可以，公司网路
   >https://cr.console.aliyun.com/

## 私有仓库
Docker默认只信任 TLS 加密的仓库地址，所有非 https 仓库默认无法登陆也无法拉取镜像。

`insecure-registries` 字面意思为不安全的仓库，通过添加这个参数对非 https 仓库进行授信。可以设置多个 `insecure-registries` 地址，以数组形式书写，地址不能添加协议头 http。
```json
{
 "insecure-registries": ["<IP>:<PORT>","<IP>:<PORT>"] 
}
```

## Docker存储驱动
OverlayFS 是一个新一代的联合文件系统，类似于 AUFS ，但速度更快，实现更简单。

Docker为 OverlayFS 提供了两个存储驱动程序：旧版的overlay，新版的 overlay2 (更稳定)。

启用 overlay2 条件：Linux内核版本4.0或更高版本。
```json
{ 
   "storage-driver": "overlay2", 
   "storage-opts": ["overlay2.override_kernel_check=true"] 
}
```
## 日志驱动
容器在运行时会产生大量日志文件，很容易占满磁盘空间。通过配置日志驱动来限制文件大小与文件的数量。

日志等级分为 debug|info|warn|error|fatal ，默认为 info
```json
{
 "log-level": "warn",
 "log-driver": "json-file", 
 "log-opts": { 
   "max-size": "100m", 
   "max-file": "3"
  }, 
}
```

## 数据存储路径
默认路径为 /var/lib/docker
```json
{ 
"data-root": "/home/docker" 
}
```

## Demo
这里提供一个经常使用的配置模板
```json
{
 "insecure-registries": ["192.168.2.2:8080"],
 "oom-score-adjust": -1000,
 "exec-opts": ["native.cgroupdriver=systemd"],
 "registry-mirrors": ["https://ucjisdvf.mirror.aliyuncs.com"],
 "storage-driver": "overlay2",
 "storage-opts": ["overlay2.override_kernel_check=true"], 
"log-level": "warn", 
"log-driver": "json-file", 
"log-opts": { 
     "max-size": "100m", 
     "max-file": "3" 
},
"data-root": "/home/docker" 
}
```

# Docker 使用

- [Docker 镜像使用](# Docker 镜像使用)
- [Docker 容器使用](# Docker 容器使用)
- [Docker 仓库管理](# Docker 仓库管理)
- [Docker 容器连接](# Docker 容器连接)
- [Docker Dockerfile](# Docker Dockerfile)

----

## Docker 镜像使用

### 获取一个新的镜像： `docker pull` 

从镜像仓库中拉取或者更新指定镜像，在未声明镜像标签时，默认标签为latest。

当我们在本地主机上使用一个不存在的镜像时 Docker 就会自动下载这个镜像。默认是从 Docker Hub 公共镜像源下载

如果我们想预先下载这个镜像，我们可以使用 `docker pull` 命令来下载它。

Usage:
```
Usage: docker pull [OPTIONS] NAME[:TAG|@DIGEST] 
Options: 
    -a 拉取某个镜像的所有版本
    --disable-content-trust 跳过校验，默认开启
```


e.g:
```
liqian@ubuntu:~$ sudo docker pull ubuntu:16.04
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

#### 从指定的私有仓库下载
PS：需要先记性登录，请使用`docker login <host>`进行登录。

Usage:
```
docker pull <host>/<project>/<repo>:<tag>
```


e.g:
NDS协会的JFrog:
```bash
docker login artifactory.nds-association.org
docker pull artifactory.nds-association.org/tooling-dockerreg/ndslivereg:latest
```

DBC的JFrog：

TODO Action：如何能够免密或者非手动输入账号密码？？？登录后可以记住密码和账号。

### 推送镜像 `docker push`

```
Usage:
docker push [OPTIONS] NAME[:TAG]
OPTIONS说明：
  --disable-content-trust :忽略镜像的校验,默认开启  
```


### 列出本地镜像列表： `docker images` 

Usage:
```
Usage: docker images [OPTIONS] [REPOSITORY[:TAG]]
Options:
  -a, --all 显示所有镜像
  -f, --filter filter 使用过滤器过滤镜像
    dangling true or false, true列出没有标签的，false相反
    label (label=<key> or label=<key>=<value>)，如果镜像设置有label，则可以通过label过 滤
    before (<image-name>[:<tag>], <image id> or <image@digest>) - 某个镜像前的镜像
    since (<image-name>[:<tag>], <image id> or <image@digest>) - 某个镜像后的镜像
    reference (pattern of an image reference) - 模糊查询,例：-- 
    filter=reference='busy*:*libc' 
  --format string 格式化输出
    .ID 镜像ID
    .Repository 镜像仓库
    .Tag 镜像tag
    .Digest Image digest
    .CreatedSince 创建了多久
    .CreatedAt 镜像创建时间
    .Size 镜像大小
-q, --quiet 只显示镜像ID
```

e.g
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



### 查找镜像：`docker search name` 
我们可以从 Docker Hub 网站来搜索镜像，
Docker Hub 网址为： https://hub.docker.com/

我们也可以使用 `docker search name` 命令来搜索镜像。

比如我们需要一个 ubuntu 的镜像,我们可以通过 `docker search` 命令搜索 ubuntu 来寻找适合我们的镜像。 
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
* _**stars**_: 类似 Github 里面的 star，表示点赞的意思。
* _**AUTOMATED**_: 自动构建。


### 删除镜像： `docker rmi name` 
镜像删除使用 `docker rmi name` 命令，比如我们删除 hello-world 镜像：
```
liqian@ubuntu:~$ sudo docker rmi hello-world
Untagged: hello-world:latest
Untagged: hello-world@sha256:8c5aeeb6a5f3ba4883347d3747a7249f491766ca1caa47e5da5dfcf6b9b717c0
Deleted: sha256:bf756fb1ae65adf866bd8c456593cd24beb6a0a061dedf42b26a993176745f6b
Deleted: sha256:9c27e219663c25e0f28493790cc0b88bc973ba3b1686355f221c38a36978ac63
```

### 创建镜像
当我们从 docker 镜像仓库中下载的镜像不能满足我们的需求时，我们可以通过以下两种方式对镜像进行更改。
- 更新镜像，创建副本：从已经创建的容器中更新镜像，并且提交这个镜像
- 使用 Dockerfile 指令来创建一个新的镜像
#### 更新镜像，创建副本 `docker commit`
```
Usage: docker commit [OPTIONS] CONTAINER [REPOSITORY[:TAG]]
Options:
    -a, --author string 作者
    -m, --message string 提交信息
```
参数说明：
* *-a*: 镜像作者
* *-m*:镜像信息描述
* *`CONTAINER`*：容器ID
* *`[REPOSITORY[:TAG]]`*:指定要创建的目标镜像名


**Step1**:
更新镜像之前，我们需要使用镜像来创建一个容器。
```bash
docker run -t -i ubuntu /bin/bash
```

**Step2**:
对容器做下改动，以验证副本Image是否OK。
1. 运行`apt update`,然后运行`apt install lsb-release -y`安装lsb-release package.
2. `lsb_release -a` 查看是否OK。
```text
root@9f94739dff7d:/# lsb_release -a
No LSB modules are available.
Distributor ID: Ubuntu
Description:    Ubuntu 21.04
Release:        21.04
Codename:       hirsute
root@9f94739dff7d:/#
```
3. 记录下容器ID：9f94739dff7d
4. `exit`退出容器。

**Step3**:
使用`docker commit `提交副本。
```bash
docker commit -m='based on:21.04 install:lsb-release' -a='liqian' 9f94739dff7d liqian/ubuntu:21.04_commit
```
运行结果：
sha256:4cf79f6ddd10730462acc0f7c51977005ac9afc3c6abd01dd9c18f2916202e3a

创建成功，使用`docker images`查看下。

使用新的镜像，启动容器，查看下。

#### `dockerfile`构建镜像
- 官方推荐方式。
- 详细解释参照 [Dockerfile详解.md]
- docker build:
  ```
  Usage: docker build [OPTIONS] PATH | URL | -
  Options:
      -f, --file string 指定Dockerfile，默认为当前路径的Dockerfile，可以指定绝对路径
      -q, --quiet 安静模式，构建成功后输出镜像ID
      -t, --tag list 给镜像设置tag，name:tag
  ```

我们使用命令 docker build ， 从零开始来创建一个新的镜像。

为此，我们需要创建一个 Dockerfile 文件，其中包含一组指令来告诉 Docker 如何构建我们的镜像。

Dockerfile其实就是我们用来构建Docker镜像的源码，是一些命令的组合，只要理解它的逻辑和语法格式，就可以编写Dockerfile了。

```Dockerfile
FROM ubuntu:21.04
LABEL maintainer='liqian@mxnavi.com'
RUN apt update
RUN apt install lsb-release -y
```
保存为Dockerfile文件，如果非默认名字，需要制定绝对路径。

每一个指令都会在镜像上创建一个新的层，每一个指令的前缀都必须是大写的,为了区分指令，推荐使用全部大写。

- 第一条FROM，指定使用哪个镜像源

- RUN 指令告诉docker 在镜像内执行命令，安装了什么。。。

然后，我们使用 Dockerfile 文件，通过 docker build 命令来构建一个镜像。
```
docker build -t liqian/ubuntu:21.04_dockerfile .
```

使用`docker images`查看下是否创建成功。

### 镜像创建tag `docker tag`
我们可以使用 docker tag 命令，为镜像添加一个新的标签。

新tag可以理解为原镜像的一个别名，标签。他们共用一个实体。

```
Usage: docker tag SOURCE_IMAGE[:TAG] TARGET_IMAGE[:TAG]
```
docker tag 镜像ID 新镜像名
镜像ID 可以用ImageID 或者 REPOSITORY:TAG

e.g
```
docker images

REPOSITORY                                                     TAG                IMAGE ID       CREATED        SIZE
liqian/ubuntu                                                  21.04_dockerfile   b8b2a5f5ee64   2 hours ago    147MB
liqian/ubuntu                                                  21.04_commit       4cf79f6ddd10   4 hours ago    147MB
ubuntu                                                         latest             9873176a8ff5   7 hours ago    72.7MB
ubuntu                                                         21.04              478aa0080b60   3 weeks ago    74.1MB
artifactory.nds-association.org/tooling-dockerreg/ndslivereg   latest             ad00a5204758   7 months ago   1.37GB
ubuntu                                                         20.04              d70eaf7277ea   7 months ago   72.9MB
ubuntu                                                         18.04              56def654ec22   8 months ago   63.2MB
```

```
docker tag ubuntu:18.04 ubuntu:18.04_alis

docker images

REPOSITORY                                                     TAG                IMAGE ID       CREATED        SIZE
liqian/ubuntu                                                  21.04_dockerfile   b8b2a5f5ee64   2 hours ago    147MB
liqian/ubuntu                                                  21.04_commit       4cf79f6ddd10   4 hours ago    147MB
ubuntu                                                         latest             9873176a8ff5   7 hours ago    72.7MB
ubuntu                                                         21.04              478aa0080b60   3 weeks ago    74.1MB
artifactory.nds-association.org/tooling-dockerreg/ndslivereg   latest             ad00a5204758   7 months ago   1.37GB
ubuntu                                                         20.04              d70eaf7277ea   7 months ago   72.9MB
ubuntu                                                         18.04              56def654ec22   8 months ago   63.2MB
ubuntu                                                         18.04_alis         56def654ec22   8 months ago   63.2MB
```

---

## Docker 容器使用
### Docker客户端帮助
- 使用`docker`命令，直接列出客户端支持的命令。
- 可以通过命令 `docker command --help` 更深入的了解指定的 Docker 命令使用方法
e.g.
```
docker stats --help

```
查看各个容器运行状态，如占资源情况等信息

### 查看容器 `docker ps`
参数说明:
* -a:查看所有容器，包含启动的 未启动的
* -q:只显示container id

```
liqian@ubuntu:~$ docker ps -a
CONTAINER ID   IMAGE                            COMMAND       CREATED        STATUS                   PORTS     NAMES
db3eca6bd18b   liqian/ubuntu:21.04_dockerfile   "/bin/bash"   3 hours ago    Exited (0) 3 hours ago             kind_goldstine
9f94739dff7d   ubuntu:21.04                     "/bin/bash"   5 hours ago    Exited (0) 5 hours ago             unruffled_franklin
74ec269d0744   ubuntu:20.04                     "/bin/bash"   2 months ago   Exited (0) 6 hours ago             testGDB
```
各个选项含义:
* CONTAINER ID:容器的ID
* IMAGE: 创建容器时使用的镜像
* COMMAND: 创建容器时的命令
* CREATED: 容器创建时间
* STATUS: 当前容器状态
* PORTS: 映射端口号
* NAMES: 容器的名字。(创建是使用 --name参数设定的名字，如果没设置，系统会自动给分配一个)

### 创建/运行容器 `docker run`.
```
Usage: docker run [OPTIONS] IMAGE [COMMAND] [ARG...]
Options:
  -d, --detach 后台运行容器，并输出容器ID
  -e, --env list 设置环境变量，该变量可以在容器内使用
  -h, --hostname string 指定容器的hostname
  -i, --interactive 以交互模式运行容器，通常与-t同时使用
  -l, --label list 给容器添加标签
  --name string 设置容器名称，否则会自动命名
  --network string 将容器加入指定网络
  -p, --publish list 设置容器映射端口
  -P,--publish-all 将容器设置的所有exposed端口进行随机映射
  --restart string 容器重启策略，默认为不重启
    on-failure[:max-retries]：在容器非正常退出时重启，可以设置重启次数。
    unless-stopped：总是重启，除非使用stop停止容器
    always：总是重启
  --rm 容器退出时则自动删除容器
  -t, --tty 分配一个伪终端
  -u, --user string 运行用户或者UID
  -v, --volume list 数据挂载
  -w, --workdir string 容器的工作目录
  --privileged 给容器特权
```
参数说明：
* -i:交互式操作
* -t:分配个终端
* -d:启动守护进程，在后台运行，并返回容器ID
* -P:将容器内部使用的网络端口随机映射到我们使用的主机上。docker默认开放5000端口，随机映射到主机端口号。
* -p:映射容器端口 到 主机端口
* --name:给启动的容器设定名字，不能重复; 如果不指定，默认随机生成名字。为了方便使用最好是自己起个名字。e.g. C1
 C2  
* ImageName:tag: tag如果省略，默认使用latest。  
e.g. ubuntu就是使用ubutun镜像。  
可以使用ubuntu:20.04指定Image的名字。  
如果本地没有镜像，或默认取网上获取，获取不到会报错。
* /bin/bash：放在镜像名后的是命令，这里我们希望有个交互式 Shell，因此用的是 /bin/bash。

#### 交互式模式启动容器
以下命令使用 ubuntu 镜像启动一个容器，参数为以命令行模式进入该容器：  
```
docker run -i -t --name C1 ubuntu /bin/bash
```
自动进入容器。  
一旦使用`exit`退出这个容器，容器停止运行。

#### 后台运行容器
以下命令使用 ubuntu 镜像启动一个容器，参数为以命令行模式进入该容器：  
```
docker run -i -t -d --name C2 ubuntu /bin/bash
```
**注**：加了 -d 参数默认不会进入容器，想要进入容器需要使用指令 docker exec（下面会介绍到）。

### 启动已停止的容器
使用命令`docker start containerId/name`:

使用命令`docker restart containerId/name`:

- 不管是交互式(-i)还是后台式(-d)启动后，都不会自动进入容器，需要手动进入。

### 进入容器
在使用 -d 参数时，容器启动后会进入后台。此时想要进入容器，可以通过以下指令进入：
* docker attach
* docker exec：推荐大家使用 docker exec 命令，因为此退出容器终端，不会导致容器的停止。

#### attach 命令

下面使用 `docker attach containerId/name` 命令
```
$ docker attach 1e560fca3906
```
**注意**： 如果从这个容器退出，会导致容器的停止,不管是否是以 -d 参数启动的容器。

#### exec 命令
下面使用`docker exec containerId/name` 命令
```
docker exec -it 243c32535da7 /bin/bash
```
**注意**： 如果从这个容器退出，不会导致容器的停止，这就是为什么推荐大家使用 docker exec 的原因。

更多参数说明请使用 docker exec --help 命令查看。

### 删除容器
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
### 导出和导入容器

#### 导出容器 `docker export`
如果要导出某个容器(容器快照）到本地，可以使用 docker export 命令。

```
Usage: docker export [OPTIONS] CONTAINER
Options:
    -o, --output string tar包名称  Write to a file, instead of STDOUT
```
* CONTAINER: 容器ID /  容器名称
* -o: 导出的文件直接写入文件，推荐方式。这种方式同时采用了压缩。
* > :中方式输出的是把标准输出流直接写入文件，不会采用压缩，不推荐使用。


e.g
```bash
docker export 9f94739dff7d > ubuntu.tar
```

```bash
docker export 9f94739dff7d -o u1.tar
```

```bash
docker export 9f94739dff7d > D:/ubuntu.tar
docker export 9f94739dff7d -o D:/u1.tar
```

这样将导出容器快照到本地文件。

#### 导入容器 `docker import`
可以使用 `docker import` 从容器快照文件中再导入为**镜像**:

```
Usage: docker import [OPTIONS] file|URL|- [REPOSITORY[:TAG]]
Options:
   -m, --message string 设置提交信息
   file|URL|- file:指定文件路径 URL：指定URL路径 -：STDOUT
```

e.g.
以下实例将快照文件 ubuntu.tar 导入到镜像 test/ubuntu:v1

**NOTE1**: 速度快，耗内存少。
```bash
docker import u1.tar test/ubuntu:u1
```

**NOTE2**: 这种方式比较耗内存，不推荐使用。除非一些特殊情况下
```bash下
cat ubuntu.tar | docker import - test/ubuntu:ubuntu
```

URL形式：这种没有详细研究，后续可以研究下
```bash
docker import http://example.com/exampleimage.tgz example/imagerepo
```

----

## Docker 仓库管理
仓库（Repository）是集中存放镜像的地方。以下介绍一下 [Docker Hub](https://hub.docker.com/)。
当然不止 docker hub，只是远程的服务商不一样，操作都是一样的。

### docker hub
- 登录 `docker login`
  > 登录需要输入用户名和密码，登录成功后，我们就可以从 docker hub 上拉取自己账号下的全部镜像。
- 退出 `docker logout`
- 然后可以使用 `docker pull` 拉取镜像，`docker push`推送镜像。

### JFrog 私服

### docker registry 私服


----

## Docker 容器连接



----

## Docker Dockerfile


----

## Docker Compose
