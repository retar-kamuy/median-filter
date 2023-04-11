cc_library(
    name = "bubbleSort",
    srcs = ["bubbleSort.cpp"],
    hdrs = ["include/bubbleSort.hpp"],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
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
