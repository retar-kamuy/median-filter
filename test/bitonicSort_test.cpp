#include <random>
#include <gtest/gtest.h>    // NOLINT
#include "include/bitonicSort.hpp"

#define N 32

TEST(BitonicSortTest, FunctionTest) {
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::uniform_int_distribution<> rand(0, 255);

    unsigned char a0[N];
    for (int i = 0; i < N; i++) {
        a0[i] = rand(engine);
    }

    for (int k = 0; k < N; k++) {
        std::cout << static_cast<int>(a0[k]) << " ";
    }
    std::cout << std::endl;

    bitonicSort(a0, N);

    for (int k = 0; k < N - 1; k++) {
        ASSERT_LE(a0[k], a0[k + 1]);
        std::cout << static_cast<int>(a0[k]) << " ";
    }
    std::cout << static_cast<int>(a0[N - 1]) << std::endl;
}
