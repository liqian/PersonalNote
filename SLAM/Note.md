# 学习过程
- 圈子：SLAM知识星球
- https://github.com/orgs/OpenSLAM/repositories?type=all
- [awesome-SLAM-list](https://github.com/OpenSLAM/awesome-SLAM-list)
- [深蓝学院](https://www.shenlanxueyuan.com/orientation/slam)
# 视觉SLAM
- 
## OpenCV
- 金字塔
- 滤波
- 

# 开源数学库
## 矩阵处理库Eigen
## 李代数库Sophus
## 图优化库G2o
## 非线性优化库Ceres
## 云库PCL [Point Cloud Library.md]
##  isam
## gtsam



# 激光SLAM
- [激光雷达SLAM算法大全 知乎文章--不错](https://www.zhihu.com/column/c_1220713322028761088)

## [The KITTI Vision Benchmark Suite](http://www.cvlibs.net/datasets/kitti/eval_odometry.php)
这里全是SLAM数据集以及各个SLAM算法的评测结果。

## 激光SLAM 开源库
- [LOAM/Note.md]
- 推荐一本书籍：上海交大刘佩林教授、应忍冬教授最近刚出了新书《玩转3D视界 —3D机器视觉及其应用》


# 数学
- [国际Zlibray网址]https://b-ok.as/book/16839550/d138d4?dsource=recommend
- 公式书写：https://www.latexlive.com/##

## 线性代数
- [B站线性代数视频教学] https://www.bilibili.com/video/BV1ys411472E?spm_id_from=333.999.0.0
- 线性代数及其应用（原书第5版）第九章
### 向量基本运算
- https://blog.csdn.net/qq_23869697/article/details/82693000
- https://zhuanlan.zhihu.com/p/387074063
- https://zhuanlan.zhihu.com/p/362035810


# OTher
- [视觉/激光SLAM从理论到实战](https://zhuanlan.zhihu.com/p/293039582)
- [SLAM算法入门必备资料](https://zhuanlan.zhihu.com/p/356596070)
- [SLAM入门的书](https://zhuanlan.zhihu.com/p/168027225)
- [SLAM入门的书](https://www.zhihu.com/question/392255715)
- [g2o学习](https://zhuanlan.zhihu.com/p/121628349)
- [SLAM激光SLAM初学者代码及论文推荐](https://blog.csdn.net/inf4inf/article/details/108574555)
- [CSDN 博主关于SLAM算法的分析和源码阅读](https://blog.csdn.net/weixin_42048023?type=blog)
- [国外的一个图形视觉的课程，资料不错](https://cseweb.ucsd.edu/classes/sp21/cse291-i/)


## 图像处理算法库
- OpenCV -- 开源
- HaIcon -- 商业收费，德国
- VisionPro -- 商业收费 美国
## 学习项
- 机器人学
- 计算机图形学

## 坐标系
1. 全局坐标系Global frame

该坐标系为世界坐标系，其他各传感器之间的坐标变换都可用该坐标系作为参考。该坐标系的z轴指向天空，x轴指向正东方，y轴指向北极。

2. 车身坐标系Vehicle frame

该坐标系随车的位置变化而变化，可以看作车的自我坐标系(ego)，它的x轴指向车的正前方，y轴指向车的左边，z轴指向天空。（车的姿态矩阵pose定义为vehicle frame到global frame的变换矩阵）

3. 传感器坐标系Sensor frame

可以看作传感器的自我坐标系(ego)。它的x轴指向传感器的正前方，y轴指向传感器的左边，z轴指向天空。（它的位姿定义为sensor frame到vehicle frame的转移矩阵，可以看作传感器到车身的外参）

4. 图像坐标系Image frame

与上面的坐标系不同，此处是2D坐标系，它的横坐标x长度是width，纵坐标y的长度是height。原点是图像的左上角。(由sensor frame到image frame是内参)

5. 雷达球形坐标系LiDAR Spherical coordinate system

该坐标系和其他几个3D检测数据集的坐标系很不一样，它把一个LiDAR坐标(x,y,z)转换成球坐标系下的(range长度，azimuth左右方位角，inclination上下方位角)
![](lidar_coordinate_system.jpg)

# 多传感器融合
## 卡尔曼滤波
- 高效率的递归滤波器