#ifndef EMSCCHART_DATASET_CONTROLLER_H
#define EMSCCHART_DATASET_CONTROLLER_H

#include "config.h"
#include <nlohmann/json.hpp>
#include <functional>
#include <memory>

namespace emscchart {
struct Metaset;
struct Dataset;
class Chart;
class Element;
class CanvasRenderingContext;
class DatasetController {
 public:
  using ElementFactory = std::function<std::unique_ptr<Element>()>;
  static ElementFactory dataset_element_factory_;
  static ElementFactory data_element_factory_;
  DatasetController(Chart& chart, unsigned int dataset_index);
  virtual ~DatasetController() = default;
  void Initialize();
  void UpdateIndex(unsigned int dataset_index);
  enum class UpdateMode : std::uint8_t { kDefault, kReset };
  void Update() { Update(UpdateMode::kDefault); }
  virtual void Update(UpdateMode mode) = 0;
  virtual void UpdateElements(std::vector<std::unique_ptr<Element>>& elements,
                              unsigned int start, unsigned int count,
                              UpdateMode mode) = 0;
  void Draw();

  void AddElements();
  void BuildOrUpdateElements(bool reset_new_element);
  auto GetDataset() const -> emscchart::Dataset const&;
  [[nodiscard]] auto GetMeta() const -> Metaset&;
  [[nodiscard]] auto CachedMeta() const -> Metaset const&;
  [[nodiscard]] auto CachedMeta() -> Metaset&;
  [[nodiscard]] auto Data() const -> std::vector<Dataset::Data> const&;
  [[nodiscard]] auto Data() -> std::vector<Dataset::Data>&;

 protected:
  virtual void UpdateElement(Element& element, unsigned int index,
                             nlohmann::json const& properties, UpdateMode mode);
  void ResyncElements(bool reset_new_element);

 private:
  Chart& chart_;
  CanvasRenderingContext& ctx_;
  unsigned int index_;
  Metaset& cached_meta_;
  std::vector<Dataset::Data> data_;
  ElementFactory dataset_element_type_;
  ElementFactory data_element_type_;

  void DataCheck();
  void InsertElements(unsigned int start, unsigned int count,
                      bool reset_new_elements = true);
  void RemoveElements(unsigned int start, unsigned int count);
};
}  // namespace emscchart

#endif  // EMSCCHART_DATASET_CONTROLLER_H