#ifndef EMSCCHART_CONFIG_H_
#define EMSCCHART_CONFIG_H_

#include <string>
#include <vector>

namespace emscchart {
struct Dataset {};
using Label = std::string;
struct Data {
  std::vector<Dataset> datasets;
  std::vector<Label> labels;
};
struct Options {
  struct {
  } plugins;
  struct {
  } scales;
};
struct Configuration {
  Data data;
  Options option;
};

class Config {
 public:
  explicit Config(Configuration config);

  void Update();
  void ClearCache();

  [[nodiscard]] auto Data() const -> emscchart::Data const&;
  void Data(emscchart::Data const& data);
  [[nodiscard]] auto Options() const -> emscchart::Options const&;
  void Options(emscchart::Options const& options);

  [[nodiscard]] auto chartOptionScopes() const -> std::vector<std::string>;

 private:
  Configuration config_;

#ifdef TESTING
  friend class ConfigTest;
#endif
};
}  // namespace emscchart

#endif  // EMSCCHART_CONFIG_H_
