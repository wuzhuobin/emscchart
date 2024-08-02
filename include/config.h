#ifndef EMSCCHART_CONFIG_H_
#define EMSCCHART_CONFIG_H_

#include <string>
#include <vector>

namespace emscchart {
struct Dataset {
  std::string type;
};
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
  // platform;
  std::string type;
  Data data;
  Options option;
  // plugins;
};

class Config {
 public:
  explicit Config(Configuration config);

  void Update();
  void ClearCache();

  [[nodiscard]] auto Type() const -> std::string const&;
  void Type(std::string const& type);
  [[nodiscard]] auto Data() const -> emscchart::Data const&;
  [[nodiscard]] auto Data() -> emscchart::Data&;
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
