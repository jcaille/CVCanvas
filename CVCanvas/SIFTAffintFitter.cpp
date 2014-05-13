//
//  SIFTAffintFitter.cpp
//  CVCanvas
//
//  Created by Jean Caillé on 28/03/2014.
//  Copyright (c) 2014 Jcaille. All rights reserved.
//

#include "SIFTAffintFitter.h"

using namespace cv;

SIFTAffineFitter::SIFTAffineFitter(cv::Mat inputImage, cv::Mat referenceImage)
{
    input = inputImage;
    reference = referenceImage;
}

void SIFTAffineFitter::fit()
{
    std::vector<cv::KeyPoint> keypointsInput, keypointsReference;
    Mat descriptorsInput, descriptorsReference;
    SIFT s;

    s(input, Mat(), keypointsInput, descriptorsInput);
    s(reference, Mat(), keypointsReference, descriptorsReference);

    BFMatcher matcher(NORM_L2, false);
    std::vector<DMatch> matches, goodMatches;
    matcher.match(descriptorsInput, descriptorsReference, matches);
    
    
    std::vector<Point2f> pointsReference, pointsInput;
    
    /*float meanDistance = 0.0;
    for(DMatch match : matches)
    {
        meanDistance += match.distance;
    }
    
    meanDistance /= matches.size();

    float stdDev = 0.0;
    for(DMatch match : matches){
        stdDev = (match.distance - meanDistance) * (match.distance - meanDistance);
    }
    
    stdDev = sqrt(stdDev / matches.size());
    std::cout << "Mean : " << meanDistance << std::endl;
    std::cout << "StdDev : " << stdDev << std::endl;
    */
    //std::cout << "Raw matches : " << matches.size() << std::endl;/private/tmp/matches.png
    /*for (DMatch match : matches) {
        if (match.distance < meanDistance + 3 * stdDev) {
            goodMatches.push_back(match);
            pointsInput.push_back(keypointsInput[match.queryIdx].pt);
            pointsReference.push_back(keypointsReference[match.trainIdx].pt);
        }
    }
	*/
	for (unsigned i=0; i<matches.size(); i++) {
        DMatch match=matches[i];
        pointsInput.push_back(keypointsInput[match.queryIdx].pt);
        pointsReference.push_back(keypointsReference[match.trainIdx].pt);
    }
    std::cout << "Good matches : " << pointsInput.size() << std::endl;

    std::vector<uchar> inliers;
    Mat homography = findHomography(Mat(pointsInput), Mat(pointsReference), CV_RANSAC, 10, inliers);
   
    int inliersNumber = 0;
	for (unsigned i = 0; i<inliers.size(); i++)
	{
		inliersNumber += (int) inliers[i];
	}
//	for (uchar u : inliers) {
//        inliersNumber += (int) u;
//    }
    
    std::cout << "Inliers : " << inliersNumber << std::endl;

    output = Mat(reference.size(), input.type());
    warpPerspective(input, output, homography, reference.size());

    Mat m;
    drawMatches(input, keypointsInput, reference, keypointsReference, matches, m, Scalar::all(-1), Scalar::all(-1), (Mat) inliers);
    imshow("Matches", m);
    imwrite("/tmp/working.png", input);
    imwrite("/tmp/fitted.png", output);
//    waitKey();
}
