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
    cv::Size outputSize;
    bool isDefiningCorners;
    
    /**
     *  Called at every mouse event when user is defining the corners
     */
    static void mouseCallback( int event, int x, int y, int flags, void* param );
    
    /**
     *  Ask the user for the corners of the painting
     *
     *  @return A std::vector containing the four corners in clockwise order, starting at the top-left corner.
     */
    std::vector<cv::Point2f> userDefinedInitialCorners();

public:
    /**
     *  The fitted image
     */
    cv::Mat output;

    /**
     *  Constructor for the object.
     *
     *  @param outputSize   The size of the output image
     *  @param inputMatrix  An image containing the painting we want.
     */
    UserAffineFitter(cv::Size outputSize, cv::Mat inputMatrix);
    
    void fit();

};

#endif /* defined(__CVCanvas__AffineFitter__) */
