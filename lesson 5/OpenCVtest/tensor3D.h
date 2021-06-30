#pragma once
#include <iostream>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <array>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "tensor2D.h"
#include "Exception.h"

enum imreadType { GRAY, RGB };
class Tensor3D {
	std::vector<Tensor2D> data;
	std::array<std::size_t, 3> shape;

	cv::Mat fillDataInMat(int channel);
public:
	Tensor3D() : shape{ 0, 0, 0 } {}
	Tensor3D(std::initializer_list<Tensor2D>);
	Tensor3D(const cv::Mat&);
	Tensor3D(const std::string& filePath, imreadType type);
	~Tensor3D() noexcept {}

	Tensor3D(const Tensor3D& y);
	Tensor3D(Tensor3D&&);
	Tensor3D& operator=(const Tensor3D&);
	Tensor3D& operator=(Tensor3D&&);

	std::array<std::size_t, 3> getShape();
	void transpose();
	std::vector<double> flatten() const;
	void printElements();
	friend void swap(Tensor3D&, Tensor3D&);

	double& at(std::size_t depth, std::size_t row, std::size_t column);
	void setValue(int channel, int row, int column, double value);
	void pushChannel(const Tensor2D&);

	operator cv::Mat();
	bool operator==(Tensor3D& right);
	void man_to_0_250();
	void darkenImage(double amount);
	void lightenImage(double amount);
	Tensor3D& convolve(const std::vector<double>&);
};

