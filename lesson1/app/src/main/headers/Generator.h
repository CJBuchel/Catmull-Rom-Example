#include <math.h>
#include <iostream>
#include <bits/stdc++.h>

#include "Splines.h"

class Generator {
 public:
  static Spline buildPath(Spline spline);
  static double calculateSegLength(int node, Spline spline);
};