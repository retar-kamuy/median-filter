#include <iostream>
#include <cmath>
#include "include/bitonicSort.hpp"

#ifdef __SYNTHESIS__

#define N 32

void kernel(unsigned char dst[], unsigned char src[], int p, int q) {
#pragma HLS ARRAY_RESHAPE variable=src type=complete dim=0  // NOLINT
#pragma HLS ARRAY_RESHAPE variable=dst type=complete dim=0  // NOLINT

    int d = 1 << (p - q);

    unsigned char in[N];
    unsigned char out[N];
#pragma HLS ARRAY_RESHAPE variable=in type=complete dim=0   // NOLINT
#pragma HLS ARRAY_RESHAPE variable=out type=complete dim=0  // NOLINT

    // memcpy(out, src, N);
    for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
        out[i] = src[i];
    }

    LOOP_KERNEL: for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
        // memcpy(in, out, N);
        for (int j = 0; j < N; j++) {
#pragma HLS UNROLL
            in[j] = out[j];
        }

        bool up = ((i >> p) & 2) == 0;

        if ((i & d) == 0 && (in[i] > in[i | d]) == up) {
            out[i] = in[i | d];
            out[i | d] = in[i];
        } else {
            out[i] = in[i];
        }
    }

    // memcpy(dst, out, N);
    for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
        dst[i] = out[i];
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

// #define LOGN static_cast<int>(log2(N))
#define LOGN 5

void bitonicSortCore(unsigned char dst[N], unsigned char src[N]) {
#pragma HLS ARRAY_RESHAPE variable=src type=complete dim=0  // NOLINT
#pragma HLS ARRAY_RESHAPE variable=dst type=complete dim=0  // NOLINT

    unsigned char merged[LOGN][N];
#pragma HLS ARRAY_RESHAPE variable=merged type=complete dim=2   // NOLINT

    LOOP_MAIN: for (int i = 0; i < LOGN; i++) {
        unsigned char sorted[LOGN][N];
#pragma HLS ARRAY_RESHAPE variable=sorted type=complete dim=0   // NOLINT
        LOOP_SUB: for (int j = 0; j < LOGN; j++) {
            if (j <= i) {
                if (i == 0 && j == 0) {
                    kernel(merged[i], src, i, j);
                } else if (j == 0) {
                    kernel(sorted[j], merged[i - 1], i, j);
                } else if (i == LOGN - 1 && j == LOGN - 1) {
                    kernel(dst, sorted[j - 1], i, j);
                } else if (j == i) {
                    kernel(merged[i], sorted[j - 1], i, j);
                } else {
                    kernel(sorted[j], sorted[j - 1], i, j);
                }
            }
        }
    }
}

void bitonicSort(unsigned char a[], int len) {
    unsigned char t[N];
    // memcpy(t, a, len);
    for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
        t[i] = a[i];
    }

    bitonicSortCore(a, t);
}
#else
void bitonicSort(unsigned char a[], int len) {
    int logn = log2(len);

    for (int i = 0; i < logn; i++) {
        for (int j = 0; j <= i; j++) {
            kernel(a, len, i, j);
        }
    }
}
#endif  // __SYNTHESIS__
