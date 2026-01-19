#include <gtest/gtest.h>
#include "knncolle_kmknn/knncolle_kmknn.hpp"
#include "aarand/aarand.hpp"

#include <vector>
#include <random>

class TestCore {
protected:
    inline static int nobs, ndim;
    inline static std::vector<double> data;
    inline static std::tuple<int, int> last_params;

protected:
    static void assemble(const std::tuple<int, int>& param) {
        if (param == last_params) {
            return;
        }
        last_params = param;

        nobs = std::get<0>(param);
        ndim = std::get<1>(param);

        std::mt19937_64 rng(nobs * 10 + ndim);
        std::normal_distribution distr;

        data.resize(nobs * ndim);
        for (auto& d : data) {
            d = distr(rng);
        }
    }

    template<class It_, class Rng_>
    static void fill_random(It_ start, It_ end, Rng_& eng) {
        std::normal_distribution distr;
        while (start != end) {
            *start = distr(eng);
            ++start;
        }
    }
};

class KmknnTest : public TestCore, public ::testing::TestWithParam<std::tuple<std::tuple<int, int>, int> > {
protected:
    void SetUp() {
        assemble(std::get<0>(GetParam()));
    }
}; 

TEST_P(KmknnTest, FindEuclidean) {
    int k = std::get<1>(GetParam());
    auto eucdist = std::make_shared<knncolle::EuclideanDistance<double, double> >();

    knncolle::SimpleMatrix<int, double> mat(ndim, nobs, data.data());
    knncolle_kmknn::KmknnBuilder<int, double, double> kb(eucdist);
    auto kptr = kb.build_unique(mat);
    EXPECT_EQ(ndim, kptr->num_dimensions());
    EXPECT_EQ(nobs, kptr->num_observations());

    // Building a brute-force reference.
    knncolle::BruteforceBuilder<int, double, double> bb(eucdist);
    auto bptr = bb.build_unique(mat);

    // Testing other types. 
    knncolle::SimpleMatrix<size_t, double> mat2(ndim, nobs, data.data());
    knncolle_kmknn::KmknnBuilder<size_t, double, float> kb2(std::make_shared<knncolle::EuclideanDistance<double, float> >());
    auto kptr2 = kb2.build_unique(mat2);

    std::vector<int> kres_i, ref_i;
    std::vector<double> kres_d, ref_d;
    auto bsptr = bptr->initialize();
    auto ksptr = kptr->initialize();
    std::vector<size_t> kres2_i;
    std::vector<float> kres2_d;
    auto ksptr2 = kptr2->initialize();

    for (int x = 0; x < nobs; ++x) {
        ksptr->search(x, k, &kres_i, &kres_d);
        bsptr->search(x, k, &ref_i, &ref_d);
        EXPECT_EQ(kres_i, ref_i);
        EXPECT_EQ(kres_d, ref_d);

        // Trying with some NULLs.
        ksptr->search(x, k, NULL, &kres_d);
        EXPECT_EQ(kres_d, ref_d);
        ksptr->search(x, k, &kres_i, NULL);
        EXPECT_EQ(kres_i, ref_i);

        ksptr2->search(x, k, &kres2_i, &kres2_d);
        EXPECT_EQ(kres_i.size(), kres2_i.size());
        for (size_t i = 0; i < kres_i.size(); ++i) {
            EXPECT_EQ(kres_i[i], kres2_i[i]);
            EXPECT_FLOAT_EQ(kres_d[i], kres2_d[i]);
        }
    }
}

TEST_P(KmknnTest, FindManhattan) {
    int k = std::get<1>(GetParam());    
    auto mandist = std::make_shared<knncolle::ManhattanDistance<double, double> >();

    knncolle::SimpleMatrix<int, double> mat(ndim, nobs, data.data());
    knncolle::BruteforceBuilder<int, double, double> bb(mandist);
    auto bptr = bb.build_unique(mat);
    knncolle_kmknn::KmknnBuilder<int, double, double> kb(mandist);
    auto kptr = kb.build_shared(mat); // making a shared pointer for some variety.

    std::vector<int> kres_i, ref_i;
    std::vector<double> kres_d, ref_d;
    auto bsptr = bptr->initialize();
    auto ksptr = kptr->initialize();

    for (int x = 0; x < nobs; ++x) {
        ksptr->search(x, k, &kres_i, &kres_d);
        bsptr->search(x, k, &ref_i, &ref_d);
        EXPECT_EQ(kres_i, ref_i);
        EXPECT_EQ(kres_d, ref_d);
    }
}

