#ifndef EMSCCHART_DATASET_CONTROLLER_H
#define EMSCCHART_DATASET_CONTROLLER_H

namespace emscchart {
class Chart;
class DatasetController {
 public:
  DatasetController(Chart const& chart, unsigned int dataset_index);
  void Initialize();

 private:
  Chart const& chart_;
};
}  // namespace emscchart

#endif  // EMSCCHART_DATASET_CONTROLLER_H