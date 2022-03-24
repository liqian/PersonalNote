# 压缩解压
7Z：
	- 安装：sudo apt-get install p7zip-full p7zip-rar p7zip
	- 解压7z：使用方法：7z x file file是你要解压的文件名。
-----------------------------------------------------------------------------------------------------------
tar
解包：tar xvf FileName.tar
打包：tar cvf FileName.tar DirName
（注：tar是打包，不是压缩！）
———————————————
.gz
解压1：gunzip FileName.gz
解压2：gzip -d FileName.gz
压缩：gzip FileName
.tar.gz
解压：tar zxvf FileName.tar.gz
压缩：tar zcvf FileName.tar.gz DirName
———————————————
.bz2
解压1：bzip2 -d FileName.bz2
解压2：bunzip2 FileName.bz2
压缩： bzip2 -z FileName
.tar.bz2
解压：tar jxvf FileName.tar.bz2
压缩：tar jcvf FileName.tar.bz2 DirName
———————————————
.bz
解压1：bzip2 -d FileName.bz
解压2：bunzip2 FileName.bz
.tar.bz
解压：tar jxvf FileName.tar.bz
———————————————
.Z
解压：uncompress FileName.Z
压缩：compress FileName
.tar.Z
解压：tar Zxvf FileName.tar.Z
压缩：tar Zcvf FileName.tar.Z DirName
———————————————
.tgz
解压：tar zxvf FileName.tgz

.tar.tgz
#压缩
tar -czvf ***.tar.gz dirname
tar -cjvf ***.tar.bz2 
#解压缩
tar -xzvf ***.tar.gz -C dirname
tar -xjvf ***.tar.bz2 -C dirname

———————————————
.zip
解压：unzip FileName.zip
压缩：zip FileName.zip DirName

分卷情况：
linux下有时应为文件过大，传输过程中需要将源文件压缩为多个zip文件，一下是具体方法

压缩
zip -r -s 1g split.zip fold/
解压
zip -s 0 split.zip --out unsplit.zip
unzip unslit.zip

———————————————
.rar
解压：rar a FileName.rar
压缩：rar e FileName.rar  将会是所有文件都到当前目录，无法保持以前目录层级
         rar x FileName.rar 保持以前目录层级
———————————————
.lha
解压：lha -e FileName.lha
压缩：lha -a FileName.lha FileName

 

ZIP
zip可能是目前使用得最多的文档压缩格式。它最大的优点就是在不同的操作系统平台，比如Linux， Windows以及MacOS，上使用。缺点就是支持的压缩率不是很高，而tar.gz和tar.gz2在压缩率方面做得非常好。闲话少说，我们步入正题吧：
我们可以使用下列的命令压缩一个目录：
# zip -r archive_name.zip directory_to_compress

下面是如果解压一个zip文档：
# unzip archive_name.zip

TAR
Tar是在Linux中使用得非常广泛的文档打包格式。它的好处就是它只消耗非常少的CPU以及时间去打包文件，他仅仅只是一个打包工具，并不负责压缩。下面是如何打包一个目录：
# tar -cvf archive_name.tar directory_to_compress

如何解包：
# tar -xvf archive_name.tar.gz

上面这个解包命令将会将文档解开在当前目录下面。当然，你也可以用这个命令来捏住解包的路径：
# tar -xvf archive_name.tar -C /tmp/extract_here/

TAR.GZ
这种格式是我使用得最多的压缩格式。它在压缩时不会占用太多CPU的，而且可以得到一个非常理想的压缩率。使用下面这种格式去压缩一个目录：
# tar -zcvf archive_name.tar.gz directory_to_compress

解压缩：
# tar -zxvf archive_name.tar.gz

上面这个解包命令将会将文档解开在当前目录下面。当然，你也可以用这个命令来捏住解包的路径：
# tar -zxvf archive_name.tar.gz -C /tmp/extract_here/

TAR.BZ2
这种压缩格式是我们提到的所有方式中压缩率最好的。当然，这也就意味着，它比前面的方式要占用更多的CPU与时间。这个就是你如何使用tar.bz2进行压缩。
# tar -jcvf archive_name.tar.bz2 directory_to_compress

上面这个解包命令将会将文档解开在当前目录下面。当然，你也可以用这个命令来捏住解包的路径：
# tar -jxvf archive_name.tar.bz2 -C /tmp/extract_here/



# Linux tee命令
Linux tee命令用于读取标准输入的数据，并将其内容输出成文件。

tee指令会从标准输入设备读取数据，将其内容输出到标准输出设备，同时保存成文件。

## 语法
tee [-ai][--help][--version][文件...]

## 参数：
-a或--append 　附加到既有文件的后面，而非覆盖它．
-i或--ignore-interrupts 　忽略中断信号。
--help 　在线帮助。
--version 　显示版本信息。

## 例子
```shell
ls|tee q.txt
```