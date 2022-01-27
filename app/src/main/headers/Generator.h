#include "Splines.h"

class Generator {
 public:
  static Spline buildPath(Spline spline);
  static double calculateSegLength(int node, Spline spline);
};