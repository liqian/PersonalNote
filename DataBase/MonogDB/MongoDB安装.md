
# Windows

# Linux

# Docker
## DockerHub 拉取MongoDB镜像
- https://hub.docker.com/_/mongo?tab=tags 查看所有可用的Docker MongoDB镜像

- 可以使用`docker pull mongo:latest`拉取当前最新的。

- 可以使用 `docker pull mongo:5.0.2`拉取固定版本的，我当前取的是5.0.2

## 运行容器
```shell
docker run -itd --name mongo_learn -p 27017:27017 mongo:5.0.2 --auth
```
参数说明：
- -p 27017:27017 ：映射容器服务的 27017 端口到宿主机的 27017 端口。外部可以直接通过 宿主机 ip:27017 访问到 mongo 的服务。
- --auth：需要密码才能访问容器服务。 默认账号密码为： mongo admin
PS：尝试了下 不加 `--auth`，也可以。但是进入时同样需要输入密码。建议加上这个参数。

## 进入容器
```shell
 docker exec -it mongo_learn mongo admin
```

```shell
MongoDB shell version v5.0.2
connecting to: mongodb://127.0.0.1:27017/admin?compressors=disabled&gssapiServiceName=mongodb
Implicit session: session { "id" : UUID("2aec28f2-54ef-4bc0-83b3-f2366cc1c9de") }
MongoDB server version: 5.0.2
================
Warning: the "mongo" shell has been superseded by "mongosh",
which delivers improved usability and compatibility.The "mongo" shell has been deprecated and will be removed in
an upcoming release.
We recommend you begin using "mongosh".
For installation instructions, see
https://docs.mongodb.com/mongodb-shell/install/
================
Welcome to the MongoDB shell.
For interactive help, type "help".
For more comprehensive documentation, see
        https://docs.mongodb.com/
Questions? Try the MongoDB Developer Community Forums
        https://community.mongodb.com
>
```
说明成功进入Docker容器，mongodb可以使用了。

## 使用MongoDB 简单测试