# 学习过程
- 圈子：SLAM知识星球
- https://github.com/orgs/OpenSLAM/repositories?type=all
- [awesome-SLAM-list](https://github.com/OpenSLAM/awesome-SLAM-list)
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

## 2021年十大最佳开源SLAM算法()
- TANDEM 
> 纯视觉SLAM
> 创新点：
> 1. 一种新的单目实时稠密SLAM框架，将经典的直接VO和基于学习的MVS重建无缝结合； 
> 2. 第一个利用全局TSDF模型渲染的深度图，实现单目稠密跟踪前端
> 3. 一种新的MVS网络，CVA-MVSnet,他能够通过视图聚合和多级深度预测来使用整个关键帧窗口

- MonoRec
> 纯视觉SLAM
> 不需要激光雷达， 只需要单目相机，即可在动态环境下，实现半监督稠密重建。
> 动态重建的难点：如何保证不受移动物体的影响？ 
> 作者结合了深度MVS和单目深度估计算法，
> 先使用了MaskModule识别移动像素，降低代价体中相应体素的权重，在利用DepthModule，实现对静态和动态物体进行深度估计。
> 可以应用于三维重建，用于自动驾驶和AR领域。

- Range-MCL
> 激光雷达SLAM
> 可用于自动驾驶汽车的激光雷达的全局定位。
> 该工作基于蒙特卡罗定位和粒子滤波，来估计移动机器人和自动驾驶汽车的姿态，以实现全局定位。
> 传感器模型将当前的激光雷达臊面的距离图像和三角网格渲染的合成距离图像，进行比较，更新粒子的权重。

- MULLS
> 激光雷达SLAM：高效 低漂移 通用的
> 前端使用双阈值地面滤波和PCA，从每帧中提取地面、柱子等特征，然后用多尺度线性最小二乘ICP算法实现子地图的配准。
> 对于后端，在存储的历史子图之间进行分层位姿图优化，以减少因航位推算而产生的漂移。

- LiLi-OM
> 激光雷达惯性SLAM：专门用于固态和机械激光雷达
> 特点：
> 1. 针对Livox Horizon的不规则扫描模式量身定做了新的特征提取方法
> 2. 前端为基于特征的轻量级激光雷达里程计，采用自适应的关键帧选择，提供快速的运动估计。
> 3. 后端采用基于关键帧的分层滑动窗口优化，直接融合IMU和LiDAR测量数据。

- FAST-LIO2
> 激光雷达惯性SLAM
> 可用于自动驾驶、无人机、快速移动的手持设备等场景。
> 特点：
> 1. 计算效率高，在大型室外环境中帧率能达到100Hz
> 2. 鲁棒性高，在旋转速度高达1000度/秒的杂乱室内环境中进行可靠的姿态估计。
> 3. 通用性好，适用于多线旋转和固态激光雷达、无人机和手持平台。
> 4. 精度高

- R3LIVE
> 多传感器融合SLAM:开源视觉+激光+惯性的多传感器融合SLAM系统

- GVINS
> 多传感器融合SLAM：GNSS-视觉-惯性融合的SLAM系统

- LVI-SAM
> 多传感器融合SLAM：视觉+激光+惯性

- DSP-SLAM
> 语义SLAM

- 来源(https://appafc4omci9700.h5.xiaoeknow.com/v1/course/column/p_61cc350be4b0a91144afd6ab?app_id=appafc4omci9700&entry=2&entry_type=2001&payment_type=&product_id=p_61cc350be4b0a91144afd6ab&resource_id=&resource_type=6&scene=%E5%88%86%E4%BA%AB&share_type=5&share_user_id=u_61ea035b79b55_4jA90l3j0l&type=3)

## 图像处理算法库
- OpenCV -- 开源
- HaIcon -- 商业收费，德国
- VisionPro -- 商业收费 美国
## 学习项
- 机器人学
- 计算机图形学

