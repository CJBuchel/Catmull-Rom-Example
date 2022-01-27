#include <iostream>

#include "Splines.h"
#include "Generator.h"

Spline myPath = {
  { 
    {0,0}, 
    {2,2} 
  },

  {-1, 0}, // Control point 1
  {3, 2}
};

Spline builtSpline;

int main() {
  // std::cout << myPath.waypoints[0].x << std::endl;
  builtSpline = Generator::buildPath(myPath);
  // std::cout << number1 + number2 << std::endl;
  return 0;
}