#include "point.h"
#include "canvas.h"
#include "canvas_rendering_context.h"

emscchart::Point::Point(Cfg const& cfg) : Props(cfg), Options(cfg) {
  X(cfg.x);
  Y(cfg.y);
}

void emscchart::Point::Draw(CanvasRenderingContext& ctx,
                            geometric::ChartArea const& area) const {
  (void)area;
  // const options = this.options;
  DrawPointOptions const options{
      .point_style = DrawPointOptions::PointStyle::kCircle, .radius = Radius()};

  // if (this.skip || options.radius < 0.1 || !_isPointInArea(this, area,
  // this.size(options) / 2)) {
  //   return;
  // }

  // ctx.strokeStyle = options.borderColor;
  // ctx.lineWidth = options.borderWidth;
  // ctx.fillStyle = options.backgroundColor;
  DrawPoint(ctx, options, X(), Y());
}

void emscchart::Point::Radius(unsigned int radius) { options.radius = radius; }

auto emscchart::Point::Radius() const -> unsigned int { return options.radius; }

auto emscchart::Point::InRange(unsigned int point_x,
                               unsigned int point_y) const -> bool {
  return (point_x - X()) * (point_x - X()) + (point_y - Y()) * (point_y - Y()) <
         (options.radius + options.hit_radius) *
             (options.radius + options.hit_radius);
}
