#pragma once
#include <iostream>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <array>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/core.hpp>
#include "abstract_tensor.h"
#include "Exception.h"

class Tensor2D : public Tensor {
	double** data;
	std::array<std::size_t, 2> shape;

	void allocate2D(const std::size_t, const std::size_t);
	void allocate2D(const std::size_t, std::size_t, const double);

	template <typename destIterator>
	void allocate2D(const std::size_t rowSize, const std::size_t columnSize, destIterator it);

	double convolve3(int i, int j, const std::vector<double>&);
public:
	Tensor2D() : data{ nullptr }, shape{ 0,0 }{}
	Tensor2D(std::initializer_list<std::initializer_list<double>>);
	Tensor2D(const std::size_t, const std::size_t);
	Tensor2D(const std::size_t, const std::size_t, const double);
	~Tensor2D() noexcept;

	Tensor2D(const Tensor2D&);
	Tensor2D(Tensor2D&&);
	Tensor2D& operator=(const Tensor2D&);
	Tensor2D& operator=(Tensor2D&&);

	std::array<std::size_t, 2> getShape() const;
	void printElements() const override;
	void transpose() override;
	std::vector<double> flatten() const override;
	friend void swap(Tensor2D&, Tensor2D&);
	void initializeWith(const double);
	void setValue(int, int, double);
	double& getValue(std::size_t row, std::size_t colum);

	Tensor2D& matmul(const Tensor2D& right);
	std::vector<double> getRow(int row);
	std::vector<double> getColumn(int column);
	Tensor2D(const cv::Mat&);
	std::vector<uchar> change2uchar();

	Tensor2D& convolve(const std::vector<double>&);
};