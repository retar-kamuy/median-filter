#include <cstring>
#include "include/bubbleSort.hpp"

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
