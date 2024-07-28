#include <string>
#ifndef EMSCCHART_ELEMENT_H_
#define EMSCCHART_ELEMENT_H_
namespace emscchart {
class CanvasRenderingContext;
namespace geometric {
struct ChartArea;
}  // namespace geometric
class Element {
 public:
  virtual ~Element() = default;
  virtual void Draw(CanvasRenderingContext& ctx,
                    geometric::ChartArea const& area) const = 0;

  void X(unsigned int point_x) { x_ = point_x; }
  [[nodiscard]] auto X() const -> unsigned int { return x_; }
  void Y(unsigned int point_y) { y_ = point_y; }
  [[nodiscard]] auto Y() const -> unsigned int { return y_; }

 private:
  unsigned int x_;
  unsigned int y_;
};

template <typename... PropTs>
struct PropMixin : public PropTs... {};

template <typename... OptionTs>
struct OptionMixin {
  struct Options : public OptionTs... {};
  Options options;
};

}  // namespace emscchart
#endif  // EMSCCHART_ELEMENT_H_