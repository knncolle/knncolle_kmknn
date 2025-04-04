# knncolle bindings for KMKNN

![Unit tests](https://github.com/knncolle/knncolle_kmknn/actions/workflows/run-tests.yaml/badge.svg)
![Documentation](https://github.com/knncolle/knncolle_kmknn/actions/workflows/doxygenate.yaml/badge.svg)
[![Codecov](https://codecov.io/gh/knncolle/knncolle_kmknn/branch/master/graph/badge.svg)](https://codecov.io/gh/knncolle/knncolle_kmknn)

## Overview

This library implements the [k-means for k-nearest neighbors (KMKNN)](https://doi.org/10.1109/IJCNN.2011.6033373) algorithm for an exact neighbor search.
The idea is to apply k-means clustering on the input dataset, and then use the distances to the cluster centroids to narrow the search space for neighbors of an observation of interest.
This is an exact nearest neighbor search that is also capable of finding all neighbors within a threshold distance.
Users can easily swap in KMKNN in any framework that accepts [**knncolle**](https://github.com/knncolle/knncolle) interfaces.

## Quick start

Instances of the various **`knncolle_kmknn** classes can be used anywhere that accepts the corresponding **knncolle** interface.
For example:

```cpp
#include "knncolle/knncolle_kmknn.hpp"

int ndim = 10;
int nobs = 1000;
std::vector<double> matrix(ndim * nobs); // column-major ndim x nobs matrix.

// Wrap our data in a light SimpleMatrix.
knncolle::SimpleMatrix<int, double> mat(ndim, nobs, matrix.data());

// Build an KMKNN index. 
auto dist = std::make_shared<knncolle_kmknn::EuclideanDistance<double, double> >();
knncolle_kmknn::KmknnBuilder<int, double, double> kbuilder(dist);
auto kindex = kbuilder.build_unique(mat);

// Find 10 nearest neighbors of every element.
auto results = knncolle::find_nearest_neighbors(*kindex, 10); 
```

Check out the [reference documentation](https://knncolle.github.io/knncolle_kmknn/) for more details.

## Customizing the search

We can customize the behavior of the `KmknnBuilder` by modifying some of its options.
For example, to modify the k-means clustering:

```cpp
auto& opt = kbuilder.get_options();
opt.initialize_algorithm.reset(new knncolle_kmknn::InitializeRandom<int, double, double>);
opt.refine_algorithm.reset(new knncolle_kmknn::RefineLloyd<int, double, double>);
auto kindex2 = kbuilder.build_unique(mat);

// Alternatively we can pass some options directly to the KmknnBuilder's constructor.
knncolle_kmknn::KmknnOptions<int, double, double> new_options;
new_options.power = 0.8;
knncolle_kmknn::KmknnBuilder<int, double, double> kbuilder(dist, new_options);
```

We can also pass in a different distance metric, if so desired.
KMKNN works most naturally with the Euclidean distance as k-means aims to minimize the Euclidean distance between data points and the centroids.
But a different distance metric will still give the correct results:

```cpp
auto man_dist = std::make_shared<knncolle_kmknn::ManhattanDistance<double, double> >();
knncolle_kmknn::KmknnBuilder<int, double, double> man_kbuilder(man_dist);
```

As with other **knncolle** classes, advanced users can choose their own types via different template parametrizations.
This may provide some opportunities for devirtualization if polymorphism is not required.

```cpp
knncolle_kmknn::KmknnBuilder<
    /* observation index */ size_t,
    /* input data type */ float,
    /* distance type */ double,
    /* input matrix representation */ knncolle::SimpleMatrix<size_t, float>,
    /* distance metric */ knncolle_kmknn::EuclideanDistance<double, double>
> kbuilder_typed(dist);
```

## Building projects 

### CMake with `FetchContent`

If you're using CMake, you just need to add something like this to your `CMakeLists.txt`:

```cmake
include(FetchContent)

FetchContent_Declare(
  knncolle
  GIT_REPOSITORY https://github.com/knncolle/knncolle_kmknn
  GIT_TAG master # or any version of interest
)

FetchContent_MakeAvailable(knncolle_kmknn)
```

Then you can link to **knncolle_kmknn** to make the headers available during compilation:

```cmake
# For executables:
target_link_libraries(myexe knncolle::knncolle_kmknn)

# For libaries
target_link_libraries(mylib INTERFACE knncolle::knncolle_kmknn)
```

### CMake with `find_package()`

```cmake
find_package(knncolle_knncolle_kmknn CONFIG REQUIRED)
target_link_libraries(mylib INTERFACE knncolle::knncolle_kmknn)
```

To install the library, use:

```sh
mkdir build && cd build
cmake .. -DKNNCOLLE_KMKNN_TESTS=OFF
cmake --build . --target install
```

By default, this will use `FetchContent` to fetch all external dependencies.
If you want to install them manually, use `-DKNNCOLLE_KMKNN_FETCH_EXTERN=OFF`.
See [`extern/CMakeLists.txt`](extern/CMakeLists.txt) to find compatible versions of each dependency.

### Manual

If you're not using CMake, the simple approach is to just copy the files in `include/` - either directly or with Git submodules - and include their path during compilation with, e.g., GCC's `-I`.
See [`extern/CMakeLists.txt`](extern/CMakeLists.txt) for the required external dependencies.
