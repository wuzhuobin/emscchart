#include "bubble.h"
#include "controller.h"

void emscchart::BubbleController::Update(UpdateMode mode) {
  UpdateElements(CachedMeta().data, 0, CachedMeta().data.size(), mode);
}

void emscchart::BubbleController::UpdateElements(
    std::vector<std::unique_ptr<Element>>& elements, unsigned int start,
    unsigned int count, UpdateMode mode) {
  auto reset = mode == UpdateMode::kReset;
  // const {iScale, vScale} = this._cachedMeta;
  // const {sharedOptions, includeOptions} = this._getSharedOptions(start,
  // mode); const iAxis = iScale.axis; const vAxis = vScale.axis;

  for (auto i = start; i < start + count; i++) {
    //   const point = points[i];
    auto& point = elements[i];
    //   const parsed = !reset && this.getParsed(i);
    //   const properties = {};
    //   const iPixel = properties[iAxis] = reset ?
    //   iScale.getPixelForDecimal(0.5) :
    //   iScale.getPixelForValue(parsed[iAxis]); const vPixel =
    //   properties[vAxis] = reset ? vScale.getBasePixel() :
    //   vScale.getPixelForValue(parsed[vAxis]);

    //   properties.skip = isNaN(iPixel) || isNaN(vPixel);

    //   if (includeOptions) {
    //     properties.options = sharedOptions ||
    //     this.resolveDataElementOptions(i, point.active ? 'active' : mode);

    //     if (reset) {
    //       properties.options.radius = 0;
    //     }
    //   }

    Point::Cfg properties(
        Point::Props{{.x = static_cast<unsigned int>(Data()[i].x),
                      .y = static_cast<unsigned int>(Data()[i].y)}},
        Point::Options{
            .options = {{{}, static_cast<unsigned int>(Data()[i].r), {}}, {}}});
    UpdateElement(*point, i, properties, mode);
  }
}
