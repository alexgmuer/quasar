#include <stdio.h>
#include "stdlib.h"
#include <print>

#include "grpc/grpc.h"
#include "grpcpp/server_builder.h"

#include "cluster_controller/lib/engine.hpp"

int main() {
    std::print("--CLUSTER SCHEDULER INITIALIZATION---\n");

    JobStore job_store;
    SchedulerServiceImpl service(job_store);
    std::string server_addr("0.0.0.0:50051");

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_addr, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::print("Server listening on {}...\n", server_addr);
    server->Wait();
    return 0;
}