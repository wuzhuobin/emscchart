#ifndef RADAR_H
#define RADAR_H

#include "dataset_controller.h"

namespace emscchart {
class RadarController : public DatasetController {
 public:
  static constexpr char const* kId = "radar";
  RadarController(Chart& chart, unsigned int dataset_index);
  void Update() override;
};
}  // namespace emscchart
#endif  // RADAR_H