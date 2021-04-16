# const 修饰类对象，常对象
- 常对象只能访问类的 const成员变量和const 函数。
- 
# const 真正修饰的左侧最近元素
1. const 修饰的左侧内容，表说左侧内容是常量
2. 如果左侧没有内容，修饰右侧最近的。
3. const int * p 同 int const * p 是一样的。 代表*p内容不能修改，但是p可以修改。
```C++
    const int* p0 = new int(0);
    int const* p1 = new int(1);
    int* const p2 = new int(2);
    printf("p0=%d\n", *p0);
    printf("p1=%d\n", *p1);
    printf("p2=%d\n", *p2);

    p0 = p1;//指针指向发生变更
    *p2 = 100;//指针指向区域内容发生变更
    
    //*p0 = 200;//指针指向区域为const，不能修改，编译出错: p0不能给常量赋值
    //*p1 = 200;//指针指向区域为const，不能修改，编译出错: p1不能给常量赋值
    //p2 = p1;//指针为const，不能修改，编译出错。“=”: 无法从“const int *”转换为“int *const ”
    printf("p0=%d\n", *p0);
    printf("p1=%d\n", *p1);
    printf("p2=%d\n", *p2);
```
输出结果为：
> p0=0
> p1=1
> p2=2
> p0=1
> p1=1
> p2=100

```C++
    
    
```