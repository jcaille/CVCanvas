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



void fit(std::vector<cv::Mat>& inputImages, cv::Mat referenceImage, FitStrategy strategy, std::vector<cv::Mat>& fittedImages)
{
    fittedImages.clear();

    if(strategy == USER)
    {
        UserAffineFitter userFitter(referenceImage);
        for(int i = 0 ; i < inputImages.size() ; i++)
        {
            fittedImages.push_back(userFitter.fit(inputImages[i]));
        }
    }
    else if(strategy == SIFT)
    {
        SIFTAffineFitter siftFitter(referenceImage);
        for(int i = 0 ; i < inputImages.size() ; i++)
        {
            fittedImages.push_back(siftFitter.fit(inputImages[i]));
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
