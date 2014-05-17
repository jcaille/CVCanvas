//
//  AffineFitter.cpp
//  CVCanvas
//
//  Created by Jean Caillé on 10/03/2014.
//  Copyright (c) 2014 Jcaille. All rights reserved.
//

#include "UserAffineFitter.h"

UserAffineFitter::UserAffineFitter(cv::Mat referenceImage, int flags)
{
    flags = flags;
    input = referenceImage;
    referenceCorners = userDefinedInitialCorners(referenceImage);

}

// Called each time a mouse event fires
void UserAffineFitter::mouseCallback( int event, int x, int y, int flags, void* param )
{
    std::vector<cv::Point2f> *cornerVector = (std::vector<cv::Point2f>*) param;
    
    switch (event) {
        case CV_EVENT_LBUTTONDOWN:
            //User did finish clicking on a point
            std::cout << "Ok, I got your point" << std::endl;
            cornerVector->push_back(cv::Point2f(x,y));
            break;
            
        default:
            break;
    }
}

std::vector<cv::Point2f> UserAffineFitter::userDefinedInitialCorners(cv::Mat image)
{
    std::vector<cv::Point2f> res;
    cv::imshow("Input Image Corners", image);
    std::cout << "Please click on each corner, starting from the top-left one, in clockwise order" << std::endl ;
    
    cv::setMouseCallback("Input Image Corners", this->mouseCallback, (void*) &res);
    
    while (res.size() != 4) {
        cv::waitKey(1);
    }
    cv::setMouseCallback("Input Image Corners", NULL, NULL);
    
    for (int i = 0; i < 4; i++) {
        std::cout << "Point : " << res[i].x << " " << res[i].y << std::endl;
    }
    
    cv::destroyWindow("Input Image Corners");
    
    return res;
}

cv::Mat UserAffineFitter::fit(cv::Mat inputImage)
{
    std::vector<cv::Point2f> corners = userDefinedInitialCorners(inputImage);
    cv::Mat perspective;
    
    if (flags & CV_WARP_INVERSE_MAP) {
        perspective = cv::getPerspectiveTransform(referenceCorners, corners);
    } else {
        perspective = cv::getPerspectiveTransform(referenceCorners, corners);
    }
    
    
    cv::Mat output = cv::Mat(input.size(),input.type());
    cv::warpPerspective(inputImage, output, perspective, inputImage.size(), flags);
    return output;
}