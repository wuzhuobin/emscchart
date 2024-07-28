
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>

// emscchart
#include "canvas.h"
#include "helper.h"
#include "sdl2_rendering_context.h"

auto main(int argc, char* argv[]) -> int {
  (void)argc;
  (void)argv;
  auto* window =
      SDL_CreateWindow("Draw a point", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
  SDL_CreateRenderer(window, -1, 0);
  auto* renderer = SDL_GetRenderer(window);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  emscchart::SDL2RenderingContext sdl2RenderingContext(*renderer);
  emscchart::DrawPoint(
      sdl2RenderingContext,
      emscchart::DrawPointOptions{
          emscchart::DrawPointOptions::PointStyle::kCircle, 5.0},
      320, 240);

  SDL_RenderPresent(renderer);
  Loop();

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}