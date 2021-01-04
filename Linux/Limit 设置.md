# 查看当前系统的参数：ulimit -a 
```
 core file size          (blocks, -c) 0
 data seg size           (kbytes, -d) unlimited
 scheduling priority             (-e) 0
 file size               (blocks, -f) 8192
 pending signals                 (-i) 127998
 max locked memory       (kbytes, -l) 64
 max memory size         (kbytes, -m) unlimited
 open files                      (-n) 1024
 pipe size            (512 bytes, -p) 8
 POSIX message queues     (bytes, -q) 819200
 real-time priority              (-r) 0
 stack size              (kbytes, -s) 8192
 cpu time               (seconds, -t) unlimited
 max user processes              (-u) 127998
 virtual memory          (kbytes, -v) unlimited
 file locks                      (-x) unlimited
```

**Note**: Ubuntu系统区分终端和Desktop。

# 修改Limit限制 -- 系统级别，永久生效
修改/etc/security/limits.conf: 
```bash
sudo vim /etc/security/limits.conf 
```
 添加：
```bash
    root hard nofile 10240
    root soft nofile 10240
    *    hard nofile 10240
    *    soft nofile 10240
    
    vcb  soft memlock 134217728
    vcb  hard memlock 134217728
```

## Ubuntu系统需要多设置的内容，否则不生效 
在 ` /etc/pam.d/common-session ` 和 ` etc/pam.d/common-session-noninteractive `文件中，都添加下面内容：
```  
  session required pam_limits.so
```
保存 退出，重启生效。

## Ubunut Desktop需要设置的内容:
修改 ` /etc/systemd/system.conf ` 文件:
```
DefaultLimitNOFILE=10240
DefaultLimitMEMLOCK=134217728

```
如果不修改这个文件的话，重启后当前登录的 bro 用户不会超过这个限制（影响的是登录桌面的用户）。
修改完成后，如果是远程链接，重新链接即可生效； 如果是桌面环境，重启后生效。

