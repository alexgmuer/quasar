load("@rules_proto//proto:defs.bzl", "proto_library")
load("@grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

package(default_visibility = ["//visibility:public"])

proto_library(
    name = "cluster_controller_proto",
    srcs = ["cluster_controller_api.proto"],
)

cc_proto_library(
    name = "cluster_controller_cc_proto",
    deps = [":cluster_controller_proto"],
)

cc_grpc_library(
    name = "cluster_controller_cc_grpc",
    srcs = [":cluster_controller_proto"],
    grpc_only = True,
    deps = [":cluster_controller_cc_proto"],
)
