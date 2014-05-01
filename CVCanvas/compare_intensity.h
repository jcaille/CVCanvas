///@author Jean Caille, Theophile Dalens, 2014

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/**
 *  Creates a file containing the values of each pixel for the two given matrices
 *
 *  @param imx            The first matrix
 *  @param imy            The second matrix
 *  @param outputFileName Path to the output file
 */
void compare(const cv::Mat& imx, const cv::Mat& imy, const std::string& outputFilePath);
