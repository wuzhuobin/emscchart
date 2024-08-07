#include "dataset_controller.h"
#include "controller.h"
#include "element.h"
#include <functional>

using emscchart::Element;

emscchart::DatasetController::ElementFactory
    emscchart::DatasetController::dataset_element_factory_;
emscchart::DatasetController::ElementFactory
    emscchart::DatasetController::data_element_factory_;
emscchart::DatasetController::DatasetController(Chart& chart,
                                                unsigned int dataset_index)
    : chart_(chart),
      index_(dataset_index),
      cached_meta_(GetMeta()),
      dataset_element_type_(dataset_element_factory_),
      data_element_type_(data_element_factory_) {
  // this._ctx = chart.ctx;
  // this._cachedDataOpts = {};
  // this._type = this._cachedMeta.type;
  // this.options = undefined;
  // /** @type {boolean | object} */
  // this._parsing = false;
  // this._data = undefined;
  // this._objectData = undefined;
  // this._sharedOptions = undefined;
  // this._drawStart = undefined;
  // this._drawCount = undefined;
  // this.enableOptionSharing = false;
  // this.supportsDecimation = false;
  // this.$context = undefined;
  // this._syncList = [];
  Initialize();
}

void emscchart::DatasetController::Initialize() {
  // const meta = this._cachedMeta;
  // this.configure();
  // this.linkScales();
  // meta._stacked = isStacked(meta.vScale, meta);
  AddElements();

  // if (this.options.fill && !this.chart.isPluginEnabled('filler')) {
  //   console.warn("Tried to use the 'fill' option without the 'Filler' plugin
  //   enabled. Please import and register the 'Filler' plugin and make sure it
  //   is not disabled in the options");
  // }
}

void emscchart::DatasetController::Draw() {
  // const ctx = this._ctx;
  // const chart = this.chart;
  // const meta = this._cachedMeta;
  // const elements = meta.data || [];
  // const area = chart.chartArea;
  // const active = [];
  // const start = this._drawStart || 0;
  // const count = this._drawCount || (elements.length - start);
  // const drawActiveElementsOnTop = this.options.drawActiveElementsOnTop;
  // let i;

  if (cached_meta_._dataset) {
    // cached_meta_.dataset.draw(ctx, area, start, count);
  }

  // for (i = start; i < start + count; ++i) {
  //   const element = elements[i];
  //   if (element.hidden) {
  //     continue;
  //   }
  //   if (element.active && drawActiveElementsOnTop) {
  //     active.push(element);
  //   } else {
  //     element.draw(ctx, area);
  //   }
  // }

  // for (i = 0; i < active.length; ++i) {
  //   active[i].draw(ctx, area);
  // }
}

void emscchart::DatasetController::AddElements() {
  // this._dataCheck();

  if (data_element_type_) {
    // meta.dataset = new this.datasetElementType();
    cached_meta_.dataset = data_element_type_();
  }
}

void emscchart::DatasetController::BuildOrUpdateElements(bool resetNewElement) {
  (void)resetNewElement;
  // const meta = this._cachedMeta;
  // const dataset = this.getDataset();
  // let stackChanged = false;

  // this._dataCheck();

  // // make sure cached _stacked status is current
  // const oldStacked = meta._stacked;
  // meta._stacked = isStacked(meta.vScale, meta);

  // // detect change in stack option
  // if (meta.stack !== dataset.stack) {
  //   stackChanged = true;
  //   // remove values from old stack
  //   clearStacks(meta);
  //   meta.stack = dataset.stack;
  // }

  // // Re-sync meta data in case the user replaced the data array or if we
  // missed
  // // any updates and so make sure that we handle number of datapoints
  // changing. this._resyncElements(resetNewElements);

  // // if stack changed, update stack values for the whole dataset
  // if (stackChanged || oldStacked !== meta._stacked) {
  //   updateStacks(this, meta._parsed);
  // }
}

auto emscchart::DatasetController::GetMeta() const -> Metaset& {
  return chart_.GetDatasetMeta(index_);
}
