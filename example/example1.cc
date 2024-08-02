// Copyright 2015 The Emscripten Authors.  All rights reserved.
// Emscripten is available under two separate licenses, the MIT license and the
// University of Illinois/NCSA Open Source License.  Both these licenses can be
// found in the LICENSE file.

#include <SDL2/SDL.h>
#include <assert.h>
#include <array>
#include "controller.h"
#include "helper.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

static void sdlError(char const* str) {
  fprintf(stderr, "Error at %s: %s\n", str, SDL_GetError());

#ifdef __EMSCRIPTEN__
  emscripten_force_exit(1);
#endif
}

void draw(SDL_Window* window, SDL_Surface* surface) {
  int x, y;

  if (SDL_MUSTLOCK(surface)) {
    if (SDL_LockSurface(surface) != 0) sdlError("SDL_LockSurface");
  }

  for (y = 0; y < 256; y++) {
    Uint32* p = (Uint32*)(((Uint8*)surface->pixels) + surface->pitch * y);
    for (x = 0; x < 256; x++) {
      *(p++) = SDL_MapRGB(surface->format, x, x ^ y, y);
    }
  }

  if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
  if (SDL_UpdateWindowSurface(window) != 0) sdlError("SDL_UpdateWindowSurface");
}

void verify(void) {
#ifdef __EMSCRIPTEN__
  int res = EM_ASM_INT({
    var ctx = Module['canvas'].getContext('2d');
    var data = ctx.getImageData(0, 0, 256, 256).data;
    var idx = 0;
    for (var y = 0; y < 256; y++) {
      for (var x = 0; x < 256; x++) {
        if (data[idx] != = x || data[idx + 1] != = (x ^ y) || data[idx + 2] !=
            = y || data[idx + 3] != = 255) {
          return 1;
        }
        idx += 4;
      }
    }
    return 0;
  });

  printf("%s\n", res ? "FAIL" : "PASS");
  assert(res == 0);
#endif
}

int main(void) {
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Surface* surface;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) sdlError("SDL_Init");

  window = SDL_CreateWindow("SDL 2 test", 0, 0, 640, 640, SDL_WINDOW_SHOWN);

  renderer = SDL_CreateRenderer(window, -1, 0);

  if (window == NULL) sdlError("SDL_CreateWindow");
  surface = SDL_GetWindowSurface(window);
  if (surface == NULL) sdlError("SDL_GetWindowSurface");

  // draw(window, surface);
  // verify();

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 127);
  std::array<SDL_Point, 4> points{
      SDL_Point{1, 1},
      SDL_Point{1, 639},
      SDL_Point{639, 639},
      SDL_Point{639, 1},
  };
  SDL_RenderDrawLines(renderer, points.data(), points.size());

  SDL_RenderPresent(renderer);

  Loop();

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
