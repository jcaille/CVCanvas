//
//  MedianMerger.cpp
//  CVCanvas
//
//  Created by Jean Caillé on 10/03/2014.
//  Copyright (c) 2014 Jcaille. All rights reserved.
//

#include "MedianMerger.h"
#include <algorithm>

cv::Scalar_<uint8_t> median(std::vector<cv::Scalar_<uint8_t>> colors)
{
    cv::Scalar_<uint8_t> res(0);
    for (int i = 0; i < 4; i++) {
        // For each component
        std::vector<uint8_t> values;
        for (int j = 0; j < colors.size(); j++) {
            values.push_back(colors[j][i]);
        }
        sort(values.begin(), values.end());

        uint8_t median;
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
            std::vector<cv::Scalar_<uint8_t>> colors;
            for (int k = 0; k < images.size(); k++) {
                colors.push_back(images[k].at<cv::Scalar_<uint8_t>>(j, i));
            }
            res.at<cv::Scalar_<uint8_t>>(j,i) = median(colors);
        }
    }
    
    return res;
}