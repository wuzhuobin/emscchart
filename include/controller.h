#ifndef EMSCCHART_CHART_H_
#define EMSCCHART_CHART_H_
#include <memory>
#include <string>
#include <vector>
#include "config.h"
namespace emscchart {
class DatasetController;
class Element;
struct Metaset {
  std::string type;
  std::vector<std::unique_ptr<Element>> data;
  std::unique_ptr<Element> dataset;
  std::unique_ptr<emscchart::DatasetController> controller;
  // hidden: null,			// See isDatasetVisible() comment
  // xAxisID: null,
  // yAxisID: null,
  // order: dataset && dataset.order || 0,
  // index: datasetIndex,
  unsigned int index;
  Dataset* _dataset;
  // _parsed: [],
  // _sorted: false
};

class Chart {
 public:
  Chart(std::string const& item, Configuration const& user_config);
  ~Chart();
  void Initialize();

  void Update();
  void Render();
  void Draw();

  [[nodiscard]] auto Data() const -> emscchart::Data const&;
  [[nodiscard]] auto Data() -> emscchart::Data&;
  void Data(emscchart::Data const& data);

  [[nodiscard]] auto GetDatasetMeta(unsigned int dataset_index) -> Metaset&;
  auto GetSortedVisibleDatasetMetas()
      -> std::vector<std::reference_wrapper<Metaset>>;

  struct Context {
    // Chart const& chart;
    // std::string type;
  };

  [[nodiscard]] auto GetContext() const -> Context const&;
  void BuildOrUpdateScales();
  auto BuildOrUpdateControllers()
      -> std::vector<std::reference_wrapper<DatasetController>>;

 private:
  void UpdateDatasets();
  void UpdateDataset();
  void UpdateScales();
  void UpdateMetasets();

  void DrawDatasets();
  void DrawDataset(Metaset const& meta);

  void DestroyDatasetMeta(unsigned int dataset_index);
  void RemoveUnreferencedMetasets();

  std::unique_ptr<Config> config_;
  std::vector<Metaset> metasets_;
  std::vector<std::reference_wrapper<Metaset>> sorted_metasets_;
  Context context_;
  bool attached_ = false;
};

}  // namespace emscchart
#endif  // EMSCCHART_CHART_H_