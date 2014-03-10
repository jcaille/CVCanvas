//
//  AffineFitter.cpp
//  CVCanvas
//
//  Created by Jean Caillé on 10/03/2014.
//  Copyright (c) 2014 Jcaille. All rights reserved.
//

#include "UserAffineFitter.h"

UserAffineFitter::UserAffineFitter(cv::Size wantedOutputSize, cv::Mat inputMatrix)
{
    input = inputMatrix;
    outputSize = wantedOutputSize;
    isDefiningCorners = false;
}

#pragma mark - Define Image by clicking

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

std::vector<cv::Point2f> UserAffineFitter::userDefinedInitialCorners()
{
    std::vector<cv::Point2f> res;
    cv::imshow("Input Image Corners", input);
    std::cout << "Please click on each corner, starting from the top-left one, in clockwise order" << std::endl ;
    
    cv::setMouseCallback("Input Image Corners", this->mouseCallback, (void*) &res);
    
    while (res.size() != 4) {
        cv::waitKey(1);
    }
    
    for (int i = 0; i < 4; i++) {
        std::cout << "Point : " << res[i].x << " " << res[i].y << std::endl;
    }
    
    cv::setMouseCallback("Input Image Corners", NULL, NULL);

    return res;
}

void UserAffineFitter::fit()
{
    std::vector<cv::Point2f> corners = userDefinedInitialCorners();
    
    std::vector<cv::Point2f> outCorners;
    outCorners.push_back(cv::Point2f(0,0));
    outCorners.push_back(cv::Point2f(outputSize.width, 0));
    outCorners.push_back(cv::Point2f(outputSize.width, outputSize.height));
    outCorners.push_back(cv::Point2f(0, outputSize.height));
    
    cv::Mat perspective = cv::getPerspectiveTransform(corners, outCorners);
    
    output = cv::Mat(outputSize, input.type());
    cv::warpPerspective(input, output, perspective, outputSize);
}