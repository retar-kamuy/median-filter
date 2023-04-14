# median-filter

```sh
export INSTALL_DIR=/opt/opencv-4.7.0

dnf install -y cmake make llvm-toolset

curl -OL https://github.com/opencv/opencv/archive/4.7.0.zip
unzip 4.7.0.zip && rm -f 4.7.0.zip

cd opencv-4.7.0 && mkdir build && build

export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

cmake .. -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR
cmake --build . --parallel `nproc`

mkdir -p /usr/local/lib64/pkgconfig
cp opencv.pc /usr/local/lib64/pkgconfig/
```

```sh
export LD_LIBRARY_PATH=/opt/opencv/lib64
export PKG_CONFIG_PATH=/usr/local/lib64/pkgconfig
g++ main.cpp -o sample1.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
```

### opencv.pc

```make
Package Information for pkg-config

prefix=/opt/opencv-4.7.0
exec_prefix=${prefix}
includedir_old=${prefix}/include/opencv4/opencv
includedir_new=${prefix}/include/opencv4
libdir=${exec_prefix}/lib64

Name: opencv
Description: The opencv library
Version: 4.7.0
Libs: -L${libdir} -lopencv_dnn -lopencv_gapi -lopencv_highgui -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_video -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_videoio -lopencv_imgcodecs -lopencv_imgproc -lopencv_core
Libs.private: -ldl -lm -lpthread -lrt
Cflags: -I${includedir_old} -I${includedir_new}
```

# Reference

* [https://xilinx.github.io/Vitis-Tutorials/2021-1/build/html/docs/Hardware_Acceleration/Design_Tutorials/01-convolution-tutorial/lab2_conv_filter_kernel_design.html](https://xilinx.github.io/Vitis-Tutorials/2021-1/build/html/docs/Hardware_Acceleration/Design_Tutorials/01-convolution-tutorial/lab2_conv_filter_kernel_design.html)
* [https://xilinx.github.io/Vitis-Tutorials/2021-1/build/html/docs/Hardware_Acceleration/Design_Tutorials/01-convolution-tutorial/README.html](https://xilinx.github.io/Vitis-Tutorials/2021-1/build/html/docs/Hardware_Acceleration/Design_Tutorials/01-convolution-tutorial/README.html)