# Readme
This is an example project showing how to integrate a kNearestNeighbors impelemented in C++ use Cppyy to enable calling from Python.

There are two C++ classes defined - *Point* and *NearestNeighbor*. From C++ we would use them as follow:

```c++
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

  auto nearest = knn.nearest2(Point(0, 0), 3);
  for (const auto n : nearest) {
    cout << n.x << ", " << n.y << endl;
  }
}
```

And from Python we can use it as follow:

```python
from cppyy.gbl import std
import knn_example
from knn_example import NearestNeighbors, Point

# TODO put this in a pythonization that gets loaded in automatically
# Tell python how to print our C++ Class
Point.__repr__ = lambda self: repr(str(self.x) + ", " + str(self.y))

print(knn_example.__file__)

knn = NearestNeighbors()
points = [Point(2,0), Point(1,0), Point(0,10), Point(5,5), Point(2,5)]
knn.points = std.vector[Point](points)
result = knn.nearest2(Point(2.1, 5.3), 4)
print(list(result))
```

# Setup

*Note: I'm using Python 2*
This is because even the latest clang-python (for clang 6) only provides Python 2 bindings. It seems that Python 3 support should work, it may require building Clang from source though, I plan to test this in the future.

I have only tested this setup using Debian with the latest testing repository (buster).

The [Cppyy docs](https://cppyy.readthedocs.io/en/latest/installation.html) are a great resource and I highly recommend you read them before trying the project.

Install dependencies
```
sudo apt-get install python2 python-pip
sudo apt-get install clang-6.0
sudo apt-get install libclang-6.0-dev
sudo apt-get install python-clang-6.0
```

I encountered the [following bug](https://bitbucket.org/wlav/cppyy/issues/21/pip-install-fails-on-ubuntu-on-windows) which is addressed by explicitly installing with the following.
```
pip install cppyy-cling
pip install cppyy-backend
pip install CpyCppyy
pip install cppyy
```

We can verify that things are working with:

```
>>>  from clang.cindex import Config
>>>  Config().lib
>>>  <CDLL 'libclang-6.0.so', handle 7fffe4d35490 at 7f496430ee90>
```

# Building

```
mkdir build
cmake -G Ninja ..
cmake --build .
```

# Using with Python

From the directory containing the knn_examples folder (build in this case):

```python
from cppyy.gbl import std
import knn_example
from knn_example import NearestNeighbors, Point

# TODO put this in a pythonization that gets loaded in automatically
# Tell python how to print our C++ Class
Point.__repr__ = lambda self: repr(str(self.x) + ", " + str(self.y))

print(knn_example.__file__)

knn = NearestNeighbors()
points = [Point(2,0), Point(1,0), Point(0,10), Point(5,5), Point(2,5)]
knn.points = std.vector[Point](points)
result = knn.nearest2(Point(2.1, 5.3), 4)
print(list(result))
```