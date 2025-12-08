load("//toolchain:flags.bzl", "CPP_FLAGS")

cc_binary(
    name = "cluster_controller",
    srcs = ["cluster_controller.cpp"],
    hdrs = ["cluster_controller.hpp"],
    deps = ["//lib:engine"]
    copts = CPP_FLAGS
)