//
//  SIFTAffintFitter.cpp
//  CVCanvas
//
//  Created by Jean Caillé on 28/03/2014.
//  Copyright (c) 2014 Jcaille. All rights reserved.
//

#include "SIFTAffintFitter.h"

using namespace cv;

SIFTAffineFitter::SIFTAffineFitter(cv::Mat referenceImage)
{
    reference = referenceImage;
    SIFT s;
    s(reference, Mat(), keypointsReference, descriptorsReference);
}

cv::Mat SIFTAffineFitter::fit(cv::Mat inputImage)
{
    std::vector<cv::KeyPoint> keypointsInput;
    Mat descriptorsInput;
    SIFT s;

    s(inputImage, Mat(), keypointsInput, descriptorsInput);

    BFMatcher matcher(NORM_L2, false);
    std::vector<DMatch> matches, goodMatches;
    matcher.match(descriptorsInput, descriptorsReference, matches);
    
    std::vector<Point2f> pointsReference, pointsInput;

	for (unsigned i=0; i<matches.size(); i++) {
        DMatch match=matches[i];
        pointsInput.push_back(keypointsInput[match.queryIdx].pt);
        pointsReference.push_back(keypointsReference[match.trainIdx].pt);
    }
    std::cout << "    Good matches : " << pointsInput.size() << std::endl;

    std::vector<uchar> inliers;
    Mat homography = findHomography(Mat(pointsInput), Mat(pointsReference), CV_RANSAC, 10, inliers);
   
    int inliersNumber = 0;
	for (unsigned i = 0; i<inliers.size(); i++)
	{
		inliersNumber += (int) inliers[i];
	}
    
    std::cout << "   Inliers : " << inliersNumber << std::endl;

    Mat output(reference.size(), inputImage.type());
    warpPerspective(inputImage, output, homography, reference.size());

#if 0
    
    Mat m;
    drawMatches(inputImage, keypointsInput, reference, keypointsReference, matches, m, Scalar::all(-1), Scalar::all(-1), (Mat) inliers);
    imshow("Matches", m);
    imwrite("/tmp/working.png", input);
    imwrite("/tmp/fitted.png", output);
    
    waitKey();
#endif
    
    return output;
}
