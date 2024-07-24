#include "controller.h"
#include <algorithm>
#include <memory>
#include "config.h"
#include "dataset_controller.h"
using emscchart::Chart;
using emscchart::Config;

emscchart::Chart::Chart(std::string item, Configuration const& user_config)
    : config_(std::make_unique<Config>(user_config)) {
  // initialCanvas const = getCanvas(item);

  Initialize();

  if (attached_) {
    Update();
  }
}

emscchart::Chart::~Chart() = default;

void Chart::Initialize() {
  //   // Before init plugin notification
  //   this.notifyPlugins('beforeInit');

  //   if (this.options.responsive) {
  //     this.resize();
  //   } else {
  //     retinaScale(this, this.options.devicePixelRatio);
  //   }

  //   this.bindEvents();

  //   // After init plugin notification
  //   this.notifyPlugins('afterInit');

  //   return this;
}

void emscchart::Chart::Update() {
  //  const config = this.config;

  // config.update();
  // const options = this._options =
  // config.createResolver(config.chartOptionScopes(), this.getContext()); const
  // animsDisabled = this._animationsDisabled = !options.animation;

  // this._updateScales();
  // this._checkEventBindings();
  // this._updateHiddenIndices();

  // // plugins options references might have change, let's invalidate the cache
  // // https://github.com/chartjs/Chart.js/issues/5111#issuecomment-355934167
  // this._plugins.invalidate();

  // if (this.notifyPlugins('beforeUpdate', {mode, cancelable: true}) === false)
  // {
  //   return;
  // }

  // // Make sure dataset controllers are updated and new controllers are reset
  // auto newControllers = BuildOrUpdateControllers();

  // this.notifyPlugins('beforeElementsUpdate');

  // // Make sure all dataset controllers have correct meta data counts
  // let minPadding = 0;
  // for (let i = 0, ilen = this.data.datasets.length; i < ilen; i++) {
  //   const {controller} = this.getDatasetMeta(i);
  //   const reset = !animsDisabled && newControllers.indexOf(controller) ===
  //   -1;
  //   // New controllers will be reset after the layout pass, so we only want
  //   to modify
  //   // elements added to new datasets
  //   controller.buildOrUpdateElements(reset);
  //   minPadding = Math.max(+controller.getMaxOverflow(), minPadding);
  // }
  // minPadding = this._minPadding = options.layout.autoPadding ? minPadding :
  // 0; this._updateLayout(minPadding);

  // // Only reset the controllers if we have animations
  // if (!animsDisabled) {
  //   // Can only reset the new controllers after the scales have been updated
  //   // Reset is done to get the starting point for the initial animation
  //   each(newControllers, (controller) => {
  //     controller.reset();
  //   });
  // }

  // this._updateDatasets(mode);

  // // Do this before render so that any plugins that need final scale updates
  // can use it this.notifyPlugins('afterUpdate', {mode});

  // this._layers.sort(compare2Level('z', '_idx'));

  // // Replay last event from before update, or set hover styles on active
  // elements const {_active, _lastEvent} = this; if (_lastEvent) {
  //   this._eventHandler(_lastEvent, true);
  // } else if (_active.length) {
  //   this._updateHoverStyles(_active, _active, true);
  // }

  // this.render();
}

auto emscchart::Chart::Data() const -> emscchart::Data const& {
  return config_->Data();
}

void emscchart::Chart::Data(emscchart::Data const& data) {
  config_->Data(data);
}

auto emscchart::Chart::GetDatasetMeta(unsigned int dataset_index)
    -> Metaset const& {
  // return metasets_[dataset_index];
  auto const& dataset = Data().datasets[dataset_index];

  auto cit = std::find_if(
      metasets_.cbegin(), metasets_.cend(),
      [&dataset](auto metaset) { return metaset.dataset == &dataset; });

  if (cit != metasets_.cend()) {
    return *cit;
  }

  // Metaset metaset;
  // metasets_.push_back(metaset);
  // return metaset;
}

auto emscchart::Chart::BuildOrUpdateControllers() const
    -> std::vector<std::unique_ptr<emscchart::DatasetController>> {
  // const newControllers = [];
  // const datasets = this.data.datasets;
  auto const datasets = Data().datasets;
  // let i, ilen;

  // this._removeUnreferencedMetasets();
  for (auto const& dataset : datasets) {
  }

  // for (i = 0, ilen = datasets.length; i < ilen; i++) {
  //   const dataset = datasets[i];
  //   let meta = this.getDatasetMeta(i);
  //   const type = dataset.type || this.config.type;

  //   if (meta.type && meta.type !== type) {
  //     this._destroyDatasetMeta(i);
  //     meta = this.getDatasetMeta(i);
  //   }
  //   meta.type = type;
  //   meta.indexAxis = dataset.indexAxis || getIndexAxis(type, this.options);
  //   meta.order = dataset.order || 0;
  //   meta.index = i;
  //   meta.label = '' + dataset.label;
  //   meta.visible = this.isDatasetVisible(i);

  //   if (meta.controller) {
  //     meta.controller.updateIndex(i);
  //     meta.controller.linkScales();
  //   } else {
  //     const ControllerClass = registry.getController(type);
  //     const {datasetElementType, dataElementType} =
  //     defaults.datasets[type]; Object.assign(ControllerClass, {
  //       dataElementType: registry.getElement(dataElementType),
  //       datasetElementType: datasetElementType &&
  //       registry.getElement(datasetElementType)
  //     });
  //     meta.controller = new ControllerClass(this, i);
  //     newControllers.push(meta.controller);
  //   }
  // }

  // this._updateMetasets();
  // return newControllers;
  return std::vector<std::unique_ptr<emscchart::DatasetController>>();
}

void emscchart::Chart::UpdateDatasets() {
  //   if (this.notifyPlugins('beforeDatasetsUpdate', {mode, cancelable: true})
  //   === false) { return;
  // }

  // for (let i = 0, ilen = this.data.datasets.length; i < ilen; ++i) {
  //   this.getDatasetMeta(i).controller.configure();
  // }

  // for (let i = 0, ilen = this.data.datasets.length; i < ilen; ++i) {
  //   this._updateDataset(i, isFunction(mode) ? mode({datasetIndex : i}) :
  //   mode);
  // }

  // this.notifyPlugins('afterDatasetsUpdate', {mode});
}

void emscchart::Chart::UpdateDataset() {}
