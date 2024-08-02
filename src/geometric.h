#ifndef EMSCHART_GEOMETRIC_H_
#define EMSCHART_GEOMETRIC_H_

namespace emscchart::geometric {

struct Point {
  unsigned int x;
  unsigned int y;
};

struct ChartArea {
  unsigned int top;
  unsigned int left;
  unsigned int right;
  unsigned int bottom;
  unsigned int width;
  unsigned int height;
};
}  // namespace emscchart::geometric

#endif  // EMSCHART_GEOMETRIC_H_