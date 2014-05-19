//
//  ImageFitter.h
//  CVCanvas
//
//  Created by Jean Caillé on 17/05/2014.
//  Copyright (c) 2014 Jcaille. All rights reserved.
//

#ifndef __CVCanvas__ImageFitter__
#define __CVCanvas__ImageFitter__

#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// This class simply handles dispatching between different fit strategies :

typedef enum FitStrategy
{
    USER,
    SIFT,
    NONE
} FitStrategy;


/**
 *  Fits the image by calling the appropriate Fitter (SiftAffineFitter, UserAffineFitter, or nothing).
 *
 *  @param inputImages    The images to fit
 *  @param referenceImage The reference image which we will fit against
 *  @param strategy       The fit strategy
 *  @param fittedImages   Upon completion, will contain the fitted images, in the same order as the input.
 */
void fit(std::vector<cv::Mat>& inputImages, cv::Mat referenceImage, FitStrategy strategy, std::vector<cv::Mat>& fittedImages, int flags = cv::INTER_LINEAR, int inlierThreshold = 40);
#endif /* defined(__CVCanvas__ImageFitter__) */
