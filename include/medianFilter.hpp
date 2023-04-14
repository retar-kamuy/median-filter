#ifndef MEDIANFILTER_HPP_
#define MEDIANFILTER_HPP_

#ifdef __SYNTHESIS__
void medianFilter(
    hls::stream<unsigned char> &src,
    int width,
    int height,
    hls::stream<unsigned char> &dst
);
#else
void medianFilter(
    unsigned char src[],
    int width,
    int height,
    unsigned char dst[]
);
#endif  // __SYNTHESIS__

#endif  // MEDIANFILTER_HPP_
