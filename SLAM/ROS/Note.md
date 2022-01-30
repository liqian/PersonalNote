# ROS
- http://wiki.ros.org/ROS/Tutorials
- [动手学ROS](https://zhuanlan.zhihu.com/p/422007778)

# ROS常用命令
## [rosbag](http://wiki.ros.org/rosbag/Commandline)
- `rosbag info <your bagfile>`
will show the following info:
```
path:        2014-12-10-20-08-34.bag
version:     2.0
duration:    1:38s (98s)
start:       Dec 10 2014 20:08:35.83 (1418270915.83)
end:         Dec 10 2014 20:10:14.38 (1418271014.38)
size:        865.0 KB
messages:    12471
compression: none [1/1 chunks]
types:       geometry_msgs/Twist [9f195f881246fdfa2798d1d3eebca84a]
             rosgraph_msgs/Log   [acffd30cd6b6de30f120938c17c593fb]
             turtlesim/Color     [353891e354491c51aabe32df673fb446]
             turtlesim/Pose      [863b248d5016ca62ea2e895ae5265cf9]
topics:      /rosout                    4 msgs    : rosgraph_msgs/Log   (2 connections)
             /turtle1/cmd_vel         169 msgs    : geometry_msgs/Twist
             /turtle1/color_sensor   6149 msgs    : turtlesim/Color
             /turtle1/pose           6149 msgs    : turtlesim/Pose
```

This tells us topic names and types as well as the number (count) of each message topic contained in the bag file.

- `rosbag play <your bagfile>`
In this window you should immediately see something like:
```
[ INFO] [1418271315.162885976]: Opening 2014-12-10-20-08-34.bag

Waiting 0.2 seconds after advertising topics... done.

Hit space to toggle paused, or 's' to step.
```

The waiting period can be specified with the -d option.

1. `rosbag play -s 5  <your bagfile>`: Start SEC seconds into the bags.

2. `rosbag play -r 2 <your bagfile>` : 以2倍的速率进行播放

3. `rosbag play --clock <your bagfile>` : publish the clock time

4. `rosbag play ros.bag /point_cloud_display:=/velodyne_points` : rename topic names

## [rosenode]

## [rosetopic]

# ROS rviz 显示
首先需要先将roscore运行起来
```
roscore
```

1. 数据 nsh_indoor_outdoor.bag
```
rosbag info nsh_indoor_outdoor.bag
```
可以看出topic：/velodyne_points
2. 查看Frame_id

```
rosbag play nsd_indoor_outdoor.bag
```

另起终端：
```
rostopic echo /velodyne_points | grep frame_id
``` 

查看结果如下：frame_id=velodyne

3. rviz 显示点云信息
```
rosrun rviz rviz
```

设置rviz
点击add-》PointCloud2
设置：
fix-frame=velodyne
topic：/velodyne_points

播放bag包:
```
rosbag play nsh_indoor_outdoor.bag 
```