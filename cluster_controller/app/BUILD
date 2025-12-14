load("//cluster_controller/toolchain:flags.bzl", "CPP_FLAGS")

cc_binary(
    name = "cluster_controller",
    srcs = ["cluster_controller.cpp"],
    deps = [
        "//cluster_controller/lib:engine",
        "@grpc//:grpc++",
        "@grpc//:grpc++_reflection",
        ],
    copts = CPP_FLAGS
)