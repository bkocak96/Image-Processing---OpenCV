#include "opencv2/opencv.hpp"


// resizes the image with bilinear interpolation and returns it
// outWidth is the width of the output image, and outHeight is the height of the output image
cv::Mat interpBilinear(cv::Mat image, int outWidth, int outHeight)
{


	cv::Mat outImage = cv::Mat(outHeight, outWidth, CV_8UC3);

	float h1 = outHeight;
	float h2 = image.rows;
	float ratioy = h1 / h2; // ratio of height
	float w1 = outWidth;
	float w2 = image.cols;
	float ratiog = w1 / w2; // ratio of width

	for (int x = 0; x < outImage.cols - 1; x++) {
		for (int y = 0; y < outImage.rows - 1; y++) {

			int rg = x / ratiog;
			int ry = y / ratioy;


			double x1 = x / ratiog - rg;
			double x2 = 1 - x1;
			double y1 = y / ratioy - ry;
			double y2 = 1 - y1;

			double z1 = x2*y2;
			double z2 = x2*y1;
			double z3 = x1*y2;
			double z4 = x1*y1;

			cv::Vec3b i1 = image.at<cv::Vec3b>(ry, rg);
			cv::Vec3b i2 = image.at<cv::Vec3b>(ry + 1, rg);
			cv::Vec3b i3 = image.at<cv::Vec3b>(ry, rg + 1);
			cv::Vec3b i4 = image.at<cv::Vec3b>(ry + 1, rg + 1);

			outImage.at<cv::Vec3b>(y, x) = z1*i1 + z2*i2 + z3*i3 + z4*i4;
		}
	}
	return outImage;
}



// resizes the image with nearest neighbor interpolation and returns it
// outWidth is the width of the output image, and outHeight is the height of the output image
cv::Mat interpNN(cv::Mat image, int outWidth, int outHeight)
{
	cv::Mat outImage = cv::Mat(outHeight, outWidth, CV_8UC3);

	float h1 = outHeight;
	float h2 = image.rows;
	float ratioy = h1 / h2; // ratio of height
	float w1 = outWidth;
	float w2 = image.cols;
	float ratiog = w1 / w2; // ratio of width

	for (int x = 0; x < outImage.cols; x++) {
		for (int y = 0; y < outImage.rows; y++) {

			outImage.at<cv::Vec3b>(y, x) = image.at<cv::Vec3b>(int(y / ratioy), int(x / ratiog)); // defined int bcs 0.5 different
		}
	}
	return outImage;
}




// calculates the mean squared error between two images and returns it (see the example below)
// Say we have two 2x2 RGB images:
//         image1                          image2
// (48,219,66)  (108, 205, 51)     (253,176,148) (160,82,117)
// (241,157,220) (155,10,206)       (120,44,174) (154,122,42)
// MSE = (1 / (2*2*3)) * ((48-253)^2 + (219-176)^2 + (66-148)^2 + (108-160)^2 + (205-82)^2 + (51-117)^2 + (241-120)^2 + (157-44)^2 + (220-174)^2 + (155-154)^2 + (10-122)^2 + (206-42)^2)
double mse(cv::Mat image1, cv::Mat image2)
{
	// we can only calculate mse if the images are of the same shape
	// the following 2 lines check this and throw an exception if this is not the case
	if ((image1.rows != image2.rows) || (image1.cols != image2.cols) || (image1.channels() != image2.channels()))
	{
		std::cout << "Inputs to mse() must be of the same shape." << std::endl;
		throw std::runtime_error("Inputs to mse() must be of the same shape.");
	}

	double mse = INFINITY; // INITIALIZE THIS WITH AN APPROPRIATE VALUE

	float sqr = 0;
	float dif = 0;

	for (int i = 0; i < 3; i++) {
		for (int x = 0; x < image1.cols; x++) {
			for (int y = 0; y < image1.rows; y++) {
				dif = (image1.at<cv::Vec3b>(y, x)[i] - image2.at<cv::Vec3b>(y, x)[i]);
				sqr += dif*dif;

			}
		}
	}
	mse = sqr / (image1.rows * image1.cols * 3);

	return mse;
}