TEST_P(KmknnTest, QueryEuclidean) {
    int k = std::get<1>(GetParam());    
    auto eucdist = std::make_shared<knncolle::EuclideanDistance<double, double> >();

    knncolle::SimpleMatrix<int, double> mat(ndim, nobs, data.data());
    knncolle_kmknn::KmknnBuilder<int, double, double> kb(eucdist);
    auto kptr = kb.build_known_unique(mat); // test coverage for the known overrides.
    knncolle::BruteforceBuilder<int, double, double> bb(eucdist);
    auto bptr = bb.build_unique(mat);

    std::vector<int> kres_i, ref_i;
    std::vector<double> kres_d, ref_d;
    auto bsptr = bptr->initialize();
    auto ksptr = kptr->initialize();

    std::mt19937_64 rng(ndim * 10 + nobs - k);
    std::vector<double> buffer(ndim);

    for (int x = 0; x < nobs; ++x) {
        fill_random(buffer.begin(), buffer.end(), rng);
        ksptr->search(buffer.data(), k, &kres_i, &kres_d);
        bsptr->search(buffer.data(), k, &ref_i, &ref_d);
        EXPECT_EQ(kres_i, ref_i);
        EXPECT_EQ(kres_d, ref_d);

        // Trying with some NULLs.
        ksptr->search(buffer.data(), k, NULL, &kres_d);
        EXPECT_EQ(kres_d, ref_d);
        ksptr->search(buffer.data(), k, &kres_i, NULL);
        EXPECT_EQ(kres_i, ref_i);
    }
}

TEST_P(KmknnTest, AllEuclidean) {
    int k = std::get<1>(GetParam());    
    auto eucdist = std::make_shared<knncolle::EuclideanDistance<double, double> >();

    knncolle_kmknn::KmknnBuilder<int, double, double> kb(eucdist);
    auto kptr = kb.build_known_shared(knncolle::SimpleMatrix<int, double>(ndim, nobs, data.data())); // test coverage for the known overrides.
    auto ksptr = kptr->initialize();
    std::vector<int> output_i, ref_i;
    std::vector<double> output_d, ref_d;

    EXPECT_TRUE(ksptr->can_search_all());

    for (int x = 0; x < nobs; ++x) {
        {
            ksptr->search(x, k, &ref_i, &ref_d);
            double new_threshold = ref_d.back() * 0.99;
            while (ref_d.size() && ref_d.back() > new_threshold) {
                ref_d.pop_back();
                ref_i.pop_back();
            }

            auto num = ksptr->search_all(x, new_threshold, &output_i, &output_d);
            EXPECT_EQ(output_i, ref_i); 
            EXPECT_EQ(output_d, ref_d);
            EXPECT_EQ(num, ref_i.size());

            ksptr->search_all(x, new_threshold, NULL, &output_d);
            EXPECT_EQ(output_d, ref_d);
            ksptr->search_all(x, new_threshold, &output_i, NULL);
            EXPECT_EQ(output_i, ref_i);

            auto num2 = ksptr->search_all(x, new_threshold, NULL, NULL);
            EXPECT_EQ(num, num2);
        }

        {
            auto ptr = data.data() + x * ndim;
            ksptr->search(ptr, k, &ref_i, &ref_d);
            double new_threshold = ref_d.back() * 0.99;
            while (ref_d.size() && ref_d.back() > new_threshold) {
                ref_d.pop_back();
                ref_i.pop_back();
            }

            auto num = ksptr->search_all(ptr, new_threshold, &output_i, &output_d);
            EXPECT_EQ(output_i, ref_i);
            EXPECT_EQ(output_d, ref_d);
            EXPECT_EQ(num, ref_i.size());

            ksptr->search_all(ptr, new_threshold, NULL, &output_d);
            EXPECT_EQ(output_d, ref_d);
            ksptr->search_all(ptr, new_threshold, &output_i, NULL);
            EXPECT_EQ(output_i, ref_i);

            auto num2 = ksptr->search_all(ptr, new_threshold, NULL, NULL);
            EXPECT_EQ(num, num2);
        }
    }
}

