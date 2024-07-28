#ifndef EMSCCHART_CANVAS_H_
#define EMSCCHART_CANVAS_H_

#include <SDL2/SDL_render.h>
#include <optional>

namespace emscchart {
class CanvasRenderingContext;
struct DrawPointOptions {
  enum class PointStyle { kCircle } point_style;
  double radius;
};
void DrawPoint(CanvasRenderingContext& ctx, DrawPointOptions const& options,
               unsigned int point_x, unsigned int point_y);
void DrawPointLegend(CanvasRenderingContext& ctx,
                     DrawPointOptions const& options, unsigned int point_x,
                     unsigned int point_y,
                     std::optional<unsigned int> point_w = std::nullopt);
}  // namespace emscchart

#endif  // EMSCCHART_CANVAS_H_