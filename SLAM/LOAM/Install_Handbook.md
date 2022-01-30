# Lego-LOAM
## Depency
### Common
- cmake
- g++ gcc
- git
### ROS
- support limited info
> https://www.ros.org/reps/rep-0003.html

> ROS Noetic Ninjemys (May 2020 - May 2025):
>   Ubuntu Focal Fossa (20.04)
> Requirements:

|Package | Ubuntu Focal   | Debian Buster      | Fedora 32         |
|--------|----------------|--------------------|-------------------|
|        |Required Support|	Recommended support|Recommended support|
|Boost   |	    1.71!     |	         1.67      | 1.69!      |
|CMake   |	    3.16.3!	  |          3.13.4    |  3.17!     |
|Gazebo  |	    11.x*     |          11.x*	   |  10.1.0!   |
|Ignition|	    Citadel	  |          Citadel   |  N/A       |
|Ogre    |	    1.9!	  |          1.9       |  1.9!      |
|OpenCV  |	    4.2!	  |          3.2       |  4.2       |
|PCL     |	    1.10!	  |          1.9.1	   |  1.9.1!    |
|PyQt    |	    5.14.1!	  |          5.11.3	   |  5.14.2!   |
|Qt5     |	    5.12.5!	  |          5.11.3	   |  5.13.2!   |

" * " means that this is not the upstream version (available on the official Operating System repositories) but a package distributed by OSRF or the community (package built and distributed on custom repositories).

" ! " means that this package will be at least this version (since these distributions have not yet been released); this may change as those releases get closer.

