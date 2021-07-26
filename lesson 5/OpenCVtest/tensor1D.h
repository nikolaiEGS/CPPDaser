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

enum Orientation { HORIZONTAL, VERTICAL };

class Tensor1D : public Tensor {
	double* data;
	std::size_t size;
	std::array<std::size_t, 2> shape;
public:
	Tensor1D() : data{ nullptr }, size{ 0 }, shape{ 0 }{}
	Tensor1D(std::initializer_list<double>, Orientation m_n_ = HORIZONTAL);
	virtual ~Tensor1D() noexcept;

	Tensor1D(const Tensor1D&);
	Tensor1D(Tensor1D&&);
	void printElements() const override;
	Tensor1D& operator=(const Tensor1D&);
	Tensor1D& operator=(Tensor1D&&);

	std::array<std::size_t, 2> getShape() const override;
	std::vector<double> flatten() const override;
	void transpose() override;
	friend void swap(Tensor1D&, Tensor1D&);
};
