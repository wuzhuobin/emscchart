
#include "canvas.h"
#include "helper.h"
#include "sdl2_rendering_context.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

auto main(int argc, char* argv[]) -> int {
  (void)argc;
  (void)argv;
  auto* window =
      SDL_CreateWindow("Draw a point", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
  SDL_CreateRenderer(window, -1, 0);
  auto* renderer = SDL_GetRenderer(window);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  emscchart::SDL2RenderingContext sdl2_rendering_context(*renderer);
  emscchart::DrawPoint(
      sdl2_rendering_context,
      emscchart::DrawPointOptions{
          emscchart::DrawPointOptions::PointStyle::kCircle, 5U},
      320, 240);

  SDL_RenderPresent(renderer);
  Loop();

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}