- Ubuntu install of ROS Noetic(http://wiki.ros.org/Installation/Ubuntu)
**only for 20.04**
1. Installation
1.1. Configure your Ubuntu repositories
Configure your Ubuntu repositories to allow "restricted," "universe," and "multiverse."

1.2. Setup your sources.list
Setup your computer to accept software from packages.ros.org. 
```bash
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
```

**use mirror(Recommended)**:   http://wiki.ros.org/ROS/Installation/UbuntuMirrors
```bash - china
sudo sh -c '. /etc/lsb-release && echo "deb http://mirrors.ustc.edu.cn/ros/ubuntu/ `lsb_release -cs` main" > /etc/apt/sources.list.d/ros-latest.list'
```

1.3. Set up your keys
```bash
sudo apt install curl # if you haven't already installed curl
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
```

如果出现：gpg:no valid OpenPGP data found.
是因为国内网站限制，ros.asc无法下载。

```预先下载
wget -O ros.asc https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc
```

添加公钥：
```
sudo apt-key add ros.asc
```
1.4. Installation
First, make sure your Debian package index is up-to-date:
```
    sudo apt update
```
Now pick how much of ROS you would like to install.

**Desktop-Full Install: (Recommended)**: Everything in Desktop plus 2D/3D simulators and 2D/3D perception packages
```
    sudo apt install ros-noetic-desktop-full
```

1.5 Environment setup
You must source this script in every bash terminal you use ROS in.
```bash
source /opt/ros/noetic/setup.bash
```
It can be convenient to automatically source this script every time a new shell is launched. These commands will do that for you. 

```bash
echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

### gstam
1. Recimmended:
  ```
  wget -O ~/Downloads/gtsam.zip https://github.com/borglab/gtsam/archive/4.0.0-alpha2.zip
  cd ~/Downloads/ && unzip gtsam.zip -d ~/Downloads/
  cd ~/Downloads/gtsam-4.0.0-alpha2/
  mkdir build && cd build
  cmake -DGTSAM_BUILD_WITH_MARCH_NATIVE=OFF -DGTSAM_USE_SYSTEM_EIGEN=ON ..
  sudo make install
  ```

2. [github](https://github.com/borglab/gtsam)
注意：GTSAM_USE_SYSTEM_EIGEN 使用系统的eigen库，因为gtsam自带一个老版本的，不使用。
```
git clone https://github.com/borglab/gtsam.git
cd gtsam
mkdir build && cd build
cmake -DGTSAM_USE_SYSTEM_EIGEN=ON ..
sudo make install
```
### install OpenCV
```bash
cd OpencvSrc
mkdir -p build
cd build
cmake ..
cmake --build . 
sudo make install
```

### install pcl
- 使用预编译好的包：ubuntu20.04 默认是1.10
```bash
sudo apt install libpcl-dev
sudo apt install libpcl-*
sudo apt install pcl-tools #一些pcl常用工具，例如 pcl_viewer
```


## Lego-SALM Build
1.  LeGO-LOAM的编译需要使用catkin，init catkin. 如果已经建立catkin_ws,可以跳过下面这步.
```bash
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
catkin_init_workspace
```
2. Dowonload And Build Lego-SLAM source code:
```bash
cd ~/catkin_ws/src
git clone https://github.com/RobustFieldAutonomyLab/LeGO-LOAM.git

cd .. #note here. 
catkin_make -j1
```
When you compile the code for the first time, you need to add "-j1" behind "catkin_make" for generating some message types. "-j1" is not needed for future compiling.


3. [Ubuntu 20.04 下编译 Lego Loam 踩过的一些坑](https://xiaotaoguo.com/p/lego-loam-setup-ubuntu20/)
> 1. fatal error: opencv/cv.h: No such file or directory
> 替换`#include <opencv/cv.h>`为`#include <opencv2/imgproc.hpp>`

> Ubuntu20.04 默认安装 opencv 4.2.0，opencv4 对头文件名作出了一点修改，
> 因此需要对 Lego LOAM 中 include opencv 头文件的部分做出修改，
> 将 Utility.h 中的 `#include <opencv/cv.h>` 改成 `#include <opencv2/opencv.hpp>`

> 2. /usr/include/pcl-1.10/pcl/pcl_config.h:7:4: error: #error PCL requires C++14 or above

> 字面意思，PCL 1.10 要求使用 c++14 及以上版本，
> 将 LEGO LOAM 中的 CMakeLists.txt 中的编译选项 `set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")` 改为 `-std=c++14` 即可


> 3. error: ‘Index’ is not a member of ‘Eigen’
> 这个错误是因为 Lego LOAM 中原作者建议使用的 gtsam 版本为 4.0.0-alpha2，
> gtsam 是自带了一个 eigen 库的，而这个版本的 gtsam 中使用的是较低版本的 Eigen，还没有 Eigen::Index 这个定义。
> 比较简单的做法是将 PCL 中用到的 Eigen::Index 改为 int 即可。
> build gtsam时，使用新版的Eigen库：`cmake -DGTSAM_BUILD_WITH_MARCH_NATIVE=OFF -DGTSAM_USE_SYSTEM_EIGEN=ON ..`
> 除此之外，用新版本的 gtsam 也可以解决这个问题。


> 4. boost can not find serialization thread chrono....; 如果没有这个问题，下面的忽略
```cmake add following :
find_package(Boost 1.43 COMPONENTS 
                  serialization 
                  system 
                  filesystem 
                  thread 
                  program_options 
                  date_time 
                  timer 
                  chrono)

set(TEMP_BOOST_LIBRARIES
    ${Boost_SERIALIZATION_LIBRARY} 
    ${Boost_SYSTEM_LIBRARY} 
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY} 
    ${Boost_DATE_TIME_LIBRARY} 
    ${Boost_TIMER_LIBRARY} 
    ${Boost_CHRONO_LIBRARY})
```


4. Run
更新工作区间：`source devel/setup.bash`
运行Lego-Loam：`roslaunch lego_loam run.launch`

打开数据集：
```
rosbag play test.bag --clock --topic /velodyne_points 
```
或：
```
rosbag play test.bag --clock --topic /velodyne_points /imu/data 
```
test.bag: 数据集的包名
velodyne_points ： 话题名


# run Demo
## LOAM
1. 使用Bag数据:http://wiki.ros.org/loam_velodyne
> Dataset1: 
>from inside of a building to outside : Dataset/NSH_indoor_outdoor

> Dataset2:
> test with an IMU : Dataset/withIMU_gates_oscillating_motion



2. 第一个窗口：启动LOAM
```
cd catkin_ws
source devel/setup.bash
roslaunch loam_velodyne loam_velodyne.launch
```

3. 第二个窗口：播放bag文件
```
cd catkin_ws # 进入到bag文件位置
source devel/setup.bash
rosbag play nsh_indoor_outdoor.bag
```

