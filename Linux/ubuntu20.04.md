## 安装搜狗中文输入法
参照 https://zhuanlan.zhihu.com/p/142206571
```bash
#添加ubuntukylin源
curl -sL 'https://keyserver.ubuntu.com/pks/lookup?&op=get&search=0x73BC8FBCF5DE40C6ADFCFFFA9C949F2093F565FF' | sudo apt-key add
sudo apt-add-repository 'deb http://archive.ubuntukylin.com/ukui focal main'
sudo apt upgrade

#安装搜狗输入法
sudo apt install sogouimebs

#输入法设置
sogouIme-configtool 
```

## nds_sqlite3 运行问题
- 缺少 libncurses.so.5
```bash
    sudo apt install libncurses5 libncurses5-dev
```

## 文件管理器 左侧栏设定
```bash
    vim ~/.config/user-dirs.dirs
```
