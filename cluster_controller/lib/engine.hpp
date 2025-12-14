#include "grpc/grpc.h"
#include "grpcpp/server_builder.h"

#include "rpc_interfaces/cluster_controller_api.pb.h"
#include "rpc_interfaces/cluster_controller_api.grpc.pb.h"

class SchedulerServiceImpl final : public scheduler::v1::SchedulerService::Service {
public:
    SchedulerServiceImpl() = default;

    grpc::Status SubmitJob(
        grpc::ServerContext*,
        const scheduler::v1::SubmitJobRequest* request,
        scheduler::v1::SubmitJobResponse* response) override {
        scheduler::v1::Job job;
        const std::string job_id = next_job_id();

        job.set_job_id(job_id);
        *job.mutable_spec() = request->spec();
        job.set_state(scheduler::v1::JobState::JOB_STATE_PENDING);
        job.set_submit_time_unix_ms(now_ms());

        {
            std::lock_guard<std::mutex> lock(mu_);
            jobs_[job_id] = job;
        }

        response->set_job_id(job_id);

        std::print("Submitted job {}\n", job_id);
        return grpc::Status::OK;
    }

private:
    static uint64_t now_ms() {
        using namespace std::chrono;
        return duration_cast<milliseconds>(
            system_clock::now().time_since_epoch()).count();
    }

    static std::string next_job_id() {
        static std::atomic<uint64_t> counter{1};
        return "job-" + std::to_string(counter++);
    }

    std::mutex mu_;
    std::unordered_map<std::string, scheduler::v1::Job> jobs_;
};