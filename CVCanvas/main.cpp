//
//  main.cpp
//  CVCanvas
//
//  Created by Jean Caillé on 10/03/2014.
//  Copyright (c) 2014 Jcaille. All rights reserved.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>

#include "ImageLoader.h"
#include "ImageFitter.h"
#include "ImageMerger.h"

// This project demonstrate the artifact removing technique described in
// http://www.dtic.upf.edu/~gharo/Download/paintings_siims_no_compression.pdf
// The method is devided in two parts : Matchings and Merging.
// During the matching part, we try to find a common perspective to all the images
// During the Merging part, we merge the images to remove artifact.

// The implementartion has been divided in multiple classes and files to be easy to use
// Everything can be configured with those arguments :

ImageLoaderSet set = ImageLoaderSet::BRUSH_ALL;

FitStrategy fitStrategy = SIFT;

MergeStrategy mergeStrategy = MergeStrategy::MINIMUM;

//This threshold determines if an image has been fitted correctly.
int inlierThreshold = 40;

int main(int argc, const char * argv[])
{
    std::vector<cv::Mat> images;
    std::vector<cv::Mat> fittedImages;
    
    loadImage(set, images);
    std::cout << "Fitting" << std::endl;

	fit(images, images[0], fitStrategy, fittedImages, 1, inlierThreshold);
    
	for (unsigned i=0; i<fittedImages.size(); i++)
	{
		std::stringstream ss;
		ss << "Fitted image " << i;
		cv::imshow(ss.str(),fittedImages[i]);
	}
    
    std::cout << "Merging" << std::endl;
    
    cv::Mat merged = merge(fittedImages, mergeStrategy);
    
    cv::imshow("Merge", merged);

    std::cout << "Done" << std::endl;
    cv::imwrite("merge.png", merged);

    cv::waitKey();
    
    return 0;
}

