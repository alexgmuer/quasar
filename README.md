# About
# NOTE: This project has migrated to gitlab [here](https://gitlab.com/alexgmuer/quasar) and this github repo is no longer maintained.
This is a repo containing the various components of a workload scheduler.

# High Level Architecture
Below is the target architecture:
![Architecture](docs/WorkloadScheduler.drawio.svg)

The tentative implementation will use protobufs and gRPC for communication between the different components.

# Roles and Responsibilities

## Client CLI
- Makes workload requests of the Cluster Controller

## Cluster Controller
- Schedules requests made by the client with available node agents
- Accepts new node registration requests
- Monitors node agent heartbeats and resource utilization

## Node Agent
- Registers with the cluster controller
- Accepts requests from the controller and executes them
- Reports heartbeat and resource utilization

# Requirements

All components should be able to be containerized, so I can also experiment with deployment strategies (Kubernetes, etc).

## Client CLI
- (Initial) Issues the requests to the cluster controller in a way that can generalize to a gitlab runner easily
- (Initial) Written in a language which is different from the cluster controller and node agent (For my own interest)

## Cluster Controller
- (Long term) Be able to characterize nodes based on their reported hardware availability, and schedule jobs appropriately. (i.e if a node has a lot of GPU horsepower, and a job comes in which has a matching workload, schedule it there)

## Node Agent
- High performance and low footprint


# Development
## Building and Running
I chose to use [Bazel build system](https://bazel.build) for this project, as a fun learning exercise. In order to build all targets, one simply has to run (from the base directory):
```bash
bazel build
```

To build a specific target, use the following syntax:
```bash
bazel build //<path to BUILD file with target>:<name of target>
```

For example, to build the cluster controller executable:
```bash
bazel build //cluster_controller/app:cluster_controller
```
And following with the example, to run it:
```bash
bazel run //cluster_controller/app:cluster_controller
```
