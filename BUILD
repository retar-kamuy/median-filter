cc_library(
    name = "bubbleSort",
    srcs = ["bubbleSort.cpp"],
    hdrs = ["include/bubbleSort.hpp"],
)

cc_library(
    name = "bitonicSort",
    srcs = ["bitonicSort.cpp"],
    # copts = ["-D__SYNTHESIS__"],
    hdrs = ["include/bitonicSort.hpp"],
)

cc_binary(
    name = "medianFilter",
    srcs = ["main.cpp", "medianFilter.cpp", "include/medianFilter.hpp"],
    copts = ["-fdiagnostics-color=always","-g", "-std=c++17"],
    linkopts = ["-L/opt/opencv-4.7.0/lib64"],
    env = {"LD_LIBRARY_PATH": "/opt/opencv-4.7.0/lib64"},
    data = ["data/Lenna_noise.png"],
    deps = ["//:bitonicSort", "@opencv_linux//:opencv"],
)

cc_test(
    name = "bubbleSort_test",
    srcs = ["test/bubbleSort_test.cpp"],
    copts = ["-ImedianFilter"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//:bubbleSort",
    ],
)

cc_test(
    name = "bitonicSort_test",
    srcs = ["test/bitonicSort_test.cpp"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//:bitonicSort",
    ],
)