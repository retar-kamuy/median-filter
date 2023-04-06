#include <iostream>
#include <random>
#include <cstring>
#include "include/bitonicSort.hpp"

void kernel(unsigned char a[], int len, int p, int q) {
    int d = 1 << (p - q);

    KERNEL: for (int i = 0; i < len; i++) {
        bool up = ((i >> p) & 2) == 0;

        if ((i & d) == 0 && (a[i] > a[i | d]) == up) {
            int t = a[i];
            a[i] = a[i | d];
            a[i | d] = t;
        }
    }

    for (int k = 0; k < len; k++) {
        std::cout << static_cast<int>(a[k]) << " ";
    }
    std::cout << std::endl;
}

void bitonicSort(unsigned char a[], int len, int logn) {
    MAIN: for (int i = 0; i < logn; i++) {
        SUB: for (int j = 0; j <= i; j++) {
            kernel(a, len, i, j);
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
