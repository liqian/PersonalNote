# 编译是出现 空间不够 ，堆内存不够
参考：Using MSBuild with the 64-bit Compiler and Tools
https://docs.microsoft.com/en-us/cpp/build/walkthrough-using-msbuild-to-create-a-visual-cpp-project?view=msvc-160&viewFallbackFrom=vs-2019#using-msbuild-with-the-64-bit-compiler-and-tools

在*..vcxproj 中添加：
```XML
<PropertyGroup>
    <PreferredToolArchitecture>x64</PreferredToolArchitecture>
</PropertyGroup>

```
