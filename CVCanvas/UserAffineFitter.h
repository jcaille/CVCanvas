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

class UserAffineFitter {
    cv::Mat input;
    std::vector<cv::Point2f> referenceCorners;
    int flags;
    
    /**
     *  Called at every mouse event when user is defining the corners
     */
    static void mouseCallback( int event, int x, int y, int flags, void* param );
    

    /**
     *  Ak the user for the corners of the painting
     *
     *  @param image The image in which the painting is present
     *
     *  @return A std::vector containing the four corners defined by the user.
     */
    std::vector<cv::Point2f> userDefinedInitialCorners(cv::Mat image);

public:

    /**
     *  Constructor for the object. It will ask the user for the corners of the painting in the reference image.
     */
    UserAffineFitter(cv::Mat referenceImage, int flags);
    
    /**
     *  Fits the painting in the image by asking the user to click on the 4 corners.
     *
     *  @param inputImage The image to fit
     *
     *  @return The fitted image
     */
    cv::Mat fit(cv::Mat inputImage);

};

#endif /* defined(__CVCanvas__AffineFitter__) */
