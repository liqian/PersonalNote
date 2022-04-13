[PCL点云滤波](https://zhuanlan.zhihu.com/p/102748557)


## VoxelGridFilter
点云VoxelGridFilter，称为体素格下采样，也叫抽稀。下采样是一种能显著减少点云的数据量，并保持其形状特征和空间结构信息与原始点云基本没差别的算法。

其核心是: 将点云分割成一个个微小的立方体，落在立方体内的所有点用一个重心点来最终表示，对所有的小立方体处理后得到最终的点云结果。

取重心点比所有点取平均值的算法稍慢，但是其结果更准确；
下采样设置的voxelGridFilter.set_leaf_size(rate,rate,rate) 值越大，最后保留的点云越少。

### error：[pcl::VoxelGrid::applyFilter] Leaf size is too small for the input dataset. Integer indices would overflow
划分的立方体格子的个数index是int32位，由于输入的点云的x，y，z跨度太大，导致划分的立方体个数超出了int32的最大大小，因此报错。

- 通用解决办法
    1. 对精度要求没那么高的话，可以将leaf size大小设置大一些。
    2. 将要降采样的点云先分割成几块、在做降采样。
    3. 使用 OctreeVoxelGridFilter，参考PCL论坛。