#include "sdl2_rendering_context.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2_gfxPrimitives.h>

emscchart::SDL2RenderingContext::SDL2RenderingContext(SDL_Renderer& renderer)
    : renderer_(renderer) {}

void emscchart::SDL2RenderingContext::Circle(uint16_t point_x, uint16_t point_y,
                                             uint16_t radius) {
  Uint8 color_r;
  Uint8 color_g;
  Uint8 color_b;
  Uint8 color_a;
  SDL_GetRenderDrawColor(&renderer_, &color_r, &color_g, &color_b, &color_a);
  circleRGBA(&renderer_, point_x, point_y, radius, color_r, color_g, color_b,
             color_a);
}
