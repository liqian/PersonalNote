# SCP 命令
```
scp [options] file_source file_target 
```

本地拷贝到远程
```
scp ./test_file liqian@192.168.31.28:~/workspace
```

```
scp ./test_file liqian@192.168.31.28:~/workspace/test_file
```



远程拷贝到本地：

```
scp liqian@192.168.31.28:~/workspace/test_file ./test_file
```
