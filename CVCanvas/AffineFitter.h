//
//  AffineFitter.h
//  CVCanvas
//
//  Created by Jean Caillé on 10/03/2014.
//  Copyright (c) 2014 Jcaille. All rights reserved.
//

#ifndef __CVCanvas__AffineFitter__
#define __CVCanvas__AffineFitter__

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class AffineFitter {
    cv::Mat input;
    cv::Size outputSize;
    bool isDefiningCorners;
    
    static void mouseCallback( int event, int x, int y, int flags, void* param );

public:
    cv::Mat output;
    AffineFitter(cv::Size outputSize, cv::Mat inputMatrix);
    std::vector<cv::Point2f> userDefinedInitialCorners();
    void fit(std::vector<cv::Point2f>corners);

};

#endif /* defined(__CVCanvas__AffineFitter__) */
