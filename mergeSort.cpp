void merge(unsigned char array[], int low, int middle, int high) {
    int n1 = middle - low + 1;  // number of elements in first subarray
    int n2 = high - middle;     // number of elements in second subarray

    // create temporary subarrays
#ifdef __SYNTHESIS__
    unsigned char lowerArray[5];
    unsigned char higherArray[5];
    #pragma HLS ARRAY_RESHAPE variable=lowerArray type=complete dim=1
    #pragma HLS ARRAY_RESHAPE variable=higherArray type=complete dim=1
#else
    unsigned char lowerArray[n1];   // array[low..middle]
    unsigned char higherArray[n2];  // array[middle+1..r]
#endif

    // copy data to subarrays lowerArray and higherArray
    copyL: for (int i = 0; i < n1; i++) {
        #pragma HLS unroll
        lowerArray[i] = array[low + i];
    }
    copyR: for (int j = 0; j < n2; j++) {
        #pragma HLS unroll
        higherArray[j] = array[middle + 1 + j];
    }

    // merge the two arrays
    int l = 0;  // index of lowerArray
    int h = 0;  // index of higherArray
    int m = low;    // index of merged array

    mergeLR: while (l < n1 && h < n2) {
        if (lowerArray[l] <= higherArray[h]) {
            array[m] = lowerArray[l];
            l++;
        } else {
            array[m] = higherArray[h];
            h++;
        }
        m++;
    }

    mergeL: while (l < n1) {
        array[m] = lowerArray[l];
        l++;
        m++;
    }

    mergeR: while (h < n2) {
        array[m] = higherArray[h];
        h++;
        m++;
    }
}

void mergeSort(unsigned char array[], int low, int high) {
    if (low < high) {
        // avoids overflow for large low and high
        int middle = low + (high - low) / 2;

        mergeSort(array, low, middle);
        mergeSort(array, middle + 1, high);
        merge(array, low, middle, high);
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
