#include "canvas.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2_gfxPrimitives.h>
#include <cmath>
#include <optional>
#include "canvas_rendering_context.h"

void emscchart::DrawPoint(CanvasRenderingContext& ctx,
                          DrawPointOptions const& options, unsigned int point_x,
                          unsigned int point_y) {
  DrawPointLegend(ctx, options, point_x, point_y, std::nullopt);
}

void emscchart::DrawPointLegend(CanvasRenderingContext& ctx,
                                DrawPointOptions const& options,
                                unsigned int point_x, unsigned int point_y,
                                std::optional<unsigned int> point_w) {
  //   let type: string, xOffset: number, yOffset: number, size: number,
  //   cornerRadius: number, width: number, xOffsetW: number, yOffsetW: number;
  auto style = options.point_style;
  //   const rotation = options.rotation;
  auto radius = options.radius;
  //   let rad = (rotation || 0) * RAD_PER_DEG;

  //   if (style && typeof style === 'object') {
  //     type = style.toString();
  //     if (type === '[object HTMLImageElement]' || type === '[object
  //     HTMLCanvasElement]') {
  //       ctx.save();
  //       ctx.translate(x, y);
  //       ctx.rotate(rad);
  //       ctx.drawImage(style, -style.width / 2, -style.height / 2,
  //       style.width, style.height); ctx.restore(); return;
  //     }
  //   }

  if (std::isnan(radius) || radius <= 0) {
    return;
  }

  //   ctx.beginPath();

  switch (style) {
      // Default includes circle
    default:
      if (point_w) {
        // ctx.ellipse(x, y, w / 2, radius, 0, 0, TAU);
      } else {
        ctx.Circle(point_x, point_y, radius);
      }
      break;
      //     case 'triangle':
      //       width = w ? w / 2 : radius;
      //       ctx.moveTo(x + Math.sin(rad) * width, y - Math.cos(rad) *
      //       radius); rad += TWO_THIRDS_PI; ctx.lineTo(x + Math.sin(rad) *
      //       width, y - Math.cos(rad) * radius); rad += TWO_THIRDS_PI;
      //       ctx.lineTo(x + Math.sin(rad) * width, y - Math.cos(rad) *
      //       radius); ctx.closePath(); break;
      //     case 'rectRounded':
      //     // NOTE: the rounded rect implementation changed to use `arc`
      //     instead of
      //     // `quadraticCurveTo` since it generates better results when rect
      //     is
      //     // almost a circle. 0.516 (instead of 0.5) produces results with
      //     visually
      //     // closer proportion to the previous impl and it is inscribed in
      //     the
      //     // circle with `radius`. For more details, see the following PRs:
      //     // https://github.com/chartjs/Chart.js/issues/5597
      //     // https://github.com/chartjs/Chart.js/issues/5858
      //       cornerRadius = radius * 0.516;
      //       size = radius - cornerRadius;
      //       xOffset = Math.cos(rad + QUARTER_PI) * size;
      //       xOffsetW = Math.cos(rad + QUARTER_PI) * (w ? w / 2 - cornerRadius
      //       : size); yOffset = Math.sin(rad + QUARTER_PI) * size; yOffsetW =
      //       Math.sin(rad + QUARTER_PI) * (w ? w / 2 - cornerRadius : size);
      //       ctx.arc(x - xOffsetW, y - yOffset, cornerRadius, rad - PI, rad -
      //       HALF_PI); ctx.arc(x + yOffsetW, y - xOffset, cornerRadius, rad -
      //       HALF_PI, rad); ctx.arc(x + xOffsetW, y + yOffset, cornerRadius,
      //       rad, rad + HALF_PI); ctx.arc(x - yOffsetW, y + xOffset,
      //       cornerRadius, rad
      //       + HALF_PI, rad + PI); ctx.closePath(); break;
      //     case 'rect':
      //       if (!rotation) {
      //         size = Math.SQRT1_2 * radius;
      //         width = w ? w / 2 : size;
      //         ctx.rect(x - width, y - size, 2 * width, 2 * size);
      //         break;
      //       }
      //       rad += QUARTER_PI;
      //     /* falls through */
      //     case 'rectRot':
      //       xOffsetW = Math.cos(rad) * (w ? w / 2 : radius);
      //       xOffset = Math.cos(rad) * radius;
      //       yOffset = Math.sin(rad) * radius;
      //       yOffsetW = Math.sin(rad) * (w ? w / 2 : radius);
      //       ctx.moveTo(x - xOffsetW, y - yOffset);
      //       ctx.lineTo(x + yOffsetW, y - xOffset);
      //       ctx.lineTo(x + xOffsetW, y + yOffset);
      //       ctx.lineTo(x - yOffsetW, y + xOffset);
      //       ctx.closePath();
      //       break;
      //     case 'crossRot':
      //       rad += QUARTER_PI;
      //     /* falls through */
      //     case 'cross':
      //       xOffsetW = Math.cos(rad) * (w ? w / 2 : radius);
      //       xOffset = Math.cos(rad) * radius;
      //       yOffset = Math.sin(rad) * radius;
      //       yOffsetW = Math.sin(rad) * (w ? w / 2 : radius);
      //       ctx.moveTo(x - xOffsetW, y - yOffset);
      //       ctx.lineTo(x + xOffsetW, y + yOffset);
      //       ctx.moveTo(x + yOffsetW, y - xOffset);
      //       ctx.lineTo(x - yOffsetW, y + xOffset);
      //       break;
      //     case 'star':
      //       xOffsetW = Math.cos(rad) * (w ? w / 2 : radius);
      //       xOffset = Math.cos(rad) * radius;
      //       yOffset = Math.sin(rad) * radius;
      //       yOffsetW = Math.sin(rad) * (w ? w / 2 : radius);
      //       ctx.moveTo(x - xOffsetW, y - yOffset);
      //       ctx.lineTo(x + xOffsetW, y + yOffset);
      //       ctx.moveTo(x + yOffsetW, y - xOffset);
      //       ctx.lineTo(x - yOffsetW, y + xOffset);
      //       rad += QUARTER_PI;
      //       xOffsetW = Math.cos(rad) * (w ? w / 2 : radius);
      //       xOffset = Math.cos(rad) * radius;
      //       yOffset = Math.sin(rad) * radius;
      //       yOffsetW = Math.sin(rad) * (w ? w / 2 : radius);
      //       ctx.moveTo(x - xOffsetW, y - yOffset);
      //       ctx.lineTo(x + xOffsetW, y + yOffset);
      //       ctx.moveTo(x + yOffsetW, y - xOffset);
      //       ctx.lineTo(x - yOffsetW, y + xOffset);
      //       break;
      //     case 'line':
      //       xOffset = w ? w / 2 : Math.cos(rad) * radius;
      //       yOffset = Math.sin(rad) * radius;
      //       ctx.moveTo(x - xOffset, y - yOffset);
      //       ctx.lineTo(x + xOffset, y + yOffset);
      //       break;
      //     case 'dash':
      //       ctx.moveTo(x, y);
      //       ctx.lineTo(x + Math.cos(rad) * (w ? w / 2 : radius), y +
      //       Math.sin(rad) * radius); break;
      //     case false:
      //       ctx.closePath();
      //       break;
  }

  //   ctx.fill();
  //   if (options.borderWidth > 0) {
  //     ctx.stroke();
  //   }
}
