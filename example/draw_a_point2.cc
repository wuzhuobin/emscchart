#include "bubble.h"
#include "canvas.h"
#include "controller.h"
#include "helper.h"
#include "point.h"
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

  emscchart::Chart chart(
      SDL_GetWindowID(window),
      emscchart::Configuration{
          .type = "bubble",
          .data =
              {
                  .labels = {},
                  .x_labels = {},
                  .y_labels = {},
                  .datasets = {{.type = {},
                                .data = {{{"x", 100}, {"y", 100}, {"r", 10}},
                                         {{"x", 100}, {"y", 100}, {"r", 30}}}}},
              },
          .option = {}});

  emscchart::DatasetController::data_element_factory_ =
      &std::make_unique<emscchart::Point>;
  emscchart::BubbleController bubble(chart, 0);
  bubble.BuildOrUpdateElements(true);
  // bubble.Configure();
  bubble.Update(emscchart::BubbleController::UpdateMode::kDefault);
  bubble.Draw();

  SDL_RenderPresent(renderer);
  Loop();

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}