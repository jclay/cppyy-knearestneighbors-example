#pragma once

#include <iostream>
#include <vector>

class Point {
public:
  Point() {};
  Point(double x, double y) : x(x), y(y) {};
  double x, y;
};

class NearestNeighbors {
 public:
  NearestNeighbors() {};
  std::vector<Point> points;
  std::vector<Point> nearest(Point, int k);
};
