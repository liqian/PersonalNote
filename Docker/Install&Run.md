# Install on Ubuntu
[参照文档](https://docs.docker.com/get-started/)

# Uninstall 
## Uninstall old versions:  
Older versions of Docker were called docker, docker.io, or docker-engine. If these are installed, uninstall them:
```bash
sudo apt-get remove docker docker-engine docker.io containerd runc
```

## Uninstall Docker Engine:  
1. Uninstall the Docker Engine, CLI, and Containerd packages:
```bash
sudo apt-get purge docker-ce docker-ce-cli containerd.io
```

2. Images, containers, volumes, or customized configuration files on your host(`/var/lib/docker/`) are not automatically removed.  
To delete all images, containers, and volumes:
```bash
sudo rm -rf /var/lib/docker
```
## test Docker
Verify that Docker Engine is installed correctly by running the hello-world image.
```
sudo docker run hello-world
```

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