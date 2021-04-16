# GDB 是什么
- The GNU Project Debugger
- http://www.gnu.org/software/gdb/
- 调试程序时候使用的。
- 支持绝大多数的系统 Linux MacOS Windows(不常用)
- 支持的语言：
    1. Ada
    2. Assembly 汇编
    3. C
    4. C++
    5. D
    6. Fortran
    7. Go
    8. Objective-C
    9. OpenCL
    10. Modula-2
    11. Pascal
    12. Rust
## 安装环境
Ubuntu
```
apt install gdb
```   

检查是否安装成功：
```
gdb --version
```

## QuickStart
- 官网有个pdf，官方说明文档。
### gdb调试基本命令
正常gcc编译
```shell
gcc test.c

./test.out
```

1. 添加 -g 参数，编译程序
```shell
gcc -g test.c

```

2. gdb启动程序
```shell
gdb ./test.out
```

3. run/next命令 程序跑起来
```shell
run #程序运行起来
next #程序一步一步执行
```
简写为:r
如果程序有输入参数，直接在run后面加参数就可以。
```
run [arg list]
```

4. quit命令，退出程序

5. break命令，打断点
```shell
break main # 在函数打断
break 9 # 在第9行打断点
info break # 显示断点信息
list # 显示源文件
```
PS: 使用man gdb 查看官方帮助文档
6. bt 显示程序的调用栈

7. print命令，打印变量值
```shell
print i
print a[0]
print &a[0]
print &a[2]
```
8. step 进入函数
9. continue 继续执行，知道下一个断点或者程序结果

### gdb shell命令
gdb中可以直接使用shell命令
```
gdb a.out
shell ll

shell mkdir ingdbtest
```

### gdb log模式
```
set logging on
```
开启日志模式，将调试过程中的输入和输出全部记录下来。

### gdb一个正在运行的程序
```
gdb -p progressid
gdb -p 1234
```

### gdb core文件 - 一个挂掉的文件

# 解决什么问题


# 了解它的底层