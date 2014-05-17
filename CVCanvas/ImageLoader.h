//
//  ImageLoader.h
//  CVCanvas
//
//  Created by Jean Caillé on 17/05/2014.
//  Copyright (c) 2014 Jcaille. All rights reserved.
//

#ifndef __CVCanvas__ImageLoader__
#define __CVCanvas__ImageLoader__

#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/**
 *  This file contains some helper functions designed to load images from the dataset
 */

/**
 *  Possible datasets
 */
typedef enum ImageLoderSet {
    BRUSH_ODD,
    BRUSH_ALL,
    MAN_ALL,
    MAN_RIGHT,
    BRUSH_FITTED,
    PINK,
    MEDUSE,
}ImageLoaderSet;

/**
 *  Loads images from disk, converts them to OpenCV format and stores them in a vector.
 *
 *  @param set    The set to load. See ImageLoader.h for possible values
 *  @param images Upon completion, will contain the images.
 */
void loadImage(ImageLoaderSet set, std::vector<cv::Mat>& images);


#endif /* defined(__CVCanvas__ImageLoader__) */
