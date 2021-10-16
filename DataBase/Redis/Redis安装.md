
# Windows

# Linux

# Docker
## DockerHub 拉取Redis镜像
- https://hub.docker.com/_/redis?tab=tags 查看所有可用的Docker redis镜像

- 可以使用`docker pull redis:latest`拉取当前最新的。

- 可以使用 `docker pull redis:6.2.5`拉取固定版本的，我当前取的是6.2.5

## 运行容器
```shell
 docker run -itd --name redis_learn -p 6379:6379 redis:6.2.5
```
参数说明：
-p 6379:6379：映射容器服务的 6379 端口到宿主机的 6379 端口。外部可以直接通过宿主机ip:6379 访问到 Redis 的服务。

## 进入容器
```shell
docker exec -it redis-test /bin/bash
```