workspace(name = "opencv")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_google_googletest",
    urls = ["https://github.com/google/googletest/archive/5ab508a01f9eb089207ee87fd547d290da39d015.zip"],
    strip_prefix = "googletest-5ab508a01f9eb089207ee87fd547d290da39d015",
)

# opecv4
new_local_repository(
    name = "opencv_linux",
    # path = "/opt/opencv-4.7.0/include",
    path = "C:\\opencv\\build\\include",
    build_file = "@//:opencv_linux.BUILD"
)
