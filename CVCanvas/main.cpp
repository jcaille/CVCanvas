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

#include "UserAffineFitter.h"
#include "MedianMerger.h"

int main(int argc, const char * argv[])
{
    cv::Mat GT = cv::imread("Brush/GroundTruth.png");
    
    std::vector<cv::Mat> images;
    std::vector<cv::Mat> fittedImages;

    images.push_back(cv::imread("Brush/0.jpg"));
    images.push_back(cv::imread("Brush/1.jpg"));
    images.push_back(cv::imread("Brush/2.jpg"));
    images.push_back(cv::imread("Brush/3.jpg"));

    for (int i = 0; i < images.size(); ++i)
    {
        UserAffineFitter fitter = UserAffineFitter(GT.size(), images[i]);
        fitter.fit();
        fittedImages.push_back(fitter.output);
        cv::imshow("Image", fitter.output);
        cv::waitKey(0);
    }

    std::cout << "Merging" << std::endl;
    
    
    cv::Mat merged = merge(fittedImages);
    
    cv::imshow("Merge", merged);
    
    cv::waitKey(0);
    
    return 0;
}

