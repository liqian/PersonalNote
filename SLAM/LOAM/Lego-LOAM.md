# 简介
LeGO-LOAM: Lightweight and Ground-Optimized Lidar Odometry and Mapping on Variable Terrain

论文：https://ieeexplore.ieee.org/abstract/document/8594299

代码：
> [LeGO-LOAM-BOR](https://github.com/facontidavide/LeGO-LOAM-BOR/tree/speed_optimization) 
> [LeGO-LOAM NOTED](https://github.com/wykxwyc/LeGO-LOAM_NOTED)
>  [Github](https://github.com/RobustFieldAutonomyLab/LeGO-LOAM)

文章：
- [三维SLAM算法LeGO-LOAM源码阅读一](https://blog.csdn.net/weixin_42048023/article/details/87452610)


# 代码
- [Github](https://github.com/RobustFieldAutonomyLab/LeGO-LOAM)


# 算法核心
## 点云分割
1. 地面
- [地面分割：Fast Segmentation of 3D Point Clouds for Ground Vehicles](https://blog.csdn.net/lovelyaiq/article/details/118826534 )
> 参考论文：M. Himmelsbach, F.V. Hundelshausen, and H-J. Wuensche, 
> “Fast Segmentation of 3D Point Clouds for Ground Vehicles,” 
> Proceedings of the IEEE Intelligent Vehicles Symposium, pp. 560-565, 2010

> **核心思想**：
> 将点云从三维p(x,y,z)将到二维p(d, z)，虽然点云的维度减少，但点云的有效信息是不减少的：
> 1. d = sqrt(x*x + y*y) ，相当于把笛卡尔坐标系转换到极坐标系。
> 2. 保留Z轴的信息，要基于z的高度信息判断是否该点是否为路面点。

> Lego中采用的是atan2(z,d) < 10 度为Ground Point

2. 非地面 -- 基于图像深度的分割方式进行聚类
- [range image上分割](https://blog.csdn.net/weixin_43211438/article/details/89357039)
> 参考论文：
> I. Bogoslavskyi and C. Stachniss, 
> “Fast Range Image-based Segmentation of Sparse 3D Laser Scans for Online Operation,” 
> Proceedings of the IEEE/RSJ International Conference on Intelligent Robots and Systems, pp. 163-169, 2016. 

> **核心思路**
> 
