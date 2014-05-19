//
//  ImageFitter.cpp
//  CVCanvas
//
//  Created by Jean Caillé on 17/05/2014.
//  Copyright (c) 2014 Jcaille. All rights reserved.
//

#include "ImageFitter.h"
#include "SIFTAffintFitter.h"
#include "UserAffineFitter.h"



void fit(std::vector<cv::Mat>& inputImages, cv::Mat referenceImage, FitStrategy strategy, std::vector<cv::Mat>& fittedImages, int flags)
{
    fittedImages.clear();

    if(strategy == USER)
    {
        UserAffineFitter userFitter(referenceImage, flags);
        for(int i = 0 ; i < inputImages.size() ; i++)
        {
            fittedImages.push_back(userFitter.fit(inputImages[i]));
        }
    }
    else if(strategy == SIFT)
    {
        SIFTAffineFitter siftFitter(referenceImage, flags);
        for(int i = 0 ; i < inputImages.size() ; i++)
        {
            int inliers;
            cv::Mat fitted = siftFitter.fit(inputImages[i], inliers);
            if(inliers > 40)
            {
                // Only add the image if there is enough inliers
                fittedImages.push_back(fitted);
            } else {
                std::cout << "    Rejecting image" << std::endl;
            }
        }
    }
    else
    {
        for (int i = 0; i < inputImages.size(); i++) {
            cv::Mat outputImage;
            inputImages[i].copyTo(outputImage);
            fittedImages.push_back(outputImage);
        }
    }
    
}
