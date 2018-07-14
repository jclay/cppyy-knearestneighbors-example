#include <algorithm>
#include "nearest_neighbors.h"

using namespace std;

vector<Point> NearestNeighbors::nearest(Point point, int k) {
  sort(points.begin(), points.end(), [point](Point a, Point b) {
    // Not concerned with actual distances, so skip the sqrt
    auto norm_a =
        (a.x - point.x) * (a.x - point.x) + (a.y - point.y) * (a.y - point.y);

    auto norm_b =
        (b.x - point.x) * (b.x - point.x) + (b.y - point.y) * (b.y - point.y);

    return norm_a < norm_b;
  });

  auto k_nearest = vector<Point>(points.begin(), points.begin() + k);
  return k_nearest;
}
