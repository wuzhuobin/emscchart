#ifndef RADAR_H
#define RADAR_H

#include "dataset_controller.h"

namespace emscchart {
class RadarController : public DatasetController {
 public:
  static constexpr std::string_view kId = "radar";
  RadarController(Chart& chart, unsigned int dataset_index);
  void Update(UpdateMode mode) override;
};
}  // namespace emscchart
#endif  // RADAR_H