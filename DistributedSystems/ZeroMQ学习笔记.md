# OverView
- [Offical Doc](https://zeromq.org/get-started/)
- [API Doc](http://api.zeromq.org/)
- [github libzmq](https://github.com/zeromq/libzmq)
- [github cppzmq](https://github.com/zeromq/cppzmq)
- libzmq version:4.3.4

# 九大优势
- ZMQ为应用程序提供了一套简单的套接字API，不用考虑实际使用的协议类型
    > 进程内 进程间 机器间 广播
- ZMQ提供了多种模式进行消息路由，如请求-应答模式，发布-订阅模式， PUSH-PULL模式等，这些模式用来搭建网络拓扑结构。
- ZMQ是通过后台的I/O线程进行消息传输的。
    > 一个I/O线程已经足以处理多个套接字的数据传输要求。
- ZMQ消息的读写都是异步的
    > 无论是消息的接收还是发送，ZMQ都是将消息放入管道中。
    > 当Reactor轮询到相应的读写事件的时候，适时的读写消息，并且所有I/O操作都在后台进行。
- ZMQ保证进程不会因为内存溢出而崩溃。
    > 因为ZMQ有阈值（HWM)机制，可以避免消息溢出。
    > 当队列已满，ZMQ会自动阻塞发送者，或丢弃部分消息，这些行为取决于你所使用的消息模式。
- 当节点调动时，ZMQ会自动的进行连接或重连。
    > 这意味着你可以以任何顺序启动组件。
    > 用它创建的面向服务架构（SOA）中，服务端可以随意的加入和退出网络。
- ZMQ会在必要的情况下自动将消息放入队列中保存，一旦建立连接就开始发送。
- ZMQ使用消息帧的机制来传递整个消息，但不强制使用某种消息格式。
    > 消息的序列化/反序列化由应用层负责处理。
- ZMQ会处理套接字异常，能够智能的处理网络错误。
    > 优势它会进行重试，有时会告知某项操作发生错误。
    
# libzmq 编译笔记
- BUILD_SHARED 编译动态库 dll 默认 ON
> 会在 build/bin/debug/libzmq-v142-mt-gd-4_3_5.dll

- BUILD_STATIC 编译静态库 lib 默认 ON
> 会在 build/lib/debug/libzmq-v142-mt-sgd-4_3_5.lib

- ZMQ_BUILD_TESTS 默认 ON
> 生成test一些exe和工具。

- WITH_PERF_TOOL 默认 ON
> 生成性能分析工具

- ENABLE_ASAN defalt is OFF
> 分析内存泄漏和非法访问的工具。gcc支持 msvc还在支持中。。。当前不支持。

- ENABLE_CURVE default is ON
> CURVE机制定义了一种安全的认证方式和保密方式，用于客户端和服务器之间的交流。
> CURVE 计划用于工作在公网上。CURVE机制在RFC文档 http://rfc.zeromq.org/spec:25 中进行了定义。

> 如果没有需求 可以关掉。 影响就是 [zmq_curve – 安全的认证方式和保密方式]无法使用。
> 如果需要使用，依赖libsodium。

> sodium是一个全新而且易用的加密库，用于加密、解密、签名和生成密码哈希等等。 它是一个可移植的、跨编译器支持、可安装的，基于 NaCI 开发，提供了一个兼容 API 和一个提高更高可用性的扩展 API。 它的目标是提供构建一个更高级的加密工具所需要的所有核心操作。 Sodium 支持各种各样的编译器和操作系统，包括 Windows( 如 MingW 或者 Visual Studio, x86 和 x64)，iOS 和 Android。

- WITH_TLS defualt is ON
> 这个需要GnuTLS库。
> GnuTLS 是一个安全通讯库，实现了 SSL、TLS 和 DTLS 协议和相关技术。提供了简单的 C 语言编程接口用来访问这些安全通讯协议，提供解析和读写 X.509、PKCS #12、OpenPGP 和其他相关结构。特点是可移植性和高效。

> 可以关掉，我们的平台是在内网使用，可以不用考虑这个问题。

- ENABLE_DRAFTS 
> 如果是从官方github上的代码，会检测是否有.git目录，有 就设成 ON 否则是OFF。
> 用途： 主要是一些 草案API支持，非稳定的。
> 正式项目中一般会设成 OFF。

**亲测参数如下**:
```cmake
cmake -DWITH_PERF_TOOL=OFF -DENABLE_DRAFTS=OFF -DZMQ_BUILD_TESTS=OFF -DBUILD_STATIC=OFF -DENABLE_CURVE=OFF -DWITH_TLS=OFF ..
```

# cppzmq 编译笔记
- CPPZMQ_BUILD_TESTS 单元测试，default is ON
> 可以去掉。
> 我在编译是 设成了OFF
> 当前代码存在问题，需要设成OFF 否则CMAKE失败。

**亲测参数如下**: CMAKE_PREFIX_PATH 设置libzmq的编译路径
```cmake
cmake -DCMAKE_PREFIX_PATH=D:\github\ZeroMQProject\libzmq\build -DCPPZMQ_BUILD_TESTS=OFF ..
```

Demo:
- 注意 CMAKE_PREFIX_PATH 如果是多个路径，需要使用 **分号** 分割并且需要加上**双引号**。
- 如果路径有空也是同理，需要加上**双引号**.
```cmake-window
cmake -DCMAKE_PREFIX_PATH="D:\github\ZeroMQProject\libzmq\build;D:\github\ZeroMQProject\cppzmq\build" ..
```
```cmake-linux
cmake -DCMAKE_PREFIX_PATH="/home/liqian/Workspace/github/ZeroMQProject/libzmq/build/;/home/liqian/Workspace/github/ZeroMQProject/cppzmq/build/" ..
```

# ZeroMQ 官网文档阅读笔记
## Messages
A ZeroMQ message is a discrete unit of data passed between applications or components of the same application.
> ZeroMQ 消息是在应用直接或者同一应用不同组件之间 传递离散数据单元。

From the point of view of ZeroMQ itself messages are considered to be opaque binary data.
> 从ZeroMQ 自身来看，消息可以认为是不透明的二进制数据。

On the wire, ZeroMQ messages are blobs of any size from zero upwards that fit in memory. 
> 在网络上，ZeroMQ消息是从0向上到任意适合内存大小的blob。

You do your own serialization using protocol buffers, msgpack, JSON, or whatever else your applications need to speak. 
> 你可以使用 protocol buffers、msgpack、JSON或者任何你的程序需要协议 进行序列化。

It’s wise to choose a data representation that is portable, but you can make your own decisions about trade-offs.
> 选择可移植的数据表示法是明智的，需要你自己决定和权衡。

The simplest ZeroMQ message consist of one frame (also called message part). 
> 最简单的ZeroMQ消息有一帧构成。（也可以成为消息部分）

Frames are the basic wire format for ZeroMQ messages. A frame is a length-specified block of data. The length can be zero upwards. 
> 帧是ZeroMQ 消息的最基本的网络格式。一帧是一个固定长度的数据块。长度需要大于0.

ZeroMQ guarantees to deliver all the parts (one or more) for a message, or none of them. This allows you to send or receive a list of frames as a single on-the-wire message.
> ZeroMQ 负责交付消息的所有部分（1个或者更多）,或者没有任何内容。 这允许你将帧列表作为一个单独的消息进行发送和接受。

A message (single or multipart) must fit in memory. If you want to send files of arbitrary sizes, you should break them into pieces and send each piece as separate single-part messages. Using multipart data will not reduce memory consumption.
> 消息（单独或者多部分的）必须适应内存. 如果你要发送任意大小的文件，你应该把它们分成多组然后使用single-part 消息进行多次发送。使用multipart不会消减内存消耗。

## Socket API
- [OfficalWebsite](https://zeromq.org/socket-api/)

Sockets are the de facto standard API for network programming. 
> `de facto`: 事实上的
> Socket 是网络编程事实上的标准API。 

That’s why ZeroMQ presents a familiar socket-based API. 
>那就是为什么ZeroMQ提供熟悉的基于套接字的API.
 
One thing that make ZeroMQ especially tasty to developers is that it uses different socket types to implement any arbitrary messaging pattern.
> ZeroMQ 对开发者特别有吸引力的一件事就是使用不同类型socket去实现任意的消息传递模式.

Furthermore ZeroMQ sockets provide a clean abstraction over the underlying network protocol which hides the complexity of those protocols and makes switching between them very easy.
> 进一步来说，ZeroMQ socket对底层网络协议提供了清晰的抽象，隐藏了那些复杂协议，使得切换起来更加容易。

### Key differences to conventional sockets
- 同传统Socket的主要区别

Generally speaking, conventional sockets present a synchronous interface to either connection-oriented reliable byte streams (SOCK_STREAM), or connection-less unreliable datagrams (SOCK_DGRAM). 
>一般来说，传统套接字给 面向连接的可靠数据流 和 无连接不可靠报文 提供同步接口。

In comparison, ZeroMQ sockets present an abstraction of an asynchronous message queue, with the exact queueing semantics depending on the socket type in use. 
> 相比之下，ZeroMQ socket 提供异步消息队列的抽象， 确切的消息队列语义依赖使用时的socket类型。

Where conventional sockets transfer streams of bytes or discrete datagrams, ZeroMQ sockets transfer discrete messages.
> 传统Socket传输字节流和离散数据，ZeroMQ Socket传输离散消息。

ZeroMQ sockets being asynchronous means that the timings of the physical connection setup and tear down, reconnect and effective delivery are transparent to the user and organized by ZeroMQ itself. 
> ZeroMQ Socket是异步意味着：物理连接建立和关闭、重新连接和有效的交付对用户是透明的，ZeroMQ自身组织管理。

Further, messages may be queued in the event that a peer is unavailable to receive them.
> 此外，消息会在队列中等待，当对方无法收到消息时候。


Conventional sockets allow only strict one-to-one (two peers), many-to-one (many clients, one server), or in some cases one-to-many (multicast) relationships. 
> 传统的Socket只允许严格1对1，多对1（多客户端，1个服务端）或者在某些情况下1对多（多播）的关系。

With the exception of PAIR sockets, ZeroMQ sockets may be connected to multiple endpoints, while simultaneously accepting incoming connections from multiple endpoints bound to the socket, thus allowing many-to-many relationships.
> 除去PAIR，ZeroMQ socket可以允许多个终端连接，同时接受多个终端的绑定，既允许多对多的关系。


### Socket lifetime
ZeroMQ sockets have a life in four parts, just like BSD sockets:
> ZeroMQ socket 生命期有4部分，类似于BSD socket.

- Creating and destroying sockets, which go together to form a karmic circle of socket life
> 创建和销毁socket，共同组成了socket 生命周期循环。

- Configuring sockets by setting options on them and checking them if necessary
> 通过配置选项进行配置socket，并在必要时进行检查。

- Plugging sockets into the network topology by creating ZeroMQ connections to and from them.
> 通过创建ZeroMQ，将其插入网络拓扑中。

- Using the sockets to carry data by writing and receiving messages on them
> 使用socket通过写入和接受消息进行数据传输。

### Bind vs Connect
With ZeroMQ sockets it doesn’t matter who binds and who connects. 
> ZeroMQ 套接字不关心谁绑定 谁连接。

In the above you may have noticed that the server used Bind while the client used Connect.
> 在上面 你注意到，服务器用Bind，客户端用Connect

Why is this, and what is the difference?
> 为什么？有什么区别？


ZeroMQ creates queues per underlying connection. If your socket is connected to three peer sockets, then there are three messages queues behind the scenes.
> ZeroMQ给每个底层连接创建队列。如果你的套接字连接到了3个对等套接字，那么这中场景下会有3个消息队列。
> peer sockets: 可以理解为 对等连接。 例如 Peer-To-Peer Sockets  既 P2P Socket。

With Bind, you allow peers to connect to you, thus you don’t know how many peers there will be in the future and you cannot create the queues in advance. Instead, queues are created as individual peers connect to the bound socket.
> 使用Bind，你允许点连接到你，然而你不知道将会有多少个点连接，你也无法提前创建队列。相反，队列是在每个点连接到套接字时创建的。

With Connect, ZeroMQ knows that there’s going to be at least a single peer and thus it can create a single queue immediately. This applies to all socket types except ROUTER, where queues are only created after the peer we connect to has acknowledge our connection.
> 使用Connect，ZeroMQ知道至少有一个点连接了，会立即创建一个队列。这适用于除ROUTE外的所有套接字类型，队列只会在我们连接到已知的连接后创建。
> 注意：使用connect，ip地址不能是*。必须是明确的ip。 

Consequently, when sending a message to bound socket with no peers, or a ROUTER with no live connections, there’s no queue to store the message to.
> 因此，当发送消息给 没有点连接的某个套接字时，或者没有实时连接的ROUTER时，这里没有队列用于存储消息。

### When should I use bind and when connect?
> As a general rule use bind from the most stable points in your architecture, and use connect from dynamic components with volatile endpoints.
> 一般情况下，在你的架构中对于最稳定的点使用Bind，对于动态的终端使用Connect。

> For request/reply, the service provider might be the point where you bind and the clients are using connect. Just like plain old TCP.
> 对于请求-回应 模式，提供服务的点使用Bind，客户端使用Connect。就像TCp一样。

> If you can’t figure out which parts are more stable (i.e. peer-to-peer), consider a stable device in the middle, which all sides can connect to.
> 如果你无法确定那部分是最稳定的，考虑稳定的设备用Bind，其他的用Connect。


You can read more about this at the ZeroMQ FAQ under the “Why do I see different behavior when I bind a socket versus connect a socket?” section.

### High-Water-Mark
The high water mark is a hard limit on the maximum number of outstanding messages ZeroMQ is queuing in memory for any single peer that the specified socket is communicating with.
> 高水位线是与socket传输数据的对等端在内存中排队为发送消息的最大数的硬限制。

If this limit has been reached the socket enters an exceptional state and depending on the socket type, ZeroMQ will take appropriate action such as blocking or dropping sent messages. 
> 如果到达了这个限制，socket会进入异常状态。并且会依赖于socket 类型，ZeroMQ将会表现出阻塞或者丢弃消息。

Refer to the individual socket descriptions below for details on the exact action taken for each socket type.
> 下一章节是关于各个socket类型的详细描述。

### Messaging Patterns
Underneath the brown paper wrapping of ZeroMQ’s socket API lies the world of messaging patterns. ZeroMQ patterns are implemented by pairs of sockets with matching types.

The built-in core ZeroMQ patterns are:
- **<font color="red">Request-reply</font>**, which connects a set of clients to a set of services. This is a remote procedure call and task distribution pattern.
    > Request-reply 是一组clinet连接一组service的模式。 主要用于远程调用（RPC)和任务分发模式。 

- **<font color="red">Pub-sub</font>**, which connects a set of publishers to a set of subscribers. This is a data distribution pattern.
    > 一组发布者连接一组订阅制。这是数据分发模式。

- **<font color="red">Pipeline</font>**, which connects nodes in a fan-out/fan-in pattern that can have multiple steps and loops. This is a parallel task distribution and collection pattern.
    > 以fan-out/fan-in连接节点的模式，可以有多步骤和循环。这是一个并行任务分发和收集的模式。

    > fan-out fan-in 没有圈钱理解是啥含义？？

- **<font color="red">Exclusive pair</font>**, which connects two sockets exclusively. This is a pattern for connecting two threads in a process, not to be confused with “normal” pairs of sockets.
    > 两个套接字的独有连接。这个模式用于连接同一个进程中的2个线程，不要同“mormal” socket混淆。
    
    > 如果是线程通信，使用队列数据结构就很容易解决，为什么要有这个模式？？？
    > 可能是为了在ZeroMQ编程中，行为统一化处理吧。

There are more ZeroMQ patterns that are still in draft state: 草案状态
- **<font color="red">Client-server</font>**, which allows a single ZeroMQ server talk to one or more ZeroMQ clients. The client always starts the conversation, after which either peer can send messages asynchronously, to the other.
    > 允许单个 ZeroMQ服务器与一个或多个 ZeroMQ客户端通信。客户端始终开始对话，之后任一对等方都可以向另一方异步发送消息。

- **<font color="red">Radio-dish</font>**, which used for one-to-many distribution of data from a single publisher to multiple subscribers in a fan out fashion.
    > 用于以扇出方式将数据从单个发布者到多个订阅者的一对多分发

#### Request-reply pattern


## The Guide
- [OfficalWebsite](https://zguide.zeromq.org/)


## Low-Level API
- [OfficalWebsite](http://api.zeromq.org/)
- [v4.3 stable](http://api.zeromq.org/4-3:_start)
### Basic/最常用的 API
####  zmq_bind
- http://api.zeromq.org/4-3:zmq-bind
#### zmq_connect
- http://api.zeromq.org/4-3:zmq-connect
#### zqm_socket
- http://api.zeromq.org/4-3:zmq_socket

### Request-reply pattern
- [OfficalWebsite](http://api.zeromq.org/master:zmq-socket)
- ZMQ_REQ
    > A socket of type ZMQ_REQ is used by a client to send requests to and receive replies from a service. 
    > ZEM_REQ类型的套接字用于客户端发送请求和 从服务端接受。

    > This socket type allows only an alternating sequence of zmq_send(request) and subsequent zmq_recv(reply) calls.
    > 这种类型socket只允许 zmq_send(request) ，后续紧跟着 zqm_recv(reply)的调用顺序。

    > Each request sent is round-robined among all services, and each reply received is matched with the last issued request.
    > 发送的每个请求在所有服务间进行轮询。每个收到的回应对应匹配最有一次发出的请求。

    > If no services are available, then any send operation on the socket shall block until at least one service becomes available. The REQ socket shall not discard messages.
    > 如果没有可用的服务，每个请求会阻塞知道至少有一个可用的服务。 REQ不会丢弃掉消息。

    Summary of ZMQ_REQ characteristics:总结
    |Item                      ||Comment|内容|
    |--------------------------|------|-------|-------|
    |Compatible peer sockets   |兼容匹配的socket类型|ZMQ_REP, ZMQ_ROUTER            |ZMQ_REP, ZMQ_ROUTER|
    |Direction                 |方向               |Bidirectional                  |双向|
    |Send/receive pattern      |发送/接收模式       |Send, Receive, Send, Receive, …|发送，接受  发送，接受 。。。|
    |Outgoing routing strategy |出站路由策略        |Round-robin                    |循环|
    |Incoming routing strategy |传入路由策略        |Last peer                      |最后一个对等点|
    |Action in mute state      |静音状态下的动作     |Block                          |阻塞|




# 实践笔记
- [参考文章](https://www.cnblogs.com/neooelric/p/9020872.html)


## 数据/消息 发送接收
- `zmq_send()`与`zmq_recv()`是用来传输"数据"的接口. 
- 而"消息"这个术语, 在zmq中有指定含义, 传递消息的接口是`zmq_msg_send()`与`zmq_msg_recv()`
- `zmq_recv()` 有一个缺点：需要预测数据长度，如果你预测的数据长度小于真实长度，会将数据流阶段。这种请使用`zmq_msg_recv()`替代。 
- 当我们说起"数据"的时候, 我们指的是二进制串. 当我们说"消息"的时候, 指提是zmq中的一种特定结构体.
- `zmq_msg_send()`时，会将msg结构体中的数据 清除，放到了消息缓冲中了，如果想多发发送这个消息数据，请在`zmq_msg_send()`前，做好copy。
-  **需要额外注意的是**, 无论是调用`zmq_send()`还是`zmq_msg_send()`, 当调用返回时, **消息并没有真正被发送出去, 更没有被对方收到**. 调用返回只代表zmq将你要发送的"消息"或"数据"放进了一个叫"发送缓冲区"的地方. 这是zmq实现收发异步且带缓冲队列的一个设计.

## I/O线程
我们先前提到过, ZMQ在后台使用独立的线程来实现异步I/O处理. 

一般情况下吧, 一个I/O线程就应该足以处理当前进程的所有socket的I/O作业, 
但是这个凡事总有个极限情况, 所以总会存在一些很荀的场景, 你需要多开几个I/O线程.

当你创建一个context的时候, ZMQ就在背后创建了一个I/O处理线程. 

如果这么一个I/O线程不能满足你的需求, 那么就需要在创建context的时候加一些料, 让ZMQ多创建几个I/O处理线程.

一般有一个简单估算I/O线程数量的方法: 每秒你的程序有几个G字节的吞吐量, 你就开几个I/O线程.

下面是自定义I/O线程数量的方法:
```C++
int io_threads = 4;
void * context = zmq_ctx_new();
zmq_ctx_set(context, ZMQ_IO_THREADS, io_threads);
assert(zmq_ctx_get(context, ZMQ_IO_THREADS) == io_threads);
```
## Client - Service 的Socket Type配对组合
- PUB SUB. 经典的发布-订阅套路
- REQ REP. 经典的请求-应答套路
- REQ ROUTER (注意, REQ发出的数据中, 以一个空帧来区分消息头与消息体)
- DEALER REP(注意, REP假定收到的数据中, 有一个空帧用以区分消息头与消息体)
- DEALER ROUTER
- DEALER DEALER ??
- ROUTER ROUTER ??
- PUSH PULL. 经典的流水线套路.
- PAIR PAIR. 一夫一妻套路

其它没列出的组合的行为是未定义的，请不要使用，避免API出错。


## 三种基本模型 Demo代码

### Request-Reply（请求-回复）
- 可以有 N 个客户端，一个服务端，因此是 1-N 连接。
- 以 “Hello World” 为例。客户端发起请求，并等待服务端回应请求。
- 客户端发送一个简单的 “Hello”，服务端则回应一个 “World”。
- 一个服务端可以多次调用zmq_bind()以将自己关联到多个endpoint上.(所谓的endpoint, 就是通讯协议+通讯地址的组合, 它一般情况下指代了在这种通讯协议中的一个网络结点, 但这个结点可以是逻辑性的, 不一定只是一台机器).这就意味着, zmq socket可以同时接受来自多个不同通讯协议的多组请求消息.
```C++
zmq_bind(socket, "tcp://*:5555");
zmq_bind(socket, "tcp://*:999");
zmq_bind(socket, "inproc://suprise_motherfucker");
```

- 服务端代码如下：
```java
import org.zeromq.ZMQ;
public class ReqRepserver {
    public static void main(String[] args) throws InterruptedException {
        ZMQ.Context context = ZMQ.context(1);
        ZMQ.Socket responder = context.socket(ZMQ.REP);
        responder.bind("tcp://*:5555");
        while (!Thread.currentThread().isInterrupted()) {
            byte[] request = responder.recv(0);
            System.out.println("Received" + new String(request));
            Thread.sleep(1000);
            String reply = "World";
            responder.send(reply.getBytes(),0);
        }
        responder.close();
        context.term();
    }
}
```

```python
import time
import zmq
context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")
while True:
    message = socket.recv()
    print("Received request: %s" % message)
    # Do some 'work'
    time.sleep(1)
    socket.send(b"World")
```

```C++
#include <chrono>
#include <thread>
#include <iostream>

#include <zmq.hpp>

int main()
{
    zmq::context_t context;

    zmq::socket_t repsond(context, zmq::socket_type::rep);

    repsond.bind("tcp://192.168.32.4:9999");

    while (1)
    {
        zmq::message_t msg;
        repsond.recv(msg);
        std::cout << "service recv message:" << std::string(static_cast<char*>(msg.data()), msg.size()) << std::endl;

        std::string msg_name = "Service Receive Success!";// +std::string(static_cast<char*>(reply_buff.data()), reply_buff.size());
        repsond.send(msg_name.c_str(), msg_name.size());
        std::cout << "service send message:" << msg_name << std::endl;

        std::cout << "================================" << std::endl;
    }
    repsond.close();
    context.close();

    return 0;
}

```

- 客户端代码如下:
```java
import org.zeromq.ZMQ;
public class hwclient {
    public static void main(String[] args) {
        ZMQ.Context context = ZMQ.context(1);
        ZMQ.Socket requester = context.socket(ZMQ.REQ);
        requester.connect("tcp://localhost:5555");
        for (int requestNbr = 0; requestNbr != 10; requestNbr++) {
            String request = "Hello";
            System.out.println("Sending Hello" + requestNbr);
            requester.send(request.getBytes(),0);
            byte[] reply = requester.recv(0);
            System.out.println("Reveived " + new String(reply) + " " + requestNbr);
        }
        requester.close();
        context.term();
    }
}
```

```python
import zmq
context = zmq.Context()
print("Connecting to hello world server...")
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")
for request in range(10):
    print("Sending request %s ..." % request)
    socket.send(b"Hello")
    message = socket.recv()
    print("Received reply %s [ %s ]" % (request,message))
```

```C++
#include <chrono>
#include <thread>
#include <iostream>
#include <zmq.hpp>

int main()
{
    zmq::context_t context;

    zmq::socket_t request(context,zmq::socket_type::req);

    request.connect("tcp://192.168.32.4:9999");

    int i = 0;
    while (1)
    {
        ++i;
        std::string msg_name = "World " + std::to_string(i);
        const int send_size = request.send(msg_name.c_str(), msg_name.size());
        std::cout <<"client send message"<< msg_name << std::endl;

        zmq::message_t msg;
        request.recv(msg);//在req-rep中调用send后，必须调用recv。
        std::cout << "client recv message:" << std::string(static_cast<char *>(msg.data()),msg.size()) << std::endl;

        std::cout << "================================" << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));

    }
    request.close();
    context.close();

    return 0;
}

```

- Summary：从以上的过程，我们可以了解到使用 ZMQ 写基本的程序的方法，需要注意的是：
    > 1. 服务端和客户端无论谁先启动，效果是相同的，这点不同于 Socket。
    > 2. 在服务端收到信息以前，程序是阻塞的，会一直等待客户端连接上来。
    > 3. 服务端收到信息后，会发送一个 “World” 给客户端。值得注意的是一定是客户端连接上来以后，发消息给服务端，服务端接受消息然后响应客户端，这样一问一答。
    > 4. ZMQ 的通信单元是消息，它只知道消息的长度，并不关心消息格式。因此，你可以使用任何你觉得好用的数据格式，如 Xml、Protocol Buffers、Thrift、json 等等。

- 性能评测
使用公司的内网环境。笔记本和台式机通信。
```
Spead Time(milliseconds):108 Buffer Size(MB):10
Spead Time(milliseconds):567 Buffer Size(MB):50
Spead Time(milliseconds):1126 Buffer Size(MB):100
Spead Time(milliseconds):1574 Buffer Size(MB):150
Spead Time(milliseconds):2095 Buffer Size(MB):200
Spead Time(milliseconds):2615 Buffer Size(MB):250
Spead Time(milliseconds):3351 Buffer Size(MB):300
Spead Time(milliseconds):4667 Buffer Size(MB):350
Spead Time(milliseconds):5667 Buffer Size(MB):400
Spead Time(milliseconds):4818 Buffer Size(MB):450
Spead Time(milliseconds):5785 Buffer Size(MB):500
Spead Time(milliseconds):5706 Buffer Size(MB):550
Spead Time(milliseconds):6300 Buffer Size(MB):600
Spead Time(milliseconds):8996 Buffer Size(MB):650
Spead Time(milliseconds):9327 Buffer Size(MB):700
Spead Time(milliseconds):9005 Buffer Size(MB):750
Spead Time(milliseconds):9443 Buffer Size(MB):800
Spead Time(milliseconds):11594 Buffer Size(MB):850
Spead Time(milliseconds):17702 Buffer Size(MB):900
Spead Time(milliseconds):25374 Buffer Size(MB):950
Spead Time(milliseconds):13405 Buffer Size(MB):1000
```

### DEALER 和ROUTER 模式
- DEALER就像是一个异步的REQ,
- 而ROUTER就像一个异步的REP。
- ROUTER做代理可以提供可靠的模式来分别识别客户端和后端服务器
- 同REQ 和REP区别
    > 对于Request类型的socket，它是同步的，它一个时刻只能对一个连接进行操作，在一个连接上发送了数据之后，必须接着在这个连接上执行recv，也就是send与recv必须同时匹配出现

    > Response类型的socket也是同步的，与Request的意思差不多，不过顺序是先recv再send

    > Router类型的socket是异步的，他可以在随时执行recv与send，而不必在同一时刻必须要强制在某个连接上进行操作，它会根据标志帧来具体的区分应该在哪一个链接上进行操作

    > Dealer类型的socket，这个更简单的，异步。。。它基本上就没做啥工作。

### Publish-Subscribe（发布-订阅）
- 没有队列缓存，断开连接数据将永远丢失.

下面以一个天气预报的例子来介绍该模式。

服务端不断地更新各个城市的天气，客户端可以订阅自己感兴趣（通过一个过滤器）的城市的天气信息。

- 服务端代码
```java
import org.zeromq.ZMQ;
import java.util.Random;
public class wuserver {
    public static void main(String[] args) {
        ZMQ.Context context = ZMQ.context(1);
        ZMQ.Socket publisher = context.socket(ZMQ.PUB);
        publisher.bind("tcp://*:5556");
        publisher.bind("icp://weather");
        Random srandom = new Random(System.currentTimeMillis());
        while (!Thread.currentThread().isInterrupted()) {
            int zipcode, temperature, relhumidity;
            zipcode = 10000 + srandom.nextInt(10000);
            temperature = srandom.nextInt(215) - 80 + 1;
            relhumidity = srandom.nextInt(50) + 10 + 1;
            String update = String.format("%05d %d %d", zipcode, temperature, relhumidity);
        }
        publisher.close();
        context.term();
    }
}
```

```python
from random import randrange
import zmq
context = zmq.Context()
socket = context.socket(zmq.PUB)
socket.bind("tcp://*:5556")
while True:
    zipcode = randrange(1, 100000)
    temperature = randrange(-80, 135)
    relhumidity = randrange(10, 60)
    socket.send_string("%i %i %i" % (zipcode, temperature, relhumidity))
```

```C++
void pub_sub_module_service()
{
    
    zmq::context_t context;

    zmq::socket_t pub(context,zmq::socket_type::pub);

    pub.bind("tcp://*:9999");
    
    std::vector<std::string> vecMsg{
        "BJ:rain ",
        "BJ:snow ",
        "SY:sunshine ",
        "SY:wind ",
        "HB:cloud ",
        "HE:storm "
    };
    int i = 0;
    while (1) {
        ++i;
        for (const auto& msg:vecMsg)
        {
            pub.send(zmq::buffer(msg+std::to_string(i)));
            std::cout<<Timer::currentTimeString()<<"pub msg no:"<<i<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));//方便测试 等待1秒
        }

    }
    pub.close();
    context.close();
}
```

- 客户端代码
```java
import org.zeromq.ZMQ;
import java.util.StringTokenizer;
public class wuclient {
    public static void main(String[] args) {
        ZMQ.Context context = ZMQ.context(1);
        ZMQ.Socket suscriber = context.socket(ZMQ.SUB);
        suscriber.connect("tcp://localhost:5556");
        String filter = (args.length > 0) ? args[0] : "10001";
        suscriber.suscribe(filter.getBytes());  //过滤条件
        int update_nbr;
        long total_temp = 0;
        for (update_nbr = 0; update_nbr < 100; update_nbr++) {
            String string = suscriber.recvStr(0).trim();
            StringTokenizer sscanf = new StringTokenizer(string, " ");
            int zipcode = Integer.valueOf(sscanf.nextToken());
            int temperature = Integer.valueOf(sscanf.nextToken());
            int relhumidity = Integer.valueOf(sscanf.nextToken());
            total_temp += temperature;
        }
        System.out.println("Average temperature for zipcode '" + filter + "' was " + (int) (total_temp / update_nbr));
        suscriber.close();
        context.term();
    }
}
```

```python
import sys
import zmq
context = zmq.Context()
socket = context.socket(zmq.SUB)
print("Collecting updates from weather server...")
socket.connect("tcp://localhost:5556")
zip_filter = sys.argv[1] if len(sys.argv) > 1 else "10001"
if isinstance(zip_filter, bytes):
    zip_filter = zip_filter.decode('ascii')
socket.setsockopt_string(zmq.SUBSCRIBE, zip_filter)
total_temp = 0
for update_nbr in range(5):
    string = socket.recv_string()
    zipcode, temperature, relhumidity = string.split()
    total_temp += int(temperature)
print("Average temperature for zipcode '%s' was %dF" % (zip_filter, total_temp / (update_nbr + 1)))
```

```C++
void pub_sub_module_client(std::string filerStr)
{
    
    zmq::context_t context;

    zmq::socket_t sub(context,zmq::socket_type::sub);

    sub.connect("tcp://192.168.31.75:9999");
    //sub.connect("tcp://192.168.32.4:9999");
    
    //sub.set(zmq::sockopt::subscribe,"");//接收所有消息

    sub.set(zmq::sockopt::subscribe, filerStr);//只接收前缀为 liqian的消息，例如 liqian1 liqian123

    int i = 0;
    while (1) {
        zmq::message_t msg;
        zmq::recv_result_t res = sub.recv(msg);
        std::cout<<"filter:"<< filerStr << "== NO."<<++i<<" == " << msg.to_string() << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));//方便测试 等待1秒
    }
    sub.close();
    context.close();
}
```

需要注意的是：
> 1. 与 “Hello World” 例子不同的是，Socket 的类型变成 ZMQ.PUB 和 ZMQ.SUB 。
> 2. 客户端需要设置一个过滤条件，接收自己感兴趣的消息。
> 3. 发布者一直不断地发布新消息，如果中途有订阅者退出，其他均不受影响。当订阅者再连接上来的时候，收到的就是后来发送的消息了。
> 4. 这样比较晚加入的或者是中途离开的订阅者必然会丢失掉一部分信息。这是该模式的一个问题，即所谓的 "Slow joiner" 。

### Parallel Pipeline
- 并行管道流
- 这种模式描述的场景是数据被散布到以管道方式组织的各个节点上。管道的每一步都连接一个或多个节点，连接多个节点时数据以RoundRobin方式往下流。
> 注意是流，意味着数据跟发布模式一样是单向的。这个模式对应的socket是ZMQ_PUSH和ZMQ_PULL.

- 如果没有节点接收数据，send会阻塞，消息不会丢失。
- 这种模式也多见于并行计算、分布式计算这些场景中.
- 非常经典的了吧，Push产生消息，Pull角色来拿消息。。。甚至可以用生产者/消费者模型来对应。。。应用场景就非常的广泛了。。。最典型的应用场景就是任务分发。。。


如下 使用例子：
ventilator 分发任务到各个 worker
每个 worker 执行分配到的任务
最后由 sink 收集从 worker 发来的结果

- taskevent
```java
import org.zeromq.ZMQ;
import java.io.IOException;
import java.util.Random;
import java.util.StringTokenizer;
public class taskvent {
    public static void main(String[] args) throws IOException {
        ZMQ.Context context = new ZMQ.context(1);
        ZMQ.Socket sender = context.socket(ZMQ.PUSH);
        sender.bind("tcp://*:5557");
        ZMQ.Socket sink = context.socket(ZMQ.PUSH);
        sink.connect("tcp://localhost:5558");
        System.out.println("Please enter when the workers are ready: ");
        System.in.read();
        System.out.println("Sending task to workes\n");
        sink.send("0",0);
        Random srandom = new Random(System.currentTimeMillis());
        int task_nbr;
        int total_msec = 0;
        for (task_nbr = 0; task_nbr < 100; task_nbr++) {
            int workload;
            workload = srandom.nextInt(100) + 1;
            total_msec += workload;
            System.out.print(workload + ".");
            String string = String.format("%d", workload);
            sender.send(string, 0);
        }
        System.out.println("Total expected cost: " + total_msec + " msec");
        sink.close();
        sender.close();
        context.term();
    }
}
```

```python
import org.zeromq.ZMQ;
import java.io.IOException;
import java.util.Random;
import java.util.StringTokenizer;
public class taskvent {
    public static void main(String[] args) throws IOException {
        ZMQ.Context context = new ZMQ.context(1);
        ZMQ.Socket sender = context.socket(ZMQ.PUSH);
        sender.bind("tcp://*:5557");
        ZMQ.Socket sink = context.socket(ZMQ.PUSH);
        sink.connect("tcp://localhost:5558");
        System.out.println("Please enter when the workers are ready: ");
        System.in.read();
        System.out.println("Sending task to workes\n");
        sink.send("0",0);
        Random srandom = new Random(System.currentTimeMillis());
        int task_nbr;
        int total_msec = 0;
        for (task_nbr = 0; task_nbr < 100; task_nbr++) {
            int workload;
            workload = srandom.nextInt(100) + 1;
            total_msec += workload;
            System.out.print(workload + ".");
            String string = String.format("%d", workload);
            sender.send(string, 0);
        }
        System.out.println("Total expected cost: " + total_msec + " msec");
        sink.close();
        sender.close();
        context.term();
    }
}
```

- taskwork
```java
import org.zeromq.ZMQ;
public class taskwork {
    public static void main(String[] args) {
        ZMQ.Context context = ZMQ.context(1);
        ZMQ.Socket receiver = context.socket(ZMQ.PULL);
        receiver.connect("tcp://localhost:5557");
        ZMQ.Socket sender = context.socket(ZMQ.PUSH);
        sender.connect("tcp://localhost:5558");
        while (!Thread.currentThread().isInterrupted()) {
            String string = receiver.recv(0).trim();
            Long mesc = Long.parseLong(string);
            System.out.flush();
            System.out.print(string + ".");
            Sleep(mesc);
            sender.send("".getBytes(), 0);
        }
        sender.close();
        receiver.close();
        context.term();
    }
}
```

```python
import zmq
import time
import sys
context = zmq.Context()
receiver = context.socket(zmq.PULL)
receiver.connect("tcp://localhost:5557")
sender = context.socket(zmq.PUSH)
sender.connect("tcp://localhost:5558")
while True:
    s = receiver.recv()
    sys.stdout.write('.')
    sys.stdout.flush()
    time.sleep(int(s) * 0.001)
    sender.send(b'')
```

- tasksink
```java
import org.zeromq.ZMQ;
public class tasksink {
    public static void main(String[] args) {
        ZMQ.Context context = ZMQ.context(1);
        ZMQ.Socket receiver = context.socket(ZMQ.PULL);
        receiver.bind("tcp://*:5558");
        String string = new String(receiver.recv(0));
        long tstart = System.currentTimeMillis();
        int task_nbr;
        int total_mesc = 0;
        for (task_nbr = 0; task_nbr < 100; task_nbr++) {
            string = new String(receiver.recv(0).trim());
            if ((task_nbr / 10) * 10 == task_nbr) {
                System.out.print(":");
            } else {
                System.out.print(".");
            }
        }
        long tend = System.currentTimeMillis();
        System.out.println("\nTotal elapsed time: " + (tend - tstart) + "msec");
        receiver.close();
        context.term();
    }
}
```

```python
import time
import zmq
import sys
context = zmq.Context()
receiver = context.socket(zmq.PULL)
receiver.bind("tcp://*:5558")
s = receiver.recv()
tstart = time.time()
for task_nbr in range(1, 100):
    s = receiver.recv()
    if task_nbr % 10 == 0:
        sys.stdout.write(':')
    else:
        sys.stdout.write('.')
    sys.stdout.flush()
tend = time.time()
print("Total elapsed time: %d msec" % ((tend - tstart) * 1000))
```

以下两点需要注意：
> 1. ventilator 使用 ZMQ.PUSH 来分发任务；worker 用 ZMQ.PULL 来接收任务，用 ZMQ.PUSH 来发送结果；sink 用 ZMQ.PULL 来接收 worker 发来的结果。
> 2. ventilator 既是服务端，也是客户端（此时服务端是 sink）；worker 在两个过程中都是客户端；sink 也一直都是服务端。


# FAQ
## `zmq_send`需要注意
- zmq_send 发送消息，会将buffer拷贝一份，内存会翻倍。

# 源码
## 阻塞如何实现
- 