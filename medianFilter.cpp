#include <cstring>
#include "include/medianFilter.hpp"
#include "include/bitonicSort.hpp"

void get8NeighborCoordinates(int width, int center, int *neighbors) {
    neighbors[0] = center - width - 1;
    neighbors[1] = center - width;
    neighbors[2] = center - width + 1;
    neighbors[3] = center         - 1;
    neighbors[4] = center         + 1;
    neighbors[5] = center + width - 1;
    neighbors[6] = center + width;
    neighbors[7] = center + width + 1;
}

void medianFilter(
    int width, int height,
    unsigned char src[], unsigned char dst[]
) {
    for (int i = 0; i < width- 2; i++) {
        for (int j = 0; j < height - 2; j++) {
            int center = (j + 1) * (width + 2) + i + 1;
            int neighbors[8];

            get8NeighborCoordinates(width, center, neighbors);

            unsigned char target[9];
            target[0] = center;
            for (int k = 1; k < 9; k++) {
                target[k] = src[neighbors[k - 1]];
            }
            bitonicSort(target, 9);

            dst[j * width + i] = target[4];
        }
    }
}
