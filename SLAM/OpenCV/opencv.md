#
- https://opencv.org/

## ubunt20.04安装
1. 预编译好的Python安装包
```bash
sudo apt update
sudo apt libopencv-dev python3-opencv
``` 

2. Install OpenCV through the source
2.1. Install build tools
Install the required build tools and dependencies on your system by using the following command:
```
sudo apt install build-essential cmake git 
sudo apt install pkg-config libgtk-3-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev \
gfortran openexr libatlas-base-dev python3-dev python3-numpy \
libtbb2 libtbb-dev libdc1394-22-dev libopenexr-dev \
libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev
```

2.2. Clone OpenCV’s repositories
Make the directory and navigate in it. Clone the OpenCV repository by running the following command:
```
mkdir ~/opencv_build && cd ~/opencv_build
git clone https://github.com/opencv/opencv.git
```

Then, clone the OpenCV contrib repositories by using the following command:
```
git clone https://github.com/opencv/opencv_contrib.git
```

2.3. Setup OpenCV build
Once the download is completed, create a directory named ‘build’ and navigate to it as follows:
```
cd ~/opencv_build/opencv
mkdir -p build && cd build
```

Now, setup OpenCV build with CMake by using the following command:
```
cmake -D CMAKE_BUILD_TYPE=RELEASE \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D INSTALL_C_EXAMPLES=ON \
-D INSTALL_PYTHON_EXAMPLES=ON \
-D OPENCV_GENERATE_PKGCONFIG=ON \
-D OPENCV_EXTRA_MODULES_PATH=~/opencv_build/opencv_contrib/modules \
-D BUILD_EXAMPLES=ON ..
```

2.4. Start a compilation
```
make -j8
```

2.5. Install OpenCV
Install the OpenCV by executing the following command:
```
sudo make install
```

2.6. Verify
After completing the installation process, type the following command to verify the OpenCV installation. For C++ binding:
```
pkg-config --modversion opencv4
```

For python binding run the command as follows:
```
python3 -c "import cv2; print(cv2.__version__)"
```