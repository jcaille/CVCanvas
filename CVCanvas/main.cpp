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
#include "TrueMedianMerger.h"


int main(int argc, const char * argv[])
{
    std::vector<cv::Mat> images;
    std::vector<cv::Mat> fittedImages;

//    images.push_back(cv::imread("Meduse_fake/1_reflet.png"));
//    images.push_back(cv::imread("Meduse_fake/2_reflet.png"));
//    images.push_back(cv::imread("Meduse_fake/3_reflet.png"));
//    images.push_back(cv::imread("Meduse_fake/4_reflet.png"));
//    images.push_back(cv::imread("Meduse_fake/5_reflet.png"));
//    images.push_back(cv::imread("Brush/0.jpg"));
    images.push_back(cv::imread("Brush/1.jpg"));
    images.push_back(cv::imread("Brush/2.jpg"));
    images.push_back(cv::imread("Brush/3.jpg"));

    std::cout << "Fitting" << std::endl;

    
    for (unsigned i = 0; i < images.size(); ++i)
    {
        SIFTAffineFitter fitter = SIFTAffineFitter(images[i], images[0]);
        fitter.fit();
        fittedImages.push_back(fitter.output);
    }
	
	for (unsigned i=0; i<images.size(); i++)
	{
		std::stringstream ss;
		ss << i;
		cv::imshow(ss.str(),fittedImages[i]);
	}
//	cv::waitKey();

    std::cout << "Merging" << std::endl;
    
    
    cv::Mat merged = merge(fittedImages);
    
    cv::imshow("Merge", merged);
    cv::imwrite("/tmp/medianMerge.png", merged);
    
	TrueMedianMerger tmm(fittedImages);
	cv::imshow("True Merge", tmm.output);
    cv::imwrite("/tmp/trueMerge.png", tmm.output);

    cv::waitKey();
    
    return 0;
}

