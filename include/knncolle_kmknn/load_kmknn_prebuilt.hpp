#ifndef KNNCOLLE_KMKNN_LOAD_KMKNN_PREBUILT_HPP
#define KNNCOLLE_KMKNN_LOAD_KMKNN_PREBUILT_HPP

#include "knncolle/knncolle.hpp"

#include <string>

/**
 * @file load_kmknn_prebuilt.hpp
 * @brief Load a prebuilt KMKNN index from disk.
 */

namespace knncolle_kmknn {

/**
 * Helper function to define a `knncolle::LoadPrebuiltFunction` for KMKNN in `knncolle::load_prebuilt_raw()`.
 *
 * To load an KMKNN index from disk, users are expected to define and register an KMKNN-specific `knncolle::LoadPrebuiltFunction`.
 * In this function, users should call `load_kmknn_prebuilt_types()` to figure out the saved index's `KMKNNDistance_`, `KMKNNIndex` and `KMKNNData_`.
 * Then, they should call `load_kmknn_prebuilt()` with the appropriate types to return a pointer to a `knncolle::Prebuilt` object.
 * This user-defined function should be registered in `load_prebuilt_registry()` with the key in `knncolle_kmknn::save_name`.
 *
 * @tparam Index_ Integer type for the observation indices.
 * @tparam Data_ Numeric type for the input and query data.
 * @tparam Distance_ Floating-point type for the distances.
 * @tparam KmeansFloat_ Floating-point type of the cluster centroids.
 *
 * @param dir Path to a directory in which a prebuilt KMKNN index was saved.
 * An KMKNN index would typically be saved by calling the `knncolle::Prebuilt::save()` method of the KMKNN subclass instance.
 *
 * @return Pointer to a `knncolle::Prebuilt` KMKNN index.
 */
template<typename Index_, typename Data_, typename Distance_, typename KmeansFloat_ = Distance_>
auto load_kmknn_prebuilt(const std::filesystem::path& dir) {
    return new KmknnPrebuilt<
        Index_,
        Data_,
        Distance_,
        knncolle::DistanceMetric<Data_, Distance_>,
        KmeansFloat_,
        knncolle::DistanceMetric<KmeansFloat_, Distance_>
    >(dir);
}

}

#endif
