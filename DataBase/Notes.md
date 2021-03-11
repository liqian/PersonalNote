## dbdiagrm.io 数据库设计

# 几种常用数据库对比和简介
## Redis 
- REmote DIctionary Server(Redis) 是一个由 Salvatore Sanfilippo 写的 key-value 存储系统，是跨平台的非关系型数据库。

- Redis 是一个开源的使用 ANSI C 语言编写、遵守 BSD 协议、支持网络、可基于内存、分布式、可选持久性的键值对(Key-Value)存储数据库，并提供多种语言的 API。

- Redis 通常被称为数据结构服务器，因为值（value）:
1. 字符串(String)
2. 哈希(Hash)
3. 列表(list)
4. 集合(sets)
5. 有序集合(sorted sets)
- 内存数据库，效率很高，读效率 110000/s, 写81000/s ，多当做缓存工具。
- Redis 官网：https://redis.io/

- 源码地址：https://github.com/redis/redis

- Redis 在线测试：http://try.redis.io/

- Redis 命令参考：http://doc.redisfans.com/ 和 https://www.redis.net.cn/order
## memcached

## KV存储 LevelDB 
- https://github.com/google/leveldb
- LevelDB is a fast key-value storage library written at Google that provides an ordered mapping from string keys to string values.
- 单机数据库，不支持网络
- 基于LSM结构的KV存储，leveldb常被用作各类数据库和存储系统的存储引擎，在BAT都在使用。
- LevelDB 是单进程的服务，性能非常之高，在一台4核Q6600的CPU机器上，每秒钟写数据超过40w，而随机读的性能每秒钟超过10w。
此处随机读是完全命中内存的速度，如果是不命中，速度大大下降。
- **levelDB是一种更适合写多读少的NoSQL数据库**