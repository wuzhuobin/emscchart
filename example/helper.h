#ifndef EMSCCHART_HELPER_H_
#define EMSCCHART_HELPER_H_

#include <SDL2/SDL.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

bool handle_event() {
  SDL_Event event;
  SDL_PollEvent(&event);
  if (event.type == SDL_QUIT) {
    return false;
  }
  return true;
}

void Loop() {
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop([]() { handle_event(); }, 0, 1);
#else
  for (; handle_event(););

#endif
}

#endif  // EMSCCHART_HELPER_H_