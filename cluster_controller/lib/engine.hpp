#include "grpc/grpc.h"
#include "grpcpp/server_builder.h"

#include "rpc_interfaces/cluster_controller_api.pb.h"
#include "rpc_interfaces/cluster_controller_api.grpc.pb.h"

// todo for class: error handling, maybe sizing/allocators as template args?
class JobStore {
public:
    JobStore() = default;

    void insert_job(std::string job_id, scheduler::v1::Job job) {
        std::lock_guard<std::mutex> lock(job_mutex);
        jobs[job_id] = job;
    }

    // get_job definitely returns a copy and not a ref so we don't downstream the race condition
    scheduler::v1::Job get_job(std::string job_id) {
        std::lock_guard<std::mutex> lock(job_mutex);
        return jobs[job_id];
    }

private:
    std::mutex job_mutex;
    // todo: technically the lock semantics is very heavy handed at the moment. 
    // This will likely impact performance at some point, and it would be good design to limit the scope of locking
    std::unordered_map<std::string, scheduler::v1::Job> jobs;
};

class SchedulerServiceImpl final : public scheduler::v1::SchedulerService::Service {
public:
    // Needs to be initialized with externally allocated job_store, that will also be passed into other classes
    SchedulerServiceImpl(JobStore& _job_store) : job_store(_job_store) {}

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

        // call to insert_job()
        job_store.insert_job(job_id, job);

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

    // ref here because the data will be owned by the caller
    JobStore& job_store;
};