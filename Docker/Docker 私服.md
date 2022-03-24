- https://www.slant.co/topics/2436/~best-docker-image-private-registries
- [Jfrog Docker Registry](https://blog.csdn.net/Uwentaway/article/details/105507746 )
- [Docker Registry](https://www.cnblogs.com/xcloudbiz/articles/5526262.html)

# Docker官方提供的Registry
- 参考官网 https://hub.docker.com/_/registry
## 安装
1. 以当前最新的2.7.1为例
```
docker pull registry:2.7.1
```

2. 启动DockerRegistry容器：
```
docker run -d -p 5000:5000 --restart always --name registry registry:2.7.1
```

```
docker run -d -p 5000:5000 --restart always --name registry -v ~/DockerRepository:/var/lib/registry registry:2.7.1
```

3. 测试registry
```
curl 192.168.2.155:5000/v2/_catalog
```
返回：
```
{"repositories":[]}
```
说明是个空的，当前没有镜像数据。

## 配置
- https://docs.docker.com/registry/configuration/
### 自动启动 registry
如果你希望将 registry 用作永久性基础架构的一部分，则应将其设置为在 Docker 重新启动或退出时自动重新启动。本示例使用 --restart always 标志为 registry 设置重新启动策略。
```bash
$ docker run -d \
  -p 5000:5000 \
  --restart=always \
  --name registry \
  registry:2
```
### 自定义发布的端口
如果端口 5000 已经被占用，或者你想运行多个本地 registry 来分隔关注的区域，则可以自定义 registry 的端口。下面的示例在端口 5001 上运行 registry，并将其命名为 registry-test。请记住，-p 值的第一部分是主机端口，第二部分是容器内的端口。在容器中，registry 默认在端口 5000 上监听。
```bash
$ docker run -d \
  -p 5001:5000 \
  --name registry-test \
  registry:2
```
如果要在容器中更改 registry 监听的端口（If you want to change the port the registry listens on within the container），可以使用环境变量 REGISTRY_HTTP_ADDR 来更改它。此命令使 registry 监听容器内的端口 5001：

```bash
$ docker run -d \
  -e REGISTRY_HTTP_ADDR=0.0.0.0:5001 \
  -p 5001:5001 \
  --name registry-test \
  registry:2
```
### 自定义存储位置
默认情况下，registry 数据在主机文件系统上作为 docker卷 持久保存。如果要将 registry 内容存储在主机文件系统上的特定位置，例如挂载到特定目录的 SSD 或 SAN ，则可以使用绑定挂载。绑定挂载更依赖于 Docker 主机的文件系统布局，但在许多情况下性能更高。下面的示例将主机的 /mnt/registry 目录绑定到 registry 容器的 /var/lib/registry/ 目录中。
```bash
$ docker run -d \
  -p 5000:5000 \
  --restart=always \
  --name registry \
  -v /mnt/registry:/var/lib/registry \
  registry:2
```

### 自定义存储后端
默认情况下，registry 将其数据存储在本地文件系统中，无论你是使用绑定挂载还是使用卷。可以使用 存储驱动程序 将 registry 数据存储在 Amazon S3 bucket，Google Cloud Platform 或其他存储后端中。更多信息，请参阅 存储配置选项。

### docker regeistry 容器配置文件
1. 查看配置文件
```
docker exec -it container cat /etc/docker/registry/config.yml
```
2. 修改配置文件
```
docker exec -it container vi /etc/docker/registry/config.yml
```
3. 重启容器生效配置
```
docker restart container
```

## 使用
1. 本地的Image重新tag
```
docker tag ubuntu:20.04 192.168.2.155:5000/liqian/ubuntu:20.04
```
```
docker tag ubuntu:18.04  docker.mxdbcnds.com:5000/dockerhub/ubuntu:18.04
```

2. 将镜像推送到docker registry中
```
docker push 192.168.2.155:5000/liqian/ubuntu:20.04
```

3. 查看所有镜像
```
curl 192.168.2.155:5000/v2/_catalog
```
或者：
```
curl -X GET 192.168.2.155:5000/v2/_catalog

curl -X GET http://192.168.2.155:5000/v2/_catalog
```


返回结果：
```
{"repositories":["liqian/ubuntu"]}
```

4. 查看镜像所有tag
```
curl 192.168.2.155:5000/v2/<images_name>/tags/list
```

e.g
```
curl 192.168.2.155:5000/v2/dockerhub/ubuntu/tags/list
```

返回结果：
```
{"repositories":["liqian/ubuntu"],"tags":["20.04_v1","20.04"]}
```

5. 删除镜像
* 首先查看要删除镜像的Digest
```
curl --header "Accept: application/vnd.docker.distribution.manifest.v2+json" -I -X GET http://registry_host:5000/v2/<images_name>/manifests/<tag>
```
e.g
```
curl --header "Accept: application/vnd.docker.distribution.manifest.v2+json" -I -X GET http://192.168.2.155:5000/v2/liqian/ubuntu/manifests/20.04_v1
```

返回：
```
HTTP/1.1 200 OK
Content-Length: 529
Content-Type: application/vnd.docker.distribution.manifest.v2+json
Docker-Content-Digest: sha256:376209074d481dca0a9cf4282710cd30a9e7ff402dea8261acdaaf57a18971dd
Docker-Distribution-Api-Version: registry/2.0
Etag: "sha256:376209074d481dca0a9cf4282710cd30a9e7ff402dea8261acdaaf57a18971dd"
X-Content-Type-Options: nosniff
Date: Fri, 25 Jun 2021 03:26:05 GMT
```

Digest=sha256:376209074d481dca0a9cf4282710cd30a9e7ff402dea8261acdaaf57a18971dd

* 删除镜像
```
curl -I -X DELETE http://10.74.234.17:5001/v2/<images_name>/manifests/<Digest>
```

e.g
```
curl -I -X DELETE http://192.168.2.155:5000/v2/liqian/ubuntu/manifests/sha256:376209074d481dca0a9cf4282710cd30a9e7ff402dea8261acdaaf57a18971dd
```

如果出现删除失败：
```
HTTP/1.1 405 Method Not Allowed
Content-Type: application/json; charset=utf-8
Docker-Distribution-Api-Version: registry/2.0
X-Content-Type-Options: nosniff
Date: Fri, 25 Jun 2021 03:32:06 GMT
Content-Length: 78
```

需要修改Docker Registry容器中的配置：更改registry容器内/etc/docker/registry/config.yml文件
增加 delete段，将enabled设置为true
```
storage:
  delete:
    enabled: true
```


NOTE:
1. 如果是同一个镜像，但是不同tag名，删除时都会一并删除了。

* 垃圾回收
当从repository中删除镜像后，repository大小不会收缩，需要手动处理
```
docker registry garbage-collect /etc/docker/registry/config.yml
```
* 删除tag

## 私有仓库 TLS https问题
Docker默认只信任 TLS 加密的仓库地址，所有非 https 仓库默认无法登陆也无法拉取镜像。
`/etc/docker/daemon.json`.

`insecure-registries` 字面意思为不安全的仓库，通过添加这个参数对非 https 仓库进行授信。可以设置多个 `insecure-registries` 地址，以数组形式书写，地址不能添加协议头 http。
```json
{
 "insecure-registries": ["<IP>:<PORT>","<IP>:<PORT>"] 
}
```

## DockerRegistry中的`registry`命令的使用

# Docker Registry : Habor
- https://www.cnblogs.com/wxwgk/p/13287336.html

