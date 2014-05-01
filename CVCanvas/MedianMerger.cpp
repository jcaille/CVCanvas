//
//  MedianMerger.cpp
//  CVCanvas
//
//  Created by Jean Caillé on 10/03/2014.
//  Copyright (c) 2014 Jcaille. All rights reserved.
//

#include "MedianMerger.h"
#include <algorithm>

cv::Scalar_<uchar> median(std::vector<cv::Scalar_<uchar>> colors)
{
    cv::Scalar_<uchar> res(0);
    for (int i = 0; i < 4; i++) {
        // For each component
        std::vector<uchar> values;
        for (unsigned int j = 0; j < colors.size(); j++) {
            values.push_back(colors[j][i]);
        }
        sort(values.begin(), values.end());

        uchar median;
        if ((values.size() % 2) == 0)
        {
            median = (values[values.size() / 2] + values[values.size() / 2 - 1]) / 2;
        }
        else
        {
            median = values[values.size() / 2];
        }
        res[i] = median;
    }
    return res;
}

cv::Mat merge(std::vector<cv::Mat> images)
{
    cv::Mat res(images[0].size(), images[0].type());
    
    for (int i = 0; i < res.cols; i++)
    {
        std::cout << "Col # " << i << " / " << res.cols << std::endl;
        for(int j = 0 ; j < res.rows ; j++)
        {
            std::vector<cv::Scalar_<uchar>> colors;
            for (unsigned int k = 0; k < images.size(); k++) {
                colors.push_back(images[k].at<cv::Scalar_<uchar>>(j, i));
            }
            res.at<cv::Scalar_<uchar>>(j,i) = median(colors);
        }
    }
    
    return res;
}