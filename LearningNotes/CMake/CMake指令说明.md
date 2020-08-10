# 指令说明
target_include_directories()：指定目标包含的头文件路径。官方文档

target_link_libraries()：指定目标链接的库。官方文档

target_compile_options()：指定目标的编译选项。官方文档

目标 由 add_library() 或 add_executable() 生成。

这三个指令类似，这里以 target_include_directories() 为例进行讲解。

# 关键字用法说明：

## PRIVATE：私有的。
生成 libhello-world.so时，只在 hello_world.c 中包含了 hello.h，  
libhello-world.so 对外的头文件——hello_world.h 中不包含 hello.h。  
而且 main.c 不会调用 hello.c 中的函数，或者说 main.c 不知道 hello.c 的存在，  
那么在 hello-world/CMakeLists.txt 中应该写入：
```cmake
target_link_libraries(hello-world PRIVATE hello)
target_include_directories(hello-world PRIVATE hello)
```

## INTERFACE：接口。
生成 libhello-world.so 时，只在libhello-world.so 对外的头文件——hello_world.h 中包含 了 hello.h，  
hello_world.c 中不包含 hello.h，即 libhello-world.so 不使用 libhello.so 提供的功能，只使用 hello.h 中的某些信息，比如结构体。  
但是 main.c 需要使用 libhello.so 中的功能。那么在 hello-world/CMakeLists.txt 中应该写入：
```cmake
target_link_libraries(hello-world INTERFACE hello)
target_include_directories(hello-world INTERFACE hello)
```

## PUBLIC：公开的。PUBLIC = PRIVATE + INTERFACE。
生成 libhello-world.so 时，在 hello_world.c 和 hello_world.h 中都包含了 hello.h。  
并且 main.c 中也需要使用 libhello.so 提供的功能。那么在 hello-world/CMakeLists.txt 中应该写入：
```cmake
target_link_libraries(hello-world PUBLIC hello)
target_include_directories(hello-world PUBLIC hello)
```