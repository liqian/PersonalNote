# Window 
## 破解失效后处理方式：
安装目录下：
删除BCUnRar.dll

删除C:\Users\Administrator\AppData\Roaming\Scooter Software\Beyond Compare 4 下面所有东西。


## Ubuntu
### 安装
- 可以参考：https://www.scootersoftware.com/download.php?zz=kb_linux_install

```bash
#如果本地已经有了 deb包
sudo dpkg -i 安装包.deb

```

### 卸载
```bash
sudo apt remove bcompare
```

### 破解方法：
-一直使用试用版，使用30天，到期删除注册文件，继续试用。
```bash
#bcompare在ubuntu的配置文件路径是：.config/bcompare

cd .config/bcompare

# 在该路径下找到 registry.dat 删除即可。（一般是隐藏的，crtl+h可以显示）
rm registry.dat
```
