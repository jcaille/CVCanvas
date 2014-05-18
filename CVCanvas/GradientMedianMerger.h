// Theophile Dalens 2014

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class GradientMedianMerger{
	std::vector<cv::Mat> images;

public:
	GradientMedianMerger(std::vector<cv::Mat> images);
	cv::Mat output;

};