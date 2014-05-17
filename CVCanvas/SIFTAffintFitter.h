//
//  SIFTAffintFitter.h
//  CVCanvas
//
//  Created by Jean Caillé on 28/03/2014.
//  Copyright (c) 2014 Jcaille. All rights reserved.
//

#ifndef __CVCanvas__SIFTAffintFitter__
#define __CVCanvas__SIFTAffintFitter__

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>

class SIFTAffineFitter{
    cv::Mat reference;
    int flags;
    
public:

    /**
     *  Creates the fitter with the given reference image.
     */
    SIFTAffineFitter(cv::Mat referenceImage, int flags);
    
    /**
     *  Fits the input image with respect to the reference image of the fitter
     *
     *  @param inputImage The image to be fitted
     *
     *  @return A fitted image.
     */
    cv::Mat fit(cv::Mat inputImage);
    
private :
    std::vector<cv::KeyPoint> keypointsReference;
    cv::Mat descriptorsReference;
};


#endif /* defined(__CVCanvas__SIFTAffintFitter__) */
