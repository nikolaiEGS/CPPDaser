#include "tensor.h"
#include "Exception.h"
/*
Tensor1D::Tensor1D(std::initializer_list<double> data_, Orientation m_n_)
	: data{ new double[data_.size()]() }, size{ data_.size() } {

	//shape((m_n_ == HORIZONTAL) ? {1, data_.size()} : {data_.size(), 1 });
	if (m_n_ == Orientation::HORIZONTAL) {
		shape[0] = 1;
		shape[1] = data_.size();
	}
	else {
		shape[0] = data_.size();
		shape[1] = 1;
	}
	std::size_t i = 0;
	for (const auto& val : data_) {
		data[i] = val;
		++i;
	}
}

Tensor1D::~Tensor1D() {
	delete[] data;
}

Tensor1D::Tensor1D(const Tensor1D& copyObj) {
	data = new double[copyObj.size];
	size = copyObj.size;
	shape = copyObj.shape;
	for (std::size_t i = 0; i < size; ++i) {
		data[i] = copyObj.data[i];
	}
}

Tensor1D::Tensor1D(Tensor1D&& moveObj): Tensor1D() {
	swap(*this, moveObj);
}

Tensor1D& Tensor1D::operator=(const Tensor1D& copyAss) {
	Tensor1D tmp(copyAss);
	swap(*this, tmp);
	return *this;
}

Tensor1D& Tensor1D::operator=(Tensor1D&& moveAss) {
	swap(*this, moveAss);
	return *this;
}
void swap(Tensor1D& left, Tensor1D& right) {
	std::swap(left.data, right.data);
	std::swap(left.size, right.size);
	std::swap(left.shape, right.shape);
}

void Tensor1D::transpose() {
	Tensor1D tmp(*this);
	for (std::size_t k = 0, i = size - 1; k < size; ++k, --i) {
			data[k] = tmp.data[i];
	}
}

std::array<std::size_t, 2> Tensor1D::getShape() {
	return shape;
}

std::vector<double> Tensor1D::flatten() {
	std::vector<double> flattend;
	for (std::size_t i = 0; i < size; ++i ) {
		double tmp = data[i];
		flattend.push_back(tmp);
	}
	return flattend;
} 

void Tensor1D::printElements(){
	for (std::size_t i = 0; i < size; ++i) {
		std::cout << data[i] << " , " << std::flush;
	}
	std::cout << std::endl;
}
*/
/// ////////////////////////////////////////////////////

Tensor2D::Tensor2D(std::initializer_list<std::initializer_list<double>> data_, Orientation m_n_) {
	std::size_t row, column;

	auto* it = data_.begin();
	std::size_t in_size = it->size(); // {{in_size}, {in_size}}
	
	while (++it != data_.end()) {
		try {
			if (in_size != it->size()) {
				throw Exception(" !!!!!! wrong size !!!!!!\n");
			}
		}
		catch (Exception& e) {
			std::cout << e.getMessage() << std::endl;
		}
	}
	
	if (m_n_ == Orientation::HORIZONTAL) {
		row = data_.size();
		column = in_size;
	}
	else {
		row = in_size;
		column = data_.size();
	}
	
	shape[0] = row;     // not so nice, maybe a nother solution?
	shape[1] = column; // not so nice, maybe a nother solution?

	data = new double* [row];
	for (std::size_t i = 0; i < row; ++i) {
		data[i] = new double[column];
	}

	std::size_t i = 0;
	for (const auto& tmp : data_) {
		double* copyElem = data[i];
		std::copy(tmp.begin(), tmp.end(), copyElem );
		++i;
	}
}

Tensor2D::~Tensor2D() {
	std::size_t row = shape[0];
	for (std::size_t i = 0; i < row; ++i) {
		delete[] data[i];
	}
	delete[] data;
}

Tensor2D::Tensor2D(const Tensor2D& copyObj) {
	shape = copyObj.shape;
	std::size_t row = shape[0];
	std::size_t column = shape[1];

	data = new double* [row];
	for (std::size_t i = 0; i < row; ++i) {
		data[i] = new double[column];
	}

	for (std::size_t i = 0; i < row; ++i) {
		for (std::size_t k = 0; k < column; ++k) {
			data[i][k] = copyObj.data[i][k];
		}
	}
}

Tensor2D::Tensor2D(Tensor2D&& moveObj) : Tensor2D() {
	swap(*this, moveObj);
}

void swap(Tensor2D& left, Tensor2D& right) {
	std::swap(left.data, right.data);
	std::swap(left.shape, right.shape);
}

void Tensor2D::printElements() {
	std::size_t row = shape[0];
	std::size_t column = shape[1];

	for (std::size_t i = 0; i < row; ++i) {
		for (std::size_t k = 0; k < column; ++k) {
			std::cout << data[i][k] << " , " << std::flush;
		}
		std::cout << std::endl;
	}
}

Tensor2D& Tensor2D::operator=(const Tensor2D&copyAss) {
	Tensor2D tmp(copyAss);
	swap(*this, tmp);
	return *this;
}

Tensor2D& Tensor2D::operator=(Tensor2D&& moveAss) {
	swap(*this, moveAss);
	return *this;
}

std::array<std::size_t, 2> Tensor2D::getShape() {
	return shape;
}

void Tensor2D::transpose() {
	Tensor2D tmp;
	std::size_t row_trans = shape[1];
	std::size_t column_trans = shape[0];
	
	tmp.data = new double* [row_trans];
	for (std::size_t i = 0; i < row_trans; ++i) {
		tmp.data[i] = new double[column_trans];
	}
	
	std::size_t row = shape[0];
	std::size_t column = shape[1];

	for (std::size_t i = 0; i < row; ++i) {
		std::cout << "++++ insigt for 1 ++++" << std::endl;
		for (std::size_t k = 0; k < column; ++k) {
			std::cout << "++++ insigt for 2 ++++" << std::endl;
			tmp.data[k][i] = data[i][k];
		}
	}
	swap(*this, tmp);
}

std::vector<double> Tensor2D::flatten() {
	std::vector<double> flattend;

	std::size_t row = shape[0];
	std::size_t column = shape[1];

	for (std::size_t i = 0; i < row; ++i) {
		for (std::size_t k = 0; k < column; ++k) {
			double tmp = data[i][k];
			flattend.push_back(tmp);
		}
	}
	return flattend;
}