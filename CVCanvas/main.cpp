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

//    images.push_back(cv::imread("Meduse_fake/1_reflet.png"));
//    images.push_back(cv::imread("Meduse_fake/2_reflet.png"));
//    images.push_back(cv::imread("Meduse_fake/3_reflet.png"));
//    images.push_back(cv::imread("Meduse_fake/4_reflet.png"));
//    images.push_back(cv::imread("Meduse_fake/5_reflet.png"));
    images.push_back(cv::imread("Brush/0.jpg"));
    images.push_back(cv::imread("Brush/1.jpg"));
    images.push_back(cv::imread("Brush/2.jpg"));
    images.push_back(cv::imread("Brush/3.jpg"));

    std::cout << "Fitting" << std::endl;

    
    for (int i = 0; i < images.size(); ++i)
    {
        SIFTAffineFitter fitter = SIFTAffineFitter(images[i], GT);
        fitter.fit();
        fittedImages.push_back(fitter.output);
    }

    std::cout << "Merging" << std::endl;
    
    
    cv::Mat merged = merge(fittedImages);
    
    cv::imshow("Merge", merged);
    
    cv::waitKey(0);
    
    return 0;
}

