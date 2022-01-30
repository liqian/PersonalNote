# 清理VSCode缓存
## cpptools
C:\Users\Administrator\AppData\Local\Microsoft\vscode-cpptools  
- 可以删除，这里记录的是C++插件打开工程后的一些缓存，删除后，下次还会生成。
## workspaceStorage
C:\Users\Administrator\AppData\Roaming\Code\User\workspaceStorage  
- workspaceStorage：平时打开工程的缓存文件，也可以删除。
## AppData\Local\Temp
C:\Users\liqian\AppData\Local\Temp

# VSCode架构
- https://zhuanlan.zhihu.com/p/96041706

# Linux Remote-ssh connect to windows
error: time out 
setting->extensions->remote-ssh->edit in setting.json
add new line:
```
"remote.SSH.useLocalServer": false,
```