load("//cluster_controller/toolchain:flags.bzl", "CPP_FLAGS")

cc_library(
    name = "engine",
    srcs = ["engine.cpp"],
    hdrs = ["engine.hpp"],
    visibility = ["//visibility:public"],
    deps = [
        "//rpc_interfaces:cluster_controller_cc_proto",
        "//rpc_interfaces:cluster_controller_cc_grpc",
        "@grpc//:grpc++",
        "@grpc//:grpc++_reflection",
    ],
    copts = CPP_FLAGS
)