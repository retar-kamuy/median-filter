#include <iostream>
#include <cstring>
#include <cassert>
#include "include/medianFilter.hpp"
#include "include/bitonicSort.hpp"

void get8NeighborCoordinates(
    int neighbors[], int width, int height, int center
) {
    neighbors[0] = center - width - 1;
    neighbors[1] = center - width;
    neighbors[2] = center - width + 1;
    neighbors[3] = center         - 1;
    neighbors[4] = center         + 1;
    neighbors[5] = center + width - 1;
    neighbors[6] = center + width;
    neighbors[7] = center + width + 1;

    for (int i = 0; i < 8; i++) {
        assert(neighbors[i] >= 0);
        if (neighbors[i] >= width * height) {
            std::cout << "neighbors[" << i << "] = " << neighbors[i]
                      << ", center = " << center << std::endl;
        }
        assert(neighbors[i] < width * height);
    }
}

void medianFilter(
    unsigned char dst[],
    int width, int height, unsigned char src[]
) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int center = (j + 1) * (width + 2) + (i + 1);

            assert(center >= 0);
            assert(center < (width + 2) * (height + 2));

            int neighbors[8];

            // std::cout << "j = " << j << ", i =" << i << std::endl;
            get8NeighborCoordinates(neighbors, width + 2, height + 2, center);

            unsigned char target[16];
            for (int k = 0; k < 16; k++) {
                target[k] = 255;
            }
            target[0] = src[center];
            for (int k = 1; k < 9; k++) {
                target[k] = src[neighbors[k - 1]];
            }

            bitonicSort(target, 16);

            dst[j * width + i] = target[4];
        }
    }
}
