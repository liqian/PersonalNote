# 优秀的开源SLAM
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

## 2022.03.02 优秀的开源SLAM

### 视觉SLAM
1. ORB SLAM2(单双目RGB-D)  https://github.com/raulmur/ORB_SLAM2
2. DSO（单目） https://github.com/JakobEngel/dso
3. InfiniTAM v3(RGB-D) https://github.com/victorprad/InfiniTAM
> 接近实战。当前已经不在更新了。
4. Sold² https://github.com/cvg/SOLD2
> Sold²是一种深线段检测器和描述符，可以在没有手动标记线段的情况下进行训练，并且即使存在遮挡的情况下也能可靠地匹配直线。
> 利用描述符学习的最新进展，提出线描述符具有高度的区分性，同时对视点变化和遮挡保持鲁棒性。
> 论文：https://arxiv.org/abs/2104.03362
### 视觉+惯导SLAM
1. VINS-Fusion(单双目+IMU) https://github.com/HKUST-Aerial-Robotics/VINS-Fusion
2. OKVIS(单双目+IMU) https://github.com/ethz-asl/okvis
3. ORB SLAM3(单双目+IMU) https://github.com/UZ-SLAMLab/ORB_SLAM3

### 激光SLAM
1. Lego-LOAM https://github.com/RobustFieldAutonomyLab/LeGO-LOAM
2. Cartographer(Lidar+IMU) https://github.com/cartographer-project/cartographer

### 多传感器融合
LVI-SAM(LIDAR+单目+IMU+RTK+GPS) https://github.com/TixiaoShan/LVI-SAM

## 2022.03.03 F-LOAM
1. 南洋理工大学 F-LOAM ：最为快速和精准开源激光SLAM方案之一
2. F-LOAM：Fast Lidar Odometry And Mapping
3. https://github.com/wh200720041/floam
4. https://zhuanlan.zhihu.com/p/452544259

## 激光语义分割

### SuMa++: Efficient LiDAR-based Semantic SLAM
- https://github.com/PRBonn/semantic_suma
- [paper](https://www.ipb.uni-bonn.de/wp-content/papercite-data/pdf/chen2019iros.pdf)
- (./Paper/Others/LidarSematic/SuMa++  Efficient LiDAR-based Semantic SLAM.pdf)