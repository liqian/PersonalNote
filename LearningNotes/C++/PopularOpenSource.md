
## SQLite

## Redis

## Memcached
- [OfficalWebsite](http://memcached.org/)
- Memcached 是一个高性能的分布式内存对象缓存系统，用于动态Web应用以减轻数据库负载。
- 它通过在内存中缓存数据和对象来减少读取数据库的次数，从而提供动态数据库驱动网站的速度。
- Memcached 基于一个存储键/值对的 hashmap。
- Memcached-1.4.7的代码量还是可以接受的，只有10K行左右。

## LevelDB
- [GitHub LevelDB](https://github.com/google/leveldb)
- 谷歌两位大神发起的开源项目
- 能够支持10亿级别规模的Key-Value数据库，C++程序库。
- 代码优美、简单，命名规范。
- 存储入门看LevelDB不错，可以学到redo log既wal的关键细节
1. prepare point
2. commit point
3. apply point
4. checkpoint
5. prune point
6. group commit
- 存储入门2个关键：wal rsm
- 压缩编码比较丰富
- fdcache blockcache,存储格式的iterator模式等

## MyTinySTL
- 用C++11 重新复写了一个小型STL（容器库+算法库）。
- 代码结构清晰规范，包含中文文档和注释，并且自带一个简单的测试框架，非常适合新手学习。

## oat++(oatpp)
- https://oatpp.io/
- https://github.com/oatpp/oatpp
- An Open Source C++ Web Framework
- 轻量、跨平台、高性能、完全零依赖，用纯C++实现的Web框架。
- 对标Java的Spring系列。
- (Swagger-UI)
## Boost.Asio
- 它是异步输入输出的核心。 
- 名字本身就说明了一切：Asio 意即异步输入/输出。
- 该库可以让 C++ 异步地处理数据，且平台独立。
- 异步数据处理就是指，任务触发后不需要等待它们完成。
- 相反，Boost.Asio 会在任务完成时触发一个应用。
- 异步任务的主要优点在于，在等待任务完成时不需要阻塞应用程序，可以去执行其它任务。
- [OfficalDoc](https://www.boost.org/doc/libs/1_58_0/doc/html/boost_asio.html)

## muduo
- 一个基于Boost库实现的现代C++高并发网络库，陈硕 大神编写
- 其核心代码不超过4500行，使用non-blocking IO(IO Multiplexing) + one loop per thread模型。
- 适合于linux下多线程服务端应用程序。

## CppNet
- 一个封装在TCP协议上的Procator模式multithread网络库。
- 包含OS接口调用，回调处理，定时器，缓存管理等。
- 这里有从操作系统到应用层的所有网络细节，便于初学者学习和实践。

## tmux
- linux上终端软件，长连接。

## RPC 框架 rest_rpc
- https://github.com/qicosmos/rest_rpc
- 简介：C++11 high performance，cross platform,easy to use rpc framework.
- Modern C++开发的RPC库。

## webbench
- linux下的网站压力测试框架，比较轻量，适合初学者学习网络编程的
## Tinyhttpd
- tinyhttpd是一个超轻量型Http Server，使用C语言开发，
- 全部代码只有502行(包括注释)，附带一个简单的Client，
- 可以通过阅读这段代码理解一个 Http Server 的本质。

## cJSON
- cJSON是C语言中的一个JSON编解码器，非常轻量级，C文件只有500多行，速度也非常理想。
- cJSON也存在几个弱点，虽然功能不是非常强大，但cJSON的小身板和速度是最值得赞赏的。
- 其代码被非常好地维护着，结构也简单易懂，可以作为一个非常好的C语言项目进行学习。
- 

## Libevent
- [Libevent GitHub](https://github.com/libevent/libevent)
- libevent是一个开源的事件驱动库，基于epoll，kqueue等OS提供的基础设施。
- 其以高效出名，它可以将IO事件，定时器，和信号统一起来，统一放在事件处理这一套框架下处理。
- 基于Reactor模式，效率较高，并且代码精简（4.15版本8000多行），是学习事件驱动编程的很好的资源。

## OSG
OpenSceneGraph是一个开源的三维引擎，被广泛的应用在可视化仿真、游戏、虚拟现实、科学计算、三维重建、地理信息、太空探索、石油矿产等领域。OSG采用标准C++和OpenGL编写而成，可运行在所有的Windows平台、OSX、GNU/Linux、IRIX、Solaris、HP-Ux、AIX、Android和FreeBSD 操作系统。OSG在各个行业均有着丰富的扩展，能够与使用OpenGL书写的引擎无缝的结合，使用国际上最先进的图形渲染技术，让每个用户都能站在巨人的肩上。


- http://www.openscenegraph.org/
- http://www.osgchina.org/
- ![SourceCode](https://github.com/openscenegraph/OpenSceneGraph)
- ![LearnNode](https://github.com/Epulari/osg-exercise)