TEST_P(KmknnTest, AllManhattan) {
    int k = std::get<1>(GetParam());    
    auto mandist = std::make_shared<knncolle::ManhattanDistance<double, double> >(); // Using Manhattan to test that denormalization is done correctly.

    knncolle_kmknn::KmknnBuilder<int, double, double> kb(mandist);
    auto kptr = kb.build_unique(knncolle::SimpleMatrix<int, double>(ndim, nobs, data.data()));
    auto ksptr = kptr->initialize();
    std::vector<int> output_i, ref_i;
    std::vector<double> output_d, ref_d;

    EXPECT_TRUE(ksptr->can_search_all());

    for (int x = 0; x < nobs; ++x) {
        ksptr->search(x, k, &ref_i, &ref_d);
        double new_threshold = ref_d.back() * 0.99;
        while (ref_d.size() && ref_d.back() > new_threshold) {
            ref_d.pop_back();
            ref_i.pop_back();
        }

        auto num = ksptr->search_all(x, new_threshold, &output_i, &output_d);
        EXPECT_EQ(output_i, ref_i); 
        EXPECT_EQ(output_d, ref_d);
        EXPECT_EQ(num, ref_i.size());
    }
}

INSTANTIATE_TEST_SUITE_P(
    Kmknn,
    KmknnTest,
    ::testing::Combine(
        ::testing::Combine(
            ::testing::Values(10, 500), // number of observations
            ::testing::Values(5, 20) // number of dimensions
        ),
        ::testing::Values(3, 10, 20) // number of neighbors (one is greater than # observations, to test correct limiting)
    )
);

class KmknnDuplicateTest : public TestCore, public ::testing::TestWithParam<int> {
protected:
    void SetUp() {
        assemble({ 5, 3 });
    }
};

TEST_P(KmknnDuplicateTest, Basic) {
    // Duplicate tests also check that KMKNN handles zero-size clusters
    // correctly when these clusters occur after all other clusters. With the
    // default kmeans++ initialization, the trailing clusters will be empty if
    // 'k' is larger than the number of unique points.
    //
    // Note that we don't consider zero-size clusters that are intermingled
    // with non-zero-size clusters; see the SkipEmpty test below for that.

    int duplication = 10;
    std::vector<double> dup;
    for (int d = 0; d < duplication; ++d) {
        dup.insert(dup.end(), data.begin(), data.end());
    }

    auto eucdist = std::make_shared<knncolle::EuclideanDistance<double, double> >();
    knncolle_kmknn::KmknnBuilder<int, double, double> bb(eucdist);
    int actual_nobs = nobs * duplication;
    auto bptr = bb.build_unique(knncolle::SimpleMatrix<int, double>(ndim, actual_nobs, dup.data()));
    auto bsptr = bptr->initialize();
    std::vector<int> res_i;
    std::vector<double> res_d;

    int k = GetParam();
    for (int o = 0; o < actual_nobs; ++o) {
        bsptr->search(o, k, &res_i, &res_d);
        int full_set = std::min(k, actual_nobs - 1);
        EXPECT_EQ(res_i.size(), full_set);
        EXPECT_EQ(res_d.size(), full_set);

        int all_equal = std::min(k, duplication - 1);
        for (int i = 0; i < all_equal; ++i) {
            EXPECT_EQ(res_i[i] % nobs, o % nobs);
            EXPECT_EQ(res_d[i], 0);
        }

        for (int i = all_equal; i < full_set; ++i) {
            EXPECT_NE(res_i[i] % nobs, o % nobs);
            EXPECT_GT(res_d[i], 0);
        }
    }
}

INSTANTIATE_TEST_SUITE_P(
    Kmknn,
    KmknnDuplicateTest,
    ::testing::Values(3, 10, 20) // number of neighbors
);

class KmknnMiscTest : public TestCore, public ::testing::Test {
protected:
    void SetUp() {
        assemble({ 100, 5 });
    }
};

TEST_F(KmknnMiscTest, Options) {
    auto eucdist = std::make_shared<knncolle::EuclideanDistance<double, double> >();
    knncolle_kmknn::KmknnBuilder<int, double, double> kb(eucdist);
    EXPECT_FALSE(kb.get_options().initialize_algorithm);
    EXPECT_FALSE(kb.get_options().refine_algorithm);

    knncolle_kmknn::KmknnOptions<int, double, double> opt;
    opt.initialize_algorithm.reset(new kmeans::InitializeRandom<int, double, int, double, kmeans::SimpleMatrix<int, double> >);
    opt.refine_algorithm.reset(new kmeans::RefineLloyd<int, double, int, double, kmeans::SimpleMatrix<int, double> >);

    knncolle_kmknn::KmknnBuilder<int, double, double> kb2(std::make_shared<knncolle::EuclideanDistance<double, double> >(), opt); // test the constructor.
    EXPECT_TRUE(kb2.get_options().initialize_algorithm);
    EXPECT_TRUE(kb2.get_options().refine_algorithm);

    knncolle::SimpleMatrix<int, double> mat(ndim, nobs, data.data());
    auto kptr = kb.build_unique(mat);
    auto kptr2 = kb2.build_unique(mat);

    std::vector<int> kres_i, kres2_i;
    std::vector<double> kres_d, kres2_d;
    auto ksptr = kptr->initialize();
    auto ksptr2 = kptr2->initialize();

    for (int x = 0; x < nobs; ++x) {
        ksptr->search(x, 5, &kres_i, &kres_d);
        ksptr2->search(x, 5, &kres2_i, &kres2_d);
        EXPECT_EQ(kres_i, kres2_i);
        EXPECT_EQ(kres_d, kres2_d);
    }
}

