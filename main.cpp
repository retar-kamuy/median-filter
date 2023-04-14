#include <opencv2/opencv.hpp>
#include "include/medianFilter.hpp"

cv::Mat imread(const std::string &filename) {
    cv::Mat orginalImage = cv::imread(filename, cv::IMREAD_UNCHANGED);
    std::cout << "Read '" << filename
              << "'(" << orginalImage.rows << " x " << orginalImage.cols << ")"
              << std::endl;

    return orginalImage;
}

void imwrite(const std::string &filename, cv::Mat img) {
    cv::imwrite(filename, img);
    std::cout << "Write '" << filename
              << "'(" << img.rows << " x " << img.cols << ")"
              << std::endl;
}

void padding(
    const cv::Mat &src, cv::Mat *dst,
    int padding_top, int padding_bottom, int padding_right, int padding_left
) {
    cv::copyMakeBorder(src, *dst,
        padding_top, padding_bottom, padding_right, padding_left,
        cv::BORDER_CONSTANT, 0);
    std::cout << "Padding top:" << padding_top << " bottom: " << padding_bottom
              << " right: " << padding_right << " left: " << padding_left
              << " (" << dst->rows << " x " << dst->cols << ")"
              << std::endl;
}

void matToUChar(const cv::Mat &src, unsigned char *dst) {
    for (int col = 0; col < src.cols; col++) {
        for (int row = 0; row < src.rows; row++) {
            // mat.dat is 3 channels(Blue, Green, Red)
            // dst is stored Blue channel only
            dst[col * src.rows + row] = src.data[col * (src.rows) + row];
        }
    }
}

void uCharToMat(
    int src_width, int src_height,
    unsigned char *src, const cv::Mat &dst
) {
    for (int i = 0; i < src_width; i++) {
        int src_col = i * src_height;
        int dst_col = i * src_height * 3;
        for (int j = 0; j < src_height; j++) {
            // 3 channels of mat.data are stored same data
            // dst is gray scale image
            for (int k = 0; k < 3; k++) {
                dst.data[dst_col + j * 3 + k] = src[src_col + j];
            }
        }
    }
}

int main(void) {
    cv::Mat originalImage = imread("data/Lenna_noise.png");

    cv::Mat grayScaled;
    cv::cvtColor(originalImage, grayScaled, cv::COLOR_RGB2GRAY);

    cv::Mat paddingImage;
    padding(grayScaled, &paddingImage, 1, 1, 1, 1);

    unsigned char paddingData[paddingImage.cols * paddingImage.rows];
    matToUChar(paddingImage, paddingData);

    unsigned char filteredData[grayScaled.cols * grayScaled.rows];
    medianFilter(grayScaled.cols, grayScaled.rows, paddingData, filteredData);
    std::cout << "Median filter end" << std::endl;

    cv::Mat filteredImage;
    originalImage.copyTo(filteredImage);
    uCharToMat(grayScaled.cols, grayScaled.rows, filteredData, filteredImage);

    imwrite("Lenna_output.png", filteredImage);

    return 0;
}
