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

cc_library(
    name = "medianFilter",
    srcs = ["medianFilter.cpp"],
    hdrs = ["include/medianFilter.hpp", "include/common.hpp"],
    deps = ["//:bitonicSort"],
)

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    linkopts = ["-L/opt/opencv-4.7.0/lib64"],
    env = {"LD_LIBRARY_PATH": "/opt/opencv-4.7.0/lib64"},
    data = ["data/Lenna_noise.png"],
    deps = ["//:medianFilter", "@opencv_linux//:opencv"],
)

cc_test(
    name = "bubbleSort_test",
    srcs = ["test/bubbleSort_test.cpp"],
    copts = ["-Iinclude"],
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

cc_test(
    name = "medianFilter_test",
    srcs = ["test/medianFilter_test.cpp", "include/common.hpp"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//:medianFilter",
    ],
)
