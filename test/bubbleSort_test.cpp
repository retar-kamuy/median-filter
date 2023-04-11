#include <random>
#include <gtest/gtest.h>
#include "include/bubbleSort.hpp"

#define LOGN 5
#define N 1 << LOGN

TEST(MyLibraryTest, Function1Test) {
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::uniform_int_distribution<> rand(0, 255);

    unsigned char a0[N];
    for (int i = 0; i < N; i++) {
        a0[i] = rand(engine);
    }

    for (int k = 0; k < sizeof(a0); k++) {
        std::cout << static_cast<int>(a0[k]) << " ";
    }
    std::cout << std::endl;

    bubbleSort(a0);

    for (int k = 0; k < sizeof(a0); k++) {
        std::cout << static_cast<int>(a0[k]) << " ";
    }
    std::cout << std::endl;
}
