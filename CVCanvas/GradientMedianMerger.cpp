// Theophile Dalens 2014

#include "GradientMedianMerger.h"
#include <fstream>
using namespace std;
using namespace cv;

uchar imedian(std::vector<float> fl1, std::vector<float> fl2)
{
	unsigned bestIndex = -1;
	float best = -1.f;
	for(unsigned i=0; i < fl1.size(); i++)
	{
		float sumL1 = 0;
		for(unsigned j=0; j < fl1.size(); j++)
			sumL1 += abs(fl1[i]-fl1[j])+abs(fl2[i]-fl2[j]);
		if(best < 0 ||sumL1 < best)
		{
			best=sumL1;
			bestIndex = i;
		}
	}
	return uchar(bestIndex);
}

void displayFloatMat(Mat x, char* windowTitle)
{
	double mn, mx;
	minMaxLoc(x, &mn, &mx);
	if(mx==mn)
		return;
	Mat y;
	x.convertTo(y, CV_8U, 255/(mx-mn), -255*mn/(mx-mn));
	imshow(windowTitle, y);
}
vector<Mat> grad(Mat x)
{
	vector<Mat> G;
	Mat x1(x.size(), CV_32F);
	Mat x2(x.size(), CV_32F);
	for(int i=0; i<x.cols; i++)
	{
		for(int j=0; j<x.rows; j++)
		{
			if((i+1-x.cols)*(j+1-x.rows)==0)
			{
				x1.at<float>(j,i) = 0.f;
				x2.at<float>(j,i)=0.f;
			}	
			else
			{
				x1.at<float>(j,i) = (x.at<float>(j,i+1)-x.at<float>(j,i));
				x2.at<float>(j,i) = (x.at<float>(j+1,i)-x.at<float>(j,i));
			}
		}
	}

	G.push_back(x1);
	G.push_back(x2);
	return G;
}

