#include "pch.h"
#include "ImgProc.h"
#include "atlconv.h"

ImgProc::ImgProc(CString filename)
{
	USES_CONVERSION;
	this->source_image = cv::imread(W2A(filename));
}

void ImgProc::CropMainArea(TmailLLK* llk)
{
	this->llk = llk;
	this->mainarea_image = this->ImageCropPadding(this->source_image, cvRect((int)this->llk->start_x, (int)this->llk->start_y, (int)this->llk->device_width, (int)this->llk->step_y * this->llk->row));
}

void ImgProc::CropSliceAll()
{
	for (int y = 0; y < this->llk->row; y++)
	{
		for (int x = 0; x < this->llk->col; x++)
		{
			int _start_x = x * this->llk->step_x;
			int _start_y = y * this->llk->step_y;

			cv::Rect rect = cvRect(_start_x, _start_y, this->llk->step_x, this->llk->step_y);
			this->mats.push_back(this->ImageCropPadding(this->mainarea_image, rect));
		}
	}
}

cv::Mat ImgProc::ImageCropPadding(cv::Mat srcImage, cv::Rect rect)
{
	//cv::Mat srcImage = image.clone();
	int crop_x1 = max(0, rect.x);
	int crop_y1 = max(0, rect.y);
	int crop_x2 = min(srcImage.cols, rect.x + rect.width); // 图像范围 0到cols-1, 0到rows-1      
	int crop_y2 = min(srcImage.rows, rect.y + rect.height);

	int left_x = (-rect.x);
	int top_y = (-rect.y);
	int right_x = rect.x + rect.width - srcImage.cols;
	int down_y = rect.y + rect.height - srcImage.rows;
	//cv::Mat roiImage = srcImage(cv::Range(crop_y1, crop_y2 + 1), cv::Range(crop_x1, crop_x2 + 1));    
	cv::Mat roiImage = srcImage(cv::Rect(crop_x1, crop_y1, (crop_x2 - crop_x1), (crop_y2 - crop_y1)));


	if (top_y > 0 || down_y > 0 || left_x > 0 || right_x > 0)//只要存在边界越界的情况，就需要边界填充    
	{
		left_x = (left_x > 0 ? left_x : 0);
		right_x = (right_x > 0 ? right_x : 0);
		top_y = (top_y > 0 ? top_y : 0);
		down_y = (down_y > 0 ? down_y : 0);
		//cv::Scalar(0,0,255)指定颜色填充    
		cv::copyMakeBorder(roiImage, roiImage, top_y, down_y, left_x, right_x, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 255));
		//cv::copyMakeBorder(roiImage, roiImage, top_y, down_y, left_x, right_x, cv::BORDER_REPLICATE);//复制最边缘像素    
		//cv::copyMakeBorder(roiImage, roiImage, top_y, down_y, left_x, right_x, BORDER_REFLECT_101);  //边缘对称法填充     
	}
	//else//若不存在边界越界的情况，则不需要填充了    
	//{    
	//  destImage = roiImage;    
	//}    
	return roiImage;
}


double ImgProc::imgcompare(cv::Mat img1, cv::Mat img2)
{
	cv::Mat s1;
	cv::absdiff(img1, img2, s1);       // |I1 - I2|
	s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
	s1 = s1.mul(s1);           // |I1 - I2|^2

	cv::Scalar s = sum(s1);         // sum elements per channel

	double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels

	if (sse <= 1e-10) // for small values return zero
		return 0;
	else
	{
		double  mse = sse / (double)(img1.channels() * img2.total());
		double psnr = 10.0*log10((255 * 255) / mse);
		return psnr;
	}
}

vector<int> ImgProc::getSeries()
{
	vector<vector<int>> types_container;
	for (int mat_pos = 0; mat_pos < this->mats.size(); mat_pos++)
	{
		if (types_container.size() == 0)
		{
			vector<int> v;
			v.push_back(mat_pos);
			types_container.push_back(v);
		}
		else
		{
			int flag;		//是否找到相同的
			for (int type_pos = 0; type_pos < types_container.size(); type_pos++)
			{
				flag = false;
				vector<int> type_container = types_container[type_pos];
				cv::Mat _source_mat = this->mats[type_container[0]];
				cv::Mat _target_mat = this->mats[mat_pos];

				double score = 0.0;
				for (int i = 0; i < type_container.size(); i++)
				{
					score += this->imgcompare(this->mats[type_container[i]], _target_mat);
				}
				score /= type_container.size();
				if (score > 12)
				{
					//cv::imshow("mat1", _source_mat);
					//cv::imshow("mat2", _target_mat);
					//cv::waitKey();
					types_container[type_pos].push_back(mat_pos);
					flag = true;
					break;
				}
			}
			if (!flag) 
			{
				vector<int> v;
				v.push_back(mat_pos);
				types_container.push_back(v);
			}
		}
	}

	map<int, int> _map;
	for (int i = 0; i < types_container.size(); i++)
	{
		for (int j = 0; j < types_container[i].size(); j++)
		{
			int type = i;
			int offset = types_container[i][j];
			_map[offset] = type;
		}
	}

	vector<int> series;
	for (map<int, int>::iterator it = _map.begin(); it != _map.end(); it++) 
	{
		series.push_back(it->second);
	}

	return series;
}

ImgProc::~ImgProc()
{
}
