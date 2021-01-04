分包压缩的zip文件不能被7z解压，且这种格式是Windows才能创建出来，在Linux下不会以这种方式去压包。下面是在Linux下处理这种文件的做法：

方法一：

cat xx.z01 xx.zip > full.zip
unzip full.zip
方法二：

zip xx.zip --out full.zip
unzip full.zip
方法三：

zip -s 0 xx.zip --out full.zip
unzip full.zip

这中合并，不考虑密码，即使是使用密码压缩的文件，也可以被合并。只有在unzip的时候才需要密码。

-P: 输入密码
unzip -P password delta.zip 