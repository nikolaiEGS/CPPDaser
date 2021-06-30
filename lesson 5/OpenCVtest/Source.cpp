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

	// Problem with operator cv::Mat()
	Mat tensor3d_to_image = image_to_tensor3d;

	//std::cout << " XXXXXXXXXXXXXX  AFTER operator cv::Mat  XXXXXXXXXXXXXXXXX " << std::endl;
	//assert_equal_mat(image, tensor3d_to_image);

	//image_to_tensor3d.convolve(std::vector<double>(9, 0.11));

	Tensor3D pic("./zivert.jpg", RGB);
	double tsts = pic.at(1, 2, 2);
	std::cout << "at()  tsts == "<<tsts << std::endl;

	Tensor2D R({ { 10,10,10 }, { 10,10,10 }, { 10,10,10 } });
	Tensor2D G({ { 10,10,10 }, { 200,200,200 }, { 1,2,3 } });
	Tensor2D B({ { 10,10,10 }, { 200,200,200 }, { 1,2,3 } });

	Tensor3D RGB({ R,G,B });
	//Mat testRGB = RGB;
	//pic.man_to_0_250();
	//pic.darkenImage(50);
	//pic.lightenImage(90);

	/*std::cout << "------- TEST CONVERTION digit----------" << std::endl;
	std::cout << "xxxxxxxxxxxx befor xxxxxxxxxxxxxx" << std::endl;
	Tensor3D RGB({ R,G,B });
	RGB.printElements();
	RGB.man_to_0_250();
	std::cout << "xxxxxxxxxxxx after xxxxxxxxxxxxxx" << std::endl;
	RGB.printElements();*/

	std::vector<double> kernel({ -1,-1,-1,2,2, 2,-1,-1,-1 });

	std::vector<double> kernel_line({ -1,-1,-1,
									   2, 2, 2,
									  -1,-1,-1 });

	std::vector<double> kernel_blur({ 1/99, 1/99, 1/99,
									   1/99, 1 / 99, 1 / 99,
									  1 / 99,1 / 99,1 / 99 });

	std::vector<double> kernel_test(9, 0.11);
	std::vector<double> kernel_id({ 0,0,0,0,1,0,0,0,0});
	pic.convolve(kernel_line);
	Mat testImage = pic;

	std::cout << "------- TEST CONVOLUTION----------" << std::endl;
	R.printElements();
	
	R.convolve(kernel_test);
	R.printElements();
	//assert_equal_mat(image, testImage);

	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", testImage);
	waitKey(0);

	return 0;
}
