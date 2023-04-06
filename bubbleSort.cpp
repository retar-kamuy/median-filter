#include <cstring>
#include "include/bubbleSort.hpp"

template <typename T>
int arrayLength(T array) {
    return sizeof(&array) / sizeof(array[0]);
}

void bubbleSort(unsigned char array[]) {
    int length = arrayLength(array);

    for (int i = 0; i < length - 1; i++) {
        for (int j = i; j < length; j++) {
            if (array[i] > array[j]) {
                unsigned char temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}
