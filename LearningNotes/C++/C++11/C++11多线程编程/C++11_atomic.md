参考文章：
[C++11 - atomic类型和内存模型](https://zhuanlan.zhihu.com/p/107092432)
[c++11 多线程（3）atomic 总结](https://www.jianshu.com/p/8c1bb012d5f8)
https://zhuanlan.zhihu.com/p/55178835

# 何谓原子操作？
所谓原子操作，就是多线程程序中“**最小的且不可并行化的**”操作。

对于在多个线程间共享的一个资源而言，这意味着同一时刻，多个线程中有且仅有一个线程在对这个资源进行操作，即互斥访问。

# C++ 11中atomic同 互斥 线程锁的区别 优势
1. 引入"原子数据类型"/atomic类型，以达到对开发者掩盖互斥锁、临界区的目的
2. 互斥锁 消耗的系统资源很大（需要用户态切换到内核态）
3. C++11 对常见的原子操作进行了抽象，定义出统一的接口，并根据编译选项/环境产生平台相关的实现。新标准将原子操作定义为atomic模板类的成员函数，囊括了绝大多数典型的操作——读、写、比较、交换等。
4. atomic 可以理解为 CPU指令的原子化。

# atomic 概述
## 重点在于理解：
1. 为什么要引入atomic类型，给开发者带来了哪些好处。
2. atomic类型的原子操作接口中，memory_order参数是干嘛用的。

## atomic 对内置类型的支持
|原子类型名称    |等效方式                    |内置类型 integral-type  |
|:--------------|:--------------------------|:----------------------|
|atomic_bool    |atomic<bool>               | bool                  |
|atomic_char    |atomic<char>               | char                  |
|atomic_schar   |atomic<signed char>        | signed char           |
|atomic_uchar   |atomic<unsigned char>      | unsigned char         |
|atomic_int     |atomic<int>                | int                   |
|atomic_uint    |atomic<unsigned int>       | unsinged int          |
|atomic_short   |atomic<short>              | short                 |
|atomic_ushort  |atomic<unsigned short>     | unsinged short        |
|atomic_long    |atomic<long>               | long                  |
|atomic_ulong   |atomic<unsigned long>      | unsinged long         |
|atomic_llong   |atomic<long long>          | long long             |  
|atomic_ullong  |atomic<unsigned long long> | unsinged long long    |
|atomic_char16_t|atomic<char16_t>           | char16_t              |
|atomic_char32_t|atomic<char32_t>           | char32_t              |
|atomic_wchar_t |atomic<wchar_t>            | wchar_t               |

## atomic类型原子操作接口
|操作                       |atomic_flag|atomic_bool|atomic_integral_type|atomic<bool>|atomic<T*>| atomic<class-type>|
|:--------------------------|:----------|:--------- |:------------------ |:-----------|:-------- |:-------------------|
|test_and_set               | Y         |           |                    |            |          |                    |
|clear                      | Y         |           |                    |            |          |                    |
|is_lock_free               |           |  Y        | Y                  |  Y         |  Y       |  Y                 |
|load                       |           |  Y        | Y                  |  Y         |  Y       |  Y                 |
|store                      |           |  Y        | Y                  |  Y         |  Y       |  Y                 |
|exchange                   |           |  Y        | Y                  |  Y         |  Y       |  Y                 |
|compare_exchange_weak      |           |  Y        | Y                  |  Y         |  Y       |  Y                 |
|compare_exchange_strong    |           |  Y        | Y                  |  Y         |  Y       |  Y                 |
|fetch_add , +=             |           |           | Y                  |            |  Y       |                    |
|fetch_sub , -=             |           |           | Y                  |            |  Y       |                    |
|fetch_or  , |=             |           |  Y        |                    |            |  Y       |                    |
|fetch_and , &=             |           |           | Y                  |            |          |                    |
|fetch_xor , ^=             |           |           | Y                  |            |          |                    |
|++ , --                    |           |           | Y                  |            |  Y       |  Y                 |

请注意表#2最后一列，class-type就是指自定义数据类型/UDT.

但是！UDT要满足以下5个条件，才可作为模板参数去实例化atomic模板：
```C++
#include <atomic>
#include <type_traits>

using namespace std;

struct MY_UDT
{
    //TODO:data member here
};

int main()
{
    auto ret = std::is_trivially_copyable<MY_UDT>::value;
    ret = std::is_copy_constructible<MY_UDT>::value;
    ret = std::is_move_constructible<MY_UDT>::value;
    ret = std::is_copy_assignable<MY_UDT>::value;
    ret = std::is_move_assignable<MY_UDT>::value;

    return 0;
}
```
## lock free
但并不是所有的类型的原子操作是lock-free的,是否是LockFree有时候依赖特定的硬件，如CPU架构等。（intel ARM）

这些操作都包含了一个**is_lock_free()**成员来用于判断该原子类型是原子操作是否是lock-free的。

## std::atomic_flag
- std::atomic_flag是一个原子的布尔类型，可支持两种原子操作：
> 1. test_and_set, 如果atomic_flag对象被设置，则返回true; 如果atomic_flag对象未被设置，则设置之，返回false
> 2. clear. 清楚atomic_flag对象
- std::atomic_flag可用于多线程之间的同步操作，类似于linux中的信号量。使用atomic_flag可实现mutex.

## std::atimic_int std::atomic<int> 

如下代码示例：
```C++
#include <thread>
#include <atomic>
#include <iostream>
#include <list>

std::atomic_int iAtomicCount(0);
int iCount = 0;
void threadunsafefun1()
{
    for (int i = 0; i < 1000; i++)
    {
        printf("iCount:%d\r\n", iCount++);
    }
}
void threadunsafefun2()
{
    for (int i = 0; i < 1000; i++)
    {
        printf("iCount:%d\r\n", iCount--);
    }
}

void threadfun1()
{
    for (int i = 0; i < 1000; i++)
    {
        printf("iAtomicCount:%d\r\n", iAtomicCount++);
    }
}
void threadfun2()
{
    for (int i = 0; i < 1000; i++)
    {
        printf("iAtomicCount:%d\r\n", iAtomicCount--);
    }
}

void testThreadSafe()
{
    std::list<std::thread> lstThread;
    for (int i = 0; i < 1000; i++)
    {
        lstThread.push_back(std::thread(threadfun1));
    }
    for (int i = 0; i < 1000; i++)
    {
        lstThread.push_back(std::thread(threadfun2));
    }

    for (auto& th : lstThread)
    {
        th.join();
    }

     //int x = iAtomicCount.load(std::memory_order_relaxed);
    //printf("finally iAtomicCount:%d\r\n", x);
    std::cout<<"finally iAtomicCount:"<<iAtomicCount<<std::endl;
}

void testThreadUnsafe()
{
    std::list<std::thread> lstThread;
    for (int i = 0; i < 1000; i++)
    {
        lstThread.push_back(std::thread(threadunsafefun1));
    }
    for (int i = 0; i < 1000; i++)
    {
        lstThread.push_back(std::thread(threadunsafefun2));
    }

    for (auto& th : lstThread)
    {
        th.join();
    }

    printf("finally iCount:%d\r\n",  iCount);
}
int main()
{
    testThreadSafe();
    testThreadUnsafe();

    printf("finally iCount:%d\r\n",  iCount);
    std::cout<<"finally iAtomicCount:"<<iAtomicCount<<std::endl;
    return 0;
}
```

iCount:结果不确定，有可能不是0
iAtomicCount:结果是确定的，肯定是0

1. iCount++分析
> 1.1. 先取iCount的值，
> 1.2. 然后iCount+1进行计算
> 1.3. 把 iCount+1结果放回iCount中

>如果有2个线程，同时运行到了1.1步，那么取出的iCount都是0；
>然后进行+1操作，结果都为1；
>然后将结果1放回iCount中；
>那么运行的结果就是1，不是2.

## 内存模型

### 强顺序/弱顺序
通常情况下，内存模型是一个硬件上的概念，
表示的是机器指令（或者将其视为汇编指令也可以）是以什么样的顺序被处理器执行的。

现代的处理器并不是逐条处理机器指令的。

```C++
#include <thread>
#include <atomic>
#include <iostream>
using namespace std;
atomic<int> a{0};
atomic<int> b{0};

int ValueSet(int)
{
    int t=1;
    a=t;
    b=2;
    return 0;
}
```

指令“t=1;a=t;b=2”,其伪汇编代码如下：
1:Loadi     reg3,1;     //将数1 放入寄存器reg3
2:Move      reg4,reg3;  //将reg3的数据放入reg4
3:Store     reg4,a;     //将寄存器reg4放入内存地址a
4:Loadi     reg5,2;     //将数2放入寄存器reg5
5:Store     reg5,b;     //将寄存器reg5放入内存地址b

按照通常的理解，指令总是按照1->2->3->4->5顺序执行的，

如果处理器是按照这个顺序执行的，我们称这样的内存模型为**强顺序的(strong ordered)**。 

这种执行方式下，指令3总是先于指令5执行，即a赋值在前，b赋值在后。


但是指令1、2、3（a赋值）和指令4、5(b赋值)毫不相干。

一些处理器可能将指令乱序执行，比如按照1->4->2->5->3这样的顺序。

如果指令是“乱序”执行的，我们称这样的内存模型为**弱顺序的(weak ordered)**。

这种执行方式下，指令5可能先于指令3被执行，即可能b赋值在前，a赋值在后。

所以在C++11中才出现了指定内存顺序的操作。

```C++
#include <thread>
#include <atomic>
#include <iostream>
using namespace std;
atomic<int> a{0};
atomic<int> b{0};
int ValueSet(int)
{
    int t=1;
    a.store(t,memory_order_relaxed);
    b.store(2,memory_order_relaxed);
    return 0;
}
int Observer(int)
{
    cout<<"("<<a<<","<<b<<")"<<endl;//可能有多种输出
    return 0;
}
int main()
{
    for(int i=0;i<1000;++i){
        a=0;
        b=0;
        thread t1(ValueSet,0);
        thread t2(Observer,0);
        t1.join();
        t2.join();
        cout<<"Got("<<a<<","<<b<<")"<<endl;//Got(1,2)
    }
    
    return 0;
}
```
### memory_order
在C++11标准中，设计者给出的解决方式是让程序员为原子操作指定所谓的内存顺序
```C++
typedef enum memory_order {
	memory_order_relaxed,
	memory_order_consume,
	memory_order_acquire,
	memory_order_release,
	memory_order_acq_rel,
	memory_order_seq_cst
	} memory_order;
```
|枚举值                 |定义规则|
|:---------------------:| --------------------------------------------------------------:|
|memory_order_relaxed   | 不对内存顺序做任何保证                                           |
|memory_order_consume   | 本线程中，所有后续的有关原子类型的操作，必须在本条原子操作完成后执行 |
|memory_order_acquire   | 本线程中，所有的后续读操作必须在本条原子操作完成后执行              |
|memory_order_release   | 本线程中，所有之前的写操作完成后才能执行本条原子操作                |
|memory_order_acq_rel   | 同时包含 memory_order_acquire 和 memory_order_release           | 
|memory_order_seq_cst   | 全部存取都按顺序执行                                             |

1. memory_order_seq_cst
> **定义规则：全部存取都按照顺序执行**
>1. memory_order_seq_cst 表示该原子操作必须顺序一致的.
>2. 这是C++11中所有atomic原子操作的默认值。
>3. 这样来理解“顺序一致”：即代码在线程中运行的顺序与程序员看到的代码顺序一致。
也就是说，用此值提示编译器“不要给我重排序指令，不要整什么指令乱序执行，就按照我代码的先后顺序执行机器指令”。

2. memory_order_relaxed
> **定义规则：不对执行顺序做任何保证。**
>1. 表示该原子操作指令可以任由编译器重排或者由处理器乱序执行。
>2. 就是说”想怎么乱就怎么乱吧，不管了，只要能提高指令执行效率“。

3. memory_order_acquire
> **规则定义：本线程中，所有后续的读操作，必须在本条原子操作完成后执行。(本线程中，我先读，你们后读……)**

4. memory_order_release
> **规则定义：本线程中，所有之前的写操作完成后，才能执行本原子操作。（在本线程中，你们先写，我最后写……）**

5. memory_order_consume
> **规则定义：本线程中，所有后续的有关本数据的操作，必须在本条原子操作完成之后执行。(本线程中，我只关心我自己，当我用memory_order_consume时，后面所有对我的读写操作都不能被提前执行……)**

# atomic 详解

## `<atomic>`头文件结构
原子类型是封装了一个值的类型，它的访问保证不会导致数据的竞争，并且可以用于在不同的线程之间同步内存访问。
[cppreference atomic header](https://en.cppreference.com/w/cpp/header/atomic)


|Class      |说明                                             |
|:----------|:------------------------------------------------|
|atomic     |用于bool、整数和指针类型的原子类模板和特殊化 (类模板)|
|atomic_flag|无锁布尔原子类型(类)                               |

|Types            |说明                                             |
|:----------------|:------------------------------------------------|
|memory_order     |为给定的原子操作定义内存排序约束(typedef)           |

|Typedefs                   |                               | 
|:--------------------------|:------------------------------|
|std::atomic_bool           |std::atomic<bool>              |
|std::atomic_char           |std::atomic<char>              |
|std::atomic_schar          |std::atomic<signed char>       |
|std::atomic_uchar          |std::atomic<unsigned char>     |
|std::atomic_short          |std::atomic<short>             |
|std::atomic_ushort         |std::atomic<unsigned short>    |
|std::atomic_int            |std::atomic<int>               |
|std::atomic_uint           |std::atomic<unsigned int>      |
|std::atomic_long           |std::atomic<long>              |
|std::atomic_ulong          |std::atomic<unsigned long>     |
|std::atomic_llong          |std::atomic<long long>         |
|std::atomic_ullong         |std::atomic<unsigned long long>|
|std::atomic_char16_t       |std::atomic<char16_t>          |
|std::atomic_char32_t       |std::atomic<char32_t>          |
|std::atomic_wchar_t        |std::atomic<wchar_t>           |
|std::atomic_int_least8_t   |std::atomic<int_least8_t>      |
|std::atomic_uint_least8_t  |std::atomic<uint_least8_t>     |
|std::atomic_int_least16_t  |std::atomic<int_least16_t>     |
|std::atomic_uint_least16_t |std::atomic<uint_least16_t>    |
|std::atomic_int_least32_t  |std::atomic<int_least32_t>     |
|std::atomic_uint_least32_t |std::atomic<uint_least32_t>    |
|std::atomic_int_least64_t  |std::atomic<int_least64_t>     |
|std::atomic_uint_least64_t |std::atomic<uint_least64_t>    |
|std::atomic_int_fast8_t    |std::atomic<int_fast8_t>       |
|std::atomic_uint_fast8_t   |std::atomic<uint_fast8_t>      |
|std::atomic_int_fast16_t   |std::atomic<int_fast16_t>      |
|std::atomic_uint_fast16_t  |std::atomic<uint_fast16_t>     |
|std::atomic_int_fast32_t   |std::atomic<int_fast32_t>      |
|std::atomic_uint_fast32_t  |std::atomic<uint_fast32_t>     |
|std::atomic_int_fast64_t   |std::atomic<int_fast64_t>      |
|std::atomic_uint_fast64_t  |std::atomic<uint_fast64_t>     |
|std::atomic_intptr_t       |std::atomic<intptr_t>          |
|std::atomic_uintptr_t      |std::atomic<uintptr_t>         |
|std::atomic_size_t         |std::atomic<size_t>            |
|std::atomic_ptrdiff_t      |std::atomic<ptrdiff_t>         |
|std::atomic_intmax_t       |std::atomic<intmax_t>          |
|std::atomic_uintmax_t      |std::atomic<uintmax_t>         |

|Functions          |                                                        |
|:------------------|:-------------------------------------------------------|
|kill_dependency    | 从std::memory_order_consume依赖树中删除指定对象 (模版函数)|
|atomic_thread_fence| 通用内存顺序依赖关系的隔离同步原语(函数)                   |
|atomic_signal_fence| 在同一线程中执行的线程和信号处理程序之间的隔离(函数)        |

|Functions for atomic objects (C-style)|description                                                                                         |
|:-------------------------------------|:---------------------------------------------------------------------------------------------------|
|atomic_is_lock_free                                |  检查原子类型的操作是否免锁的（函数模板）                                                 |
|atomic_store </br> atomic_store_explicit           |  使用非原子参数以原子方式替换原子对象的值（函数模板）                                      |  
|atomic_load </br> atomic_load_explicit             |  在原子对象中原子性地获取存储的值（函数模板）                                             |
|atomic_exchange </br> atomic_exchange_explicit     |  原子性地用非原子参数替换原子对象的值，并返回原子的旧值。（函数模板）                        |
|atomic_compare_exchange_weak                       |  原子地比较原子对象和非原子参数的值，如果不相等，则执行原子交换，如果没有，就load atomic     |
|atomic_compare_exchange_weak_explicit              |  原子地比较原子对象和非原子参数的值，如果不相等，则执行原子交换，如果没有，就load atomic     |
|atomic_compare_exchange_strong                     |  原子地比较原子对象和非原子参数的值，如果不相等，则执行原子交换，如果没有，就load atomic     |
|atomic_compare_exchange_strong_explicit            |  原子地比较原子对象和非原子参数的值，如果不相等，则执行原子交换，如果没有，就load atomic     |
|atomic_fetch_add </br> atomic_fetch_add_explicit   |  向原子对象添加非原子值，并获取原子的前值(函数模板)                                       |
|atomic_fetch_sub </br> atomic_fetch_sub_explicit   |  从原子对象中减去非原子值，并获得原子的前值(函数模板)                                     |
|atomic_fetch_and </br> atomic_fetch_and_explicit   |  用逻辑结果和非原子参数替换原子对象，并获得原子的前值(函数模板)                            |
|atomic_fetch_or </br> atomic_fetch_or_explicit     |  用逻辑或非原子参数替换原子对象，并获得原子的前值(函数模板)                                |
|atomic_fetch_xor </br> atomic_fetch_xor_explicit   |  用逻辑XOR和非原子参数替换原子对象，并获得原子的前值(函数模板)                             |


|Functions for atomic flags (C-style)   |description                                  |
|:--------------------------------------|:--------------------------------------------|
|atomic_flag_test_and_set               |  原子地将flag设置为true并返回其先前的值 (函数) |
|atomic_flag_test_and_set_explicit      |  原子地将flag设置为true并返回其先前的值 (函数) |
|atomic_flag_clear                      |  原子地将flag设置成false（函数）              |
|atomic_flag_clear_explicit             |  原子地将flag设置成false（函数）              |

|Preprocessor macros|description                        |
|:------------------|:----------------------------------|
|ATOMIC_VAR_INIT    |静态存储时间的原子变量的常量初始化(宏)|
|ATOMIC_FLAG_INIT   |初始化 std::atomic_flag为 false     |

Macro constants:
```C++
// lock-free property
#define ATOMIC_BOOL_LOCK_FREE /*unspecified*/
#define ATOMIC_CHAR_LOCK_FREE /*unspecified*/
#define ATOMIC_CHAR16_T_LOCK_FREE /*unspecified*/
#define ATOMIC_CHAR32_T_LOCK_FREE /*unspecified*/
#define ATOMIC_WCHAR_T_LOCK_FREE /*unspecified*/
#define ATOMIC_SHORT_LOCK_FREE /*unspecified*/
#define ATOMIC_INT_LOCK_FREE /*unspecified*/
#define ATOMIC_LONG_LOCK_FREE /*unspecified*/
#define ATOMIC_LLONG_LOCK_FREE /*unspecified*/
#define ATOMIC_POINTER_LOCK_FREE /*unspecified*/
```

以上C-Style的函数，去掉 `atomic_`就是C++ style的函数了。

## std::atomic
```C++
定义 ：  //类模版
template< class T > struct atomic;  (1)      (since C++11)
template<>  struct atomic<Integral>;  (2)   (since C++11)
template<>  struct atomic<bool>;   (3)  (since C++11)
template< class T >  struct atomic<T*>;  (4)     (since C++11) 指针特化
```

std::atomic模板的每个实例化和专门化都定义了一个原子类型。

如果一个线程在另一个线程读取它时写入一个原子对象，那么行为就会被明确定义(参见关于数据竞争的详细信息的内存模型)。

此外，对原子对象的访问可以建立线程间的同步，并按照std::memoryorder指定非原子性的内存访问。

std::atomic可以用任何简单的可复制的实例化。

同时std::atomic是不可复制的，也不是可移动的


### Member functions

1. (constructor)构造函数
```C++
atomic() noexcept = default;(1)             default        (since C++11)
constexpr atomic( T desired ) noexcept;(2)  initialization (since C++11)
atomic( const atomic& ) = delete;(3)       copy [deleted] (since C++11)
```
> 构造新的原子变量：
> 1. 将原子对象放在未初始化的状态中。一个未初始化的原子对象可以通过调用atomicinit来初始化。
> 2. 用desired 初始化对象。初始化不是原子性的。
> 3. 原子变量不是可复制的。

Example:
```C++
  // constructing atomics
  #include <iostream>       // std::cout
  #include <atomic>         // std::atomic, std::atomic_flag,   ATOMIC_FLAG_INIT
  #include <thread>         // std::thread, std::this_thread::yield
  #include <vector>         // std::vector

  std::atomic<bool> ready (false);
  std::atomic_flag winner = ATOMIC_FLAG_INIT;

  void count1m (int id) {
    while (!ready) { std::this_thread::yield(); }      // wait for the ready signal
    for (volatile int i=0; i<1000000; ++i) {}          // go!, count to 1 million
    if (!winner.test_and_set()) { std::cout << "thread #" << id << " won!\n"; }
  };

  int main ()
  {
    std::vector<std::thread> threads;
    std::cout << "spawning 10 threads that count to 1 million...\n";
    for (int i=1; i<=10; ++i) threads.push_back(std::thread(count1m,i));
    ready = true;
    for (auto& th : threads) th.join();
  
    return 0;
  }
  ```

2. operator=
```C++
T operator=( T desired ) noexcept;               set value (1)
T operator=( T desired ) volatile noexcept;      set value (1)
atomic& operator=( const atomic& ) = delete;          copy [deleted] (2)
atomic& operator=( const atomic& ) volatile = delete; copy [deleted] (2)
```

> 1. 用val替换存储的值。该操作是原子性的，并使用顺序一致性(memoryorderseqcst)。要使用不同的内存排序来修改值，请参见atomic::store。
> 2. 原子对象没有定义的复制赋值，但是注意它们是可以隐式地转换为类型T。
> 注意：与大多数赋值运算符不同，原子类型的赋值运算符不会返回对它们的左参数的引用。它们返回一个存储值的副本。

```C++
   // atomic::operator=/operator T example:
  #include <iostream>       // std::cout
  #include <atomic>         // std::atomic
  #include <thread>         // std::thread, std::this_thread::yield
  
   std::atomic<int> foo(0);
  
   void set_foo(int x) {
   foo = x;
 }

  void print_foo() {
    while (foo==0) {             // wait while foo=0
      std::this_thread::yield();
    }
    std::cout << "foo: " << foo << '\n';
  }

  int main ()
  {
    std::thread first (print_foo);
    std::thread second (set_foo,10);
    first.join();
    second.join();
    return 0;
  }
```
### General atomic operations

1. std::atomic::is_lock_free
```C++
bool is_lock_free() const noexcept;
bool is_lock_free() const volatile noexcept;
```

> 一个无锁对象并不会导致其他线程在访问时被阻塞(可能使用某种类型的事务性内存)。
> 该函数返回的值与相同类型的所有其他对象返回的值一致。
> 检查这个类型的所有对象的原子操作是否都是无锁的。返回true表示lock_free.

Example:
```C++
  #include <iostream>
  #include <utility>
  #include <atomic>
   
  struct A { int a[100]; };
  struct B { int x, y; };
  int main()
  {
      std::cout << std::boolalpha
              << "std::atomic<A> is lock free? "
              << std::atomic<A>{}.is_lock_free() << '\n'
              << "std::atomic<B> is lock free? "
              << std::atomic<B>{}.is_lock_free() << '\n';
       return 0;
  }
```

2. std::atomic::store std::atomic::load
```C++
void store (T val, memory_order sync = memory_order_seq_cst) volatile noexcept;
void store (T val, memory_order sync = memory_order_seq_cst) noexcept;

T load (memory_order sync = memory_order_seq_cst) const volatile noexcept;
T load (memory_order sync = memory_order_seq_cst) const noexcept;
```
> store 存写数据  load 读取数据。 
> 操作是原子的，按照同步所指定的内存顺序内存数序包括（std::memory_order_relaxed, std::memory_order_release 和std::memory_order_seq_cst）

Example:
```C++
  // atomic::load/store example
  #include <iostream>       // std::cout
  #include <atomic>         // std::atomic, std::memory_order_relaxed
  #include <thread>         // std::thread

  std::atomic<int> foo (0);

  void set_foo(int x) {
    foo.store(x,std::memory_order_relaxed);     // set value atomically
  }

  void print_foo() {
    int x;
    do {
      x = foo.load(std::memory_order_relaxed);  // get value atomically
    } while (x==0);
    std::cout << "foo: " << x << '\n';
  }

  int main ()
  {
    std::thread first (print_foo);
    std::thread second (set_foo,10);
    first.join();
    second.join();
    return 0;
  }
```

3. std::atomic::operator T
```C++
operator T() const volatile noexcept;
operator T() const noexcept;
```

> 这是一个类型转换的操作符:这个表达式期望它包含的类型(T)的值，调用这个成员函数，访问包含的值。
> 该操作是原子的，并使用顺序一致性(memory_order_seq_cst)。
> 相当于std::atomic::load。

Example:
```C++
  // atomic::operator=/operator T example:
  #include <iostream>       // std::cout
  #include <atomic>         // std::atomic
  #include <thread>         // std::thread, std::this_thread::yield

  std::atomic<int> foo(0);
  std::atomic<int> bar(0);

  void set_foo(int x) {
    foo = x;
  }
  void copy_foo_to_bar () {
    while (foo==0) std::this_thread::yield();
    bar = static_cast<int>(foo);
  }
  void print_bar() {
    while (bar==0) std::this_thread::yield();
    std::cout << "bar: " << bar << '\n';
  }

  int main ()
  {
    std::thread first (print_bar);
    std::thread second (set_foo,10);
    std::thread third (copy_foo_to_bar);
    first.join();
    second.join();
    third.join();
    return 0;
  }
```

4. std::atomic::exchange
```C++
T exchange (T val, memory_order sync = memory_order_seq_cst) volatile noexcept;
T exchange (T val, memory_order sync = memory_order_seq_cst) noexcept;
```

> 访问和修改包含的值
> 用val替换所包含的值，并返回它之前的值。
> 整个操作是原子性的(一个原子的读-修改-写操作):在读取(返回)值和被该函数修改的那一刻之间，值不会受到其他线程的影响。

Example:
```C++
  // atomic::exchange example
  #include <iostream>       // std::cout
  #include <atomic>         // std::atomic
  #include <thread>         // std::thread
  #include <vector>         // std::vector

  std::atomic<bool> ready (false);
  std::atomic<bool> winner (false);

  void count1m (int id) {
    while (!ready) {}                  // wait for the ready signal
    for (int i=0; i<1000000; ++i) {}   // go!, count to 1 million
    if (!winner.exchange(true)) { std::cout << "thread #" << id << " won!\n"; }
  };

  int main ()
  {
    std::vector<std::thread> threads;
    std::cout << "spawning 10 threads that count to 1 million...\n";
    for (int i=1; i<=10; ++i) threads.push_back(std::thread(count1m,i));
    ready = true;
    for (auto& th : threads) th.join();

    return 0;
  }
```

5. std::atomic::compare_exchange_weak 和std::atomic::compare_exchange_strong
```C++
bool compare_exchange_weak (T& expected, T val,
    memory_order sync = memory_order_seq_cst) volatile noexcept;  (1)
bool compare_exchange_weak (T& expected, T val,
    memory_order sync = memory_order_seq_cst) noexcept;           (1)

bool compare_exchange_weak (T& expected, T val,
    memory_order success, memory_order failure) volatile noexcept;  (2)
bool compare_exchange_weak (T& expected, T val,
    memory_order success, memory_order failure) noexcept;           (2)

bool compare_exchange_strong (T& expected, T val,
    memory_order sync = memory_order_seq_cst) volatile noexcept;  (1)
bool compare_exchange_strong (T& expected, T val,
    memory_order sync = memory_order_seq_cst) noexcept;           (1)

bool compare_exchange_strong (T& expected, T val,
    memory_order success, memory_order failure) volatile noexcept; (2)
bool compare_exchange_strong (T& expected, T val,
    memory_order success, memory_order failure) noexcept;          (2)
```

* 比较原子对象的包含值与预期的内容:
--1 如果是真的，它会用val替换包含的值(比如存储)。
--2 如果是假的，它会用所包含的值替换预期,因此调用该函数之后，如果被该原子对象封装的值与参数 expected 所指定的值不相等，expected 中的内容就是原子对象的旧值。
e.g:
atomic_int a=5;
expected =6
compare_exchange_strong(expected,7);
expected =5 //


* 函数总是访问包含的值来读取它，如果这个比较是真的，那么它也会替换它。但是整个操作都是原子性的:在读取值和被替换的时刻之间，它的值不能被其他线程修改。

* 在第(2)种情况下，内存序（Memory Order）的选择取决于比较操作结果，如果比较结果为 true(即原子对象的值等于 expected)，则选择参数 success 指定的内存序，否则选择参数 failure 所指定的内存序。

**注意**
这个函数直接的比较物理内容所包含的价值与预期的内容,这可能导致得到使用operator==比较的结果是一个失败的结果,因为对象底层的物理内容中可能存在位对齐或其他逻辑表示相同但是物理表示不同的值(比如 true 和 2 或 3，它们在逻辑上都表示"真"，但在物理上两者的表示并不相同)。
不像 compare_exchange_strong，这个弱版本允许(spuriously 地)返回 false(即原子对象所封装的值与参数 expected 的物理内容相同，但却仍然返回 false)，即使在预期的实际情况与所包含的对象相比较时也是如此。对于某些循环算法来说，这可能是可接受的行为，并且可能会在某些平台上带来显著的性能提升。在这些虚假的失败中，函数返回false，而不修改预期。
对于非循环算法来说， compare_exchange_strong通常是首选。

```C++
  // atomic::compare_exchange_weak example:
  #include <iostream>       // std::cout
  #include <atomic>         // std::atomic
  #include <thread>         // std::thread
  #include <vector>         // std::vector

  // a simple global linked list:
  struct Node { int value; Node* next; };
  std::atomic<Node*> list_head (nullptr);

  void append (int val) {     // append an element to the list
    Node* oldHead = list_head;
    Node* newNode = new Node {val,oldHead};

    // what follows is equivalent to: list_head = newNode, but in a thread-safe way:
    while (!list_head.compare_exchange_weak(oldHead,newNode))
      newNode->next = oldHead;
  }

  int main ()
  {
    // spawn 10 threads to fill the linked list:
    std::vector<std::thread> threads;
    for (int i=0; i<10; ++i) threads.push_back(std::thread(append,i));
    for (auto& th : threads) th.join();

    // print contents:
    for (Node* it = list_head; it!=nullptr; it=it->next)
      std::cout << ' ' << it->value;
    std::cout << '\n';

    // cleanup:
    Node* it; while (it=list_head) {list_head=it->next; delete it;}

    return 0;
  }
```

> compare_exchange_strong 跟 compare_exchange_week 不同的是：
> 与weak 不同, strong版本的 compare-and-exchange 操作不允许(spuriously 地)返回 false，
> 即原子对象所封装的值与参数 expected 的物理内容相同，比较操作一定会为 true。
> 不过在某些平台下，如果算法本身需要循环操作来做检查， compare_exchange_weak 的性能会更好。

### 特定的操作支持(整形和指针)
1. std::atomic::fetch_add/std::atomic::fetch_sub
```C++
if T is integral (1)    
  T fetch_add (T val, memory_order sync = memory_order_seq_cst) volatile noexcept;
  T fetch_add (T val, memory_order sync = memory_order_seq_cst) noexcept;
  T fetch_sub (T val, memory_order sync = memory_order_seq_cst) volatile noexcept;
  T fetch_sub (T val, memory_order sync = memory_order_seq_cst) noexcept;
if T is pointer (2) 
  T fetch_add (ptrdiff_t val, memory_order sync = memory_order_seq_cst) volatile noexcept;
  T fetch_add (ptrdiff_t val, memory_order sync = memory_order_seq_cst) noexcept;
  T fetch_sub (ptrdiff_t val, memory_order sync = memory_order_seq_cst) volatile noexcept;
  T fetch_sub (ptrdiff_t val, memory_order sync = memory_order_seq_cst) noexcept;
```

> 1. 加或者减去val值,并返回在操作之前的值。
> 2. 整个操作是原子的(一个原子的读-修改-写操作):当在这个函数被修改的时候,读取的(返回)值被读取，值不受其他线程的影响。
> 3. 这个成员函数是对整数(1)和指针(2)类型(除了bool除外)的原子专门化中定义。
> 4. 如果第二个参数使用默认值，则该函数等价于原子::运算符+ =。

Example
```C++
#include <iostream>
#include <thread>
#include <atomic>
 
std::atomic<long long> data;
void do_work()
{
  data.fetch_add(1, std::memory_order_relaxed);
}
 
int main()
{
  std::cout << "Init:" << data << '\n';
  std::thread th1(do_work);
  std::thread th2(do_work);
  std::thread th3(do_work);
  std::thread th4(do_work);
  std::thread th5(do_work);

  th1.join();
  th2.join();
  th3.join();
  th4.join();
  th5.join();

  std::cout << "Result:" << data << '\n';
  return 0;
}
```

2. std::atomic::fetch_and/std::atomic::fetch_or/std::atomic::fetch_xor
```C++
  T fetch_and (T val, memory_order sync = memory_order_seq_cst) volatile noexcept;
  T fetch_and (T val, memory_order sync = memory_order_seq_cst) noexcept;
  T fetch_or (T val, memory_order sync = memory_order_seq_cst) volatile noexcept;
  T fetch_or (T val, memory_order sync = memory_order_seq_cst) noexcept;
  T fetch_xor (T val, memory_order sync = memory_order_seq_cst) volatile noexcept;
  T fetch_xor (T val, memory_order sync = memory_order_seq_cst) noexcept;
```
> 1. 读取包含的值并替换调该值和val执行一个位和操作的结果。
> 2. 整个操作是原子的(一个原子的读-修改-写操作):当在这个函数被修改的时候,读取的(返回)值被读取，值不受其他线程的影响。
> 3. 这个成员函数只在原子专门化中定义为整数类型(除了bool)。
> 4. 如果第二个参数使用默认值，则该函数等价于原子::operator& =。

3. std::atomic::operator++/std::atomic::operator--
```C++
pre-increment (1):
       T operator++() volatile noexcept;
       T operator++() noexcept;
       T operator--() volatile noexcept;
       T operator--() noexcept;
post-increment (2) :
       T operator++ (int) volatile noexcept;
       T operator++ (int) noexcept;
       T operator-- (int) volatile noexcept;
       T operator-- (int) noexcept;
```
>  包含值的值进行增加或减少1，操作(1)返回所得到的包含值，操作(2)返回之前的值。
>  整个操作是原子的(一个原子的读-修改-写操作):当在这个函数被修改的时候,读取的(返回)值被读取，值不受其他线程的影响。
>  函数只在原子专门化中定义为整数和指针类型(除了bool)。
>  这个函数的行为就像调用std::stomic::fetch_add(1),memory_order_seq_cst作为参数。

4. atomic::operator (comp. assign.)
```C++
if T is integral (1)    
       T operator+= (T val) volatile noexcept;
       T operator+= (T val) noexcept;
       T operator-= (T val) volatile noexcept;
       T operator-= (T val) noexcept;
       T operator&= (T val) volatile noexcept;
       T operator&= (T val) noexcept;
       T operator|= (T val) volatile noexcept;
       T operator|= (T val) noexcept;
       T operator^= (T val) volatile noexcept;
       T operator^= (T val) noexcept;
if T is pointer (2) 
       T operator+= (ptrdiff_t val) volatile noexcept;
       T operator+= (ptrdiff_t val) noexcept;
       T operator-= (ptrdiff_t val) volatile noexcept;
       T operator-= (ptrdiff_t val) noexcept;
```
> 对于整形(1)和指针(2)类型的原子专门化是支持复合赋值的;每一个函数都访问包含的值，应用合适的操作符，并在操作之前返回包含值的值;
> 所有这些操作都不会受到其他线程的影响。
> 这些函数的行为就像使用memory_order_seq_cst调用std::stomic::fetch_ *函数一样:

## atomic_flag
atomic_flag是一个原子布尔类型。

不同于std::atomic的所有专门化，它保证是lock_free。

不像std::stomic< bool >，std::atomic_flag不提供负载或存储操作。
```C++
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
 
std::atomic_flag lock = ATOMIC_FLAG_INIT;
 
void f(int n)
{
    for (int cnt = 0; cnt < 100; ++cnt) {
        while (lock.test_and_set(std::memory_order_acquire))  // acquire lock
             ; // spin
        std::cout << "Output from thread " << n << '\n';
        lock.clear(std::memory_order_release);               // release lock
    }
}
 
int main()
{
    std::vector<std::thread> v;
    for (int n = 0; n < 10; ++n) {
        v.emplace_back(f, n);
    }
    for (auto& t : v) {
        t.join();
    }
    return 0;
}
```

1. 构造函数(std::atomic_flag::atomic_flag)
```C++
  atomic_flag() noexcept = default;
  atomic_flag (const atomic_flag&T) = delete;
```
>  atomic_flag在构建(或设置或清除)上处于一个未指定的状态，除非它被显式地初始化为ATOMIC_FLAG_INIT。
> ATOMIC_FLAG_INIT初始化是通过简单地调用默认构造函数或其他方法来实现的，这取决于特定的库实现。
> atomic_flag值不能复制/移动。
**注意： std::atomic_flag::operator= 不可赋值，其赋值操作符被删除**

```C++
  // constructing atomics: atomic<bool> vs atomic_flag
  #include <iostream>       // std::cout
  #include <atomic>         // std::atomic, std::atomic_flag, ATOMIC_FLAG_INIT
  #include <thread>         // std::thread, std::this_thread::yield
  #include <vector>         // std::vector

  std::atomic<bool> ready (false);               // can be checked without being set
  std::atomic_flag winner = ATOMIC_FLAG_INIT;    // always set when checked

  void count1m (int id) {
      while (!ready) { 
        std::this_thread::yield(); 
      }      // wait for the ready signal
      for (int i=0; i<1000000; ++i) {}                   // go!, count to 1 million
      if (!winner.test_and_set()) { 
        std::cout << "thread #" << id << " won!\n"; 
      }
  };

  int main ()
  {
      std::vector<std::thread> threads;
      std::cout << "spawning 10 threads that count to 1 million...\n";

      for (int i=1; i<=10; ++i) 
        threads.push_back(std::thread(count1m,i));
      ready = true;
      for (auto& th : threads) th.join();
  
      return 0;
  }
```
执行输出结果：
spawning 10 threads that count to 1 million...
thread #6 won!

2. std::atomic_flag::test_and_set
```C++
    bool test_and_set (memory_order sync = memory_order_seq_cst) volatile noexcept;
    bool test_and_set (memory_order sync = memory_order_seq_cst) noexcept;
```
>  设置atomic_flag并返回是否在调用之前已经设置的。
>  整个操作是原子的(一个原子的读-修改-写操作):当在这个函数被修改的时候,读取的(返回)值被读取，值不受其他线程的影响。

3. std::atomic_flag::clear
```C++
    void clear (memory_order sync = memory_order_seq_cst) volatile noexcept;
    void clear (memory_order sync = memory_order_seq_cst) noexcept;
```
> 清除atomic_flag(即把atomic_flag 设为假)。
> 清除atomic_flag使下一次调用成员atomic_flag::test_and_set对象返回false。
> 操作是原子的，按照sync所指定的内存顺序。

## Functions
1. std::kill_dependency
```C++
  template <class T>
    T kill_dependency (T y) noexcept;
```
> 返回y的值而不需要依赖项。
> 使用memory_order_consume 作为内存顺序的原子操作，要求编译器检查通过访问存储的内存位置所带来的依赖关系。同步这样的依赖关系可能会导致某些硬件设置被设置，并迫使编译器放弃涉及这些内存位置的某些潜在优化。
> 调用此函数指示编译器，任何依赖于y的依赖项都不应被传递到返回值，而不需要同步。

2. atomic_thread_fence
"C"风格导出的函数：
```C++
  extern "C" void atomic_thread_fence (memory_order sync) noexcept;
```
> 建立一个多线程的隔离:对这个函数的调用的时间点变成一个获取或者一个释放(或者两者都是)的同步点。
> 在调用这个函数之前发生的释放线程的所有可见的副作用都是同步的，在调用这个函数在获取线程之前。
> 调用该函数与加载或存储原子操作具有相同的效果，但不涉及原子值。

3. atomic_signal_fence
“C”风格导出的函数：
```C++
  extern "C" void atomic_signal_fence (memory_order sync) noexcept;
```
> 建立一个单线程的隔离:对这个函数的调用点在一个线程内变成一个获取或一个释放点(或者两者)。
> 这个函数相当于atomic_thread_fence ，但是没有因为调用而发生线程间同步。该函数的作用是对编译器进行指令，以阻止它进行优化，包括将写操作移动到一个释放栅栏或在获取栅栏之前的读操作。

## Macro functions
1. ATOMIC_VAR_INIT
> ATOMIC_VAR_INIT(val) //初始化 std::atomic 对象。
> 这个宏的存在是为了与C实现兼容，在其中，它被用作构造函数(默认构造的)原子对象;在C++中，这个初始化可以由初始化构造函数直接执行。
2. ATOMIC_FLAG_INIT
> ATOMIC_FLAG_INIT //初始化 std::atomic_flag 对象。
> 这个宏的定义用来将类型std::atomic_flag的对象初始化到clear的状态。

