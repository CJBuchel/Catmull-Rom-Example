#include "Generator.h"
#include "Splines.h"

double Generator::calculateSegLength(int node, Spline spline) {
  double totalSegLength = 0.0f;

  Waypoint oldPoint, newPoint;
  oldPoint = CatmullRom::getSplinePoint((double)node, spline);

  for (double t = 0.0; t < 1.0f; t += 0.05f) {
    newPoint = CatmullRom::getSplinePoint((double)node + t, spline);
    double xrt = (newPoint.x - oldPoint.x)*(newPoint.x - oldPoint.x);
    double yrt = (newPoint.y - oldPoint.y)*(newPoint.y - oldPoint.y);
    totalSegLength += sqrt((xrt+yrt));

    oldPoint = newPoint;
  }

  return totalSegLength;
}

Spline Generator::buildPath(Spline spline) {
  double totalLength = 0;
  double segf_l = 0;
  double segl_l = 0;

  Spline internalSpline = spline;

  internalSpline.waypoints.insert(internalSpline.waypoints.begin(), spline.entryCtrl); // add ctrlpnt to beginning
  internalSpline.waypoints.push_back(spline.exitCtrl); // add to the back of array

  for (int i = 0; i < internalSpline.waypoints.size(); i++) {
    totalLength += calculateSegLength(i, internalSpline);
    std::cout << "Length... " << totalLength << std::endl;
  }

  std::cout << "Final Length: " << totalLength << std::endl;

  // Waypoint startPoint = spline.waypoints.front();
  Waypoint endPoint = spline.waypoints.back();

  double actualLength = 0;
  bool foundDistance = false;
  while (foundDistance == false) {
    Waypoint point = CatmullRom::getSplinePoint(actualLength, internalSpline);
    double angle = CatmullRom::getAngleDeg(actualLength, internalSpline);

    std::cout << std::fixed << std::setprecision(5) << "Distance: " << actualLength << ", Angle: " << angle << ", x,y: (" << point.x << "," << point.y << ")" << std::endl;

    if (point.x < endPoint.x || point.y < endPoint.y) {
      actualLength += _stepSize;
    } else {
      foundDistance = true;
    }
  }
  
  // Spline output = spline;
  internalSpline.totalLength = totalLength;
  internalSpline.actualLength = actualLength;
  return internalSpline;
}