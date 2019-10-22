#include "opencv2/opencv.hpp"
#include "adaptive_median_filter.hpp"

void main()
{
	cv::Mat image = cv::imread("fish.jpg", cv::IMREAD_GRAYSCALE);

	image = adaptiveMedian(image);

	cv::imwrite("fish_filtered.jpg", image);
}