#include <iostream>

// #include "Splines.h"
// #include "Generator.h"

#include "Generator.h"

Spline spline {{
  {0,0},
  {2,0},
  {3,0},
  {4,0}}
};

int main() {

  // Set the step size super low (absolutely useless, 0.05 works for us. But just there to give an idea of how accurate it can be)
  Generator::setStepSize(0.0001);
  if (Generator::buildPath(spline) == -1) {
    std::cout << "Spline Build failed" << std::endl;
  }

  std::cout << "Total Length: " << spline.totalLength << std::endl;
  return 0;
}