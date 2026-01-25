#ifndef KNNCOLLE_KMKNN_ALIASES_HPP
#define KNNCOLLE_KMKNN_ALIASES_HPP

#include "knncolle/knncolle.hpp"
#include "kmeans/kmeans.hpp"

#include <utility>

/**
 * @file aliases.hpp
 * @brief Aliases for the KMKNN implementation.
 */

namespace knncolle_kmknn {

/**
 * Common type for promoting `Data_` and `Distance_` during subtraction.
 * If `Data_` is integer, the common type will be the floating-point type of `Distance_`;
 * otherwise if both types are floating-point, the common type will be the higher-precision type.
 * This is used to define the common datatype for storing both the input data and the centroids,
 * so that the same `DistanceMetric` can be used to compute the distances to a query datapoint.
 *
 * @tparam Data_ Numeric type for the input and query data.
 * @tparam Distance_ Floating-point type for the distances.
 */
template<typename Data_, typename Distance_>
using Common = decltype(std::declval<Data_>() - std::declval<Distance_>()); 

/**
 * Convenient alias for `knncolle::DistanceMetric` with the first template argument set to the `Common` type.
 *
 * @tparam Data_ Numeric type for the input and query data.
 * @tparam Distance_ Floating-point type for the distances.
 */
template<typename Data_, typename Distance_>
using DistanceMetric = knncolle::DistanceMetric<Common<Data_, Distance_>, Distance_>;

/**
 * Convenient alias for `knncolle::EuclideanDistance` with the first template argument set to the `Common` type.
 *
 * @tparam Data_ Numeric type for the input and query data.
 * @tparam Distance_ Floating-point type for the distances.
 */
template<typename Data_, typename Distance_>
using EuclideanDistance = knncolle::EuclideanDistance<Common<Data_, Distance_>, Distance_>;

/**
 * Convenient alias for `knncolle::ManhattanDistance` with the first template argument set to the `Common` type.
 *
 * @tparam Data_ Numeric type for the input and query data.
 * @tparam Distance_ Floating-point type for the distances.
 */
template<typename Data_, typename Distance_>
using ManhattanDistance = knncolle::ManhattanDistance<Common<Data_, Distance_>, Distance_>;

/**
 * Convenient alias for `kmeans::Initialize`, using the `Common` type for the input data and the distances/centroids.
 *
 * @tparam Index_ Integer type for the observation indices.
 * @tparam Data_ Numeric type for the input and query data.
 * @tparam Distance_ Floating-point type for the distances.
 * @tparam KmeansMatrix_ Class of the input data matrix for **kmeans**.
 * This should satisfy the `kmeans::Matrix` interface, most typically a `kmeans::SimpleMatrix`.
 * (Note that this is a different class from the `knncolle::Matrix` interface!)
 */
template<typename Index_, typename Data_, typename Distance_, class KmeansMatrix_ = kmeans::SimpleMatrix<Index_, Data_> >
using Initialize = kmeans::Initialize<Index_, Common<Data_, Distance_>, Index_, Common<Data_, Distance_>, KmeansMatrix_>;

/**
 * Convenient alias for `kmeans::InitializeRandom`, using the `Common` type for the input data and the distances/centroids.
 *
 * @tparam Index_ Integer type for the observation indices.
 * @tparam Data_ Numeric type for the input and query data.
 * @tparam Distance_ Floating-point type for the distances.
 * @tparam KmeansMatrix_ Class of the input data matrix for **kmeans**.
 * This should satisfy the `kmeans::Matrix` interface, most typically a `kmeans::SimpleMatrix`.
 * (Note that this is a different class from the `knncolle::Matrix` interface!)
 */
template<typename Index_, typename Data_, typename Distance_, class KmeansMatrix_ = kmeans::SimpleMatrix<Index_, Data_> >
using InitializeRandom = kmeans::InitializeRandom<Index_, Common<Data_, Distance_>, Index_, Common<Data_, Distance_>, KmeansMatrix_>;

/**
 * Convenient alias for `kmeans::InitializeKmeanspp`, using the `Common` type for the input data and the distances/centroids.
 *
 * @tparam Index_ Integer type for the observation indices.
 * @tparam Data_ Numeric type for the input and query data.
 * @tparam Distance_ Floating-point type for the distances.
 * @tparam KmeansMatrix_ Class of the input data matrix for **kmeans**.
 * This should satisfy the `kmeans::Matrix` interface, most typically a `kmeans::SimpleMatrix`.
 * (Note that this is a different class from the `knncolle::Matrix` interface!)
 */
template<typename Index_, typename Data_, typename Distance_, class KmeansMatrix_ = kmeans::SimpleMatrix<Index_, Data_> >
using InitializeKmeanspp = kmeans::InitializeKmeanspp<Index_, Common<Data_, Distance_>, Index_, Common<Data_, Distance_>, KmeansMatrix_>;

/**
 * Convenient alias for `kmeans::InitializeNone`, using the `Common` type for the input data and the distances/centroids.
 *
 * @tparam Index_ Integer type for the observation indices.
 * @tparam Data_ Numeric type for the input and query data.
 * @tparam Distance_ Floating-point type for the distances.
 * @tparam KmeansMatrix_ Class of the input data matrix for **kmeans**.
 * This should satisfy the `kmeans::Matrix` interface, most typically a `kmeans::SimpleMatrix`.
 * (Note that this is a different class from the `knncolle::Matrix` interface!)
 */
template<typename Index_, typename Data_, typename Distance_, class KmeansMatrix_ = kmeans::SimpleMatrix<Index_, Data_> >
using InitializeNone = kmeans::InitializeNone<Index_, Common<Data_, Distance_>, Index_, Common<Data_, Distance_>, KmeansMatrix_>;

/**
 * Convenient alias for `kmeans::InitializeVariancePartition`, using the `Common` type for the input data and the distances/centroids.
 *
 * @tparam Index_ Integer type for the observation indices.
 * @tparam Data_ Numeric type for the input and query data.
 * @tparam Distance_ Floating-point type for the distances.
 * @tparam KmeansMatrix_ Class of the input data matrix for **kmeans**.
 * This should satisfy the `kmeans::Matrix` interface, most typically a `kmeans::SimpleMatrix`.
 * (Note that this is a different class from the `knncolle::Matrix` interface!)
 */
template<typename Index_, typename Data_, typename Distance_, class KmeansMatrix_ = kmeans::SimpleMatrix<Index_, Data_> >
using InitializeVariancePartition = kmeans::InitializeVariancePartition<Index_, Common<Data_, Distance_>, Index_, Common<Data_, Distance_>, KmeansMatrix_>;

/**
 * Convenient alias for `kmeans::Refine`, using the `Common` type for the input data and the distances/centroids.
 *
 * @tparam Index_ Integer type for the observation indices.
 * @tparam Data_ Numeric type for the input and query data.
 * @tparam Distance_ Floating-point type for the distances.
 * @tparam KmeansMatrix_ Class of the input data matrix for **kmeans**.
 * This should satisfy the `kmeans::Matrix` interface, most typically a `kmeans::SimpleMatrix`.
 * (Note that this is a different class from the `knncolle::Matrix` interface!)
 */
template<typename Index_, typename Data_, typename Distance_, class KmeansMatrix_ = kmeans::SimpleMatrix<Index_, Data_> >
using Refine = kmeans::Refine<Index_, Common<Data_, Distance_>, Index_, Common<Data_, Distance_>, KmeansMatrix_>;

/**
 * Convenient alias for `kmeans::RefineLloyd`, using the `Common` type for the input data and the distances/centroids.
 *
 * @tparam Index_ Integer type for the observation indices.
 * @tparam Data_ Numeric type for the input and query data.
 * @tparam Distance_ Floating-point type for the distances.
 * @tparam KmeansMatrix_ Class of the input data matrix for **kmeans**.
 * This should satisfy the `kmeans::Matrix` interface, most typically a `kmeans::SimpleMatrix`.
 * (Note that this is a different class from the `knncolle::Matrix` interface!)
 */
template<typename Index_, typename Data_, typename Distance_, class KmeansMatrix_ = kmeans::SimpleMatrix<Index_, Data_> >
using RefineLloyd = kmeans::RefineLloyd<Index_, Common<Data_, Distance_>, Index_, Common<Data_, Distance_>, KmeansMatrix_>;

/**
 * Convenient alias for `kmeans::RefineHartiganWong`, using the `Common` type for the input data and the distances/centroids.
 *
 * @tparam Index_ Integer type for the observation indices.
 * @tparam Data_ Numeric type for the input and query data.
 * @tparam Distance_ Floating-point type for the distances.
 * @tparam KmeansMatrix_ Class of the input data matrix for **kmeans**.
 * This should satisfy the `kmeans::Matrix` interface, most typically a `kmeans::SimpleMatrix`.
 * (Note that this is a different class from the `knncolle::Matrix` interface!)
 */
template<typename Index_, typename Data_, typename Distance_, class KmeansMatrix_ = kmeans::SimpleMatrix<Index_, Data_> >
using RefineHartiganWong = kmeans::RefineHartiganWong<Index_, Common<Data_, Distance_>, Index_, Common<Data_, Distance_>, KmeansMatrix_>;

}

#endif
