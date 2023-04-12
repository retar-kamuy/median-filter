#include <cstring>
#include "include/bubbleSort.hpp"

void bubbleSort(unsigned char a[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = i; j < len; j++) {
            if (a[i] > a[j]) {
                unsigned char t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}
