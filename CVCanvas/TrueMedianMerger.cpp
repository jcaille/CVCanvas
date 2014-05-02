// Theophile Dalens 2014

#include "TrueMedianMerger.h"

using namespace std;
using namespace cv;

cv::Scalar_<uchar> tmedian(std::vector<cv::Scalar_<uchar>> colors)
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
TrueMedianMerger::TrueMedianMerger(std::vector<cv::Mat> images) : images(images)
{
	output = Mat(images[0].size(), images[0].type());
    
    for (int i = 0; i < output.cols; i++)
    {
        for(int j = 0 ; j < output.rows ; j++)
        {
            std::vector<cv::Scalar_<uchar>> colors;
            for (unsigned int k = 0; k < images.size(); k++) {
                colors.push_back(images[k].at<cv::Scalar_<uchar>>(j, i));
            }
            output.at<cv::Scalar_<uchar>>(j,i) = tmedian(colors);
        }
    }
}