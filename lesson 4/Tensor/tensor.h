#pragma once
#include <iostream>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <array>

class Tensor {
public:
	virtual ~Tensor() noexcept {}

	virtual std::vector<std::size_t> getShape() = 0;
	virtual std::vector<double> flatten() = 0;
	virtual void printElements() = 0;
	virtual void transpose() = 0;
};

class Tensor1D : public Tensor {
	double* data;
	std::size_t elementCount;

public:
	Tensor1D(double d = 0.);
	
	Tensor1D(const Tensor1D&);
	Tensor1D(Tensor1D&&);
	Tensor1D& operator=(const Tensor1D&);
	Tensor1D& operator=(Tensor1D&&);

	virtual ~Tensor1D() noexcept;

	std::vector<std::size_t> getShape() override;

	std::vector<double> flatten() override;

	void printElements() override;

	void transpose() override;
};

class Tensor2D : public Tensor {
	double** data;
	std::size_t elementsCount;
	std::array<std::size_t, 2> shape;

public:
	Tensor2D(Type);
	~Tensor2D() noexcept;

	Tensor2D(const Tensor2D&);
	Tensor2D(Tensor2D &&);
	Tensor2D& operator=(const Tensor2D&);
	Tensor2D& operator=(Tensor2D&&);

	std::vector<std::size_t> getShape();

	std::vector<double> flatten() override;

	void printElements() override;

	void transpose() override;

	friend void swap(Tensor2D&, Tensor2D&);

};

class Tensor3D : public Tensor {
	//todo
};