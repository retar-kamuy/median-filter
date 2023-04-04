#include <cstring>
#include "include/medianFilter.hpp"

template <typename T>
int arrayLength(T array) {
    return sizeof(&array) / sizeof(array[0]);
}

void bubbleSort(unsigned char *src, unsigned char *dst) {
    int length = arrayLength(src);

    memcpy(dst, src, length);

    for (int i = 0; i < length - 1; i++) {
        for (int j = i; j < length; j++) {
            if (dst[i] > dst[j]) {
                unsigned char temp = dst[i];
                dst[i] = dst[j];
                dst[j] = temp;
            }
        }
    }
}

void get8NeighborCoordinates(
    int width, int height, int center, int *neighbors
) {
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
    unsigned char *src, unsigned char *dst
) {
    for (int i = 0; i < width- 2; i++) {
        for (int j = 0; j < height - 2; j++) {
            int center = (j + 1) * (width + 2) + i + 1;
            int neighbors[8];

            get8NeighborCoordinates(width, height, center, neighbors);

            unsigned char target[9];
            target[0] = center;
            for (int k = 1; k < 9; k++) {
                target[k] = src[neighbors[k]];
            }
            unsigned char sorted[9];
            bubbleSort(target, sorted);

            dst[j * width + i] = sorted[4];
        }
    }
}
