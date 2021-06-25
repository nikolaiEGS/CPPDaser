#include "tensor.h"
#include <iostream>
#include "Exception.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cassert>


void f(cv::Mat& mat) {
	const int channels = mat.channels();

	switch (channels) {
		case 1: {
			for (int i = 0; i < mat.rows; i++) {
				for (int j = 0; j < mat.cols; j++) {
					//std::cout << mat.at<uchar>(i, j) << std::endl;
				}
			}

			break;
		}
		case 3: {
			
			for (int i = 0; i < mat.rows; i++) {
				for (int j = 0; j < mat.cols; j++) {
					if (mat.at<cv::Vec3b>(i, j)[0] > 100) {
						mat.at<cv::Vec3b>(i, j)[0] = 250;
					}
					else {
						mat.at<cv::Vec3b>(i, j)[0] = 0;
					}
					if (mat.at<cv::Vec3b>(i, j)[1] > 100) {
						mat.at<cv::Vec3b>(i, j)[1] = 250;
					}
					else {
						mat.at<cv::Vec3b>(i, j)[1] = 0;
					}
					if (mat.at<cv::Vec3b>(i, j)[2] > 100) {
						mat.at<cv::Vec3b>(i, j)[2] = 250;
					}
					else {
						mat.at<cv::Vec3b>(i, j)[2] = 0;
					}
				}
			}
		}
	}
}

using namespace cv;


void assert_equal_mat(const cv::Mat& a, const cv::Mat& b) {
	assert(a.channels() == b.channels());
	assert(a.cols == b.cols);
	assert(a.rows == b.rows);
	assert(a.data == b.data);
}

int main() {
	
	/*
	Tensor1D d({1,2,3,4});
	d.printElements();
	Tensor1D dd(d);
	dd.printElements();
	//Tensor1D ddd(std::move(d));
	//ddd.printElements();
	Tensor1D c({ 3,3,3,3 });
	//d = c;
	d = std::move(c);
	d.printElements();
	Tensor1D t({ 10,20,30,40 });
	t.printElements();
	t.transpose();
	t.printElements();
	std::array<std::size_t, 2> shape_t = t.getShape();
	std::cout << "SHAPE" << std::endl;
	std::cout << "row = " <<shape_t[0]<< std::endl;
	std::cout << "column = " << shape_t[1]<<std::endl;
	std::vector<double> flattend =	d.flatten();
	std::cout << "FLATTEND" << std::endl;
	for (auto x : flattend) {
		std::cout << x << std::endl;
	}

	//-------------------- TENSOR 2D -------------------------------------------------------------------
	Tensor2D tt({ { 10,20,30,40 }, {10, 20, 99, 44} });
	tt.printElements();
	//Tensor2D yy(tt);
	Tensor2D yy(std::move(tt));
	yy.printElements();
	std::cout << "COPYASS" << std::endl;
	//Tensor2D zz = yy;
	Tensor2D zz = std::move(yy);
	zz.printElements();

	std::array<std::size_t, 2> shape_2D = zz.getShape();
	std::cout << "SHAPE 2 D" << std::endl;
	std::cout << "row = " << shape_2D[0] << std::endl;
	std::cout << "column = " << shape_2D[1] << std::endl;
	zz.transpose();
	zz.printElements();
	try {
		Tensor2D d2({ {1,2,3}, {4,5,6, 7} });
	}
	catch (WrongShapeTensorException& e) {
		std::cout << e.what() << std::endl;
	}
	std::vector<double> flat = zz.flatten();
	for (double x : flat) {
		std::cout << x<<" " << std::flush;
	}

	Tensor2D defVal(5, 5, 2.2);
	defVal.printElements();

	Tensor2D empty(5, 5);
	//empty.setValue(99.99);
	//empty.printElements();
	*/
	Tensor2D uu({ { 1,2,3 }, { 1,2,3 } });
	Tensor2D ii({ { 1,2,3 }, { 1,2,3 } });
	Tensor2D ff({ { 1,2,3 }, { 1,2,3 } });

	Tensor3D test({ uu, ii, ff });
	uu.printElements();


	Mat image = imread("./zivert.jpg", IMREAD_COLOR);
    if (!image.data){
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }

	Mat grayImage;
	cv::cvtColor(image, grayImage, cv::COLOR_BGRA2GRAY);
	
	//d.printElements();
	try {
		double tst = test.at(1, 1, 2);
		std::cout << "------------- at() ----------------" << std::endl;
		//test.printElements();
		std::cout << tst << std::endl;
	}
	catch (WrongSize& e) {
		std::cout << e.what() << std::endl;
	}

	Tensor2D qq({ { 1,2,3 }, { 1,2,3 } });
	Tensor2D qqq({ { 1,1 }, { 2,2 }, { 3,3 } });

	std::cout << "\n\nOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n\n\n\n";
	//test.printElements();

	Mat mm;
	image.convertTo(mm, CV_64F);

	cv::Mat chans[3];
	cv::split(image, chans);


	Tensor3D xx(image);
	Mat ll = xx;

	cv::Mat chans_ll[3];
	cv::split(ll, chans_ll);

	cv::Mat diff = chans[0] != chans_ll[0];
	//assert_equal(chans[0], image);
	// Equal if no elements disagree
	bool eq = cv::countNonZero(diff) == 0;


	int c = ll.channels();
	std::cout << ll.size << std::endl;
	//std::cout << ll << std::endl;
	//std::cout << "xTrainData (python)  = " << std::endl << format(ll, Formatter::FMT_PYTHON) << std::endl << std::endl;
	std::cout << "\n\nOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n\n\n\n";

	std::cout << "------- befor mul----------" << std::endl;
	qq.printElements();
	qqq.transpose();
	try {
		qq.matmul(qqq);
	}
	catch (WrongSize e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "------- after mul----------" << std::endl;
	qq.printElements();
	
	f(image);

	Tensor3D pic("./zivert.jpg", RGB);
	double tsts = pic.at(1, 2, 2);
	std::cout << "at()  tsts == "<<tsts << std::endl;

	Tensor2D R({ { 10,10,10 }, { 200,200,200 }, { 1,2,3 } });
	Tensor2D G({ { 10,10,10 }, { 200,200,200 }, { 1,2,3 } });
	Tensor2D B({ { 10,10,10 }, { 200,200,200 }, { 1,2,3 } });

	pic.man_to_0_250();

	std::cout << "------- TEST CONVERTION TO GRAY----------" << std::endl;
	std::cout << "xxxxxxxxxxxx befor xxxxxxxxxxxxxx" << std::endl;
	Tensor3D RGB({ R,G,B });
	RGB.printElements();
	RGB.man_to_0_250();
	std::cout << "xxxxxxxxxxxx after xxxxxxxxxxxxxx" << std::endl;
	RGB.printElements();
	Mat testImage = pic;
	//double check = at(2)
	
	if (test == RGB) {
		std::cout << "------- EQUAL----------" << std::endl;
	}
	else {
		std::cout << "------- NOT NOT NOT EQUAL----------" << std::endl;

	}

	assert_equal_mat(image, image);

    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    imshow("Display window", testImage); // Show our image inside it.
    waitKey(0);

	return 0;
}
