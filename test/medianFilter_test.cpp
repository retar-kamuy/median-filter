#include <random>
#include <gtest/gtest.h>
#include "include/common.hpp"
#include "include/medianFilter.hpp"

#define N 32

#ifndef __SYNTHESIS__
TEST(medianFilter, FunctionTest) {
#else
int main(void) {
#endif  // __SYNTHESIS__
    int width = 516;
    int height = 516;

    // std::random_device seed_gen;
    // std::mt19937 engine(seed_gen());
    // std::uniform_int_distribution<> rand(0, 8);

    unsigned char src[(MAX_IMAGE_WIDTH+2)*(MAX_IMAGE_HEIGHT+2)];
    int t = 0;
    for (int i = 0; i < width*height; i++) {
        unsigned char color;
        if (t < 4) {
            color = 0;
        } else if (t > 4) {
            color = 255;
        } else {
            color = 127;
        }
        src[i] = color;
        t = t == 8 ? 0 : t + 1;
    }

    unsigned char dst[MAX_IMAGE_WIDTH*MAX_IMAGE_HEIGHT];
    medianFilter(src, width-2, height-2, dst);

#ifndef __SYNTHESIS__
    for (int i = 0; i < (width-2)*(height-2); i++) {
        ASSERT_EQ(dst[i], 127);
    }
#else
    bool diff = false;
    for (int i = 0; i < (width-2)*(height-2); i++) {
        if (dst[i] != 127)  diff = true;
    }
    return (diff?1:0);
#endif  // __SYNTHESIS__
}

#ifndef __SYNTHESIS__
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif  // __SYNTHESIS__
