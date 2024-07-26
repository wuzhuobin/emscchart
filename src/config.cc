#include "config.h"
#include <string>
#include <utility>
using emscchart::Config;
using emscchart::Configuration;
using emscchart::Data;
using emscchart::Options;

namespace {
void initOptions(Configuration& config) {
  config.option = Options{};
  //       const options = config.options || (config.options = {});

  //   options.plugins = valueOrDefault(options.plugins, {});
  //   options.scales = mergeScaleConfig(config, options);
}
auto initData(Data&& data) -> Data { return data; }
auto initConfig(Configuration&& config) -> Configuration {
  config.data = initData(std::move(config.data));
  initOptions(config);
  return config;
}
}  // namespace
Config::Config(Configuration config) : config_(initConfig(std::move(config))) {}

void emscchart::Config::Update() {
  ClearCache();
  initOptions(config_);
}

void emscchart::Config::ClearCache() {
  // this._scopeCache.clear();
  // this._resolverCache.clear();
}

auto emscchart::Config::Type() const -> std::string const& {
  return config_.type;
}

void emscchart::Config::Type(std::string const& type) { config_.type = type; }

auto emscchart::Config::Data() const -> emscchart::Data const& {
  return config_.data;
}

auto emscchart::Config::Data() -> emscchart::Data& { return config_.data; }

void emscchart::Config::Data(emscchart::Data const& data) {
  config_.data = data;
}

auto emscchart::Config::Options() const -> emscchart::Options const& {
  return config_.option;
}

void emscchart::Config::Options(emscchart::Options const& options) {
  config_.option = options;
}