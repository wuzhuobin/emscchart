#ifndef EMSCCHART_POINT_H_
#define EMSCCHART_POINT_H_
#include "element.h"
#include "geometric.h"
#include "types.h"
namespace emscchart {
class Point
    : public Element,
      private PropMixin<geometric::Point>,
      private OptionMixin<types::PointOptions, types::PointHoverOptions> {
 public:
  using Props = PropMixin<geometric::Point>;
  using Options = OptionMixin<types::PointOptions, types::PointHoverOptions>;
  struct Cfg : public Props, public Options {};
  explicit Point(Cfg const& cfg = {});
  void Assign(nlohmann::json const& json) override;
  void Draw(CanvasRenderingContext& ctx,
            geometric::ChartArea const& area) const override;

  void Radius(unsigned int radius);
  [[nodiscard]] auto Radius() const -> unsigned int;

  [[nodiscard]] auto InRange(unsigned int point_x,
                             unsigned int point_y) const -> bool;
};
}  // namespace emscchart
#endif  // EMSCCHART_POINT_H_