#ifndef EMSCHART_CANVAS_RENDERING_CONTEXT_H_
#define EMSCHART_CANVAS_RENDERING_CONTEXT_H_

#include <cstdint>

namespace emscchart {
class CanvasRenderingContext {
 public:
  virtual ~CanvasRenderingContext() = default;
  virtual void Circle(std::uint16_t point_x, std::uint16_t point_y,
                      std::uint16_t radius) = 0;
};
}  // namespace emscchart

#endif  // EMSCHART_CANVAS_RENDERING_CONTEXT_H_