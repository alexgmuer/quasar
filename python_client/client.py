#!/usr/bin/env python3

import grpc
import rpc_interfaces.cluster_controller_api_pb2 as pb2
import rpc_interfaces.cluster_controller_api_pb2_grpc as pb2_grpc

def run():
    # Create a channel to the server
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = pb2_grpc.SchedulerServiceStub(channel)

        # Example: Submit a job
        job_spec = pb2.JobSpec(
            command="echo",
            args=["Hello, World!"],
            env={"TEST": "value"},
            resources=pb2.ResourceRequest(cpu_cores=1, memory_mb=512),
        )
        request = pb2.SubmitJobRequest(spec=job_spec)
        response = stub.SubmitJob(request)
        print(f"Submitted job with ID: {response.job_id}")

        # Example: Get the job
        get_request = pb2.GetJobRequest(job_id=response.job_id)
        get_response = stub.GetJob(get_request)
        print(f"Job state: {get_response.job.state}")

if __name__ == '__main__':
    run()