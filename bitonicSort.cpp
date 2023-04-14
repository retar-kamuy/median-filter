#include "include/common.hpp"
#include "include/bitonicSort.hpp"

#ifdef __SYNTHESIS__
void kernel(unsigned char src[], int p, int q, unsigned char dst[]) {
#pragma HLS ARRAY_RESHAPE variable=src type=complete dim=0
#pragma HLS ARRAY_RESHAPE variable=dst type=complete dim=0

    int d = 1 << (p - q);

    for (int i=0; i < SORT_SIZE; i++) {
#pragma HLS UNROLL
        bool up = ((i >> p) & 2) == 0;

        if ((i & d) == 0 && (src[i] > src[i | d]) == up) {
            dst[i] = src[i | d];
            dst[i | d] = src[i];
        } else {
            dst[i] = src[i];
        }
    }
}
#else
void kernel(unsigned char a[], int len, int p, int q) {
    int d = 1 << (p - q);

    for (int i = 0; i < len; i++) {
        bool up = ((i >> p) & 2) == 0;

        if ((i & d) == 0 && (a[i] > a[i | d]) == up) {
            unsigned char t = a[i];
            a[i] = a[i | d];
            a[i | d] = t;
        }
    }
}
#endif  // __SYNTHESIS__

#ifdef __SYNTHESIS__
void bitonicSort(unsigned char src[SORT_SIZE], unsigned char dst[SORT_SIZE]) {
#pragma HLS ARRAY_RESHAPE variable=src type=complete dim=0
#pragma HLS ARRAY_RESHAPE variable=dst type=complete dim=0

    unsigned char in[SORT_SIZE];
    unsigned char out[SORT_SIZE];

#pragma HLS ARRAY_RESHAPE variable=in type=complete dim=0
#pragma HLS ARRAY_RESHAPE variable=out type=complete dim=0

    LOOP_BITONIC_MAIN: for (int i=0; i < SORT_LOG_SIZE; i++) {
        LOOP_BITONIC_SUB: for (int j=0; j < SORT_LOG_SIZE; j++) {
#pragma HLS PIPELINE II=1
            if (j <= i) {
                for (int k=0; k < SORT_SIZE; k++) {
#pragma HLS UNROLL
                    in[k] = (j == 0 && i == 0) ? src[i] : out[k];
                }
                kernel(in, i, j, out);

                for (int k=0; k < SORT_SIZE; k++) {
#pragma HLS UNROLL
                    dst[k] = out[k];
                }
            }
        }
    }
}
#else
void bitonicSort(unsigned char a[], int len) {
    int logn = log2(len);

    for (int i=0; i < logn; i++) {
        for (int j=0; j <= i; j++) {
            kernel(a, len, i, j);
        }
    }
}
#endif  // __SYNTHESIS__
