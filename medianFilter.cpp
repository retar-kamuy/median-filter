#ifdef __SYNTHESIS__
#include "hls_stream.h"
#endif  // __SYNTHESIS__
#include "include/common.hpp"
#include "include/medianFilter.hpp"
#include "include/bitonicSort.hpp"

void get8NeighborCoordinates(
    int neighbors[], int width, int height, int center
) {
    neighbors[0] = center - width - 1;
    neighbors[1] = center - width;
    neighbors[2] = center - width + 1;
    neighbors[3] = center         - 1;
    neighbors[4] = center         + 1;
    neighbors[5] = center + width - 1;
    neighbors[6] = center + width;
    neighbors[7] = center + width + 1;

    for (int i = 0; i < 8; i++) {
        assert(neighbors[i] >= 0);
        assert(neighbors[i] < width * height);
    }
}

struct window {
    unsigned char pix[3][3];
};

#ifdef __SYNTHESIS__
void medianFilter(
   hls::stream<unsigned char> &src,
   // unsigned char src[],
   int width,
   int height,
   hls::stream<unsigned char> &dst
   // unsigned char dst[]
) {
    #pragma HLS DATAFLOW
    //#pragma HLS PIPELINE II=1

    // unsigned char LineBuffer[3][514];
    // #pragma HLS ARRAY_PARTITION variable=LineBuffer dim=1 complete
    // #pragma HLS DEPENDENCE variable=LineBuffer inter false
    // #pragma HLS DEPENDENCE variable=LineBuffer intra false

    // Sliding window of [FILTER_V_SIZE][FILTER_H_SIZE] pixels
    window Window;

    unsigned col_ptr = 0;
    unsigned ramp_up = width*((FILTER_V_SIZE-1)/2)+(FILTER_H_SIZE-1)/2;
    unsigned num_pixels = width*height;
    unsigned num_iterations = num_pixels + ramp_up;

    // LOOP_PIXEL: for (int i = 0; i < 514 * 514 ; i++) {
    LOOP_PIXEL: for (int i = 0; i < 9/*264196*/ ; i++) {
        #pragma HLS PIPELINE II=1
        //unsigned char new_pixel = (i < width*height) ? src.read() : 0;
        unsigned char new_pixel = (i < width*height) ? src.read() : 0;

        for (int m = 0; m < FILTER_V_SIZE; m++) {
            for (int n = 0; n < FILTER_H_SIZE; n++) {
                // #pragma HLS UNROLL
                //Window.pix[m][n] = Window.pix[m][n+1];
            }
            // Window.pix[m][FILTER_H_SIZE-1] = (m < FILTER_V_SIZE-1) ?
            //     LineBuffer[m][col_ptr] : new_pixel;
            //Window.pix[m][FILTER_H_SIZE-1] = new_pixel;
        }

        // for (int k = 0; k < FILTER_V_SIZE-2; k++) {
        // #pragma HLS UNROLL
        //     LineBuffer[k][col_ptr] = LineBuffer[k+1][col_ptr];
        // }
        // LineBuffer[FILTER_V_SIZE-2][col_ptr] = new_pixel;

        // Update the line buffer column pointer
        if (col_ptr == (width-1)) {
            col_ptr = 0;
        } else {
            col_ptr++;
        }

        //if (i >= ramp_up) {
            // nsigned char target[SORT_SIZE], buf[SORT_SIZE];
            // #pragma HLS ARRAY_RESHAPE variable=target type=complete dim=0
            // for (int k = 1; k < SORT_SIZE; k++) {
            //     #pragma HLS UNROLL
            //     if (k < FILTER_V_SIZE * FILTER_H_SIZE) {
            //         target[k] = Window.pix[k / FILTER_V_SIZE][k % FILTER_H_SIZE];
            //     } else {
            //         target[k] = 255;
            //     }
            // }
            // bitonicSort(target, buf);
            // dst.write(buf[4]);
            // dst.write(Window.pix[0][0]);
        	 dst.write(new_pixel);
        //}
    }
}
#else
void medianFilter(
    unsigned char src[],
    int width,
    int height,
    unsigned char dst[]
) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int center = (j + 1) * (width + 2) + (i + 1);

            assert(center >= 0);
            assert(center < (width + 2) * (height + 2));

            int neighbors[8];

            get8NeighborCoordinates(neighbors, width + 2, height + 2, center);

            unsigned char target[16];

            target[0] = src[center];
            for (int k = 1; k < 16; k++) {
                if (k < 9) {
                    target[k] = src[neighbors[k - 1]];
                } else {
                    target[k] = 255;
                }
            }
            bitonicSort(target, 16);
            dst[j * width + i] = target[4];
        }
    }
}
#endif  // __SYNTHESIS__