template<typename Index_, typename Data_, typename Cluster_, typename Float_, class Matrix_ = kmeans::Matrix<Index_, Data_> >
struct InitializeNonsense : public kmeans::Initialize<Index_, Data_, Cluster_, Float_, Matrix_> {
    Cluster_ run(const Matrix_& data, Cluster_ ncenters, Float_* centers) const {
        std::mt19937_64 eng(1000);
        auto nobs = data.num_observations();
        std::vector<Index_> chosen(std::min(nobs, static_cast<Index_>(ncenters)));
        aarand::sample(nobs, ncenters, chosen.begin(), eng);

        size_t ndim = data.num_dimensions();
        size_t nchosen = chosen.size();
        auto work = data.new_extractor(chosen.data(), nchosen);
        auto out = centers;
        for (size_t i = 0; i < nchosen; ++i) {
            auto ptr = work->get_observation();
            std::copy_n(ptr, ndim, out);
            out += ndim;
        }

        std::fill_n(centers, ndim, 100000000); // first one is nonsensically far away.
        return nchosen;
    }
};

TEST_F(KmknnMiscTest, SkipEmptyClusters) {
    // We test the code that skips empty clusters in the constructor when these
    // clusters occur before a non-empty cluster. We do so by forcing the first
    // cluster to be empty by making its center ridiculous.

    auto eucdist = std::make_shared<knncolle::EuclideanDistance<double, double> >();
    knncolle::BruteforceBuilder<int, double, double> bb(eucdist);

    knncolle_kmknn::KmknnBuilder<int, double, double> kb(eucdist);
    auto& opt = kb.get_options();
    opt.initialize_algorithm.reset(new InitializeNonsense<int, double, int, double, kmeans::SimpleMatrix<int, double> >); // nothing will be assigned to the first cluster. 
    kmeans::RefineLloydOptions ll_opt;
    ll_opt.max_iterations = 1; // no iterations so cluster centers can't be changed during refinement.
    opt.refine_algorithm.reset(new kmeans::RefineLloyd<int, double, int, double, kmeans::SimpleMatrix<int, double> >(ll_opt));

    knncolle::SimpleMatrix<int, double> mat(ndim, nobs, data.data());
    auto kptr = kb.build_unique(mat);
    auto bptr = bb.build_unique(mat);

    std::vector<int> kres_i, ref_i;
    std::vector<double> kres_d, ref_d;
    auto bsptr = bptr->initialize();
    auto ksptr = kptr->initialize();

    for (int x = 0; x < nobs; ++x) {
        bsptr->search(x, 4, &ref_i, &ref_d);
        ksptr->search(x, 4, &kres_i, &kres_d);
        EXPECT_EQ(kres_i, ref_i);
        EXPECT_EQ(kres_d, ref_d);
    }
}

TEST(Kmknn, Duplicates) {
    // Duplicates are another way to induce empty clusters.
    int ndim = 5;
    int nobs = 200;
    std::vector<double> data(ndim * nobs);

    auto eucdist = std::make_shared<knncolle::EuclideanDistance<double, double> >();
    knncolle_kmknn::KmknnBuilder<int, double, double> kb(eucdist);
    auto kptr = kb.build_unique(knncolle::SimpleMatrix<int, double>(ndim, nobs, data.data()));
    auto ksptr = kptr->initialize();
    std::vector<int> res_i(10);
    std::vector<double> res_d(10);

    ksptr->search(0, 10, NULL, &res_d);
    EXPECT_EQ(res_d, std::vector<double>(10));

    ksptr->search(199, 5, NULL, &res_d);
    EXPECT_EQ(res_d, std::vector<double>(5));
}

