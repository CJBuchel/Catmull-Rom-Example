#pragma once

#include <vector>

struct Waypoint {
  double x, y;
};

struct Spline {
  std::vector<Waypoint> waypoints; // waypoints where the robot goes through
  Waypoint entryCtrl, exitCtrl;
  double totalLength = 0;
};