# pip
- pip install packagename
- pip unstall packagename

## 默认源
https://pypi.org/simple/

## requirements.txt
### 格式
```
packagename == version
packagename >=version
packagename >=minversion,<maxversion

# 只有pyhton版本小于2.7,安装5.4.0版本
packagename == 5.4.0; python_version < '2.7'

# 仅在window下安装
packagename; sys_platform == 'win32'
```