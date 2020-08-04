# python2.7 的中文编码处理
https://www.cnblogs.com/huchong/p/9037142.html
# Unicode 字符编码表|汉字Unicode编码的区间为：0x4E00→0x9FA5(转)
https://www.cnblogs.com/chenwenbiao/archive/2011/08/17/2142718.html

# .whl安装

## 检查是否安装
    pip2 -version
    pip3 -version
如果出现pip的版本信息说明已安装.
Python2.7.9+ 和 Python3.4+默认安装了。如果不好用的话，可以按照如下方式重新安装一次。


## 安装pip,两种安装方式：
使用.whl安装： 

    python.exe pip-20.1.1-py2.py3-none-any.whl
    pip install pip-20.1.1-py2.py3-none-any.whl
使用tar.gz包安装  
 
    pip-20.1.1.tar.gz 解压。运行 python setup.py install

## 安装wheel,两种安装方式  
使用.whl安装： 

    pip3 wheel-0.34.2-py2.py3-none-any.whl  
    pip3 wheel-0.34.2-py2.py3-none-any.whl

使用tar.gz包安装  
 
    wheel-0.34.2.tar.gz 解压。运行 python setup.py install

## 安装 .whl文件
    pip2 install wheel.whl
    pip3 install wheel.whl