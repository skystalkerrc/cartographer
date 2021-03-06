/*
 * Copyright 2017 The Cartographer Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CARTOGRAPHER_CLOUD_INTERNAL_CLIENT_POSE_GRAPH_STUB_H_
#define CARTOGRAPHER_CLOUD_INTERNAL_CLIENT_POSE_GRAPH_STUB_H_

#include "cartographer/mapping/pose_graph_interface.h"
#include "grpc++/grpc++.h"

namespace cartographer {
namespace cloud {

class PoseGraphStub : public ::cartographer::mapping::PoseGraphInterface {
 public:
  PoseGraphStub(std::shared_ptr<::grpc::Channel> client_channel);

  PoseGraphStub(const PoseGraphStub&) = delete;
  PoseGraphStub& operator=(const PoseGraphStub&) = delete;

  void RunFinalOptimization() override;
  mapping::MapById<mapping::SubmapId, SubmapData> GetAllSubmapData() override;
  mapping::MapById<mapping::SubmapId, SubmapPose> GetAllSubmapPoses() override;
  transform::Rigid3d GetLocalToGlobalTransform(int trajectory_id) override;
  mapping::MapById<mapping::NodeId, mapping::TrajectoryNode>
  GetTrajectoryNodes() override;
  mapping::MapById<mapping::NodeId, mapping::TrajectoryNodePose>
  GetTrajectoryNodePoses() override;
  std::map<std::string, transform::Rigid3d> GetLandmarkPoses() override;
  bool IsTrajectoryFinished(int trajectory_id) override;
  bool IsTrajectoryFrozen(int trajectory_id) override;
  std::map<int, mapping::PoseGraphInterface::TrajectoryData> GetTrajectoryData()
      override;
  std::vector<Constraint> constraints() override;
  mapping::proto::PoseGraph ToProto() override;

 private:
  std::shared_ptr<::grpc::Channel> client_channel_;
};

}  // namespace cloud
}  // namespace cartographer

#endif  // CARTOGRAPHER_CLOUD_INTERNAL_CLIENT_POSE_GRAPH_STUB_H_
