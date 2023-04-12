cc_library(
    name = "bubbleSort",
    srcs = ["bubbleSort.cpp"],
    hdrs = ["include/bubbleSort.hpp"],
)

cc_library(
    name = "bitonicSort",
    srcs = ["bitonicSort.cpp"],
    copts = ["-D__SYNTHESIS__"],
    hdrs = ["include/bitonicSort.hpp"],
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