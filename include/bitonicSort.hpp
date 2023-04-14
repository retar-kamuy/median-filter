#ifndef BITONICSORT_HPP_
#define BITONICSORT_HPP_

#ifdef __SYNTHESIS__
    void bitonicSort(unsigned char src[], unsigned char dst[]);
#else
    void bitonicSort(unsigned char a[], int len);
#endif  // __SYNTHESIS__

#endif  // BITONICSORT_HPP_
