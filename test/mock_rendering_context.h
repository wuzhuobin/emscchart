#ifndef EMSCCHART_MOCK_RENDERING_CONTEXT_H_
#define EMSCCHART_MOCK_RENDERING_CONTEXT_H_

#include <gmock/gmock.h>
#include "canvas_rendering_context.h"

namespace emscchart {
class MockCanvasRenderingContext : public CanvasRenderingContext {
 public:
  MOCK_METHOD(void, Circle,
              (std::uint16_t point_x, std::uint16_t point_y,
               std::uint16_t radius),
              (override));
};
}  // namespace emscchart

#endif  // EMSCCHART_MOCK_RENDERING_CONTEXT_H_