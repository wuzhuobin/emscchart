#include "controller.h"
#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include "bubble.h"
#include "config.h"
#include "dataset_controller.h"
#include "element.h"
#include "line.h"
#include "point.h"
#include "radar.h"
using emscchart::Config;
using emscchart::RadarController;

emscchart::Chart::Chart(std::string const& item,
                        Configuration const& user_config)
    : config_(std::make_unique<Config>(user_config)) {
  (void)item;
  // const initialCanvas = getCanvas(item);
  // const existingChart = getChart(initialCanvas);
  // if (existingChart) {
  //   throw new Error(
  //     'Canvas is already in use. Chart with ID \'' + existingChart.id + '\''
  //     +
  // 		' must be destroyed before the canvas with ID \'' +
  // existingChart.canvas.id + '\' can be reused.'
  //   );
  // }

  // const options = config.createResolver(config.chartOptionScopes(),
  // this.getContext());

  // this.platform = new (config.platform || _detectPlatform(initialCanvas))();
  // this.platform.updateConfig(config);

  Initialize();
  if (attached_) {
    Update();
  }
}

emscchart::Chart::~Chart() = default;

void emscchart::Chart::Initialize() {
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
  config_->Update();
  // const options = this._options =
  // config.createResolver(config.chartOptionScopes(), this.getContext());
  // const animsDisabled = this._animationsDisabled = !options.animation;
  auto anims_disabled = true;

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

  // Make sure dataset controllers are updated and new controllers are reset
  auto new_controllers = BuildOrUpdateControllers();

  // this.notifyPlugins('beforeElementsUpdate');

  // // Make sure all dataset controllers have correct meta data counts
  // let minPadding = 0;
  // for (let i = 0, ilen = this.data.datasets.length; i < ilen; i++) {
  for (auto i = 0U; i < Data().datasets.size(); ++i) {
    auto& controller = GetDatasetMeta(i).controller;
    auto reset =
        !anims_disabled &&
        std::find_if(new_controllers.cbegin(), new_controllers.cend(),
                     [&controller](auto new_controller) {
                       return &(new_controller.get()) == controller.get();
                     }) == new_controllers.cend();
    (void)reset;
    // New controllers will be reset after the layout pass, so we only want to
    // modify elements added to new datasets
    //   controller.buildOrUpdateElements(reset);
    //   minPadding = Math.max(+controller.getMaxOverflow(), minPadding);
  }
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

  Render();
}

void emscchart::Chart::Render() {
  // if (this.notifyPlugins('beforeRender', {cancelable: true}) === false) {
  //   return;
  // }

  // if (animator.has(this)) {
  //   if (this.attached && !animator.running(this)) {
  //     animator.start(this);
  //   }
  // } else {
  Draw();
  //   onAnimationsComplete({chart: this});
  // }
}

void emscchart::Chart::Draw() {
  // let i;
  // if (this._resizeBeforeDraw) {
  //   const {width, height} = this._resizeBeforeDraw;
  //   this._resize(width, height);
  //   this._resizeBeforeDraw = null;
  // }
  // this.clear();

  // if (this.width <= 0 || this.height <= 0) {
  //   return;
  // }

  // if (this.notifyPlugins('beforeDraw', {cancelable: true}) === false) {
  //   return;
  // }

  // // Because of plugin hooks (before/afterDatasetsDraw), datasets can't
  // // currently be part of layers. Instead, we draw
  // // layers <= 0 before(default, backward compat), and the rest after
  // const layers = this._layers;
  // for (i = 0; i < layers.length && layers[i].z <= 0; ++i) {
  //   layers[i].draw(this.chartArea);
  // }

  DrawDatasets();

  // // Rest of layers
  // for (; i < layers.length; ++i) {
  //   layers[i].draw(this.chartArea);
  // }

  // this.notifyPlugins('afterDraw');
}

auto emscchart::Chart::Data() const -> emscchart::Data const& {
  return config_->Data();
}

auto emscchart::Chart::Data() -> emscchart::Data& { return config_->Data(); }

void emscchart::Chart::Data(emscchart::Data const& data) {
  config_->Data(data);
}

auto emscchart::Chart::GetDatasetMeta(unsigned int dataset_index) -> Metaset& {
  auto& dataset = Data().datasets[dataset_index];

  auto iterator = std::find_if(
      metasets_.begin(), metasets_.end(),
      [&dataset](auto& metaset) { return metaset._dataset == &dataset; });

  if (iterator != metasets_.end()) {
    return *iterator;
  }
  // meta = {
  //   hidden: null,			// See isDatasetVisible() comment
  //   xAxisID: null,
  //   yAxisID: null,
  //   order: dataset && dataset.order || 0,
  //   index: datasetIndex,
  //   _dataset: dataset,
  //   _parsed: [],
  //   _sorted: false
  // };
  metasets_.emplace_back(Metaset{.type = "",
                                 .data = {},
                                 .dataset = nullptr,
                                 .controller = nullptr,
                                 .index = dataset_index,
                                 ._dataset = &dataset});
  return metasets_.back();
}

auto emscchart::Chart::GetSortedVisibleDatasetMetas() const
    -> std::vector<std::reference_wrapper<Metaset>> {
  return GetSortedDatasetMetas(true);
}

auto emscchart::Chart::GetContext() const -> Chart::Context const& {
  return context_;
}

void emscchart::Chart::BuildOrUpdateScales() {}

