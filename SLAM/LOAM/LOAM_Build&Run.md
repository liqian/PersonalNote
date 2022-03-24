# Lego-LOAM
## Depency
### Common
- cmake
- g++ gcc
- git
### install ROS
- 参考 (../ROS/install_Ros.md)

### gstam
1. Recommended:
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
**在ubuntu20.04和Ubuntu18.04上发现很多莫名奇妙的死机问题，最好使用4.0.0版本**


3. 会在系统安装如下内容：
```
-- Install configuration: "Release"
-- Installing: /usr/local/lib/cmake/GTSAM
-- Installing: /usr/local/include/gtsam/
-- Installing: /usr/local/include/gtsam_unstable/
-- Installing: /usr/local/lib/cmake/GTSAMCMakeTools/

-- Installing: /usr/local/lib/libmetis-gtsam.so
-- Installing: /usr/local/include/CppUnitLite/Failure.h
-- Installing: /usr/local/include/CppUnitLite/Test.h
-- Installing: /usr/local/include/CppUnitLite/TestHarness.h
-- Installing: /usr/local/include/CppUnitLite/TestRegistry.h
-- Installing: /usr/local/include/CppUnitLite/TestResult.h
-- Installing: /usr/local/lib/libCppUnitLite.a
-- Installing: /usr/local/lib/libgtsam.so.4.1.1
-- Installing: /usr/local/lib/libgtsam.so.4
-- Installing: /usr/local/lib/libgtsam.so
-- Set runtime path of "/usr/local/lib/libgtsam.so.4.1.1" to ""

-- Installing: /usr/local/lib/libgtsam_unstable.so.4.1.1
-- Installing: /usr/local/lib/libgtsam_unstable.so.4
-- Installing: /usr/local/lib/libgtsam_unstable.so
-- Set runtime path of "/usr/local/lib/libgtsam_unstable.so.4.1.1" to ""
```


### install OpenCV -- source( 可以不考虑，因为在按照ROS时 已经安装了)
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
## eigen3
```sh
sudo apt install libeigen3-dev
```


## boost optionall
```sh
sudo apt install libboost-dev
```

## pcap optionall
```sh
sudo apt install libpcap-dev
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

**When you compile the code for the first time, you need to add "-j1" behind "catkin_make" for generating some message types.**
**"-j1" is not needed for future compiling.**
**请在第一次编译时使用`catkin_make -j1`. 因为引入自定义msg格式，第一次需要生成msg代码，并行编译会失败。**

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

> 5. 出现`error while loading shared libraries: libmetis-gtsam.so: cannot open shared object file: No such file or directory
`错误。
> 解决： `export LD_LIBRARY_PATH=/usr/local/lib/:$LD_LIBRARY_PATH` 加入到 `~/.bashrc`中。
> 原因： Linux默认只会搜索`/usr/lib`,但是libmetis-gtsam.so 在`/usr/local/lib/`下。

> 6. 如果rviz无法描画，尤其是mapping后的结果，是应为*.bag时间同ros时间不一致，导致消息丢失问题。
> 解决：`rosbag play *.bag --clock` 使用bag的时间。

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

