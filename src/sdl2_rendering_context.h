#ifndef EMSCCHART_SDL2_RENDERING_CONTEXT_H_
#define EMSCCHART_SDL2_RENDERING_CONTEXT_H_

#include "canvas_rendering_context.h"
class SDL_Renderer;

namespace emscchart {
class SDL2RenderingContext : public CanvasRenderingContext {
 public:
  explicit SDL2RenderingContext(SDL_Renderer& renderer);
  void Circle(std::uint16_t point_x, std::uint16_t point_y,
              std::uint16_t radius) override;

 private:
  SDL_Renderer& renderer_;
};
}  // namespace emscchart

#endif  // EMSCCHART_SDL2_RENDERING_CONTEXT_H_