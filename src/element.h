#ifndef EMSCCHART_ELEMENT_H_
#define EMSCCHART_ELEMENT_H_
namespace emscchart {
class Element {
 public:
  virtual ~Element() = default;
  virtual void Draw() = 0;
};
}  // namespace emscchart
#endif  // EMSCCHART_ELEMENT_H_