auto emscchart::Chart::BuildOrUpdateControllers()
    -> std::vector<std::reference_wrapper<emscchart::DatasetController>> {
  std::vector<std::reference_wrapper<emscchart::DatasetController>>
      new_controllers;
  auto const datasets = Data().datasets;

  RemoveUnreferencedMetasets();
  for (auto i = 0U; i < datasets.size(); ++i) {
    auto dataset = datasets[i];
    auto const& type = !dataset.type.empty() ? dataset.type : config_->Type();

    if (!GetDatasetMeta(i).type.empty() && GetDatasetMeta(i).type != type) {
      DestroyDatasetMeta(i);
    }
    auto& meta = GetDatasetMeta(i);
    meta.type = type;
    //   meta.indexAxis = dataset.indexAxis || getIndexAxis(type, this.options);
    //   meta.order = dataset.order || 0;
    meta.index = i;
    //   meta.label = '' + dataset.label;
    //   meta.visible = this.isDatasetVisible(i);

    if (meta.controller) {
      //     meta.controller.updateIndex(i);
      //     meta.controller.linkScales();
    } else {
      //     const ControllerClass = registry.getController(type);
      //     const {datasetElementType, dataElementType} =
      //     defaults.datasets[type]; Object.assign(ControllerClass, {
      //       dataElementType: registry.getElement(dataElementType),
      //       datasetElementType: datasetElementType &&
      //       registry.getElement(datasetElementType)
      //     });
      ///< @todo using dependency injection
      if (type == RadarController::kId) {
        DatasetController::data_element_factory_ = &std::make_unique<Point>;
        DatasetController::dataset_element_factory_ = &std::make_unique<Line>;
        meta.controller = std::make_unique<RadarController>(*this, i);
        new_controllers.push_back(std::ref(*meta.controller));
      } else if (type == BubbleController::kId) {
        DatasetController::data_element_factory_ = &std::make_unique<Point>;
        DatasetController::dataset_element_factory_ = nullptr;
        meta.controller = std::make_unique<BubbleController>(*this, i);
        new_controllers.push_back(std::ref(*meta.controller));
      } else {
        throw std::runtime_error("Unsupported chart type: " + type);
      }
    }
  }

  UpdateMetasets();
  return new_controllers;
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

void emscchart::Chart::UpdateMetasets() {
  // const metasets = this._metasets;
  // const numData = this.data.datasets.length;
  // const numMeta = metasets.length;

  // metasets.sort((a, b) => a.index - b.index);
  // if (numMeta > numData) {
  //   for (let i = numData; i < numMeta; ++i) {
  //     this._destroyDatasetMeta(i);
  //   }
  //   metasets.splice(numData, numMeta - numData);
  // }
  // this._sortedMetasets = metasets.slice(0).sort(compare2Level('order',
  // 'index'));
  ///< @todo Do real sorting.
  sorted_metasets_.clear();
  std::copy(metasets_.begin(), metasets_.end(),
            std::back_inserter(sorted_metasets_));
}

void emscchart::Chart::DrawDatasets() {
  // if (this.notifyPlugins('beforeDatasetsDraw', {cancelable: true}) === false)
  // {
  //   return;
  // }

  auto const& metasets = GetSortedVisibleDatasetMetas();
  for (auto const& metaset : metasets) {
    DrawDataset(metaset);
  }

  // this.notifyPlugins('afterDatasetsDraw');
}

void emscchart::Chart::DrawDataset(Metaset const& meta) {
  // const ctx = this.ctx;
  // const clip = meta._clip;
  // const useClip = !clip.disabled;
  // const area = getDatasetArea(meta, this.chartArea);
  // const args = {
  //   meta,
  //   index: meta.index,
  //   cancelable: true
  // };

  // if (this.notifyPlugins('beforeDatasetDraw', args) === false) {
  //   return;
  // }

  // if (useClip) {
  //   clipArea(ctx, {
  //     left: clip.left === false ? 0 : area.left - clip.left,
  //     right: clip.right === false ? this.width : area.right + clip.right,
  //     top: clip.top === false ? 0 : area.top - clip.top,
  //     bottom: clip.bottom === false ? this.height : area.bottom + clip.bottom
  //   });
  // }

  meta.controller->Draw();

  // if (useClip) {
  //   unclipArea(ctx);
  // }

  // args.cancelable = false;
  // this.notifyPlugins('afterDatasetDraw', args);
}

void emscchart::Chart::DestroyDatasetMeta(unsigned int dataset_index) {
  auto& meta = metasets_[dataset_index];
  if (meta.controller != nullptr) {
    //   meta.controller._destroy();
  }
  /// @todo Consider more efficient way.
  metasets_.erase(metasets_.begin() + dataset_index);
}

void emscchart::Chart::RemoveUnreferencedMetasets() {
  // const {_metasets: metasets, data: {datasets}} = this;
  // if (metasets.length > datasets.length) {
  //   delete this._stacks;
  // }
  // metasets.forEach((meta, index) => {
  //   if (datasets.filter(x => x === meta._dataset).length === 0) {
  //     this._destroyDatasetMeta(index);
  //   }
  // });
}

auto emscchart::Chart::GetSortedDatasetMetas(bool filter_visible) const
    -> std::vector<std::reference_wrapper<Metaset>> {
  std::vector<std::reference_wrapper<Metaset>> result;
  (void)filter_visible;
  result.reserve(sorted_metasets_.size());
  for (auto const& metaset : sorted_metasets_) {
    // if (!filter_visible || metaset.visible) {
    result.push_back(metaset);
    // }
  }

  return result;
}
