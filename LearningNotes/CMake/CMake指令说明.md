# 指令说明
target_include_directories()：指定目标包含的头文件路径。官方文档

target_link_libraries()：指定目标链接的库。官方文档

target_compile_options()：指定目标的编译选项。官方文档

目标 由 add_library() 或 add_executable() 生成。

这三个指令类似，这里以 target_include_directories() 为例进行讲解。

# 关键字用法说明：

## PRIVATE：私有的。只是当前target使用
生成 libhello-world.so时，只在 hello_world.c 中包含了 hello.h，  
libhello-world.so 对外的头文件——hello_world.h 中不包含 hello.h。  
而且 main.c 不会调用 hello.c 中的函数，或者说 main.c 不知道 hello.c 的存在，  
那么在 hello-world/CMakeLists.txt 中应该写入：
```cmake
target_link_libraries(hello-world PRIVATE hello)
target_include_directories(hello-world PRIVATE hello)
```

## INTERFACE：接口。只给外部依赖本target使用
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

## target_include_directories 和 include_directories 区别
- https://blog.csdn.net/zhizhengguan/article/details/115331314

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
## cmake command line tool
https://cmake.org/cmake/help/latest/manual/cmake.1.html#run-a-command-line-tool


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

#### cmake 命令行工具参数说明
- [OfficalDoc](https://cmake.org/cmake/help/latest/manual/cmake.1.html)
1. `-S <path-to-source>`
> Path to root directory of the CMake project to build.

e.g
```
cmake -S mysourceDir
```

2. `-B <path-to-build>`
> Path to directory which CMake will use as the root of build directory.
> If the directory doesn't already exist CMake will make it.

e.g
```
cmake -B mysourceBuildDir
```

3. `-D <var>:<type>=<value>, -D <var>=<value>`
>Create or update a CMake CACHE entry.

> When CMake is first run in an empty build tree, 
> it creates a CMakeCache.txt file and populates it with customizable settings for the project. 

> This option may be used to specify a setting that takes priority over the project's default value. 
> The option may be repeated for as many CACHE entries as desired.

> If the `:<type>` portion is given it must be one of the types specified by the set() command documentation for its CACHE signature. 
> If the `:<type>` portion is omitted the entry will be created with no type if it does not exist with a type already. 
> If a command in the project sets the type to PATH or FILEPATH then the `<value>` will be converted to an absolute path.

> This option may also be given as a single argument: `-D<var>:<type>=<value>` or `-D<var>=<value>`.

e.g
```
cmake -DCMAKE_BUILD_TYPE=Release
```

## cmake 中的install目录如何指定
使用 CMAKE_INSTALL_PREFIX 来指定。
使用`cmake --install .` 或者是`make install`运行。
或者是通buidl一起，`cmake --build . --target install`.
- 方法1-在执行cmake时指定：
  ```
  cmake -DCMAKE_INSTALL_PREFIX=<你想要安装的路径>
  ```

- 方法二-设置CMAKE_INSTALL_PREFIX 变量：
  ```
  SET(CMAKE_INSTALL_PREFIX <install_path>) 
  ```
要加在 PROJECT(< project_name>) 之后。
 

例如：
在设置完install的安装目录之后，执行install时可以通过DESTINATION直接指定安装目录之下的目录
```cmake
set(CMAKE_INSTALL_PREFIX /usr/local)
install(TARGETS test DESTINATION bin)  #将test安装到/usr/local/bin目录下
```

## 学习笔记
https://wangpengcheng.github.io/2019/08/13/learn_cmake/
https://www.cnblogs.com/zx-admin/p/14127447.html

# CMAKE中的构建命令
- https://www.cnblogs.com/zx-admin/p/14127447.html

##  CMake提供了一个命令行签名来构建一个已经生成的项目二进制树：
```
cmake --build <dir> [<options>] [-- <build-tool-options>]
```
其中包含以下选项：
1. `--build <dir>` :要构建的项目二进制目录。这是必需的，必须首先。
e.g
```
cmake --build .
```

2. `--parallel [<jobs>], -j [<jobs>]` :构建时要使用的最大并发进程数
- 如果<jobs>省略，则使用本机构建工具的 CMAKE_BUILD_PARALLEL_LEVEL.

e.g
```
cmake --build . -j16
```

3. `--target <tgt>..., -t <tgt>...` : 生成z指定<tgt>目标。可以指定多个目标，以空格分隔。

4. `--config <cfg>` : 对于多配置工具，请选择configuration <cfg>. 主要针对VS生效
e.g
```
cmake --build . --config=Rlease
```

``` VS默认是Debug，可以省略 --config=Debug
cmake --build . --config=Debug
```

5. `--clean-first` ： clean首先构建目标，然后构建。 或者： `--target clean` 

# creating a header-only library
- https://dominikberner.ch/cmake-interface-lib/#:~:text=%24%3CINSTALL_INTERFACE%3A%24%20%7BCMAKE_INSTALL_INCLUDEDIR%7D%3E%20defines%20the%20path%20if%20the%20project,is%20provided%20by%20the%20GNUInstallDirs%20package%20included%20above.
1. Defining how to “build” the header-only library

add_library tells cmake that we want to build a library and to set up the logical target. Good practice is to use the project name as a variable ${PROJECT_NAME} as the name for the library/target for consistency reasons. The target-name is important to remember, as all further options for building and installing are tied to it. The keyword INTERFACE makes our target a header only library that does not need to be compiled.
```
add_library(${PROJECT_NAME} INTERFACE)
```

2. So far the target of the library is set up, but it does not contain any files yet. 
`target_inlcude_directories` lets us add them. 
The first parameter `${PROJECT_NAME} `is again the variable containing or project name “SI”, next the keyword INTERFACE tells cmake that the files are to be exposed in the library interface, which means they are publicly visible when using the library. What follows is a list of include directories wrapped in generator expressions. The Generator expressions are evaluated at the time when the build system is generated and allow to have different values for when the library is used directly over cmake or when it is installed.

`$<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>` tells cmake that if the library is used directly by another cmake target (such as when building tests for the library or when it is included as a sub directory), then the include path is ${PROJECT_SOURCE_DIR}/include} which is a nested variable. $`{${PROJECT_NAME}_SOURCE_DIR}` contains an automatically generated variable which points to the directory in which the CMakeLists.txt lies that contains the project() call. This expands to /directory/where/CmakeList.txt/is/include

`$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>` defines the path if the project is installed. The paths are relative to the install-root chosen when installing projects. The variable CMAKE_INSTALL_INCLUDEDIR is provided by the GNUInstallDirs package included above. The target path for installation can be set by setting the CMAKE_INSTALL_PREFIX variable.
```
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
```
As the code of the SI-library uses some features of the C++17 standard, this dependency is passed along using target_compile_features. This specifies compiler features to be enabled in a compiler-agnostic way. Again the target is the by now familiar ${PROJECT_NAME} and the keyword INTERFACE again marks this feature to be exposed and required when using the library. cxx_std_17 is the catch-all feature to enable the whole C++17 standard, here individual features such as use of constexpr or auto could also be specified.

If a compiler does not support the specified feature, building the library will fail.
```
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
```

# install(EXPORT targets) 会造成target_include_directories 失败问题，需要调查为什么？
- 通过这个到处一个*.cmake,记录本库依赖的其他库的绝对路径，方便使用。（非build-tree 而是install-tree）