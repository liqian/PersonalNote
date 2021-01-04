# Ubuntu环境下python2和python3切换

## 查看本机上的python版本
- 有些机器默认安装了python2和python3，有些没有
- 使用如下命令:
```bash
which python2
which python3
```
如果没有安装，显示空。如果安装了显示系统路径。

## 使用 update-alternatives 
- --install <连接> <名称> <路径> <优先级> :建立一组候选项
- --config <名称> ：配置<名称>组中的可选项，并选择使用哪一个
- --remove <名称> <路径> : 从<名称>中去掉<路径>选项

## 首先 看下是否有Python选项
```bash
update-alternatives --list python
```
或者
```bash
update-alternatives --display python
```

如果显示： 
update-alternatives:error : no alternatives for python  
表示没有ptyhon组。

### 建立python组
- priority 越大 优先级越高，默认设置成最大的。
```bash
sudo update-alternatives --install /usr/bin/python python /usr/bin/python2.7 2 #add python2 and set priority
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3.8 1 #add python3 and set priority
```
- 设置完成后 可以使用 `python --version` 查看设置是否OK

## 切换Python
```bash
sudo update-alternatives --config python
```
根据提示，选择数字，回车即可。


## 删除可选项
```bash
sudo update-alternatives --remove python /usr/bin/python2.7
```




