#pragma once
#include <iostream>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <array>

enum Orientation { HORIZONTAL, VERTICAL };

class Tensor {
public:
	virtual ~Tensor() noexcept {}

	virtual std::array<std::size_t, 2> getShape() = 0;
	virtual std::vector<double> flatten() = 0;
	virtual void transpose() = 0;
	virtual void printElements() = 0;
};

/*class Tensor1D : public Tensor {
	double* data;
	std::size_t size;
	std::array<std::size_t, 2> shape; // shape[0] = row, shape[1] = column; shouldnt we change the arry to two size_t??
public:
	Tensor1D() : data{ nullptr }, size{ 0 }, shape{0}{}
	Tensor1D(std::initializer_list<double> data_, Orientation m_n_ = HORIZONTAL ); // works 
	Tensor1D(const Tensor1D& copyObj); // works
	Tensor1D(Tensor1D&& moveObj); // works
	void printElements() override; // works
	Tensor1D& operator=(const Tensor1D& copyAss); // works
	Tensor1D& operator=(Tensor1D&& moveAss); // wokrs
	virtual ~Tensor1D() noexcept; // works
	std::array<std::size_t, 2> getShape() override; // works
	std::vector<double> flatten() override; // works
	void transpose() override; // works
	friend void swap(Tensor1D& left, Tensor1D& right); // works
};*/

class Tensor2D : public Tensor {
	double** data;
	std::array<std::size_t, 2> shape; // shape[0] = row, shape[1] = column;

	
public:
	Tensor2D() : data{nullptr}, shape{0}{}
	Tensor2D(std::initializer_list<std::initializer_list<double>> data_, Orientation m_n_ = HORIZONTAL); // works
	~Tensor2D() noexcept; // works
	Tensor2D(const Tensor2D& copyObj); // works
	Tensor2D(Tensor2D&&); // works
	Tensor2D& operator=(const Tensor2D& copyAss); // works
	Tensor2D& operator=(Tensor2D&& moveAss); // works
	
	std::array<std::size_t, 2> getShape(); // works
	void printElements() override; // works
	void transpose() override; // does not work, after compiling "can not open - error" arised. After commenting the function out, the error is not disappearing						 									 
	std::vector<double> flatten() override;
	friend void swap(Tensor2D& left, Tensor2D& right); // works
	
};

/*enum Orientation3D { HORIZONTAL, VERTICAL, DEPTH };

class Tensor3D : public Tensor {
	std::vector<Tensor2D> data;
	std::array<std::size_t, 3> shape; // m x n x z 
public:
	Tensor3D(std::initializer_list<Tensor2D> data_);  // can constructor get tensor2D elements with different orientation??



	~Tensor3D() noexcept;
	
};*/

