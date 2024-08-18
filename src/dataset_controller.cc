#include "dataset_controller.h"
#include "controller.h"
#include "element.h"
#include "geometric.h"
#include <functional>

using emscchart::Element;

emscchart::DatasetController::ElementFactory
    emscchart::DatasetController::dataset_element_factory_;
emscchart::DatasetController::ElementFactory
    emscchart::DatasetController::data_element_factory_;
emscchart::DatasetController::DatasetController(Chart& chart,
                                                unsigned int dataset_index)
    : chart_(chart),
      ctx_(chart.Ctx()),
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

void emscchart::DatasetController::UpdateIndex(unsigned int dataset_index) {
  if (index_ != dataset_index) {
    //   clearStacks(this._cachedMeta);
  }
  index_ = dataset_index;
}

void emscchart::DatasetController::Draw() {
  auto& ctx = ctx_;
  // const chart = this.chart;
  auto const& meta = this->cached_meta_;
  // const elements = meta.data || [];
  auto const& elements = meta.data;
  // const area = chart.chartArea;
  // const active = [];
  // const start = this._drawStart || 0;
  auto start = 0U;
  // const count = this._drawCount || (elements.length - start);
  auto count = elements.size() - start;
  // const drawActiveElementsOnTop = this.options.drawActiveElementsOnTop;
  // let i;

  if (cached_meta_.dataset) {
    // cached_meta_.dataset.draw(ctx, area, start, count);
  }

  for (auto i = start; i < start + count; ++i) {
    //   const element = elements[i];
    auto const& element = elements[i];
    //   if (element.hidden) {
    //     continue;
    //   }
    //   if (element.active && drawActiveElementsOnTop) {
    //     active.push(element);
    //   } else {
    element->Draw(ctx, {});
    //   }
  }

  // for (i = 0; i < active.length; ++i) {
  //   active[i].draw(ctx, area);
  // }
}

void emscchart::DatasetController::AddElements() {
  auto& meta = CachedMeta();
  DataCheck();

  if (dataset_element_type_) {
    meta.dataset = dataset_element_type_();
  }
}

void emscchart::DatasetController::BuildOrUpdateElements(
    bool resets_new_element) {
  auto& meta = CachedMeta();
  auto& dataset = GetDataset();
  // let stackChanged = false;

  DataCheck();

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

  // Re-sync meta data in case the user replaced the data array or if we missed
  // any updates and so make sure that we handle number of datapoints changing.
  ResyncElements(resets_new_element);

  // // if stack changed, update stack values for the whole dataset
  // if (stackChanged || oldStacked !== meta._stacked) {
  //   updateStacks(this, meta._parsed);
  // }
}

auto emscchart::DatasetController::GetDataset() const
    -> emscchart::Dataset const& {
  return chart_.Data().datasets.at(index_);
}

auto emscchart::DatasetController::GetMeta() const -> Metaset& {
  return chart_.GetDatasetMeta(index_);
}

auto emscchart::DatasetController::CachedMeta() const -> Metaset const& {
  return cached_meta_;
}

auto emscchart::DatasetController::CachedMeta() -> Metaset& {
  return cached_meta_;
}

auto emscchart::DatasetController::Data() const
    -> std::vector<Dataset::Data> const& {
  return data_;
}

auto emscchart::DatasetController::Data() -> std::vector<Dataset::Data>& {
  return data_;
}

void emscchart::DatasetController::UpdateElement(
    Element& element, unsigned int index, nlohmann::json const& properties,
    UpdateMode mode) {
  // if (isDirectUpdateMode(mode)) {
  //   Object.assign(element, properties);
  element.Assign(properties);
  // } else {
  //   this._resolveAnimations(index, mode).update(element, properties);
  // }
}

void emscchart::DatasetController::ResyncElements(bool reset_new_element) {
  // const data = this._data;
  auto& data = data_;
  auto& elements = cached_meta_.data;

  // // Apply changes detected through array listeners
  // for (const [method, arg1, arg2] of this._syncList) {
  //   this[method](arg1, arg2);
  // }
  // this._syncList = [];

  auto num_meta = elements.size();
  auto num_data = data.size();
  // const count = Math.min(numData, numMeta);

  // if (count) {
  //   // TODO: It is not optimal to always parse the old data
  //   // This is done because we are not detecting direct assignments:
  //   // chart.data.datasets[0].data[5] = 10;
  //   // chart.data.datasets[0].data[5].y = 10;
  //   this.parse(0, count);
  // }

  if (num_data > num_meta) {
    InsertElements(num_meta, num_data - num_meta, reset_new_element);
  } else if (num_data < num_meta) {
    RemoveElements(num_data, num_meta - num_data);
  }
}

void emscchart::DatasetController::DataCheck() {
  auto const& dataset = GetDataset();
  // const data = dataset.data || (dataset.data = []);
  auto const& data = dataset.data;
  // const _data = this._data;

  // // In order to correctly handle data addition/deletion animation (and thus
  // simulate
  // // real-time charts), we need to monitor these data modifications and
  // synchronize
  // // the internal metadata accordingly.

  // if (isObject(data)) {
  //   const meta = this._cachedMeta;
  //   this._data = convertObjectDataToArray(data, meta);
  // } else if (_data !== data) {
  //   if (_data) {
  //     // This case happens when the user replaced the data array instance.
  //     unlistenArrayEvents(_data, this);
  //     // Discard old parsed data and stacks
  //     const meta = this._cachedMeta;
  //     clearStacks(meta);
  //     meta._parsed = [];
  //   }
  //   if (data && Object.isExtensible(data)) {
  //     listenArrayEvents(data, this);
  //   }
  //   this._syncList = [];
  //   this._data = data;
  data_ = data;
  // }
}

void emscchart::DatasetController::InsertElements(unsigned int start,
                                                  unsigned int count,
                                                  bool reset_new_elements) {
  auto& meta = cached_meta_;
  auto& data = meta.data;
  auto end = start + count;
  // let i;

  // const move = (arr) => {
  //   arr.length += count;
  //   for (i = arr.length - 1; i >= end; i--) {
  //     arr[i] = arr[i - count];
  //   }
  // };
  // move(data);

  for (auto i = start; i < end; ++i) {
    // data[i] = new this.dataElementType();
    data.emplace_back(data_element_type_());
  }

  // if (this._parsing) {
  //   move(meta._parsed);
  // }
  // this.parse(start, count);

  if (reset_new_elements) {
    UpdateElements(data, start, count, UpdateMode::kReset);
  }
}

void emscchart::DatasetController::RemoveElements(unsigned int start,
                                                  unsigned int count) {
  // const meta = this._cachedMeta;
  // const data = meta.data;
  // const end = start + count;
  // let i;

  // const move = (arr) => {
  //   arr.length += count;
  //   for (i = arr.length - 1; i >= end; i--) {
  //     arr[i] = arr[i - count];
  //   }
  // };
  // move(data);

  // for (i = start; i < end; ++i) {
  //   data[i] = new this.dataElementType();
  // }

  // if (this._parsing) {
  //   move(meta._parsed);
  // }
  // this.parse(start, count);

  // if (resetNewElements) {
  //   this.updateElements(data, start, count, 'reset');
  // }
}
