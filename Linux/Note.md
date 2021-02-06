# OOM
- https://www.cnblogs.com/sunsky303/p/9401070.html
- https://blog.csdn.net/fengda2870/article/details/12038419
- 查看 low memory 和 high memory 的状态：64bit系统 low和high是一样的，共享。
```linux
# free -lm 
             total       used       free     shared    buffers     cached 
Mem:          5769       5751         17          0          8       5267 
Low:           777        760         16          0          0          0 
High:         4991       4990          1          0          0          0 
-/+ buffers/cache:        475       5293 
Swap:         4773          0       4773 
```
# grep -i "killed" /var/log/syslog

# OOM Killer的关闭与激活方式： 对于系统危险，谨慎操作
# echo "0" > /proc/sys/vm/oom-kill
# echo "1″ > /proc/sys/vm/oom-kill