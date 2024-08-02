#ifndef EMSCCHART_TYPES_H_
#define EMSCCHART_TYPES_H_

namespace emscchart::types {

struct CommonElementOptions {
  unsigned int border_width;
  //   borderColor: Color;
  //   backgroundColor: Color;
};

struct CommonHoverOptions {
  //   hoverBorderWidth: number;
  //   hoverBorderColor: Color;
  //   hoverBackgroundColor: Color;
};

struct PointOptions : public CommonElementOptions {
  /**
   * Point radius
   * @default 3
   */
  unsigned int radius;
  /**
   * Extra radius added to point radius for hit detection.
   * @default 1
   */
  unsigned int hit_radius;
  //   /**
  //    * Point style
  //    * @default 'circle;
  //    */
  //   pointStyle: PointStyle;
  //   /**
  //    * Point rotation (in degrees).
  //    * @default 0
  //    */
  //   rotation: number;
  //   /**
  //    * Draw the active elements over the other elements of the dataset,
  //    * @default true
  //    */
  //   drawActiveElementsOnTop: boolean;
};

struct PointHoverOptions : public CommonHoverOptions {
  /**
   * Point radius when hovered.
   * @default 4
   */
  unsigned int hover_radius;
};
}  // namespace emscchart::types

#endif  // EMSCCHART_TYPES_H_