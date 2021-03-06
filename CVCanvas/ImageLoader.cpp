//
//  ImageLoader.cpp
//  CVCanvas
//
//  Created by Jean Caillé on 17/05/2014.
//  Copyright (c) 2014 Jcaille. All rights reserved.
//

#include "ImageLoader.h"

using namespace std;
using namespace cv;

void loadImagesWithNames(vector<string>& fileNames, vector<Mat>& images)
{
    images.clear();
    for (int i = 0; i < fileNames.size(); i++) {
        images.push_back(imread(fileNames[i]));
    }
}

void loadImage(ImageLoaderSet set, std::vector<cv::Mat>& images)
{
    vector<string> fileNames;
    switch (set) {
        case BRUSH_ODD:
            fileNames.push_back("Brush/0.jpg");
            fileNames.push_back("Brush/1.jpg");
            break;
        case BRUSH_ALL:
            fileNames.push_back("Brush/0.jpg");
            fileNames.push_back("Brush/1.jpg");
            fileNames.push_back("Brush/2.jpg");
            fileNames.push_back("Brush/3.jpg");
            break;
        case MAN_ALL:
            fileNames.push_back("Man/0.jpg");
            fileNames.push_back("Man/1.jpg");
            fileNames.push_back("Man/2.jpg");
            fileNames.push_back("Man/3.jpg");
            fileNames.push_back("Man/4.jpg");
            fileNames.push_back("Man/5.jpg");
            fileNames.push_back("Man/6.jpg");
            fileNames.push_back("Man/7.jpg");
            fileNames.push_back("Man/8.jpg");
            fileNames.push_back("Man/9.jpg");
            break;
        case MEDUSE:
            fileNames.push_back("Meduse_fake/1_reflet.png");
            fileNames.push_back("Meduse_fake/2_reflet.png");
            fileNames.push_back("Meduse_fake/3_reflet.png");
            fileNames.push_back("Meduse_fake/4_reflet.png");
            fileNames.push_back("Meduse_fake/5_reflet.png");
            break;
        case PINK:
            fileNames.push_back("Pink/30.jpg");
            fileNames.push_back("Pink/31.jpg");
            break;
        case MAN_RIGHT:
            fileNames.push_back("Man_Right/16.jpg");
            fileNames.push_back("Man_Right/21.jpg");
            fileNames.push_back("Man_Right/24.jpg");
            fileNames.push_back("Man_Right/26.jpg");
            fileNames.push_back("Man_Right/1.jpg");
            fileNames.push_back("Man_Right/8.jpg");
            break;
        case BRUSH_FITTED:
            fileNames.push_back("Brush_Fitted/46.jpg");
            fileNames.push_back("Brush_Fitted/47.jpg");
            fileNames.push_back("Brush_Fitted/48.jpg");
            fileNames.push_back("Brush_Fitted/49.jpg");
        default:
            break;
    }
    loadImagesWithNames(fileNames, images);
}