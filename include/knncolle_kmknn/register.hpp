#ifndef KNNCOLLE_KMKNN_REGISTER_HPP
#define KNNCOLLE_KMKNN_REGISTER_HPP

#include "knncolle/knncolle.hpp"

#include <string>

/**
 * @file register.hpp
 * @brief Register function to load KMKNN indices from disk.
 */

namespace knncolle_kmknn {

/**
 * Register a loading function for `load_prebuilt()` to load a KMKNN index from disk.
 * This should be done before any calls to `load_prebuilt()` that might need to read an on-disk representation of a KMKNN index saved with `knncolle::Prebuilt::save()`.
 * Registration is not thread-safe and should be done in a serial section only.
 *
 * @tparam Index_ Integer type for the observation indices.
 * @tparam Data_ Numeric type for the input and query data.
 * @tparam Distance_ Floating-point type for the distances.
 *
 * @return Whether any registration was performed.
 * If a function was already registered, this function is a no-op.
 */
template<typename Index_, typename Data_, typename Distance_>
bool register_load_prebuilt() {
    static bool done = false;
    if (!done) {
        auto& reg = knncolle::load_prebuilt_registry<Index_, Data_, Distance_>();
        reg["knncolle_kmknn::Kmknn"] = [](const std::string& prefix) -> knncolle::Prebuilt<Index_, Data_, Distance_>* {
            return new KmknnPrebuilt<Index_, Data_, Distance_>(prefix);
        };
        done = true;
    }
    return done;
}

}

#endif
