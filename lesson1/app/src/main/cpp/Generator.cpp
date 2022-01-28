#include "Generator.h"

static double square(double x, double i, double j) {
  double mid = (i + j) / 2;
  double mul = mid * mid;

  if ((mul == x) || (abs(mul - x) < 0.00001)) {
    return mid;
  } else if (mul < x) {
    return square(x, mid, j);
  } else {
    return square(x, i, mid);
  }
}

static double squareRoot(double x) {
  double i = 1;
  bool found = false;
  double res = 0;

  while (!found) {
    if (i * i == x) {
      // std::cout << std::fixed << std::setprecision(0) << x << std::endl;
      found = true;
    } else if (i * i > x) {
      res = square(x, i - 1, i);
      // std::cout << std::fixed << std::setprecision(5) << res << std::endl;
      found = true;
    }

    i++;
  }

  return res;
}


Waypoint getSplinePoint(double t, Spline spline) {
  int p0, p1, p2, p3;

  p1 = (int)t + 1;
  p2 = p1 + 1;
  p3 = p2 + 1;
  p0 = p1 - 1;

  t = t - (int)t;

  double tt = t * t;
  double ttt = tt * t;

  double q1 = -ttt + 2.0f*tt - t;
  double q2 = 3.0f*ttt - 5.0f*tt + 2.0f;
  double q3 = -3.0f*ttt + 4.0f*tt + t;
  double q4 = ttt - tt;

  double tx = 0.5f * (spline.waypoints[p0].x * q1 + spline.waypoints[p1].x * q2 + spline.waypoints[p2].x * q3 + spline.waypoints[p3].x * q4);
  double ty = 0.5f * (spline.waypoints[p0].y * q1 + spline.waypoints[p1].y * q2 + spline.waypoints[p2].y * q3 + spline.waypoints[p3].y * q4);

  return{ tx, ty };
}

double Generator::calculateSegLength(int node, Spline spline) {
  double totalSegLength = 0.0f;

  Waypoint oldPoint, newPoint;
  oldPoint = getSplinePoint((double)node, spline);

  for (double t = 0.0; t < 1.0f; t += 0.001f) {
    newPoint = getSplinePoint((double)node + t, spline);
    double xrt = (newPoint.x - oldPoint.x)*(newPoint.x - oldPoint.x);
    double yrt = (newPoint.y - oldPoint.y)*(newPoint.y - oldPoint.y);
    totalSegLength += sqrt((xrt+yrt));

    oldPoint = newPoint;
  }

  return totalSegLength;
}

Spline Generator::buildPath(Spline spline) {
  double totalLength = 0;

  Spline internalSpline = spline;

  internalSpline.waypoints.insert(internalSpline.waypoints.begin(), spline.entryCtrl); // add ctrlpnt to beginning
  internalSpline.waypoints.push_back(spline.exitCtrl); // add to the back of array

  for (int i = 1; i < internalSpline.waypoints.size()-1; i++) {
    totalLength += calculateSegLength(i, internalSpline);
    std::cout << "Length... " << totalLength << std::endl;
  }

  std::cout << "Final Length: " << totalLength << std::endl;
  
  // Spline output = spline;
  internalSpline.totalLength = totalLength;
  return internalSpline;
}