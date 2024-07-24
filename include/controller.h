#ifndef EMSCCHART_CHART_H_
#define EMSCCHART_CHART_H_
#include <memory>
#include <string>
#include <vector>
#include "config.h"
namespace emscchart {
class DatasetController;

struct Metaset {
  // type: null,
  // data: [],
  // dataset: null,
  Dataset* dataset = nullptr;
  // controller: null,
  // hidden: null,			// See isDatasetVisible() comment
  // xAxisID: null,
  // yAxisID: null,
  // order: dataset && dataset.order || 0,
  // index: datasetIndex,
  // _dataset: dataset,
  // _parsed: [],
  // _sorted: false
};

class Chart {
 public:
  Chart(std::string item, Configuration const& user_config);
  ~Chart();
  void Initialize();

  void Update();

  [[nodiscard]] auto Data() const -> emscchart::Data const&;
  void Data(emscchart::Data const& data);

  [[nodiscard]] auto GetDatasetMeta(unsigned int dataset_index)
      -> Metaset const&;

 private:
  [[nodiscard]] auto BuildOrUpdateControllers() const
      -> std::vector<std::unique_ptr<DatasetController>>;

  void UpdateDatasets();
  void UpdateDataset();
  void UpdateScales();

  std::unique_ptr<Config> config_;
  std::vector<Metaset> metasets_;
  bool attached_ = false;
};

}  // namespace emscchart
#endif  // EMSCCHART_CHART_H_