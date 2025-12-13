#include <stdio.h>
#include "stdlib.h"
#include <print>

#include "grpc/grpc.h"
#include "grpcpp/server_builder.h"

#include "rpc_interfaces/cluster_controller_api.pb.h"
#include "rpc_interfaces/cluster_controller_api.grpc.pb.h"

int main() {
    scheduler::v1::JobSpec job;
    job.set_command("echo");
    job.add_args("hello");

    std::print("Command: {}\n", job.command());
    return 0;
}