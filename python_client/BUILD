load("@rules_python//python:defs.bzl", "py_binary")

package(default_visibility = ["//visibility:public"])

py_binary(
    name = "client",
    srcs = ["client.py"],
    deps = [
        "//rpc_interfaces:cluster_controller_py_grpc",
    ],
)