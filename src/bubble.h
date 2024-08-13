#ifndef EMSCCHART_BUBBLE_CONTROLLER_H_
#define EMSCCHART_BUBBLE_CONTROLLER_H_

#include "dataset_controller.h"

namespace emscchart {
class BubbleController : public DatasetController {
 public:
  static constexpr std::string_view kId = "bubble";
  BubbleController(Chart& chart, unsigned int dataset_index)
      : DatasetController(chart, dataset_index) {}
  void Update(UpdateMode mode) override;
  void UpdateElements(std::vector<std::unique_ptr<Element>>& elements,
                      unsigned int start, unsigned int count,
                      UpdateMode mode) override;
};
}  // namespace emscchart

#endif  // EMSCCHART_BUBBLE_CONTROLLER_H_