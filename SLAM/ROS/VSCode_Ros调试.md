在vs code下配置ROS项目开发的环境

包括catkin创建编译工作空间，创建ROS项目，调试ROS节点.
- https://www.bilibili.com/video/BV1tm4y197vo


# VSCode ROS环境配置
## 安装VSCode的Ros插件
- Visual Studio Code Extension For ROS

## 创建工作空间
1. 首先创建一个cMake工作空间，用到了catkin_make其实就是 cmake .. make 两个步骤的缩写。
```
$ mkdir -p ~/ros_demo/src
$ cd ~/ros_demo/
$ catkin_make
```

2. 每次打开工作空间ros_demo文件要source一下

```
cd ~/ros_demo
source devel/setup.bash
```

3. 除此之外，启动ROS还需要:
```
source /opt/ros/noetic/setup.bash
```

如果将`source /opt/ros/noetic/setup.bash`加入了`~/.bashrc`:
```
source ~/.bashrc
```

至此，已经创建好了工作空间

## 创建ROS项目
1. 创建一个工程
```
catkin_create_pkg myrosdemo std_msgs rospy roscpp
```
NOTE:std_msgs roscpp 是工程中的依赖组件

或者
Shift+Ctrl+P: `ROS:Create Catkin Package`-->输入工程名字--> 处理Dependencies：`std_msgs rospy roscpp`

工程创建完毕，创建好的工程目录：
```
myrosdemo：
    include
    src
    CMakeLists.txt # 会自动添加find_package(catkin REQUIRED COMPONENTS std_msgs rospy roscpp)
    package.xml #这个里面记录的就是Dependencies
```

2. [Ros 官网例子](http://wiki.ros.org/ROS/Tutorials/WritingPublisherSubscriber%28c%2B%2B%29)
   [Github Ros Code](https://github.com/ros/ros_tutorials)
可以拷贝下里面的代码，测试下，我用的是talker这个工程。

3. 对工程进行配置
- 生成 tasks.json
> Shift+Ctrl+P --> Tasks:Configure Default Test Task --> C/C++:g++ build active file
> 在 `.vscode` 下会生成 task.json文件。


- 配置 task.json
```
{
    vsersion:"2.0.0", # 这里不需要改动
    "tasks": [
        {
            "type": "shell", # 这里改成 shell
            "label":"myrosdemo_build_debug", # 这里改成自己的名字，主要启动一个标识作用
            //"command": "catkin_make -DCMAKE_BUILD_TYPE=Debug",
            "command": "source /opt/ros/noetic/setup.bash && catkin_make -DCMAKE_BUILD_TYPE=Debug",    #因为是编译ROS程序，所以这里改下,Debug的话，需要添加一个参数。
            "args" : [], # 不需要传入参数，这里为空就可以了。
            "problemMatcher": [
                "$catkin-gcc" # 这里使用 catkin-gcc
            ],
            "group":{
                "kind": "build", #加入到build组
                "isDefault":true
            },
        }
    ]
}
```

Shift+Ctrl+P --> Tasks : Run Task:
> 如果报错，failed to launch,是因为没有运行`source /opt/ros/noetic/setup.bash`原因。需要先运行下
> 也可以在 `command`中加入这个命令，可以进行build了。

添加 clean task：
```
{
			"label":"myrosedemo_clean",
			"type": "shell",
			"command":"source /opt/ros/noetic/setup.bash && catkin_make clean ",
			"problemMatcher": [
				"$catkin-gcc"
			],
		},
```

添加 release task：
```
{
			"label":"myrosedemo_release",
			"type": "shell",
			"command":"source /opt/ros/noetic/setup.bash && catkin_make  -DCMAKE_BUILD_TYPE=Release",
			"problemMatcher": [
				"$catkin-gcc"
			],
		},
```
Shift+Ctrl+P --> Tasks : Run Task  可以选择不同的编译选项了。

- 配置launch.json
> 点击 Run按钮，Create Launch C/C++:(GDB).
program ros节点在 `devel/lib`下有一个工程名字的文件夹,如果没有是因为上面的build没有成功的原因。
```
 {
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/devel/lib/myrosdemo/myrosdemo", # 这个是要运行的程序，也就是要调试的Node节点
            "args": [],
            "preLaunchTask": "myrosedemo_build_debug",  #添加一项，这个名字就是task.json中的label名字。
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```

OK 到这里 就可以 就行Debug调试了。



4. c_cpp_properties.json生成
这个文件主要是用于语言引擎的配置，例如：指定 include 路径，智能感知，问题匹配类型等。
Ctrl+Shift+P打开Command Palette， 
找到并打开：C/C++:Edit Configurations (UI)。进行一些配置后，.vscode文件夹下会自动生成此文件。
如果采用默认配置，可以使用C/C++:Edit Configurations (JSON),直接生成c_cpp_properties.json。




