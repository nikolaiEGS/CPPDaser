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
	virtual std::array<std::size_t, 2> getShape() const = 0;
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
	Tensor1D(std::initializer_list<double>, Orientation m_n_ = HORIZONTAL ); // works
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

class Tensor2D : public Tensor {
	double** data;
	std::array<std::size_t, 2> shape;

	void allocate2D(const std::size_t, const std::size_t);
	void allocate2D(const std::size_t, std::size_t, const double);
	
public:
	Tensor2D() : data{nullptr}, shape{0}{}
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
	void setValue(const double);

	Tensor2D& matmul(const Tensor2D& r); // [DAVID] - to implement
};

class Tensor3D {
	std::vector<Tensor2D> data;
	std::array<std::size_t, 3> shape;
public:
	Tensor3D() : data {0}, shape{0} {}
	Tensor3D(std::initializer_list<Tensor2D>);
	//Tensor3D(const cv::Mat& mat); // [DAVID] - to implement
	~Tensor3D() noexcept{}

	Tensor3D(const Tensor3D&y);
	Tensor3D(Tensor3D&&);
	Tensor3D& operator=(const Tensor3D&);
	Tensor3D& operator=(Tensor3D&&);

	std::array<std::size_t, 3> getShape();
	void transpose();					 									 
	std::vector<double> flatten() const;
	void printElements();
	friend void swap(Tensor3D&, Tensor3D&);

	//operator cv::Mat() const; // [DAVID] - to implement
	double& at(int i, int j, int k); // [DAVID] - to implement
};

