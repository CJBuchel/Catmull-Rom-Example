#include <iostream>

// #include "Splines.h"
// #include "Generator.h"

#include "Generator.h"

Spline spline {{
  {2,0},
  {3,0}},

  {1,0}, {4,0}
};

Spline outputSpline;



int main() {
  outputSpline = Generator::buildPath(spline);
  std::cout << outputSpline.waypoints.size() << std::endl;
  std::cout << "Actual Length: " << outputSpline.actualLength << std::endl;
  // std::cout << "Length: " << outputSpline.totalLength << std::endl;
  // for (double i = 0; i < outputSpline.totalLength; i+=0.01) {
  //   double distance = i;
  //   double angle = CatmullRom::getAngleDeg(distance, outputSpline);
  //   Waypoint point = CatmullRom::getSplinePoint(distance, outputSpline);

  //   std::cout << std::fixed << std::setprecision(5) << "Distance: " << distance << ", Angle: " << angle << ", x,y: (" << point.x << "," << point.y << ")" << std::endl;
  // }
  return 0;
}