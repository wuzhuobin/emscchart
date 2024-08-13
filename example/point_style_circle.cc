#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

// emscchart
#include "helper.h"
#include "sdl2_rendering_context.h"

// {
//     "config": {
//         "type": "bubble",
//         "data": {
//             "datasets": [{
//                 "data": [
//                     {"x": 0, "y": 3, "r": 0},
//                     {"x": 1, "y": 3, "r": 2},
//                     {"x": 2, "y": 3, "r": 4},
//                     {"x": 3, "y": 3, "r": 8},
//                     {"x": 4, "y": 3, "r": 16},
//                     {"x": 5, "y": 3, "r": 32}
//                 ],
//                 "backgroundColor": "#00ff00",
//                 "borderColor": "transparent",
//                 "borderWidth": 0
//             }, {
//                 "data": [
//                     {"x": 0, "y": 2, "r": 0},
//                     {"x": 1, "y": 2, "r": 2},
//                     {"x": 2, "y": 2, "r": 4},
//                     {"x": 3, "y": 2, "r": 8},
//                     {"x": 4, "y": 2, "r": 16},
//                     {"x": 5, "y": 2, "r": 32}
//                 ],
//                 "backgroundColor": "transparent",
//                 "borderColor": "#0000ff",
//                 "borderWidth": 1
//             }, {
//                 "data": [
//                     {"x": 0, "y": 1, "r": 0},
//                     {"x": 1, "y": 1, "r": 2},
//                     {"x": 2, "y": 1, "r": 4},
//                     {"x": 3, "y": 1, "r": 8},
//                     {"x": 4, "y": 1, "r": 16},
//                     {"x": 5, "y": 1, "r": 32}
//                 ],
//                 "backgroundColor": "#00ff00",
//                 "borderColor": "#0000ff",
//                 "borderWidth": 2
//             }]
//         },
//         "options": {
//             "responsive": false,
//             "elements": {
//                 "point": {
//                     "pointStyle": "circle"
//                 }
//             },
//             "layout": {
//                 "padding": 40
//             },
//             "scales": {
//                 "x": {"display": false},
//                 "y": {"display": false}
//             }
//         }
//     },
//     "options": {
//         "canvas": {
//             "height": 256,
//             "width": 512
//         }
//     }
// }

auto main(int argc, char* argv[]) -> int {
  (void)argc;
  (void)argv;
  auto* window =
      SDL_CreateWindow("Point style circle", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 512, 256, SDL_WINDOW_SHOWN);
  SDL_CreateRenderer(window, -1, 0);
  auto* renderer = SDL_GetRenderer(window);

  emscchart::SDL2RenderingContext sdl2_rendering_context(*renderer);

  SDL_RenderPresent(renderer);
  Loop();

  SDL_DestroyWindow(window);
  SDL_Quit();
}