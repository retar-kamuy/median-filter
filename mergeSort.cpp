void merge(unsigned char dst[], unsigned char src[], int left, int middle, int right) {
    int n1 = middle - left + 1;  // number of elements in first subarray
    int n2 = right - middle;      // number of elements in second subarray

    // create temporary subarrays
#ifdef __SYNTHESIS__
    int L[5];
    int R[5];
#else
    int L[n1];  // array[left..middle]
    int R[n2];  // array[middle+1..r]
#endif

    // copy data to subarrays L and R
    copyL: for (int i = 0; i < n1; i++) {
        #pragma HLS unroll
        L[i] = src[left + i];
    }
    copyR: for (int j = 0; j < n2; j++) {
        #pragma HLS unroll
        R[j] = src[middle + 1 + j];
    }

    // merge the two arrays
    int l = 0;    // index of L
    int r = 0;    // index of R
    int m = left;    // index of merged array

    mergeLR: while (l < n1 && r < n2) {
        if (L[l] <= R[r]) {
            dst[m] = L[l];
            l++;
        } else {
            dst[m] = R[r];
            r++;
        }
        m++;
    }

    mergeL: while (l < n1) {
        dst[m] = L[l];
        l++;
        m++;
    }

    mergeR: while (r < n2) {
        dst[m] = R[r];
        r++;
        m++;
    }
}

void mergeSort(unsigned char dst[], unsigned char src[], int left, int right) {
    if (left < right) {
        // avoids overflow for large left and h
        int middle = left + (right - left) / 2;
        unsigned char purged[9];

        mergeSort(purged, src, left, middle);
        mergeSort(purged, src, middle + 1, right);
        merge(dst, purged, left, middle, right);
    }
}

// int main(void) {
//     int array[10] = {3, 6, 1, 7, 2, 0, 4, 5, 9, 8};
// 
//     std::cout << "       array: " << std::endl;
//     for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
//         printf("%d ", array[i]);
//     }
//     printf("\n");
// 
//     mergeSort(array, 0, sizeof(array) / sizeof(array[0]) - 1);
// 
//     printf("sorted array: ");
//     for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
//         printf("%d ", array[i]);
//     }
//     printf("\n");
// 
//     return 0;
// }
