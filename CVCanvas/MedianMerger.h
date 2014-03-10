//
//  MedianMerger.h
//  CVCanvas
//
//  Created by Jean Caillé on 10/03/2014.
//  Copyright (c) 2014 Jcaille. All rights reserved.
//

#ifndef __CVCanvas__MedianMerger__
#define __CVCanvas__MedianMerger__

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

cv::Mat merge(std::vector<cv::Mat> images);

#endif /* defined(__CVCanvas__MedianMerger__) */
