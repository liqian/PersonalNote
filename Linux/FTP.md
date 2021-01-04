# 安装
- https://www.linuxidc.com/Linux/2017-04/142493.htm
```bash
sudo apt install vsftpd
```

```bash
sudo /etc/init.d/vsftpd restart # 重启

sudo /etc/init.d/vsftpd start  # 启动
sudo /etc/init.d/vsftpd stop # 关闭
```
# 设置
```bash
anonymous_enable=NO #禁止匿名账号登录
local_enable=YES #允许本地账号登录
write_enable=YES #允许ftp写入
local_umask=022 # 目录权限755 文件644
```

## 限定登录用户
选项userlist_deny=NO 则反转了默认设置，这种情况下只有用户名被明确列出在/etc/vsftpd.userlist 中的用户才允许登录到 FTP 服务器。

userlist_enable=YES                   # vsftpd 将会从所给的用户列表文件中加载用户名字列表
userlist_file=/etc/vsftpd.userlist    # 存储用户名字的列表
userlist_deny=NO

## FTP上传的目录和文件的初始权限
local_umask=022 ：这是指定本地用户上传后的文件权限设置

umask是unix操作系统的概念，umask决定目录和文件被创建时得到的初始权限

umask = 022 时，新建的目录 权限是755，文件的权限是 644

umask = 077 时，新建的目录 权限是700，文件的权限时 600

vsftpd的local_umask和anon_umask借鉴了它

默认情况下vsftp上传之后文件的权限是600，目录权限是700

想要修改上传之后文件的权限，有两种情况：
- 如果使用vsftp的是本地用户，则要修改配置文件中的 local_umask 的值
- 如果使用vsftp的是虚拟用户，则要修改配置文件中的 anon_umask 的值

## 将ftp用户限定到当前 /home目录下
```bash
chroot_local_user=YES # 限定到只能方位/home
allow_writeable_chroot=YES # 可写 ftp主目录
```


## 注意 FTP不支持 软连接的目录
- 使用mount解决:  
mount --bind是什么意思？ 

mount --bind 是将一个目录中的内容挂载到另一个目录上，用法是 
```bash
    mount --bind olddir newdir 
```
这个命令使得自己搭建的FTP要共享某个目录的时候变得特别方便。如果要取消mount用命令： 
```bash
    mount --move olddir newdir 即可。 
```
如果mount --bind 也想写入fstab中的话格式如下： 
```bash
olddir newdir none bind 0 0 

 /mnt/dev_soft_tool/software/mxNaviViewer /home/ftp_mxnaviewer/mount_mxNaviViewer none bind 0 0
```

- 机器重启，mount就没有了。如果想永久使用，最好加到/etc/fstab 中。

## vsftp的是虚拟用户