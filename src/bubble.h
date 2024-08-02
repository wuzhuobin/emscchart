#ifndef EMSCCHART_BUBBLE_CONTROLLER_H_
#define EMSCCHART_BUBBLE_CONTROLLER_H_

#include "dataset_controller.h"

namespace emscchart {
class BubbleController : public DatasetController {
 public:
  BubbleController(Chart& chart, unsigned int dataset_index)
      : DatasetController(chart, dataset_index) {}
  static constexpr std::string_view kId = "bubble";
  void Update(UpdateMode mode) override {}
};
}  // namespace emscchart

#endif  // EMSCCHART_BUBBLE_CONTROLLER_H_