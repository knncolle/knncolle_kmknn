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

        knncolle::register_load_euclidean_distance<double, double>();
        knncolle::register_load_manhattan_distance<double, double>();
        auto& reg = knncolle::load_prebuilt_registry<int, double, double>();
        reg[knncolle_kmknn::kmknn_prebuilt_save_name] = [](const std::filesystem::path& dir) -> knncolle::Prebuilt<int, double, double>* {
            auto config = knncolle_kmknn::load_kmknn_prebuilt_types(dir);
            EXPECT_EQ(config.kmeansfloat, knncolle::NumericType::DOUBLE);
            return knncolle_kmknn::load_kmknn_prebuilt<int, double, double>(dir);
        };
    }
};

TEST_F(KmknnLoadPrebuiltTest, Euclidean) {
    auto eucdist = std::make_shared<knncolle::EuclideanDistance<double, double> >();
    knncolle_kmknn::KmknnBuilder<int, double, double> kb(eucdist, eucdist);
    auto bptr = kb.build_unique(knncolle::SimpleMatrix<int, double>(ndim, nobs, data.data()));

    const auto dir = savedir / "euclidean";
    std::filesystem::create_directory(dir);
    bptr->save(dir);

    auto reloaded = knncolle::load_prebuilt_shared<int, double, double>(dir);
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
    auto mandist = std::make_shared<knncolle::ManhattanDistance<double, double> >();
    knncolle_kmknn::KmknnBuilder<int, double, double> kb(mandist, mandist);
    auto bptr = kb.build_unique(knncolle::SimpleMatrix<int, double>(ndim, nobs, data.data()));

    const auto dir = savedir / "manhattan";
    std::filesystem::create_directory(dir);
    bptr->save(dir);

    auto reloaded = knncolle::load_prebuilt_shared<int, double, double>(dir);
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

TEST_F(KmknnLoadPrebuiltTest, Custom) {
    auto eucdist = std::make_shared<knncolle::EuclideanDistance<double, double> >();
    knncolle_kmknn::KmknnBuilder<int, double, double> kb(eucdist, eucdist);
    auto bptr = kb.build_unique(knncolle::SimpleMatrix<int, double>(ndim, nobs, data.data()));

    knncolle_kmknn::custom_save_for_kmknn_kmeansfloat<double>() = [](const std::filesystem::path& dir) -> void {
        knncolle::quick_save(dir / "custom_foo", "BAR", 3);
    };

    const auto dir = savedir / "custom";
    std::filesystem::create_directory(dir);
    bptr->save(dir);

    EXPECT_EQ(knncolle::quick_load_as_string(dir / "custom_foo"), "BAR");
}

TEST_F(KmknnLoadPrebuiltTest, Errors) {
    auto eucdist = std::make_shared<knncolle::EuclideanDistance<double, double> >();
    knncolle_kmknn::KmknnBuilder<int, double, double> kb(eucdist, eucdist);
    auto bptr = kb.build_unique(knncolle::SimpleMatrix<int, double>(ndim, nobs, data.data()));

    const auto dir = savedir / "error";
    std::filesystem::create_directory(dir);
    bptr->save(dir);

    {
        std::string msg;
        try {
            knncolle_kmknn::load_kmknn_prebuilt<int, double, double, knncolle::ManhattanDistance<double, double> >(dir);
        } catch (std::exception& e) {
            msg = e.what();
        }
        EXPECT_TRUE(msg.find("DistanceMetricData_") != std::string::npos);
    }

    {
        std::string msg;
        try {
            knncolle_kmknn::load_kmknn_prebuilt<int, double, double, knncolle::DistanceMetric<double, double>, double, knncolle::ManhattanDistance<double, double> >(dir);
        } catch (std::exception& e) {
            msg = e.what();
        }
        EXPECT_TRUE(msg.find("DistanceMetricCenter_") != std::string::npos);
    }
}
