//
//  ImageMerger.cpp
//  CVCanvas
//
//  Created by Jean Caillé on 17/05/2014.
//  Copyright (c) 2014 Jcaille. All rights reserved.
//

#include "ImageMerger.h"
#include "GradientMedianMerger.h"

/**
 *  This function computes the component-wise median of the given colors
 *
 *  @param colors A vector of colors
 *
 *  @return The median color (component wise)
 */
cv::Scalar_<uchar> componentMedian(std::vector<cv::Scalar_<uchar>> colors)
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

/**
 *  This function computes the vector median (minimising sum[|c - m| ] of the given colors
 *
 *  @param colors A vector of colors
 *
 *  @return The median color (vector wise)
 */
cv::Scalar_<uchar> vectorMedian(std::vector<cv::Scalar_<uchar>> colors)
{
	unsigned bestIndex = -1;
	float best = -1.f;
	for(unsigned i=0; i < colors.size(); i++)
	{
		float sumL1 = 0;
		for(unsigned j=0; j < colors.size(); j++)
		{
			for(unsigned c=0; c<4; c++)
			{
				sumL1 += abs(float(colors[i][c])-float(colors[j][c]));
			}
		}
		if(best < 0 ||sumL1 < best)
		{
			best=sumL1;
			bestIndex = i;
		}
	}
	return colors[bestIndex];
}

/**
 *  This function computes the average of the given colors
 *
 *  @param colors The colors
 *
 *  @return The average color
 */
cv::Scalar_<uchar> average(std::vector<cv::Scalar_<uchar>> colors)
{
    cv::Scalar_<float> res(0);
    for (int i = 0; i < 4; i++) {
        // For each component
        float r = 0.0;
        for (unsigned int j = 0; j < colors.size(); j++) {
            r += colors[j][i] * 1.0 / colors.size() ;
        }
        res[i] = (uchar)r;
    }

    cv::Scalar_<uchar> ucharRes = res;
    return ucharRes;
}

/**
 *  This function computes the minimum of each component
 *
 *  @param colors The colors
 *
 *  @return The average color
 */
cv::Scalar_<uchar> minimum(std::vector<cv::Scalar_<uchar>> colors)
{
    cv::Scalar_<uchar> res(0);
    for (int i = 0; i < 4; i++) {
        // For each component
        std::vector<uchar> values;
        for (unsigned int j = 0; j < colors.size(); j++) {
            values.push_back(colors[j][i]);
        }
        sort(values.begin(), values.end());
        res[i] = values[0];
    }
    return res;
}

cv::Mat merge(std::vector<cv::Mat> images, MergeStrategy strategy)
{
    if (strategy == GRADIENT_MEDIAN) {
        GradientMedianMerger tmm(images);
        return tmm.output;
    } else {
        // Those strategies act pixel-per-pixel
        cv::Mat res(images[0].size(), images[0].type());
        
        for (int i = 0; i < res.cols; i++)
        {
            for(int j = 0 ; j < res.rows ; j++)
            {
                std::vector<cv::Scalar_<uchar>> colors;
                for (unsigned int k = 0; k < images.size(); k++) {
                    colors.push_back(images[k].at<cv::Scalar_<uchar>>(j, i));
                }
                if (strategy == AVERAGE) {
                    res.at<cv::Scalar_<uchar>>(j,i) = average(colors);
                }
                if (strategy == MEDIAN){
                    res.at<cv::Scalar_<uchar>>(j,i) = componentMedian(colors);
                }
                if(strategy == VECTOR_MEDIAN){
                    res.at<cv::Scalar_<uchar>>(j,i) = vectorMedian(colors);
                }
                if(strategy == MINIMUM){
                    res.at<cv::Scalar_<uchar>>(j,i) = minimum(colors);
                }
            }
        }
        return res;
    }
}