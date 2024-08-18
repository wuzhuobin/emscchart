#include "line.h"

void emscchart::Line::Draw(CanvasRenderingContext& ctx,
                           geometric::ChartArea const& area) const {
  (void)ctx;
  (void)area;
}

void emscchart::Line::Assign(nlohmann::json const& json) {}
