#include "nearest_neighbors.h"
#include <iostream>

using namespace std;
int main(void) {
	NearestNeighbors knn;

  knn.points.push_back(Point(2, 0));
  knn.points.push_back(Point(1, 0));
  knn.points.push_back(Point(0, 10));
  knn.points.push_back(Point(5, 5));
  knn.points.push_back(Point(2, 5));

  auto nearest = knn.nearest(Point(0, 0), 3);
  for (const auto n : nearest) {
    cout << n.x << ", " << n.y << endl;
  }
}
