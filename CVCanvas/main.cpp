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

#include "AffineFitter.h"

int main(int argc, const char * argv[])
{
    cv::Mat I = cv::imread("/Users/jean/Devel/SI343/CVCanvas/Images/Joconde2.jpg");
    cv::Mat J = cv::imread("/Users/jean/Devel/SI343/CVCanvas/Images/Joconde.jpg");
    
    AffineFitter fitter = AffineFitter(cv::Size(396, 600), J);
    std::vector<cv::Point2f> corners = fitter.userDefinedInitialCorners();
    fitter.fit(corners);
    
    AffineFitter fitter2 = AffineFitter(cv::Size(396, 600), I);
    corners = fitter2.userDefinedInitialCorners();
    fitter2.fit(corners);
    
    cv::imshow("First image", fitter.output);
    cv::imshow("Second image", fitter2.output);
    cv::waitKey(0);
    
    return 0;
}

