#include <iostream>

// #include "Splines.h"
// #include "Generator.h"

#include "Generator.h"

Spline spline {
  {
    {0,0},
    {2,2}
  },

  {-1,0},
  {3,2}
};

Spline outputSpline;



int main() {
  outputSpline = Generator::buildPath(spline);
  return 0;
}