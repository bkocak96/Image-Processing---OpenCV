#include "opencv2/opencv.hpp"

cv::Mat histeq(cv::Mat image)
{
	cv::Mat outImage;
	cv::Mat ycr;

	int L = 256;
	double MN = image.rows * image.cols;
	double x = (L - 1) / MN;
	double nj[256];
	double sk[256];

	cvtColor(image, ycr, CV_BGR2YCrCb);

	for (int i = 0; i < 256; i++)
	{
		nj[i] = 0;
	}

	for (int x = 0; x < image.cols; x++) {
		for (int y = 0; y < image.rows; y++) {
			nj[ycr.at<cv::Vec3b>(y, x)[0]]++;
		}
	}

	for (int i = 1; i < 256; i++)
	{
		nj[i] = nj[i] + nj[i - 1];
	}

	for (int i = 0; i < 256; i++)
	{
		sk[i] = nj[i] * x;
	}

	cv::Mat equalized_ycr = ycr;

	for (int x = 0; x < image.cols; x++) {
		for (int y = 0; y < image.rows; y++) {
			equalized_ycr.at<cv::Vec3b>(y, x)[0] = (sk[ycr.at<cv::Vec3b>(y, x)[0]]);
		}
	}

	cvtColor(equalized_ycr, outImage, CV_YCrCb2BGR);

	return outImage;
}