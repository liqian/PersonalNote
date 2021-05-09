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

## execute_process
### 参数
```
execute_process(COMMAND <cmd1> [args1...]]
                [COMMAND <cmd2> [args2...] [...]]
                [WORKING_DIRECTORY <directory>]
                [TIMEOUT <seconds>]
                [RESULT_VARIABLE <variable>]
                [OUTPUT_VARIABLE <variable>]
                [ERROR_VARIABLE <variable>]
                [INPUT_FILE <file>]
                [OUTPUT_FILE <file>]
                [ERROR_FILE <file>]
                [OUTPUT_QUIET]
                [ERROR_QUIET]
                [OUTPUT_STRIP_TRAILING_WHITESPACE]
                [ERROR_STRIP_TRAILING_WHITESPACE])
```
按指定的先后顺序运行一个或多个命令，每个进程的输出通过管道连接作为下一个进程的输入。所有的进程使用单个的标准错误输出管道。
如果指定了WORKING_DIRECTORY，则指定的目录将作为子进程当前的工作目录。

如果指定了TIMEOUT值，则如果在指定的时间内（以秒为单位计算，允许有小数位）子进程执行仍未完成，则将会被中断。

如果指定了RESULT_VARIABLE变量，则最后命令执行的结果将保存在该变量中，它是最后一个子进程执行完后的返回值或描述某种错误信息的字符串。

如果指定了OUTPUT_VARIABLE或ERROR_VARIABLE变量，则该变量会分别保存标准输出和标准错误输出的内容。

如果指定的变量是同一个，则输出会按产生的先后顺序保存在该变量中。

如果指定了INPUT_FILE，UTPUT_FILE或ERROR_FILE等文件名，则它们会分别与第一个子进程的标准输入，最后一个子进程的标准输出以及所有子进程的标准错误输出相关联。

如果指定了OUTPUT_QUIET或ERROR_QUIET，则会忽略标准输出和错误输出。如果在同一管道中同时指定了多个OUTPUT_*或ERROR_*选项，则优先级顺序是未知的（应避免这种情况）。

如果未指定任何OUTPUT_*或ERROR_*选项，则命令CMake所在进程共享输出管道。

您可以指定RESULT_VARIABLE或OUTPUT_VARIABLE使用execute_process命令根据执行过程的返回码或标准输出设置CMake变量; 这可能有助于影响后续的CMake行为。

e.g:
```
execute_process(
  COMMAND ${ANT_PATH} install "-Dzserio_cpp_reflect.install_dir=${CMAKE_CURRENT_BINARY_DIR}"
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
```

### 同add_custom_command区别
- execute_process将在CMake配置阶段运行
- add_custom_command将在代码编译期间运行（在CMake完成之后）


## if (NOT TARGET projectName)
判断是否有 projectName 的工程，用于工程依赖的时候最判断
e.g
```
if (TARGET nds252)
else()
endif()
```
## 使用C++11的thread库
### 方法一
```cmake
PROJECT(HELLO)
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11")
AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_EXECUTABLE(hello ${SRC_LIST})
```
从cmake的CMakeLists.txt文件中可以看出cmake是像g++使用c++11特性一样，都有-std=c++11，所以像一样加个-pthread解决就行。

```cmake
PROJECT(HELLO)
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11 -pthread")
AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_EXECUTABLE(hello ${SRC_LIST})
```
NOTE: -pthread 不要使用 -l-pthread; -pthread是新特性，推荐。-lpthread 已被淘汰。

### 方法二
使用包Threads和链接${CMAKE_THREAD_LIBS_INIT}
```cmake
PROJECT(HELLO)
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11")
FIND_PACKAGE(Threads)
AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_EXECUTABLE(hello ${SRC_LIST})
TARGET_LINK_LIBRARIES(hello ${CMAKE_THREAD_LIBS_INIT})
```