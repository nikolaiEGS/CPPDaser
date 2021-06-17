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
	virtual std::vector<double> flatten() const = 0;
	virtual void transpose() = 0;
	virtual void printElements() const = 0;
};

class Tensor1D : public Tensor {
	double* data;
	std::size_t size;
	std::array<std::size_t, 2> shape;
public:
	Tensor1D() : data{ nullptr }, size{ 0 }, shape{0}{}
	Tensor1D(std::initializer_list<double> data_, Orientation m_n_ = HORIZONTAL ); // works
	virtual ~Tensor1D() noexcept; // works

	Tensor1D(const Tensor1D& copyObj); // works
	Tensor1D(Tensor1D&& moveObj); // works
	void printElements() const override; // works
	Tensor1D& operator=(const Tensor1D& copyAss); // works
	Tensor1D& operator=(Tensor1D&& moveAss); // wokrs

	std::array<std::size_t, 2> getShape() override; // works
	std::vector<double> flatten() const override; // works
	void transpose() override; // works
	friend void swap(Tensor1D& left, Tensor1D& right); // works
};

class Tensor2D : public Tensor {
	double** data;
	std::array<std::size_t, 2> shape; // shape[0] = row, shape[1] = column;

	void allocate2D(const std::size_t row, const std::size_t column); // works
	void allocate2D(const std::size_t row, std::size_t column, const double defVal); // works
	
public:
	Tensor2D() : data{nullptr}, shape{0}{}
	Tensor2D(std::initializer_list<std::initializer_list<double>> data_); // works
	Tensor2D(const std::size_t m, const std::size_t n); // works
	Tensor2D(const std::size_t m, const std::size_t n, const double defaultVal); // works
	~Tensor2D() noexcept; // works

	Tensor2D(const Tensor2D& copyObj); // works
	Tensor2D(Tensor2D&&); // works
	Tensor2D& operator=(const Tensor2D& copyAss); // works
	Tensor2D& operator=(Tensor2D&& moveAss); // works
	
	std::array<std::size_t, 2> getShape(); // works
	void printElements() const override; // works
	void transpose() override; // work					 									 
	std::vector<double> flatten() const override; // work
	friend void swap(Tensor2D& left, Tensor2D& right); // works
	void setValue(const double val); // works
};


class Tensor3D {
	std::vector<Tensor2D> data;
	std::array<std::size_t, 3> shape; // m x n x z 
public:
	Tensor3D() : data{ 0 }, shape{0} {}
	//Tensor3D(std::initializer_list<Tensor2D> data_);
	Tensor3D(Tensor2D Red, Tensor2D Green, Tensor2D Blue);
	// 	   
	//~Tensor3D() noexcept;

};

