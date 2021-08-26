# 硬盘信息的查看
	- sudo fdisk -l ：硬盘设备的详细信息



	- df -h ：硬盘的使用情况，和信息
	- 
	

	2. 格式化硬盘
	- sudo mkfs.ext4 /dev/sdb
	- 还有一种方法是通过Ubuntu系统中搜索框搜索disk软件查看硬盘情况，并通过该软件图形化进行格式化操作
	3. 查看硬盘分区的UUID
	- sudo blkid
	
	- sudo blkid /dev/sda2
	- 如上图，sdc 和 sdd 没有UUID，说明没有被格式化，还无法使用。需要先格式化
	4. 设置硬盘卷标，方便识别
	sudo e2label /dev/sdb1 /D
	- 
	5. 挂载：
	- 可以在home下或者mnt下创建个文件夹，代表挂载点
	- 在home下 mkdir data_sdb
	- sudo mount /dev/sdb /home/data_sdb
	- sudo mount -o rw /dev/sdb /home/data_sdb  : 以读写方式挂载
	- mount命令还可以之间挂载iso，linux下有免费光驱说法。
	- NOTE:一旦重启，将需要重现挂载。
	- NOTE：测试了下 如果挂载点是sdb，但是sdb里还有其他的文件或者文件夹，挂载完后，将被隐藏，无法看到。知道umount后，才能看到和使用。
	- NOTE：一个硬盘，可以进行多个挂载点。
	6. 卸载
	- 卸载硬盘
		○ sudo umount /dev/sdb
		○ NOTE:如果一个硬盘的进行了多个挂载点，一旦运行umount， 将全部卸载。
		○ umount的时候老显示 device busy？ 
		○ 这是因为有程序正在访问这个设备，最简单的办法就是让访问该设备的程序退出以后再umount。可能有时候用户搞不清除究竟是什么程序在访问设备，如果用户不急着umount，则可以用: 
		
		# umount -l /mnt/hda5 
		
		来卸载设备。选项 –l 并不是马上umount，而是在该目录空闲后再umount。还可以先用命令 ps aux 来查看占用设备的程序PID，然后用命令kill来杀死占用设备的进
		程，这样就umount的非常放心
		
	- 删除挂载点
	        rm -rf /mnt/sdb
	
	7. - 编辑系统挂载配置文件/etc/fstab，是的每次重启不用重新挂载
	- sudo vim /etc/fstab
	- 最后一行添加内容：
	- <file system> <mount point> <type> <options> <dump> <pass>
	- UUID='…." /mnt/sdb ext4 defaults 0 0
	- file system: 写上刚才查到的UUID
	- mount point:挂载点
	- type：文件系统格式 swap ext4 ext3 FAT等
	- options: 一般挂载的硬盘 都是defaults
	- dump:代表是否需要备份，0 从不备份
	- pass:为0就表示不检查，（/）分区永远都是1，其它的分区只能从2开始
	- 
	- 修改权限：
		○ sudo chmod -R 777 /mnt/sdb
	- 重启电脑

# 扩展硬盘挂载到HOME：
		○ 挂载点 /home 直接扩展home的空间，需要先将home下的内容拷贝到新的挂载盘下，否则系统会出问题。
		○ 例如用 sdb的home目录替换系统盘的home目录，详见系统盘的home目录拷贝到sdb下的home，然后再挂载到/home.
	- #### 1-创建目录 
	sudo mkdir /mnt/home 
	- #### 2-把/dev/sdb1挂载到/mnt/home 
	sudo mount /dev/sdb1 /mnt/home 
	- #### 3-同步/home到/media/home，同步时间根据数据量大小决定，建议在系统空闲时操作 
	sudo rsync -aXS /home/. /mnt/home/. 
	- #### 4-同步完成后重命名/home 
	sudo mv /home /home_old 
	- #### 5-新建/home 
	sudo mkdir /home 
	- #### 6-.取消/dev/sdb1挂载 
	sudo umount /dev/sdb1 
	- #### 7-重新挂载/dev/sdb1到home 
	sudo mount /dev/sdb1 /home 
	- #### 8-查看/dev/sdb1的UUID
	 blkid 
	- #### 9-把UUID复制下来，修改/etc/fstab文件，实现开机自动挂载 
	sudo gedit /etc/fstab 
	- # home 4T 
	UUID=8da46012-ab9c-434f-a855-2484112fd1a7 /home ext4 nodev,nosuid 0 2 
	- #### 10-保存之后重启系统，查看分区的挂载情况 df –h 
	- #### 11-确认一切正常后删除/home_old


Linux下分区的介绍：很详细和直观
https://www.cnblogs.com/jjzd/p/5634171.html
	

	
	
	
# 扩展知识
- 查看硬盘的文件系统
`lsblk -f`

`lsblk -l`
-