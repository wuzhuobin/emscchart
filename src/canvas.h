#ifndef EMSCCHART_CANVAS_H_
#define EMSCCHART_CANVAS_H_

#include <SDL2/SDL_render.h>
#include <cinttypes>
#include <optional>

namespace emscchart {
class CanvasRenderingContext;
struct DrawPointOptions {
  enum class PointStyle : std::uint8_t { kCircle } point_style;
  // rotation?: number;
  unsigned int radius;
  // radius: number;
  // borderWidth: number;
};
void DrawPoint(CanvasRenderingContext& ctx, DrawPointOptions const& options,
               unsigned int point_x, unsigned int point_y);
void DrawPointLegend(CanvasRenderingContext& ctx,
                     DrawPointOptions const& options, unsigned int point_x,
                     unsigned int point_y,
                     std::optional<unsigned int> point_w = std::nullopt);
}  // namespace emscchart

#endif  // EMSCCHART_CANVAS_H_