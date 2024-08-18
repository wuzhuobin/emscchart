#ifndef EMSCCHART_BUBBLE_CONTROLLER_H_
#define EMSCCHART_BUBBLE_CONTROLLER_H_

#include "dataset_controller.h"

namespace emscchart {
class BubbleController : public DatasetController {
 public:
  static constexpr std::string_view kId = "bubble";
  BubbleController(Chart& chart, unsigned int dataset_index);
  /**
   * @brief Not used yet.
   * @todo Need to check when it could be used.
   */
  void Initialize();
  void Update(UpdateMode mode) override;
  void UpdateElements(std::vector<std::unique_ptr<Element>>& elements,
                      unsigned int start, unsigned int count,
                      UpdateMode mode) override;

 private:
#ifdef TESTING
  friend class BubbleControllerTest;
#endif
};
}  // namespace emscchart

#endif  // EMSCCHART_BUBBLE_CONTROLLER_H_