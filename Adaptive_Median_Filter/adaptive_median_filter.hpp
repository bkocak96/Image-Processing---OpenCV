#include "opencv2/opencv.hpp"

// this function operates on grayscale images
cv::Mat adaptiveMedian(cv::Mat image)
{
	cv::Mat outImage;
	outImage = image;
	
	cv::Mat zeropad3;
	cv::Mat zeropad5;
	cv::Mat zeropad7;

	int max = 0;
	int min = 255;

	double a1 = 0;
	double a2 = 0;
	double b1 = 0;
	double b2 = 0;

	cv::Mat zeropad(image.rows + 6, image.cols + 6, CV_8UC1, 255);

	for (int i = 0; i<image.cols + 6; i++) {
		for (int j = 0; j<image.rows + 6; j++) {

			zeropad.at<uchar>(j, i) = 0;

		}
	}


	for (int i = 0; i<image.cols; i++) {
		for (int j = 0; j<image.rows; j++) {

			zeropad.at<uchar>(j + 3, i + 3) = image.at<uchar>(j, i);

		}
	}

	cv::medianBlur(zeropad, zeropad3, 3);
	cv::medianBlur(zeropad, zeropad5, 5);
	cv::medianBlur(zeropad, zeropad7, 7);

	for (int i = 0; i < image.cols; i++) {
		for (int j = 0; j < image.rows; j++) {

			int max = 0;
			int min = 255;
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {

					if (max < (int)zeropad.at<uchar>(j + y + 3, i + x + 3)) {
						max = (int)zeropad.at<uchar>(j + y + 3, i + x + 3);
					}
					if (min >(int)zeropad.at<uchar>(j + y + 3, i + x + 3)) {
						min = (int)zeropad.at<uchar>(j + y + 3, i + x + 3);
					}

				}
			}

			a1 = zeropad3.at<uchar>(j + 3, i + 3) - min;
			a2 = zeropad3.at<uchar>(j + 3, i + 3) - max;

			if ((a1 > 0) && (a2 < 0)) {
				b1 = image.at<uchar>(j, i) - min;
				b2 = image.at<uchar>(j, i) - max;

				if ((b1 > 0) && (b2 < 0)) {
					outImage.at<uchar>(j, i) = image.at<uchar>(j, i);
				}

				else {
					outImage.at<uchar>(j, i) = zeropad3.at<uchar>(j + 3, i + 3);
				}
			}

			else {
				int max = 0;
				int min = 255;
				for (int x = -2; x <= 2; x++) {
					for (int y = -2; y <= 2; y++) {

						if (max < (int)zeropad.at<uchar>(j + y + 3, i + x + 3)) {
							max = (int)zeropad.at<uchar>(j + y + 3, i + x + 3);

						}

						if (min >(int)zeropad.at<uchar>(j + y + 3, i + x + 3)) {
							min = (int)zeropad.at<uchar>(j + y + 3, i + x + 3);
						}

					}
				}

				a1 = zeropad5.at<uchar>(j + 3, i + 3) - min;
				a2 = zeropad5.at<uchar>(j + 3, i + 3) - max;

				if ((a1 > 0) && (a2 < 0)) {
					b1 = image.at<uchar>(j, i) - min;
					b2 = image.at<uchar>(j, i) - max;
					if ((b1 > 0) && (b2 < 0)) {
						outImage.at<uchar>(j, i) = image.at<uchar>(j, i);
					}
					else {
						outImage.at<uchar>(j, i) = zeropad5.at<uchar>(j + 3, i + 3);
					}
				}

				else {
					int max = 0;
					int min = 255;
					for (int x = -3; x <= 3; x++) {
						for (int y = -3; y <= 3; y++) {

							if (max < (int)zeropad.at<uchar>(j + y + 3, i + x + 3)) {
								max = (int)zeropad.at<uchar>(j + y + 3, i + x + 3);
							}
							if (min >(int)zeropad.at<uchar>(j + y + 3, i + x + 3)) {
								min = (int)zeropad.at<uchar>(j + y + 3, i + x + 3);
							}

						}
					}

					a1 = zeropad7.at<uchar>(j + 3, i + 3) - min;
					a2 = zeropad7.at<uchar>(j + 3, i + 3) - max;

					if ((a1 > 0) && (a2 < 0)) {
						b1 = image.at<uchar>(j, i) - min;
						b2 = image.at<uchar>(j, i) - max;
						if ((b1 > 0) && (b2 < 0)) {
							outImage.at<uchar>(j, i) = image.at<uchar>(j, i);
						}
						else {
							outImage.at<uchar>(j, i) = zeropad7.at<uchar>(j + 3, i + 3);
						}
					}
					else {
						outImage.at<uchar>(j, i) = zeropad7.at<uchar>(j + 3, i + 3);
					}

				}
			}
		}
	}

	return outImage;
}