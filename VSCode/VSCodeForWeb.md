# VSCode For Web
- Docker 安装方式
1. 安装 docker
2. 拉取 vscode-server 镜像
```shell
$ docker pull jmcdice/vscode-server
```
3. 运行容器
```shell
$ docker run -d -p 80:8080 jmcdice/vscode-server
```
4. 更换源
https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu/
```shell
$ apt-get update && apt-get upgrade
```
5. 开心的写代码啦