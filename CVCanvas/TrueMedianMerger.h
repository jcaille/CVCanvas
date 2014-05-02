// Theophile Dalens 2014

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class TrueMedianMerger{
	std::vector<cv::Mat> images;

public:
	TrueMedianMerger(std::vector<cv::Mat> images);
	cv::Mat output;

};