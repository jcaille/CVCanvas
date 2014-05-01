//
//  main.cpp
//  CVCanvas
//
//  Created by Jean Caillé on 10/03/2014.
//  Copyright (c) 2014 Jcaille. All rights reserved.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>
#include "UserAffineFitter.h"
#include "SIFTAffintFitter.h"
#include "compare_intensity.h"
#include "MedianMerger.h"

int main(int argc, const char * argv[])
{
	cv::Mat GT = cv::imread("Brush/GroundTruth.png");

    std::vector<cv::Mat> images;
    std::vector<cv::Mat> fittedImages;

//    images.push_back(cv::imread("Meduse_fake/1.png"));
    images.push_back(cv::imread("Brush/1.jpg"));
//    images.push_back(cv::imread("Brush/2.jpg"));
//    images.push_back(cv::imread("Screen/3.jpg"));
//    images.push_back(cv::imread("Screen/4.jpg"));
//    images.push_back(cv::imread("Screen/5.jpg"));

    std::cout << "Fitting" << std::endl;
	
	cv::Mat im;
    for (unsigned i = 0; i < images.size(); ++i)
    {
        SIFTAffineFitter fitter = SIFTAffineFitter(images[i], GT);
        fitter.fit();
        fittedImages.push_back(fitter.output);
		cvtColor(fitter.output, im, CV_BGR2GRAY);
    }
	cv::Mat GTBW;
	cv::cvtColor(GT, GTBW, CV_BGR2GRAY);
	compare(GTBW, im, "compare2.txt");
	std::cout << "Merging" << std::endl;
    
    
    cv::Mat merged = merge(fittedImages);
    
    cv::imshow("Merge", merged);
    
    cv::waitKey(0);
    
    return 0;
}

