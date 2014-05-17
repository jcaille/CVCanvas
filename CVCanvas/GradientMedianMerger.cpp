// Theophile Dalens 2014

#include "GradientMedianMerger.h"

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
		//double mn,mx;
		//minMaxLoc(x1,&mn,&mx); 
		//Mat L1;
		//x1.convertTo(L1, CV_8U, 255/(mx-mn), -mn);
		//imshow("horizontal gradient example", L1);
		//waitKey();
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
	double mn,mx;
	minMaxLoc(indexes,&mn,&mx); 
	Mat L1;
	indexes.convertTo(L1, CV_8U, 255/(mx-mn), -mn);
	imwrite("C:/4a/Telecom/SI343/Results/indexes.jpg",L1);
	imshow("indexes", L1);
	waitKey();
	cout << "compute all gradients" << endl;
	vector<vector<Mat>> spl;
	for(int im=0; im<images.size(); im++)
	{
		vector<Mat> s;
		cv::split(images[im], s);
		spl.push_back(s);
	}
	//double mn,mx;
	//minMaxLoc(spl[0][0],&mn,&mx);
	//cout << mn;
	//Mat L1;
	//spl[0][0].convertTo(L1, CV_8U, 255/(mx-mn), -mn);
	//imshow("example of canal original image", L1);
	//waitKey();
	vector<vector<vector<Mat>>> allGradients;
	for(int im=0; im<images.size(); im++)
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
	//minMaxLoc(allGradients[0][0][0],&mn,&mx);
	//cout << mn;
	//Mat L2;
	//allGradients[0][0][0].convertTo(L2, CV_8U, 255/(mx-mn), -mn);
	//imshow("example of canal original gradient", L2);
	//waitKey();
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
	//double mn,mx;
	//minMaxLoc(divGradRes[0],&mn,&mx);
	//Mat L1;
	//divGradRes[0].convertTo(L1, CV_8U, 255/(mx-mn), -mn);
	//imshow("example of resultant laplacian image", L1);
	//waitKey();
	//cout << "solving Poisson equation" << endl;
	vector<Mat> PoissonSolve;
	float epsilon = 0.001f;
	for(int c=0; c<3; c++)
	{
		Mat ft;
		dft(divGradRes[c], ft, cv::DFT_SCALE|cv::DFT_COMPLEX_OUTPUT);
		//for(int i=0; i<ft.cols; i++)
		//{
		//	cout << i << endl;
		//	cout << ft.rows << " " << ft.cols << " " << ft.channels() << endl;
		//	for(int j=0; j<ft.rows; j++)
		//	{
		//		if(i==0 && j==0 && abs(4-2*cos(2*3.1415f*i/float(ft.rows))-2*cos(2*3.1415f*j/float(ft.cols)))>epsilon)
		//		{
 	//				float f1 =ft.at<cv::Scalar_<float>>(j,i)[0]/(4-2*cos(2*3.1415f*i/float(ft.rows))-2*cos(2*3.1415f*j/float(ft.cols)));
		//			float f2 = ft.at<cv::Scalar_<float>>(j,i)[1]/(4-2*cos(2*3.1415f*i/float(ft.rows))-2*cos(2*3.1415f*j/float(ft.cols)));
		//			ft.at<cv::Scalar_<float>>(j,i)=Scalar(f1,f2);
		//		}
		//		else
		//			ft.at<cv::Scalar_<float>>(j,i)=Scalar(0.f,0.f);
		//	}
		//}
		Mat mu = Mat::zeros(ft.size(), CV_32FC2);
		for(int i=0; i<360; i++)
		{
			cout << i << endl;
			cout << ft.rows << " " << ft.cols << " " << ft.channels() << endl;
			for(int j=0; j<ft.rows; j++)
			{
				if(i!=0 && j!=0 && abs(4-2*cos(2*3.1415f*i/float(ft.rows))-2*cos(2*3.1415f*j/float(ft.cols)))>epsilon)
				{
 					float f1 =1/(4-2*cos(2*3.1415f*i/float(ft.rows))-2*cos(2*3.1415f*j/float(ft.cols)));
					float f2 = 1/(4-2*cos(2*3.1415f*i/float(ft.rows))-2*cos(2*3.1415f*j/float(ft.cols)));
					mu.at<cv::Scalar_<float>>(j,i)=Scalar(f1,f2);
				}
			}
		}
		ft = mu.mul(ft);
		cv::Mat fi;
		cv::dft(ft, fi, cv::DFT_INVERSE|cv::DFT_REAL_OUTPUT);

		//double mn,mx;
		//minMaxLoc(divGradRes[0],&mn,&mx);
		//Mat L1;
		//divGradRes[0].convertTo(L1, CV_8U, 255/(mx-mn), -mn);
		//imshow("example of resultant laplacian image", L1);
	    //waitKey();
	    cout << "solving Poisson equation" << endl;
		cv::Mat fo;
		double mn,mx;
		minMaxLoc(fi,&mn,&mx);
		cout << mn << " " << mx;
		fi.convertTo(fo, CV_8U, 255/(mx-mn), -mn);
		imshow("example of resultant laplacian image", fo);
	    waitKey();
		PoissonSolve.push_back(fo);
		cout << endl;
	}
	output = Mat(images[0].size(), CV_8UC3);
	merge(PoissonSolve, output);
	cout << output.at<cv::Scalar_<uchar>>(1,1)[0];
	cout << endl;
	merge(PoissonSolve,output);
}