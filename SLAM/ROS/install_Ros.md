
# ROS installtion

先更新Ubuntu的服务器，由于国外服务器连接有问题。
1. 使用mirror，更新/etc/apt/sources.list.
2. 使用 [Software&Update]-->[Download from ] 选择中国的。我试了 使用aliyun的好用。

----

## Melodic for ubuntu 18.04(Bionic)
- https://wiki.ros.org/melodic

- Ubuntu install of ROS Melodic(https://wiki.ros.org/melodic/Installation/Ubuntu)
**only for 18.04**
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
```bash
sudo apt-key add ros.asc
```
1.4. Installation
First, make sure your Debian package index is up-to-date:
```bash
    sudo apt update
```
Now pick how much of ROS you would like to install.

**Desktop-Full Install: (Recommended)**: Everything in Desktop plus 2D/3D simulators and 2D/3D perception packages
```
    sudo apt install ros-melodic-desktop-full
```

1.5 Environment setup
You must source this script in every bash terminal you use ROS in.
```bash
source /opt/ros/melodic/setup.bash
```
It can be convenient to automatically source this script every time a new shell is launched. These commands will do that for you. 

```bash
echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

----


## Noetic  for Ubuntu 20.04 (Focal) 
- https://wiki.ros.org/noetic
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

---

# 踩坑和错误
1. `pkgProblemResolver::Resolve generated breaks, this may be caused by held packages`
解决： `sudo apt dist-upgrade`