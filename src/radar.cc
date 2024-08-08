#include "radar.h"
#include "dataset_controller.h"
using emscchart::RadarController;

RadarController::RadarController(Chart& chart, unsigned int dataset_index)
    : DatasetController(chart, dataset_index) {}

void emscchart::RadarController::Update(UpdateMode mode) {
  // const meta = this._cachedMeta;
  // const line = meta.dataset;
  // const points = meta.data || [];
  // const labels = meta.iScale.getLabels();

  // // Update Line
  // line.points = points;
  // // In resize mode only point locations change, so no need to set the points
  // or options. if (mode !== 'resize') {
  //   const options = this.resolveDatasetElementOptions(mode);
  //   if (!this.options.showLine) {
  //     options.borderWidth = 0;
  //   }

  //   const properties = {
  //     _loop: true,
  //     _fullLoop: labels.length === points.length,
  //     options
  //   };

  //   this.updateElement(line, undefined, properties, mode);
  // }

  // // Update Points
  // this.updateElements(points, 0, points.length, mode);
}

void emscchart::RadarController::UpdateElements(
    std::vector<std::unique_ptr<Element>>& elements, unsigned int start,
    unsigned int count, UpdateMode mode) {}
