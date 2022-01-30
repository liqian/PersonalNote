# C++中typename和class在声明模板时的区别

# need 'typename' before *** because *** is a dependent scope


# 模板类继承后找不到父类函数的问题
- https://www.cnblogs.com/zl1991/p/7718636.html
错误示例：

```C++
template<class T> class List
{
public:
    void next(T*){
        cout<<"Doing some stuff"<<endl;
    }
};

template<class T> class Special_List: public List<T>
{
public:
    void do_other_stuff(T* item){
            next(item);
    }
};


int main(int argc, char *argv[])
{
    Special_List<int> b;
    int test_int = 3;
    b.do_other_stuff(&test_int);
}
```


使用g++编译，出现如下错误：

```shell
template_eg.cpp: In instantiation of 'void Special_List<T>::do_other_stuff(T*) [with T = int]':
template_eg.cpp:27:35:   required from here
template_eg.cpp:18:25: error: 'next' was not declared in this scope, and no declarations were found by argument-dependent lookup at the point of instantiation [-fpermissive]
template_eg.cpp:18:25: note: declarations in dependent base 'List<int>' are not found by unqualified lookup
template_eg.cpp:18:25: note: use 'this->next' instead
```

解决方法：

1.
```C++
List<T>::next(item)
```

2. 
```C++
template<class T> class Special_List: public List<T>
{
    using List<T>::next;
public:
    void do_other_stuff(T* item){
            next(item);
    }
};
```

原因:
**模板的处理过程分为两步（标准编译，VS是另一种方式）。第一步，在类型实例化前，所有不依赖于模板参数的数据被查找和检查。第二部，类型确定，而后处理剩余的部分。**

现在，在第一阶段，没有迹象表明next函数是依赖于模板参数的，因此它需要再类型例化前被处理。但是基类型是被当前模板例化的，且并不知道类型T会被例化成怎样的类，编译器无法进入基类中查找。

而this->next则将next加入了依赖模板的函数名单，这使得编译器会在第二阶段才查找next函数的实现，这时T是已知类型，基类List<T>也是已知的，编译器可以进入查找。

在处理的第二阶段，查找表只会查找参数依赖表中的函数并添加进表中。如果next函数是一个与T有关的namespace中，那么它会被查找添加，而如果它仅是基类的一个成员函数，那么它对于ADL是不可见的。对于next函数，编译器需要在查找表中检索next，而对于this->next，编译器查找的是this（在第二阶段模板类型例化后），之后才会查找next。