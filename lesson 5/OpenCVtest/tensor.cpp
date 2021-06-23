#include "tensor.h"
#include "Exception.h"
#include <iterator>

Tensor1D::Tensor1D(std::initializer_list<double> data_, Orientation m_n_)
	: data{ new double[data_.size()]() }, size{ data_.size() } {
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

Tensor1D::Tensor1D(Tensor1D&& moveObj) : Tensor1D() {
	swap(*this, moveObj);
}

Tensor1D& Tensor1D::operator=(const Tensor1D& copyAss) {
	Tensor1D tmp(copyAss);
	swap(*this, tmp);
	return *this;
}

Tensor1D& Tensor1D::operator=(Tensor1D&& moveAss) {
	Tensor1D tmp(std::move(moveAss));
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

std::array<std::size_t, 2> Tensor1D::getShape() const {
	return shape;
}

std::vector<double> Tensor1D::flatten() const {
	std::vector<double> flattend(size);
	std::copy(&data[0], &data[size], flattend.begin());
	return flattend;
}

void Tensor1D::printElements() const {
	for (std::size_t i = 0; i < size; ++i) {
		std::cout << data[i] << " " << std::flush;
	}
	std::cout << std::endl;
}

/// /////////////// TENSOR 2 D /////////////////////////////////////

void Tensor2D::initializeWith(const double val) {
	for (std::size_t i = 0; i < shape[0]; ++i) {
		for (std::size_t k = 0; k < shape[1]; ++k) {
			data[i][k] = val;
		}
	}
}

void Tensor2D::allocate2D(const std::size_t rowSize, const std::size_t columnSize) {
	data = new double* [rowSize];
	for (std::size_t i = 0; i < rowSize; ++i) {
		data[i] = new double[columnSize];
	}
}

void Tensor2D::allocate2D(const std::size_t rowSize, const std::size_t columnSize, const double defaultVal) {
	data = new double* [rowSize];
	std::vector<double> val(columnSize, defaultVal);
	for (std::size_t i = 0; i < rowSize; ++i) {
		data[i] = new double[columnSize];
		std::copy(val.begin(), val.end(), &data[i][0]);
	}
}

Tensor2D::Tensor2D(std::initializer_list<std::initializer_list<double>> data_) {
	auto* it = data_.begin();
	std::size_t in_size = it->size();

	while (++it != data_.end()) {
		if (in_size != it->size()) {
			throw WrongShapeTensorException();
		}
	}

	shape = { data_.size(), in_size };
	allocate2D(shape[0], shape[1]);

	std::size_t i = 0;
	for (const auto& tmp : data_) {
		std::copy(tmp.begin(), tmp.end(), data[i++]);
	}
}

Tensor2D::Tensor2D(const std::size_t m, const std::size_t n) : shape{ m, n } {
	allocate2D(m, n);
}

Tensor2D::Tensor2D(const std::size_t m, const std::size_t n, const double defaultVal) : shape{ m, n } {
	allocate2D(m, n, defaultVal);
}
Tensor2D::~Tensor2D() {
	for (std::size_t i = 0; i < shape[0]; ++i) {
		delete[] data[i];
	}
	delete[] data;
}

Tensor2D::Tensor2D(const Tensor2D& copyObj) {
	shape = copyObj.shape;
	allocate2D(shape[0], shape[1]);

	for (std::size_t i = 0; i < shape[0]; ++i) {
		std::copy(&copyObj.data[i][0], &copyObj.data[i][shape[1]], &data[i][0]);
	}
}

Tensor2D::Tensor2D(Tensor2D&& moveObj) : Tensor2D() {
	swap(*this, moveObj);
}

void swap(Tensor2D& left, Tensor2D& right) {
	std::swap(left.data, right.data);
	std::swap(left.shape, right.shape);
}

void Tensor2D::printElements() const {
	for (std::size_t i = 0; i < shape[0]; ++i) {
		for (std::size_t k = 0; k < shape[1]; ++k) {
			std::cout << data[i][k] << " " << std::flush;
		}
		std::cout << std::endl;
	}
}

Tensor2D& Tensor2D::operator=(const Tensor2D& copyAss) {
	Tensor2D tmp(copyAss);
	swap(*this, tmp);
	return *this;
}

Tensor2D& Tensor2D::operator=(Tensor2D&& moveAss) {
	Tensor2D tmp(std::move(moveAss));
	swap(*this, tmp);
	return *this;
}

std::array<std::size_t, 2> Tensor2D::getShape() const {
	return shape;
}

void Tensor2D::transpose() {
	Tensor2D tmp(shape[1], shape[0]);
	for (std::size_t i = 0; i < shape[0]; ++i) {
		for (std::size_t k = 0; k < shape[1]; ++k) {
			tmp.data[k][i] = data[i][k];
		}
	}
	swap(*this, tmp);
}

std::vector<double> Tensor2D::flatten() const {
	std::vector<double> flattend(shape[0] * shape[1]);
	for (std::size_t i = 0; i < shape[0]; ++i) {
		std::copy(&data[i][0], &data[i][shape[1]], flattend.begin() + i * shape[1]);
	}
	return flattend;
}

void Tensor2D::setValue(int row, int colum, double value) {
	data[row][colum] = value;
}

double& Tensor2D::getValue(std::size_t row, std::size_t column ){
	if ( row > shape[1] || row < 1 || column > shape[1] || column < 1) {
		throw WrongSize();
	}
	return data[row-1][column-1];
}

Tensor2D& Tensor2D::matmul(const Tensor2D& right) {
	if (shape[1] != right.shape[0]) {
		throw WrongSize();
	}
	std::vector<double> tmp;
	
	for (std::size_t i = 0; i < shape[0]; ++i) {
		for (std::size_t j = 0; j < right.shape[1]; ++j) {
			double sum = 0;
			for (std::size_t k = 0; k < right.shape[0]; ++k) {
				sum += data[i][k] * right.data[k][j];
			}
			tmp.push_back(sum);
		}
	}
	Tensor2D tmpTens(shape[0], right.shape[1]);
	int help = 0;
	for (std::size_t i = 0; i < shape[0]; ++i) {
		//std::copy(tmp.begin() + i * right.shape[1], tmp.end() - (right.shape[1]*(right.shape[1]-i+1 )),std::back_inserter(tmpTens.data[i][0]));
		for (std::size_t k = 0; k < shape[0]; ++k) {
			tmpTens.data[i][k] = tmp[help++];
		}
	}
	shape[1] = right.shape[1];
	swap(*this, tmpTens);
	return *this;
}
///////////////// TENSOR 3 D /////////////////////////////////////

Tensor3D::Tensor3D(std::initializer_list<Tensor2D> data_) {
	auto it = data_.begin();
	auto in_shape = it->getShape();
	for (std::size_t i = 0; i < data_.size() - 1; ++i) {
		if (in_shape != it->getShape()) { throw WrongShapeTensorException(); }
	}
	std::copy(data_.begin(), data_.end(), std::back_inserter(data));
	shape = { data.size(), in_shape[0], in_shape[1] };
}

void Tensor3D::printElements() {
	for (const auto& cur : data) {
		cur.printElements();
		std::cout << std::endl;
	}
}

void swap(Tensor3D& left, Tensor3D& right) {
	std::swap(left.data, right.data);
	std::swap(left.shape, right.shape);
}

Tensor3D::Tensor3D(const Tensor3D& copy) {
	data = copy.data;
	shape = copy.shape;
}

Tensor3D::Tensor3D(Tensor3D&& move) {
	swap(*this, move);
}

Tensor3D& Tensor3D::operator=(const Tensor3D& copyAss) {
	Tensor3D tmp(copyAss);
	swap(*this, tmp);
	return *this;
}

Tensor3D& Tensor3D::operator=(Tensor3D&& moveAss) {
	Tensor3D tmp(std::move(moveAss));
	swap(*this, tmp);
	return *this;
}

std::array<std::size_t, 3> Tensor3D::getShape() {
	return shape;
}

void Tensor3D::transpose() {
	for (auto& cur : data) { cur.transpose(); }
}

std::vector<double> Tensor3D::flatten() const {
	std::vector<double> flattend(shape[0] * shape[1] * shape[2]);
	std::size_t i = 0;
	for (auto& cur : data) {
		std::vector<double> tmp = cur.flatten();
		std::copy(tmp.begin(), tmp.end(), flattend.begin() + i++ * shape[1] * shape[2]);
	}
	return flattend;
}

Tensor3D::Tensor3D(const cv::Mat& mat) {
	const int channels = mat.channels();

	switch (channels) {
		case 1: {
			Tensor2D tmp(mat.rows, mat.cols);
			for (int i = 0; i < mat.rows; ++i) {
				for (int j = 0; j < mat.cols; ++j) {
					tmp.setValue(i, j, mat.at<uchar>(i, j));
				}
			}
			data.push_back(tmp);
			shape = { (std::size_t)channels, (std::size_t)mat.rows, (std::size_t)mat.cols };
			break;
		}
		case 3: {
			Tensor2D tmp_1(mat.rows, mat.cols);
			Tensor2D tmp_2(mat.rows, mat.cols);
			Tensor2D tmp_3(mat.rows, mat.cols);
			for (int i = 0; i < mat.rows; ++i) {
				for (int j = 0; j < mat.cols; ++j) {
					tmp_1.setValue(i, j, mat.at<cv::Vec3b>(i, j)[0]);
					tmp_2.setValue(i, j, mat.at<cv::Vec3b>(i, j)[1]);
					tmp_3.setValue(i, j, mat.at<cv::Vec3b>(i, j)[2]);
				}
			}
			data = { tmp_1, tmp_2, tmp_3 };
			shape = { (std::size_t)channels, (std::size_t)mat.rows, (std::size_t)mat.cols };
		}
	}
}

double& Tensor3D::at(std::size_t depth, std::size_t row, std::size_t column) {
	if (depth > shape[0] || depth < 1 || row > shape[1] || row < 1 || column > shape[1] || column < 1) {
		throw WrongSize();
	}
	return data[depth-1].getValue(row, column);
}

Tensor3D::operator cv::Mat() {
	//cv::Mat tmp((int)shape[1], (int)shape[2], (int)shape[0]);
	cv::Mat mat;

	switch (shape[0]) {
		case 1: {
			/*
			for (std::size_t i = 0; i < tmp.rows; ++i) {
				for (std::size_t j = 0; j < tmp.cols; ++j) {
					//tmp.at<uchar>(i, j) = (uchar)at(1, 1, 1);
				}
			}*/
			break;
		}
		case 3: {
			std::vector<cv::Mat> channels;

			for (int channel = 0; channel < shape[0]; ++channel) {
				cv::Mat tmp(shape[1], shape[2], CV_64F);
				//std::cout << "TMP: " << tmp << std::endl;
				for (int row = 0; row < shape[1]; ++row) {
					std::vector<double> rowV = data[channel].getRow(row);
					std::memcpy(tmp.row(row).data, rowV.data(), rowV.size() * sizeof(double));
				}
				//std::cout << "TMP: " << tmp << std::endl;
				
				channels.push_back(tmp);
			}
			cv::merge(channels, mat);

		}
	}
	return mat;
}
