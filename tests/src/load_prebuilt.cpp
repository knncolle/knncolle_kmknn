#include <gtest/gtest.h>

#include "TestCore.h"

#include "knncolle_kmknn/knncolle_kmknn.hpp"

#include <filesystem>
#include <memory>
#include <vector>

class KmknnLoadPrebuiltTest : public TestCore, public ::testing::Test {
protected:
    inline static std::filesystem::path savedir;

    static void SetUpTestSuite() {
        assemble({ 50, 5 });

        savedir = "save-prebuilt-tests";
        std::filesystem::remove_all(savedir);
        std::filesystem::create_directory(savedir);

        knncolle_kmknn::register_load_prebuilt<int, double, double>();
    }
};

TEST_F(KmknnLoadPrebuiltTest, Euclidean) {
    auto eucdist = std::make_shared<knncolle::EuclideanDistance<double, double> >();
    knncolle_kmknn::KmknnBuilder<int, double, double> kb(eucdist);
    auto bptr = kb.build_unique(knncolle::SimpleMatrix<int, double>(ndim, nobs, data.data()));

    const auto prefix = (savedir / "euclidean_").string();
    bptr->save(prefix);

    auto reloaded = knncolle::load_prebuilt_shared<int, double, double>(prefix);
    std::vector<int> output_i, output_i2;
    std::vector<double> output_d, output_d2;

    auto searcher = bptr->initialize();
    auto researcher = reloaded->initialize();
    for (int x = 0; x < nobs; ++x) {
        searcher->search(x, 5, &output_i, &output_d);
        researcher->search(x, 5, &output_i2, &output_d2);
        EXPECT_EQ(output_i, output_i2);
        EXPECT_EQ(output_d, output_d2);
    }
}

TEST_F(KmknnLoadPrebuiltTest, Manhattan) {
    auto eucdist = std::make_shared<knncolle::ManhattanDistance<double, double> >();
    knncolle_kmknn::KmknnBuilder<int, double, double> kb(eucdist);
    auto bptr = kb.build_unique(knncolle::SimpleMatrix<int, double>(ndim, nobs, data.data()));

    const auto prefix = (savedir / "manhattan_").string();
    bptr->save(prefix);

    auto reloaded = knncolle::load_prebuilt_shared<int, double, double>(prefix);
    std::vector<int> output_i, output_i2;
    std::vector<double> output_d, output_d2;

    auto searcher = bptr->initialize();
    auto researcher = reloaded->initialize();
    for (int x = 0; x < nobs; ++x) {
        searcher->search(x, 5, &output_i, &output_d);
        researcher->search(x, 5, &output_i2, &output_d2);
        EXPECT_EQ(output_i, output_i2);
        EXPECT_EQ(output_d, output_d2);
    }
}

