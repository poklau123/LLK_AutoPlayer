#pragma once
#include <vector>
#include <opencv2/opencv.hpp>
#include "TmallLLK.h"
using namespace std;

class ImgProc
{
public:
	cv::Mat source_image;
	cv::Mat mainarea_image;

	vector<cv::Mat> mats;

	TmailLLK* llk;

	ImgProc(CString filename);
	void CropMainArea(TmailLLK* llk);
	void CropSliceAll();
	cv::Mat ImageCropPadding(cv::Mat srcImage, cv::Rect rect);\
	double imgcompare(cv::Mat img1, cv::Mat img2);
	~ImgProc();
	vector<int> getSeries();
};

