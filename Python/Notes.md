	
```python3
python -m http.server 8000
```
```python2
python -m SimpleHTTPServer 8000
```


# pip 
## 更换源

## install安装
- 用于自动化安装，配置python依赖环境
https://www.twle.cn/t/85

## 镜像源问题
- `pip install --upgrade pip `更新成当前最新版本
- `pip config list` 查看当前源

# Python—后台运行（nohup 、&、 2>&1详解）
脚本文件(test.py)
```python
# -*- coding: UTF-8 -*-
import time
 
print("hello"," python")
os.getcwd()      # 获得当前工作目录
os.chdir(path)   # 改变当前工作路径
 
while True:
    print("start to print %s" % "python")  
    time.sleep(2)
```
二、运行脚本
```shell
[root@localhost ~]# python test.py >my.log
[root@localhost ~]# python test.py >my.log 2>&1
[root@localhost ~]# python test.py 1>my.log                          # 等同于第一条，只是1可以省略不写
[root@localhost ~]# python test.py 1>my.log 2>&1                     # 等同于第二条，只是1可以省略不写
[root@localhost ~]# python test.py 1>my.log 2>error.log              # 等同于第二条，只是把错误输出到error.log文件了
 
 
[root@localhost ~]# python test.py >>my.log                           
[root@localhost ~]# python test.py >>my.log 2>&1
[root@localhost ~]# python test.py 1>>my.log                         # 等同于第一条，只是1可以省略不写
[root@localhost ~]# python test.py 1>>my.log 2>&1                    # 等同于第二条，只是1可以省略不写
[root@localhost ~]# python test.py 1>>my.log 2>>error.log            # 等同于第二条，只是把错误输出到error.log文件了
```

三、2>&1

- 0 表示stdin标准输入，用户键盘输入的内容
- 1 表示stdout标准输出，输出到显示屏的内容
- 2 表示stderr标准错误，报错内容

`2>&1`是一个整体，>左右不能有空格，即将错误内容重定向输入到标准输出中去。

`2>&1`中的&是为了区别文件1和1(标准输出)，假如为2>1，就成了将错误内容输出到文件1中，而不是标准输出中。