#include <fstream>
#include "compare_intensity.h"

using namespace cv;

void compare(const Mat& imx, const Mat& imy, const string& outputFilePath)
{
    std::ofstream comparisonFile;
    comparisonFile.open(outputFilePath);
	
    for(int i=0; i<imx.rows; i++) {
		for(int j=0; j<imy.cols; j++) {
			comparisonFile << i << " " << j << " " << (int)imx.at<uchar>(i,j) << " " << (int)imy.at<uchar>(i,j) << std::endl;
        }
    }
    
	comparisonFile.close();
}