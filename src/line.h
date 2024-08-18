#ifndef EMSCCHART_LINE_H_
#define EMSCCHART_LINE_H_

#include "element.h"

namespace emscchart {
class Line : public Element {
 public:
  void Draw(CanvasRenderingContext& ctx,
            geometric::ChartArea const& area) const override;
  void Assign(nlohmann::json const & json) override;
};
}  // namespace emscchart

#endif  // EMSCCHART_LINE_H_