Mat myLaplacian(Mat x)
{
	Mat l(x.size(), CV_32F);
	for(int i=0; i<x.cols; i++)
		for(int j=0; j<x.rows; j++)
			if(i*j*(x.cols-1-i)*(x.rows-1-j)==0)
				l.at<float>(j,i) = 0.f;
			else
				l.at<float>(j,i)=
				x.at<float>(j,i-1)+x.at<float>(j,i+1)+
				x.at<float>(j-1,i)+x.at<float>(j+1,i)-
				4*x.at<float>(j,i);
	return l;
}
void saveFloatMat(const Mat& x, char* path)
{
	ofstream saveFile;
	saveFile.open(path);
	for(int j=0; j<x.rows; j++)
	{
		for(int i=0; i<x.cols; i++)
		{
			saveFile << x.at<float>(j,i) << '\t';
		}
		saveFile << endl;
	}
}
Mat iterativePoissonSolver(Mat lap, Mat origin, int nbOfIter = 10)
{
	Mat result, prev;
	origin.copyTo(result);
	for(int iter = 0; iter < nbOfIter; iter++)
	{
		//displayFloatMat(result, "prev");
		//cout << iter << " " << endl;
		result.copyTo(prev);
		for(int i=1; i<origin.cols-1; i++)
			for(int j=1; j<origin.rows-1; j++)
				result.at<float>(j,i) = 1/4.f*
				(prev.at<float>(j-1,i)+prev.at<float>(j+1,i)+prev.at<float>(j,i-1)+prev.at<float>(j,i+1)-lap.at<float>(j,i));
		for(int i=1; i<origin.cols-1; i++)
		{
			result.at<float>(0,i) = result.at<float>(1,i);
			result.at<float>(origin.rows-1,i) = result.at<float>(origin.rows-2,i);
		}
		for(int j=0; j<origin.rows; j++)
		{
			result.at<float>(j,0) = result.at<float>(j,1);
			result.at<float>(j,origin.cols-1) = result.at<float>(j,origin.cols-2);
		}
		//displayFloatMat(result, "now");
		//waitKey();
	}
	return result;
}
GradientMedianMerger::GradientMedianMerger(std::vector<cv::Mat> images) : images(images)
{
	cout << "compute BW gradient images" << endl;
	vector<Mat> imagesGrad1;
	vector<Mat> imagesGrad2;
	for(unsigned im=0; im<images.size(); im++)
	{
		Mat x;
		cvtColor(images[im], x, CV_RGB2GRAY);
		Mat xf;
		x.convertTo(xf, CV_32F);
		Mat x1(xf.rows, xf.cols, CV_32F);
		Mat x2(xf.rows, xf.cols, CV_32F);
		for(int i=0; i<x.cols; i++)
		{
			for(int j=0; j<x.rows; j++)
			{
				if(i*j*(i+1-x.cols)*(j+1-x.rows)==0)
				{
					x1.at<float>(j,i) = 0.f;
					x2.at<float>(j,i)=0.f;
				}	
				else
				{
					x1.at<float>(j,i) = (xf.at<float>(j,i+1)-xf.at<float>(j,i-1))/2;
					x2.at<float>(j,i) = (xf.at<float>(j+1,i)-xf.at<float>(j-1,i))/2;
				}
			}
		}
		imagesGrad1.push_back(x1);
		imagesGrad2.push_back(x2);
	}

	cout << "compute indexes for gradient image" << endl;
	Mat indexes(images[0].size(), CV_8U);
    for (int i = 0; i < indexes.cols; i++)
    {
        for(int j = 0 ; j < indexes.rows ; j++)
        {
            std::vector<float> fl1;
			std::vector<float> fl2;
            for (unsigned int k = 0; k < images.size(); k++) {
                fl1.push_back(imagesGrad1[k].at<float>(j, i));
				fl2.push_back(imagesGrad2[k].at<float>(j, i));
            }
            indexes.at<char>(j,i) = imedian(fl1, fl2);
        }
    }
	//displayFloatMat(indexes, "indexes");

	cout << "compute all gradients" << endl;
	//vector of original images by canal
	vector<vector<Mat>> spl;
	for(unsigned im=0; im<images.size(); im++)
	{
		vector<Mat> s;
		cv::split(images[im], s);
		spl.push_back(s);
	}

	vector<vector<vector<Mat>>> allGradients;
	for(unsigned im=0; im<images.size(); im++)
	{
		vector<vector<Mat>> agim;
		for(int c=0; c<3; c++)
		{
			Mat x;
			spl[im][c].convertTo(x, CV_32F);
			vector<Mat> agc;
			Mat x1(spl[im][c].size(), CV_32F);
			Mat x2(spl[im][c].size(), CV_32F);
			for(int i=0; i<spl[im][c].cols; i++)
			{
				for(int j=0; j<spl[im][c].rows; j++)
				{
					if((i+1-spl[im][c].cols)*(j+1-spl[im][c].rows)==0)
					{
						x1.at<float>(j,i) = 0.f;
						x2.at<float>(j,i)=0.f;
					}	
					else
					{
						x1.at<float>(j,i) = (x.at<float>(j,i+1)-x.at<float>(j,i));
						x2.at<float>(j,i) = (x.at<float>(j+1,i)-x.at<float>(j,i));
					}
				}
			}
			agc.push_back(x1);
			agc.push_back(x2);
			agim.push_back(agc);

		}
		allGradients.push_back(agim);
	}

	cout << "compute resultant divergence of gradient image" << endl;
	vector<Mat> divGradRes;
	divGradRes.push_back(Mat(images[0].size(), CV_32F));
	divGradRes.push_back(Mat(images[0].size(), CV_32F));
	divGradRes.push_back(Mat(images[0].size(), CV_32F));
	for(int i=0; i<images[0].cols; i++)
		for(int j=0; j<images[0].rows; j++)
			for(unsigned c=0; c<3; c++)
				if(i*j==0)
					divGradRes[c].at<float>(j,i)=0.f;
				else
					divGradRes[c].at<float>(j,i)=
					allGradients[int(indexes.at<uchar>(j,i))][c][0].at<float>(j,i)-
					allGradients[int(indexes.at<uchar>(j,i-1))][c][0].at<float>(j,i-1)+
					allGradients[int(indexes.at<uchar>(j,i))][c][1].at<float>(j,i)+
					allGradients[int(indexes.at<uchar>(j-1,i))][c][1].at<float>(j-1,i);
	displayFloatMat(divGradRes[0], "example of resultat Laplacian image");
	saveFloatMat(divGradRes[0],"C:/4a/Telecom/SI343/a0.mat");
	saveFloatMat(divGradRes[1],"C:/4a/Telecom/SI343/a1.mat");
	saveFloatMat(divGradRes[2],"C:/4a/Telecom/SI343/a2.mat");


	Mat orig;
	spl[0][0].convertTo(orig, CV_32F);
	//Laplacian(orig, j, CV_32F, 1, 1., 0., BORDER_REFLECT);
	Mat j=myLaplacian(orig);
	displayFloatMat(j, "example of original Laplaican");
	//waitKey();

	Mat distance;
	absdiff(spl[0][0], spl[1][0], distance);
	displayFloatMat(distance, "distance between input images");
	//waitKey();
	cout << "solving Poisson equation" << endl;
	vector<Mat> poissonSolve;
	for(int c=0; c<3; c++)
	{
		Mat original;
		spl[0][c].convertTo(original, CV_32F);
		Mat floatImage = iterativePoissonSolver(divGradRes[c], original, 30);
		//double mn, mx;
		//minMaxLoc(floatImage, &mn, &mx);
		Mat ucharImage;
		floatImage.convertTo(ucharImage, CV_8U);//, 255/(mx-mn), -255*mn/(mx-mn));
		poissonSolve.push_back(ucharImage);
	}
	output = Mat(images[0].size(), CV_8UC3);
	merge(poissonSolve, output);
}