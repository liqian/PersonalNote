参考：
https://www.cnblogs.com/jesse131/p/13543308.html

# ssh 连接Docker容器，手动操作，以Centos的docker容器为例

## 1.  拉取镜像
```shell
docker pull centos:centos7.9.2009
```

## 2. 使用镜像，运行容器
```shell
docker run -d --name centos_demo --privileged=true centos:7 /usr/sbin/init
```

--name 给新生成的容器命名,这个可有可无，不影响。
**--privileged=true 给容器访问Linux内核特权,后面要访问systemctl。 这重点，一定要添加，否则后面会出现错误**
/usr/sbin/init:这里也要注意下。

## 3. 进入容器
```shell
docker exec -it centos_demo /bin/bash
```

## 4. 在容器中，给root设置密码
```shell
passwd
```
PS:如果没有passwd，使用`yum install passwd`安装。

## 5. 在容器中安装ssh
```shell
yum install vim openssh-server openssh-clients -y
```

## 6. 修改SSH配置文件
```shell
 vim /etc/ssh/sshd_config
```

修改如下：
```
PubkeyAuthentication yes #启用公钥私钥配对认证方式 
AuthorizedKeysFile .ssh/authorized_keys #公钥文件路径（和上面生成的文件同） 
PermitRootLogin yes #root能使用ssh登录
ClientAliveInterval 60  #参数数值是秒 , 是指超时时间
ClientAliveCountMax 3 #设置允许超时的次数
```
## 7. 重启ssh服务，并设置开机启动
```shell
systemctl restart sshd.service
systemctl enable sshd.service
```
**Failed to get D-Bus connection: Operation not permitted**
这里如果报这个错误说明容器权限不足,第2步执行有误

## 8.退出容器并保存更改
```shell
exit
```

## 9. 用刚才生成的容器创建镜像
```
 docker commit -m 'install ssh' -a 'liqian' centos_demo centos:7.9.2009_v1
```

-m:来指定提交的说明信息，跟我们使用的版本控制工具一样
-a 可以指定更新的用户信息
centos_demo:容器名字，这里也可以使用容器的Id
centos:7.9.2009_v1: 目标镜像的仓库名

## 10. 用新生成的镜像启动新的容器并映射22端口
sshd以守护进程运行: /usr/sbin/sshd -D
```shell
docker run -d -p 50001:22 centos:7.9.2009_v1 /usr/sbin/sshd -D
```

现在可以开启ssh连接之旅了。


## 以Dockerfile的方式创建ssh直连docker容器

1. 创建Dockerfile文件
```Dockerfile
#生成的新镜像以centos7镜像为基础
FROM centos:centos7.9.2009
MAINTAINER by liqian (liq@meixing.com)
#升级系统
RUN yum -y update
#安装openssh-server
RUN yum -y install openssh-server
#修改/etc/ssh/sshd_config
RUN sed -i 's/UsePAM yes/UsePAM no/g' /etc/ssh/sshd_config

# 生成sshkey
RUN ssh-keygen -t dsa -f /etc/ssh/ssh_host_dsa_key
RUN ssh-keygen -t rsa -f /etc/ssh/ssh_host_rsa_key

#变更root密码
RUN echo "root:root123"|chpasswd
#开放窗口的22端口
EXPOSE 22
#运行脚本，启动sshd服务
CMD    ["/usr/sbin/sshd", "-D"]
```

2.在dockerfile文件同级目录中运行创建命令
```shell
docker build -t centos7_ssh .
```
命令成功后，就会创建一个名字为centos7_ssh的image，可以使用“docker images”来查看

3. 根据镜像创建容器
```
docker run -d -P --name=centos_ssh_demo centos7_ssh
```

-P:随机映射宿主机端口

查看容器ip
```
docker inspect centos_ssh_demo
```

查看端口
```
docker port centos_ssh_demo 22
```
知道ip和端口后就可以通过ssh建立连接了

----

# Ubuntu

## ssh 连接Docker容器，手动操作，以ubuntu的docker容器为例
1.pull ubuntu镜像
```bash
docker pull ubuntu:latest
```

2. 启动并进入bash
```bash
docker run -it -d ubuntu:lastest /bin/bash
# 查看刚刚运行容器的id
docker ps
# 在容器中执行bash命令
docker exec -it id /bin/bas
```

3. 安装openssh-server并启动
```bash
apt-get update
apt-get install openssh-server
# 启动之前需手动创建/var/run/sshd，不然启动sshd的时候会报错
mkdir -p /var/run/sshd
# sshd以守护进程运行
/usr/sbin/sshd -D &
# 安装netstat，查看sshd是否监听22端口
apt-get install net-tools
netstat -apn | grep ssh
```
如果已经监听22端口，说明sshd服务启动成功

4. ssh登陆设置
```bash
# 生成ssh key
ssh-keygen -t rsa
# 修改sshd-config允许root登陆
vim /etc/ssh/sshd_config

# #PermitRootLogin prohibit-password 修改为 PermitRootLogin yes  注意前面的#要去掉

```

修改完sshd-config之后需要重启sshd服务
```bash
## 找到pid
ps -aux | grep ssh
kill -9 pid
/usr/sbin/sshd -D &
```

5. 查看容器ip
```bash
ifconfig
```

6. 在主机上进行登陆
```bash
ssh root@ip
```

**就可以登录成功了，但是注意这里是docker容器的宿主机才能登陆成功，如果需要其他机器登陆，可以在启动docker的时候进行端口映射**

```bash
# 11122宿主机端口，22为容器端口
docker run -it -p 11122:22 
# 在其他机器上可以使用以下命令登陆，假设宿主机ip为192.168.1.101
ssh -p 11122 root@192.168.1.101
```

7. 保存容器
```bash
# 把id为id的容器保存
docker commit id sshd:ubuntu
# 停止容器
docker stop id
```

## 通过dockerfile

1. dockerfile
```bash
# 以最新的Ubuntu镜像为模板
FROM ubuntu:20.04

RUN apt-get update
RUN apt-get install -y openssh-server
RUN apt-get install -y net-tools
RUN apt-get install -y vim
RUN apt-get install -y git
RUN apt-get install -y cmake 
RUN apt-get install -y gcc g++ gdb
RUN mkdir -p /var/run/sshd
RUN mkdir -p mkdir/root/.ssh/
# 修改root密码，便于远程登录
RUN echo root:123456 | chpasswd
# 将key生成在指定文件内，发现已经有了
#RUN ssh-keygen -q -t rsa -b 2048  -f /etc/ssh/ssh_host_rsa_key -P '' -N ''
# 配置ssh可以使用root登陆
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

# 开放22端口
EXPOSE 22

CMD ["/usr/sbin/sshd", "-D"]
```

2.在dockerfile文件同级目录中运行创建命令
```shell
docker build -t ubuntu_ssh .
```
命令成功后，就会创建一个名字为 ubuntu_ssh 的image，可以使用“docker images”来查看

3. 根据镜像创建容器 映射端口  最好使用一个不常用的，避免冲突
```
docker run -d -P 50001:22 --name=ubuntu_ssh_demo ubuntu_ssh
```

-P:随机映射宿主机端口

查看容器ip
```
docker inspect ubuntu_ssh_demo
```

查看端口
```
docker port ubuntu_ssh_demo 22
```
知道ip和端口后就可以通过ssh建立连接了

4. 提示错误`error checking context:'can't stat /home/user/thinclient_drives'
把 Dockerfile 移动到非用户根目录下。

----

# 使用VSCode +ssh +Docker 远程开发
https://zhuanlan.zhihu.com/p/361934730