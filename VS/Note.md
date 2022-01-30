## PCH 超内存限制
https://devblogs.microsoft.com/cppblog/precompiled-header-pch-issues-and-recommendations/


factor的值     内存分配限制 
10                7.5 MB
100              75 MB
200              150 MB
1000            750 MB
2000            1500 MB

## VS2019：
### Visual Studio2019 正在从以下为位置加载ntdll.dll符号:Microsoft符号服务器
- 进入 [工具]>[选项]>[符号]，右边的“[Microsoft符号服务器]”把勾选去掉，点击确定。