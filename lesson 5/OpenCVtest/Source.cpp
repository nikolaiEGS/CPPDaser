#include "tensor.h"
#include <iostream>
#include "Exception.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cassert>

using namespace cv;


void assert_equal_mat(const cv::Mat& a, const cv::Mat& b) {
	assert(a.channels() == b.channels());
	assert(a.cols == b.cols);
	assert(a.rows == b.rows);


	if (a.channels() == 1) {
		assert(std::equal(a.begin<uchar>(), a.end<uchar>(), b.begin<uchar>()));
	}
	else if (a.channels() == 3) {
		cv::Mat chans_a[3], chans_b[3];
		cv::split(a, chans_a);
		cv::split(b, chans_b);

		for (int i = 0; i < a.channels(); ++ i) {
			assert(std::equal(chans_a[i].begin<uchar>(), chans_a[i].end<uchar>(), chans_b[i].begin<uchar>()));
		}
	}
}


int main() {
	
	Mat image = imread("./zivert.jpg", IMREAD_COLOR);
	if (!image.data) {
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	Tensor3D image_to_tensor3d(image);
	Mat tensor3d_to_image = image_to_tensor3d;

	assert_equal_mat(image, tensor3d_to_image);

	image_to_tensor3d.convolve(std::vector<double>(9, 0.11));

	//image_to_tensor3d.convolve({0,0,0,0,1,0,0,0,0});
	Mat tensor3d_to_image1 = image_to_tensor3d;

	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", tensor3d_to_image1);
	waitKey(0);

	return 0;
}
