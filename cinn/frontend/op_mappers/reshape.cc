// Copyright (c) 2021 CINN Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "cinn/backends/cuda_util.h"
#include "cinn/frontend/op_mapper_registry.h"
#include "cinn/frontend/op_mappers/common_utils.h"

namespace cinn {
namespace frontend {
namespace op_mappers {

void ReshapeOpMapper(const paddle::cpp::OpDesc& op_desc, const OpMapperContext& ctx) {
  CHECK_EQ(op_desc.Input("X").size(), 1UL);
  auto x_name = op_desc.Input("X").front();
  auto x      = ctx.GetVar(x_name);

  auto shape = utils::GetAttrOrDefault<std::vector<int>>(op_desc, "shape");

  VLOG(4) << "x shape: " << cinn::utils::Join(x->shape, ",");
  VLOG(4) << "reshape to : " << cinn::utils::Join(shape, ",");

  auto out = ctx.Builder()->reshape(x, shape);

  CHECK_EQ(op_desc.Output("Out").size(), 1UL);
  auto out_name = op_desc.Output("Out").front();
  ctx.AddVar(out_name, out);
  ctx.AddVarModelToProgram(out_name, out->id);
}

void Reshape2OpMapper(const paddle::cpp::OpDesc& op_desc, const OpMapperContext& ctx) {
  CHECK_EQ(op_desc.Input("X").size(), 1UL);
  auto x_name = op_desc.Input("X").front();
  auto x      = ctx.GetVar(x_name);

  auto shape = utils::GetAttrOrDefault<std::vector<int>>(op_desc, "shape");

  VLOG(4) << "x shape: " << cinn::utils::Join(x->shape, ",");
  VLOG(4) << "reshape to : " << cinn::utils::Join(shape, ",");

  auto out = ctx.Builder()->reshape(x, shape);

  CHECK_EQ(op_desc.Output("Out").size(), 1UL);
  auto out_name = op_desc.Output("Out").front();
  ctx.AddVar(out_name, out);
  ctx.AddVarModelToProgram(out_name, out->id);

  // Reshape2 adds an intermediate output(XShape) based on
  // Reshape, the XShape is used to carry the shape and lod of X which
  // will be used in Reshape_grad, in this way, the framework can reuse
  // the memory of X immediately the Reshape2_op is finished.
  // Considering compatibility issues, we could not fix Reshape2_op
  CHECK_EQ(op_desc.Output("XShape").size(), 1UL);
  auto xshape_name = op_desc.Output("XShape").front();

  auto xshape = x;
  xshape.set_id(cinn::utils::TransValidVarName(xshape_name));

  ctx.AddVar(xshape_name, xshape);
  ctx.AddVarModelToProgram(xshape_name, xshape->id);
}

}  // namespace op_mappers
}  // namespace frontend
}  // namespace cinn

CINN_REGISTER_HELPER(reshape) {
  CINN_REGISTER_OP_MAPPER(reshape, cinn::frontend::op_mappers::ReshapeOpMapper)
  CINN_REGISTER_OP_MAPPER(reshape2, cinn::frontend::op_mappers::Reshape2OpMapper)
  return true;
}
