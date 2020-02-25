#include "axis.h"

#include <glog/logging.h>

#include "cinn/common/axis.h"
#include "cinn/common/common.h"
#include "cinn/lang/compute.h"
#include "cinn/poly/dim.h"
#include "cinn/poly/domain.h"
#include "cinn/poly/stage.h"

namespace cinn {
namespace common {

std::vector<ir::Var> GenDefaultAxis(int naxis) {
  std::vector<ir::Var> axis;
  for (int i = 0; i < naxis; i++) {
    axis.emplace_back(common::axis_name(i));
  }
  return axis;
}

const std::vector<std::string> kAxises({
    "i",  // level 0
    "j",  // level 1
    "k",  // level 2
    "a",  // level 3
    "b",  // level 4
    "c",  // level 5
    "d",  // level 6
    "e",  // level 7
    "f",  // level 8
    "g",  // level 9
    "h"   // level 10
});

const std::string &axis_name(int level) {
  CHECK_LT(level, kAxises.size());
  return kAxises[level];
}

}  // namespace common
}  // namespace cinn
