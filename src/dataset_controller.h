#ifndef EMSCCHART_DATASET_CONTROLLER_H
#define EMSCCHART_DATASET_CONTROLLER_H

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
  enum class UpdateMode : std::uint8_t { kDefault, kReset };
  void Update() { Update(UpdateMode::kDefault); }
  virtual void Update(UpdateMode mode) = 0;
  virtual void UpdateElements(std::vector<std::unique_ptr<Element>>& elements,
                              unsigned int start, unsigned int count,
                              UpdateMode mode) = 0;
  void Draw();

  void AddElements();
  void BuildOrUpdateElements(bool resetNewElement);
  //  GetDataset();
  [[nodiscard]] auto GetMeta() const -> Metaset&;
  [[nodiscard]] auto CachedMeta() const -> Metaset const&;
  [[nodiscard]] auto CachedMeta() -> Metaset&;

 protected:
  virtual void UpdateElement(Element& element, unsigned int index,
                             std::string properties, UpdateMode mode);

 private:
  Chart& chart_;
  CanvasRenderingContext& ctx_;
  unsigned int index_;
  Metaset& cached_meta_;
  ElementFactory dataset_element_type_;
  ElementFactory data_element_type_;
};
}  // namespace emscchart

#endif  // EMSCCHART_DATASET_CONTROLLER_H