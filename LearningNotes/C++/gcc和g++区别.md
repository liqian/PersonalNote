# gcc和g++的主要区别
GCC:GNU Compiler Collection(GUN 编译器集合)，它可以编译C、C++、JAV、Fortran、Pascal、Object-C等语言。
- gcc是GCC中的GUN C Compiler（C 编译器）
- g++是GCC中的GUN C++ Compiler（C++编译器）

1. 对于 *.c和*.cpp文件，gcc分别当做c和cpp文件编译（c和cpp的语法强度是不一样的）

2. 对于 *.c和*.cpp文件，g++则统一当做cpp文件编译

3. 使用g++编译文件时，g++会自动链接标准库STL，而gcc不会自动链接STL

4. gcc在编译C文件时，可使用的预定义宏是比较少的

5. gcc在编译cpp文件时/g++在编译c文件和cpp文件时（这时候gcc和g++调用的都是cpp文件的编译器），会加入一些额外的宏。

6. 在用gcc编译c++文件时，为了能够使用STL，需要加参数 –lstdc++ ，但这并不代表 gcc –lstdc++ 和 g++等价，它们的区别不仅仅是这个。

# g++ 分步编译
1. 预处理
```shell
    g++ -E test.cpp>test.ii
```
这里将预处理的结构保存起来，方便后续使用。
非分步编译时，是不需要的。
2. 编译
```shell
    g++ -S test.ii
```

3. 汇编
```shell
    g++ -c test.s
```

4. 链接
```shell
    g++ -test.o -o test
```

5. 运行
```shell
 ./test
```

1~4步可以整合成一步：
```shell
    g++ test.cpp -o test
```

# gcc 常用选项

|选项     |含义|
|:--------|:---|
|-Idir    |在编译源程序时，增加一个搜索头文件的额外目录。既 include增加一个搜索的额外目录|
|-Ldir    |在编译源程序时，增加一个搜索库文件的额外目录。|
|-llibrary|在编译时增加一个额外的库，苦命为 liblibrary.so 注意：参数中将lib和.so省略。|
|-w       |禁止所有警告|
|-Wwaring |允许产生waring类型的警告|
|-c       |仅对源文件进行编译，不链接生成可执行文件。在对源文件进行查错时或者只需生成目标文件时可以使用这个。|
|-g[gdb]  |在可执行文件中添加调试信息，方便程序调试。如果使用括弧总中的选项，表示加入gdb扩展调试信息，方便使用gdb调试。|-O[0,1,2,3]|对生成的代码使用的优化，括弧中的优化级别。缺省的情况为2级优化，0代表不优化。|


# 编译动态链接库
`-fPIC`选项

## fPIC的目的是什么：
让使用到同一个共享对象的多个进程能尽可能多的共享物理内存。

不加fPIC，则加载so文件时，需要对代码段引用的数据对象需要重定位，重定位会修改代码段的内容,这就造成每个使用这个.so文件代码段的进程在内核里都会生成这个.so文件代码段的copy.每个copy都不一样,取决于这个.so文件代码段和数据段内存映射的位置。

可见，这种方式更消耗内存。

## 不加fPIC选项 是否可以
不加fPIC也可以生成.so文件，但是对于源文件有要求，例如

因为不加fPIC编译的so必须要在加载到用户程序的地址空间时重定向所有表目，所以在它里面不能引用其它地方的代码。

```C++
#include <stdio.h>

int func1(int a)
{
    printf("haha a=%d\n", 2);
    a++;
    return a;
}
```

gcc -shared -o libtest.so test.c 编译将报错

上面代码修改如下，就可以编译通过：
```C++
int func1(int a)
{
//    printf("haha a=%d\n", 2);
    a++;
    return a;
}
```