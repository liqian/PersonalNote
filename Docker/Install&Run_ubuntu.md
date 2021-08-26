# Install on Ubuntu
[参照文档](https://docs.docker.com/engine/install/ubuntu/)

## Uninstall 
### Uninstall old versions:  
Older versions of Docker were called docker, docker.io, or docker-engine. If these are installed, uninstall them:
```bash
sudo apt-get remove docker docker-engine docker.io containerd runc
```
It’s OK if apt-get reports that none of these packages are installed.

### Uninstall Docker Engine:  
1. Uninstall the Docker Engine, CLI, and Containerd packages:
```bash
sudo apt-get purge docker-ce docker-ce-cli containerd.io
```

2. Images, containers, volumes, or customized configuration files on your host(`/var/lib/docker/`) are not automatically removed. 

The contents of `/var/lib/docker/`, including images, containers, volumes, and networks, are preserved. If you do not need to save your existing data, and want to start with a clean installation.
To delete all images, containers, and volumes:
```bash
sudo rm -rf /var/lib/docker
```

## Install Docker
- 使用Docker Repository ，官方推荐方式。需要机器能连接互联网。
- 使用安装包安装，这种方式使用不能上网的机器。升级也需要手动升级。

### Install using the repository
- [参考官方](https://docs.docker.com/engine/install/ubuntu/#install-using-the-repository)
1. Set up the repository 安装相关依赖：
   > `sudo apt-get update`
   > `sudo apt-get install apt-transport-https ca-certificates curl gnupg lsb-release`
2. Add Docker’s official GPG key 安装CPG证书:
   > `curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg`

   > 如果网络不好用的话，可以使用国内源替代
   > `curl -fsSL https://mirrors.aliyun.com/docker-ce/linux/debian/gpg | sudo apt-key add`

3. 安装软件源
   > Use the following command to set up the stable repository:
   > `echo "deb [arch=amd64 signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null`

   > 这里添加的源为 北京外国语大学开源软件镜像站：
   > add-apt-repository "deb [arch=amd64] https://mirrors.bfsu.edu.cn/docker- ce/linux/debian $(lsb_release -cs) stable"
4. Install Docker Engine 安装Docker引擎:
   > 安装最新版本 the latest version:
   > `sudo apt-get update`
   > `sudo apt-get install docker-ce docker-ce-cli containerd.io `

   > 安装指定版本的Docker引擎 To install a specific version:
   > a. 列出当前可用版本 List the versions available in your repo
   > `apt-cache madison docker-ce`
   > b. 安装指定版本：例如 5:18.09.1~3-0~ubuntu-xenial  替换下面的VERSION_STRING.
   > `sudo apt-get install docker-ce=<VERSION_STRING> docker-ce-cli=<VERSION_STRING> containerd.io`

### Install from a package
- [参考官方](https://docs.docker.com/engine/install/ubuntu/#install-from-a-package)
- 在 https://download.docker.com/linux/ubuntu/dists/ 下载适合的版本。
- 使用命令 `sudo dpkg -i /path/to/package.deb` 安装。
### Install using the convenience script
- 这里不再详细介绍，请查看[官方说明](https://docs.docker.com/engine/install/ubuntu/#install-using-the-convenience-script)


### test Docker
Verify that Docker Engine is installed correctly by running the hello-world image.
```
sudo docker run hello-world
```
这里会从hub上下载一个 hello-world的Image，如果网速不行的话，可以查看下面的切换源操作，然后在尝试。

## Docker Engine Status
1. Ubuntu上查看服务的命令
```bash
sudo service docker --status-all
#Usage: service docker {start|stop|restart|status}

```
2. 查看Docker Engine运行状态

3. 停止docker engine：sudo service docker stop 
```bash
liqian@ubuntu:~$ sudo service docker stop
liqian@ubuntu:~$ sudo service docker status
● docker.service - Docker Application Container Engine
   Loaded: loaded (/lib/systemd/system/docker.service; enabled; vendor preset: e
   Active: inactive (dead) since Wed 2020-11-04 16:35:01 KST; 37s ago
     Docs: https://docs.docker.com
  Process: 3825 ExecStart=/usr/bin/dockerd -H fd:// --containerd=/run/containerd
 Main PID: 3825 (code=exited, status=0/SUCCESS)

```

4. 启动docker engine：sudo service docker start 
```bash
liqian@ubuntu:~$ sudo service docker start
liqian@ubuntu:~$ sudo service docker status
● docker.service - Docker Application Container Engine
   Loaded: loaded (/lib/systemd/system/docker.service; enabled; vendor preset: e
   Active: active (running) since Wed 2020-11-04 16:37:21 KST; 25s ago
     Docs: https://docs.docker.com
 Main PID: 18586 (dockerd)
    Tasks: 13
   CGroup: /system.slice/docker.service
           └─18586 /usr/bin/dockerd -H fd:// --containerd=/run/containerd/contai
```

5. 重启Docker Engine: sudo service docker restart 
