#pragma once
#include <iostream>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <array>

enum ORIENTATION { HORIZONTAL, VERTICAL };

class Tensor {
public:
	virtual ~Tensor() noexcept {}
	virtual std::array<std::size_t, 2> getShape() = 0;
	virtual std::vector<double> flatten() = 0;
	virtual void transpose() = 0;
	virtual void printElements() = 0;
};

class Tensor1D : public Tensor {
	double* data;
	std::size_t size;
	std::array<std::size_t, 2> shape; // shape[0] = row, shape[1] = column;
public:
	
	Tensor1D() : data{ nullptr }, size{ 0 }, shape{0}{}
	Tensor1D(std::initializer_list<double> data_, ORIENTATION m_n_ = HORIZONTAL ); // works 
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
};

class Tensor2D : public Tensor {
	double** data;
	std::array<std::size_t, 2> shape; // shape[0] = row, shape[1] = column;
public:

	Tensor2D(std::initializer_list<std::initializer_list<double>> data_, ORIENTATION m_n_ = HORIZONTAL);

	~Tensor2D() noexcept;

	//Tensor2D(const Tensor2D&);
	//Tensor2D(Tensor2D&&);
	//Tensor2D& operator=(const Tensor2D&);
	//Tensor2D& operator=(Tensor2D&&);

	///std::array<std::size_t, 2> getShape();
	void printElements() override;
	void transpose() override;								 									 
	std::vector<double> flatten() override;
	//friend void swap(Tensor2D&, Tensor2D&);
	
};
/*
class Tensor3D : public Tensor {
	std::vector<Tensor2D> data;



	double*** data;
	std::size_t elementsCount;
	std::array<std::size_t, 3> shape; // m x n x z ??
public:
	Tensor3D(double*** d = nullptr) :  {

		std::size_t rows = sizeof d / sizeof d[0];
		std::size_t cols = sizeof d[0] / sizeof(double);
		std::size_t depth = ;

		data = new double**[depth];
		for (int i = 0; i < depth; ++i) {
			data[depth] = new double* [rows];
			for (int k = 0; k < rows; ++k) {
				data[depth][rows] = new double[cols];
			}
		}

		for (int i = 0; i < depth; ++i) {
			for (int k = 0; k < rows; ++k) {
				for (int j = 0; j < cols; ++j) {
					data[i][k][j] = d[i][k][j];
				}
			}
		}
		
		shape[0] = depth;
		shape[1] = rows;
		shape[2] = cols;
		elementsCount = depth * rows * cols;
	}

	~Tensor3D() noexcept {
		for (int i = 0; i < shape[0]; ++i) {
			for (int k = 0; k < shape[1]; ++k) {{
					delete[] data[i][k];	
			}
			delete[] data[i];
		}
		delete[] data;
	}

	
};*/

