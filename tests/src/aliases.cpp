#include <gtest/gtest.h>

#include "knncolle_kmknn/aliases.hpp"

#include <cstddef>
#include <type_traits>

TEST(Aliases, Common) {
    {
        constexpr bool test = std::is_same<knncolle_kmknn::Common<int, float>, float>::value;
        EXPECT_TRUE(test);
    }
    {
        constexpr bool test = std::is_same<knncolle_kmknn::Common<double, float>, double>::value;
        EXPECT_TRUE(test);
    }
    {
        constexpr bool test = std::is_same<knncolle_kmknn::Common<std::size_t, float>, float>::value;
        EXPECT_TRUE(test);
    }
    {
        constexpr bool test = std::is_same<knncolle_kmknn::Common<std::size_t, double>, double>::value;
        EXPECT_TRUE(test);
    }
}

TEST(Aliases, Kmeans) {
    // Getting some coverage on these guys.
    [[maybe_unused]] knncolle_kmknn::Initialize<int, double, double>* iptr;
    [[maybe_unused]] knncolle_kmknn::InitializeRandom<int, double, double> initr;
    [[maybe_unused]] knncolle_kmknn::InitializeKmeanspp<int, double, double> initp;
    [[maybe_unused]] knncolle_kmknn::InitializeNone<int, double, double> initn;
    [[maybe_unused]] knncolle_kmknn::InitializeVariancePartition<int, double, double> initv;

    [[maybe_unused]] knncolle_kmknn::Refine<int, double, double>* rptr;
    [[maybe_unused]] knncolle_kmknn::RefineLloyd<int, double, double> refl;
    [[maybe_unused]] knncolle_kmknn::RefineHartiganWong<int, double, double> refhw;
}

