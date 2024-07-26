#ifndef EMSCCHART_DATASET_CONTROLLER_H
#define EMSCCHART_DATASET_CONTROLLER_H

#include <functional>
#include <memory>

namespace emscchart {
struct Metaset;
struct Dataset;
class Chart;
class Element;
class DatasetController {
 public:
  using ElementFactory = std::function<std::unique_ptr<Element>()>;
  static ElementFactory dataset_element_factory_;
  static ElementFactory data_element_factory_;
  DatasetController(Chart& chart, unsigned int dataset_index);
  virtual ~DatasetController() = default;
  void Initialize();
  virtual void Update() = 0;
  void Draw();

  void AddElements();
  void BuildOrUpdateElements(bool resetNewElement);
  //  GetDataset();
  [[nodiscard]] auto GetMeta() const -> Metaset&;

 private:
  Chart& chart_;
  unsigned int index_;
  Metaset& cached_meta_;
  ElementFactory dataset_element_type_;
  ElementFactory data_element_type_;
};
}  // namespace emscchart

#endif  // EMSCCHART_DATASET_CONTROLLER_H