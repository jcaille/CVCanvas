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
    cv::Mat input; cv::Mat reference;
    
public:
    /**
     *  The fitted image
     */
    cv::Mat output;
    

    /**
     *  Creates the fitter
     *  @param inputImage       The image to fit
     *  @param referenceImage   The reference image. The fitted image will have the same size, and will hopefully be aligned to this reference image.
     */
    SIFTAffineFitter(cv::Mat inputImage, cv::Mat referenceImage);
    
    void fit();
    
};


#endif /* defined(__CVCanvas__SIFTAffintFitter__) */
