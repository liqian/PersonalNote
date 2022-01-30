# 简介
PCL（Point Cloud Library）是在吸收了前人点云相关研究基础上建立起来的大型跨平台开源C++编程库，
它实现了大量点云相关的通用算法和高效数据结构，涉及到点云获取、滤波、分割、配准、检索、特征提取、识别、追踪、曲面重建、可视化等。

支持多种操作系统平台，可在Windows、Linux、Android、Mac OS X、部分嵌入式实时系统上运行。

如果说OpenCV是2D信息获取与处理的结晶，那么PCL就在3D信息获取与处理上具有同等地位。

PCL是BSD授权方式，可以免费进行商业和学术应用。

PCL起初是ROS（Robot Operating System）下由来自于慕尼黑工业大学（TUM - Technische Universität München）
和斯坦福大学（Stanford University）Radu博士等人维护和开发的开源项目，

主要应用于机器人研究应用领域，随着各个算法模块的积累，
于2011年独立出来，正式与全球3D信息获取、处理的同行一起，
组建了强大的开发维护团队，以多所知名大学、研究所和相关硬件、软件公司为主。
发展非常迅速，不断有新的研究机构等加入，
在Willow Garage, NVidia, Google (GSOC 2011), Toyota, Trimble, Urban Robotics, Honda Research Institute
等多个全球知名公司的资金支持下，不断提出新的开发计划，代码更新非常活跃，在不到一年的时间内从1.0版本已经发布到1.7.0版本。

## 官网
- [OfficalWebsite] (https://pointclouds.org/)
- [Github](https://github.com/PointCloudLibrary/pcl)
- [官方API文档](https://pointclouds.org/documentation/modules.html)
- 2021.12.27 最新为：PCL 1.12.1 unstable
### 学习资料
- [PCL(Point Cloud Library)学习指南&资料推荐（2022版）](https://zhuanlan.zhihu.com/p/268524083)
- [bilibili PCL点云库官网教程](https://space.bilibili.com/504859351/channel/series)
- [](https://github.com/HuangCongQing/pcl-learning)
- [点云库PCL学习教程，朱德海，北京航空航天大学出版社](https://github.com/MNewBie/PCL-Notes)
> 相当于官网的翻译，可以看下。入门理解。
## 安装

### windows
1. 使用发布 预编译好的二机制包进行安装。
>`PCL-1.12.0-AllInOne-msvc2019-win64.exe`
>`pcl-1.12.0-pdb-msvc2019-win64.zip`解压后放到，安装目录的bin下，方便后期的调试。
> 环境变量配置 (添加如下内容)：
> PATH = C:\Program Files\PCL_1_12_0\bin;C:\Program Files\PCL_1_12_0\3rdParty\FLANN\bin;C:\Program Files\PCL_1_12_0\3rdParty\VTK\bin;C:\Program Files\OpenNI2\Redist 
> OPENNI2_INCLUDE64 = C:\Program Files\OpenNI2\Include\
> OPENNI2_LIB64 = C:\Program Files\OpenNI2\Lib\
> OPENNI2_REDIST64 = OPENNI2_REDIST64
> PCL_ROOT = C:\Program Files\PCL_1_12_0

2. 源代码编译
> Action.....


### Linux
#### 使用预编译好的包：ubuntu20.04 默认是1.10
```bash
sudo apt install libpcl-dev

```

#### 源码编译
1. 依赖库：
必须： boost OpenNI Eigen FLANN VTK 必须安装的
可选择的：Qhull CUDA
```bash
sudo apt install libboost-all-dev 
sudo apt install libflann-dev
sudo apt install libeigen3-dev
sudo apt install libvtk6-dev
sudo apt freeglut3-dev libusb-1-0-0-dev libudev-dev # 编译是发现依赖这个库
sudo apt install libopenni2-dev

# Optional
sudo apt install libqhull-dev

```

2. 编译
```bash
mldir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -j4

```

3. 安装到系统目录: 会安装到 /usr/local/include/pcl-1.12
```bash
make install
```

如果失败，尝试:
```bash
sudo make install
```

4. 卸载
```bash
sudo rm -r /usr/local/include/pcl-1.12 /usr/local/share/pcl-1.9 /usr/local/bin/pcl* /usr/local/lib/libpcl* #移除与pcl相关文件
```
提示：可以在usr目录下搜索关键字“pcl”或者“libpcl”并通过rm移除命令移除与pcl相关文件进行删除即可。

## Learning
### 代码实践
#### 官方Demo
- https://pcl.readthedocs.io/projects/tutorials/en/latest/#

#### [黑马机器人系列-PCL-3D点云]
- https://robot.czxy.com/docs/pcl/




### ICP
- [ICP算法](https://blog.csdn.net/u014709760/article/details/99241393)
- [ICP_Algorithm.md]
ICP(Iterative Closest Point), 既最近点迭代算法，是最经典的数据匹配算法。

ICP算法的思路就是：
找到两组点云集合中距离最近的点对，根据估计的变换关系（R 和 t）来计算距离最近点对经过变换之后的误差，
经过不断的迭代直至误差小于某一阈值或者达到迭代次数来确定最终的变换关系。


ICP算法采用最小二乘估计计算变换矩阵。
    1. 采用迭代计算，计算速度较慢。
    2. 对初始值有一定要求，如初始值不合理，有可能造成陷入局部最优的情况。
- 参考
    1. 高翔，视觉 SLAM 十四讲
    2. Least-Squares Rigid Motion Using SVD
    3. [ICP（迭代最近点）算法](https://www.cnblogs.com/21207-iHome/p/6038853.html)
    4. PCL点云库：ICP算法
    5. Interactive Iterative Closest Point
    6. How to incrementally register pairs of clouds