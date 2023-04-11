#include <iostream>
#include <random>
#include <cstring>
#include "include/bitonicSort.hpp"

void kernel(unsigned char dst[], unsigned char src[], int len, int p, int q) {
#pragma HLS ARRAY_RESHAPE variable=src type=complete dim=0
#pragma HLS ARRAY_RESHAPE variable=dst type=complete dim=0

    int d = 1 << (p - q);

    for (int i = 0; i < len; i++) {
		#pragma HLS UNROLL
    	// #pragma HLS PIPELINE

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

// void bitonicSort(unsigned char dst[], unsigned char src[], int len, int logn) {
void bitonicSort(unsigned char dst[32], unsigned char src[32]) {
	#pragma HLS ARRAY_RESHAPE variable=src type=complete dim=0
	#pragma HLS ARRAY_RESHAPE variable=dst type=complete dim=0

	int len = 32;
	int logn = 5;

	unsigned char merged[5][32];
	#pragma HLS ARRAY_RESHAPE variable=merged type=complete dim=2
	// #pragma HLS DEPENDENCE variable=dst intra RAW false
	// #pragma HLS DEPENDENCE variable=merged intra RAW false

    LOOP_MAIN: for (int i = 0; i < logn; i++) {
    	unsigned char sorted[5][32];
		#pragma HLS ARRAY_RESHAPE variable=sorted type=complete dim=0
		// #pragma HLS DEPENDENCE variable=sorted intra RAW false
    	LOOP_SUB: for (int j = 0; j < logn; j++) {
    		// #pragma HLS PIPELINE II=1
            if (j <= i) {
            	if (i == 0 && j == 0) {
            		kernel(sorted[i], src, len, i, j);
            	} else if (i == logn - 1 && j == logn - 1) {
            		kernel(dst, sorted[j - 1], len, i, j);
            	} else if (j == i) {
            		kernel(merged[i], sorted[j - 1], len, i, j);
            	} else {
            		kernel(sorted[j], sorted[j - 1], len, i, j);
            	}
            }
        }
    }
}

void bitonicSortWrapper(
    unsigned char dst[32], unsigned char src[32]
) {
    // bitonicSort(dst, src, 32, 5);
	bitonicSort(dst, src);
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
