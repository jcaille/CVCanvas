//
//  ImageMerger.h
//  CVCanvas
//
//  Created by Jean Caillé on 17/05/2014.
//  Copyright (c) 2014 Jcaille. All rights reserved.
//

#ifndef __CVCanvas__ImageMerger__
#define __CVCanvas__ImageMerger__

#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/**
 *  Dispatch between the different merging strategies
 */

typedef enum MergeStrategy
{
    AVERAGE,
    MEDIAN,
    VECTOR_MEDIAN,
    GRADIENT_MEDIAN,
} MergeStrategy;

/**
 *  Merges the image using the given strategy
 *
 *  @param images   The images to merge
 *  @param strategy The strategy to user
 *
 *  @return The resulting image
 */
cv::Mat merge(std::vector<cv::Mat> images, MergeStrategy strategy);

#endif /* defined(__CVCanvas__ImageMerger__) */