TEST(Kmknn, Empty) {
    int ndim = 5;
    int nobs = 0;
    std::vector<double> data;

    auto eucdist = std::make_shared<knncolle::EuclideanDistance<double, double> >();
    knncolle_kmknn::KmknnBuilder<int, double, double> kb(eucdist);
    auto kptr = kb.build_unique(knncolle::SimpleMatrix<int, double>(ndim, nobs, data.data()));
    auto ksptr = kptr->initialize();

    std::vector<int> res_i(10);
    std::vector<double> res_d(10);
    std::vector<double> target(ndim);
    ksptr->search(target.data(), 0, &res_i, &res_d);
    EXPECT_TRUE(res_i.empty());
    EXPECT_TRUE(res_d.empty());

    res_i.resize(10);
    res_d.resize(10);
    EXPECT_EQ(ksptr->search_all(target.data(), 0, &res_i, &res_d), 0);
    EXPECT_TRUE(res_i.empty());
    EXPECT_TRUE(res_d.empty());

    // For coverage purposes:
    ksptr->search(target.data(), 0, NULL, NULL);
}

TEST(Kmknn, Ties) {
    int ndim = 5;
    int nobs = 10;
    std::vector<double> data(ndim * nobs, 1);
    std::fill(data.begin() + nobs * ndim / 2, data.end(), 2);
    const double delta = std::sqrt(ndim);

    auto eucdist = std::make_shared<knncolle::EuclideanDistance<double, double> >();
    knncolle_kmknn::KmknnBuilder<int, double, double> kb(eucdist);
    auto kptr = kb.build_unique(knncolle::SimpleMatrix<int, double>(ndim, nobs, data.data()));
    auto ksptr = kptr->initialize();
    std::vector<int> output_indices;
    std::vector<double> output_distances;

    // Check that ties are broken in a stable manner.
    {
        ksptr->search(0, 6, &output_indices, &output_distances);
        std::vector<int> expected_i { 1, 2, 3, 4, 5, 6 };
        EXPECT_EQ(output_indices, expected_i);
        std::vector<double> expected_d { 0, 0, 0, 0, delta, delta };
        EXPECT_EQ(output_distances, expected_d);
    }

    {
        ksptr->search(4, 5, &output_indices, &output_distances);
        std::vector<int> expected_i { 0, 1, 2, 3, 5 };
        EXPECT_EQ(output_indices, expected_i);
        std::vector<double> expected_d { 0, 0, 0, 0, delta };
        EXPECT_EQ(output_distances, expected_d);
    }

    {
        ksptr->search(5, 3, &output_indices, &output_distances);
        std::vector<int> expected_i { 6, 7, 8 };
        EXPECT_EQ(output_indices, expected_i);
        std::vector<double> expected_d { 0, 0, 0 };
        EXPECT_EQ(output_distances, expected_d);
    }

    {
        ksptr->search(9, 7, &output_indices, &output_distances);
        std::vector<int> expected_i { 5, 6, 7, 8, 0, 1, 2 };
        EXPECT_EQ(output_indices, expected_i);
        std::vector<double> expected_d { 0, 0, 0, 0, delta, delta, delta };
        EXPECT_EQ(output_distances, expected_d);
    }
}

TEST(Kmknn, Aliases) {
    {
        constexpr bool test = std::is_same<knncolle_kmknn::Common<int, float>, float>::value;
        EXPECT_TRUE(test);
    }
    {
        constexpr bool test = std::is_same<knncolle_kmknn::Common<double, float>, double>::value;
        EXPECT_TRUE(test);
    }
    {
        constexpr bool test = std::is_same<knncolle_kmknn::Common<size_t, float>, float>::value;
        EXPECT_TRUE(test);
    }
    {
        constexpr bool test = std::is_same<knncolle_kmknn::Common<size_t, double>, double>::value;
        EXPECT_TRUE(test);
    }

    [[maybe_unused]] knncolle_kmknn::Initialize<int, double, double>* iptr;
    [[maybe_unused]] knncolle_kmknn::InitializeRandom<int, double, double> initr;
    [[maybe_unused]] knncolle_kmknn::InitializeKmeanspp<int, double, double> initp;
    [[maybe_unused]] knncolle_kmknn::InitializeNone<int, double, double> initn;
    [[maybe_unused]] knncolle_kmknn::InitializeVariancePartition<int, double, double> initv;

    [[maybe_unused]] knncolle_kmknn::Refine<int, double, double>* rptr;
    [[maybe_unused]] knncolle_kmknn::RefineLloyd<int, double, double> refl;
    [[maybe_unused]] knncolle_kmknn::RefineHartiganWong<int, double, double> refhw;
}
