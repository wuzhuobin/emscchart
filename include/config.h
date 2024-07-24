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
struct Options {};
struct Configuration {
  Data data;
  Options option;
};

class Config {
 public:
  explicit Config(Configuration config);

  [[nodiscard]] auto Data() const -> emscchart::Data const&;
  void Data(emscchart::Data const& data);

 private:
  Configuration config_;
};
}  // namespace emscchart

#endif  // EMSCCHART_CONFIG_H_
