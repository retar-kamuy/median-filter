#include <iostream>
#include <random>
#include <cstring>
#include "include/bitonicSort.hpp"

void kernel(unsigned char dst[], unsigned char src[], int len, int p, int q) {
#pragma HLS ARRAY_RESHAPE variable=src type=complete dim=0
#pragma HLS ARRAY_RESHAPE variable=dst type=complete dim=0

	int d = 1 << (p - q);

    LOOP_KERNEL: for (int i = 0; i < len; i++) {
#pragma HLS UNROLL
        bool up = ((i >> p) & 2) == 0;

        if ((i & d) == 0 && (src[i] > src[i | d]) == up) {
            dst[i] = src[i | d];
            dst[i | d] = src[i];
        } else {
        	dst[i] = src[i];
        }
    }

    for (int k = 0; k < len; k++) {
        std::cout << static_cast<int>(src[k]) << " ";
    }
    std::cout << std::endl;
}

void bitonicSort(unsigned char dst[], unsigned char src[], int len, int logn) {
    unsigned char buf[32];

    memcpy(dst, src, len);

    LOOP_MAIN: for (int i = 0; i < logn; i++) {
        // SUB: for (int j = 0; j <= i; j++) {
        LOOP_SUB: for (int j = 0; j < logn; j++) {
        	if(j <= i) {
                memcpy(buf, dst, len);
        		kernel(dst, buf, len, i, j);
        	}
        }
    }
}

void bitonicSortWrapper(
    unsigned char* dst, unsigned char src
) {
    bool end = false;
    unsigned char srcBuf[32], dstBuf[32];

    LOOP_SRCBUF: for (int i = 0; i < 32; i++) {
        srcBuf[i] = src;

        if (i == 31) {
            bitonicSort(dstBuf, srcBuf, 32, 5);
            end = true;
        }
    }

    if (end == true) {
        LOOP_DSTBUF: for (int i = 0; i <32; i++) {
            *dst = dstBuf[i];
        }
    }
}

// int main(void) {
//     int logn = 5, n = 1 << logn;
// 
//     unsigned char a0[n];
//     std::random_device seed_gen;
//     std::mt19937 engine(seed_gen());
//     std::uniform_int_distribution<> rand(0, 255);
//     for (int i = 0; i < n; i++) {
//         a0[i] = rand(engine);
//     }
// 
//     for (int k = 0; k < sizeof(a0); k++) {
//         std::cout << static_cast<int>(a0[k]) << " ";
//     }
//     std::cout << std::endl;
// 
//     bitonicSort(a0, n, logn);
// 
//     std::cout << std::endl;
// 
//     for (int k = 0; k < sizeof(a0); k++) {
//         std::cout << static_cast<int>(a0[k]) << " ";
//     }
//     std::cout << std::endl;
// 
//     return 0;
// }
