void kernel(unsigned char a[], int low, int middle, int high) {
    int n1 = middle - low + 1;  // number of elements in first subarray
    int n2 = high - middle;     // number of elements in second subarray

    // create temporary subarrays
    unsigned char lower[n1];   // a[low..middle]
    unsigned char higher[n2];  // a[middle+1..r]

    // copy data to subarrays lower and higher
    copyL: for (int i = 0; i < n1; i++) {
        lower[i] = a[low + i];
    }
    copyR: for (int j = 0; j < n2; j++) {
        higher[j] = a[middle + 1 + j];
    }

    // merge the two arrays
    int l = 0;  // index of lower
    int h = 0;  // index of higher
    int m = low;    // index of merged array

    mergeLR: while (l < n1 && h < n2) {
        if (lower[l] <= higher[h]) {
            a[m] = lower[l];
            l++;
        } else {
            a[m] = higher[h];
            h++;
        }
        m++;
    }

    mergeL: while (l < n1) {
        a[m] = lower[l];
        l++;
        m++;
    }

    mergeR: while (h < n2) {
        a[m] = higher[h];
        h++;
        m++;
    }
}

void mergeSort(unsigned char a[], int low, int high) {
    if (low < high) {
        // avoids overflow for large low and high
        int middle = low + (high - low) / 2;

        mergeSort(a, low, middle);
        mergeSort(a, middle + 1, high);
        kernel(a, low, middle, high);
    }
}
