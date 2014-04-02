#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>
#include "compare_intensity.h"
using namespace std;
using namespace cv;
void compare(const Mat& imx, const Mat& imy, const string& output_file_name)
{
	ofstream compare;
	compare.open(output_file_name);
	for(int i=0; i<imx.rows; i++)
		for(int j=0; j<imy.cols; j++)
			compare << i << " " << j << " " << (int)imx.at<uchar>(i,j) << " " << (int)imy.at<uchar>(i,j) << std::endl;
	compare.close();

}