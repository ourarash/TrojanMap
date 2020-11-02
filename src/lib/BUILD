load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "TrojanMap",
    srcs = ["trojanmap.cc"],
    hdrs = ["trojanmap.h"],
    deps = ["@opencv//:opencv"],
    data = ["map.csv", "input.jpg"],
    visibility = ["//visibility:public"],
)