#include "tensor2D.h"

void Tensor2D::initializeWith(const double val) {
	for (std::size_t i = 0; i < shape[0]; ++i) {
		for (std::size_t k = 0; k < shape[1]; ++k) {
			data[i][k] = val;
		}
	}
}

void Tensor2D::allocate2D(const std::size_t rowSize, const std::size_t columnSize) {
	data = new double* [rowSize];
	for (std::size_t row = 0; row < rowSize; ++row) {
		data[row] = new double[columnSize];
	}
}

void Tensor2D::allocate2D(const std::size_t rowSize, const std::size_t columnSize, const double defaultVal) {
	data = new double* [rowSize];
	std::vector<double> val(columnSize, defaultVal);
	for (std::size_t row = 0; row < rowSize; ++row) {
		data[row] = new double[columnSize];
		std::copy(val.begin(), val.end(), &data[row][0]);
	}
}

template <typename destIterator>
void Tensor2D::allocate2D(const std::size_t rowSize, const std::size_t columnSize, destIterator it) {
	data = new double* [rowSize];
	for (std::size_t i = 0; i < rowSize; ++i) {
		data[i] = new double[columnSize];
		std::copy(it + (i * columnSize), it + ((i + 1) * columnSize), &data[i][0]);
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

Tensor2D::Tensor2D(char* image_rec, std::size_t begin, std::size_t rowSize, std::size_t colSize) {
	allocate2D(rowSize, colSize);
	shape = { rowSize, colSize };
	int indexCharArr = begin;
	for (int row = 0; row < rowSize; ++row) {
		for (int col = 0; col < colSize; ++col) {
			setValue(row, col, (double)image_rec[indexCharArr++]);
		}
		
	}
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
	for (std::size_t row = 0; row < shape[0]; ++row) {
		std::for_each(&data[row][0], &data[row][shape[1] - 1], [](const double printVal) {
			std::cout << "NR: " <<printVal << " " << std::flush; });
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
	if (row >= shape[0] || row < 0 || colum >= shape[1] || colum < 0) {
		throw WrongSize();
	}
	data[row][colum] = value;
}

double& Tensor2D::getValue(std::size_t row, std::size_t column) {
	if (row >= shape[0] || row < 0 || column >= shape[1] || column < 0) {
		throw WrongSize();
	}
	return data[row][column];
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
		for (std::size_t k = 0; k < shape[0]; ++k) {
			tmpTens.data[i][k] = tmp[help++];
		}
	}
	shape[1] = right.shape[1];
	swap(*this, tmpTens);
	return *this;
}

Tensor2D::Tensor2D(const cv::Mat& mat) {
	const int channels = mat.channels();
	if (channels == 1) {
		shape = { (std::size_t)mat.rows, (std::size_t)mat.cols };
		if (mat.isContinuous()) {
			allocate2D(mat.rows, mat.cols, mat.begin<uchar>());
		}
		else {
			allocate2D(mat.rows, mat.cols);
			for (int i = 0; i < mat.rows; ++i) {
				for (int j = 0; j < mat.cols; ++j) {
					setValue(i, j, mat.at<uchar>(i, j));
				}
			}
		}
	}
	else {
		throw WrongSize();
	}
}

std::vector<uchar> Tensor2D::change2uchar() {
	std::vector<uchar> tmp;
	std::vector<double> flattend = flatten();
	for (std::size_t i = 0; i < flattend.size(); ++i) {
		tmp.push_back((uchar)flattend[i]);
	}
	return tmp;
}

std::vector<double> Tensor2D::getRow(int row) {
	if (row < shape[0] && row >= 0) {
		std::vector<double> tmp;
		std::copy(&data[row][0], &data[row][shape[1]], std::back_inserter(tmp));
		return tmp;
	}
	else {
		throw WrongSize();
	}
}

std::vector<double> Tensor2D::getColumn(int column) {
	if (column < shape[1] && column >= 0) {
		std::vector<double> tmp;
		for (int k = 0; k < shape[0]; ++k) {
			tmp.push_back(data[k][column]);
		}
		return tmp;
	}
	else {
		throw WrongSize();
	}
}


double Tensor2D::convolve3(int i, int j, const std::vector<double>& kernel) {
	double sum = 0;
	for (int row = i - 1, index = 0; row < i + 2; ++row) {
		for (int col = j - 1; col < j + 2; ++col) {
			if (row >= 0 && col >= 0 && row < shape[0] && col < shape[1]) {
				sum += data[row][col] * kernel[index];
			}
			++index;
		}
	}
	return sum;
}

Tensor2D& Tensor2D::convolve(const std::vector<double>& kernel) {
	assert(kernel.size() == 9);
	Tensor2D convolvedChannel(shape[0], shape[1]);

	for (int i = 0; i < shape[0]; ++i) {
		for (int j = 0; j < shape[1]; ++j) {
			convolvedChannel.data[i][j] = convolve3(i, j, kernel);
		}
	}
	swap(*this, convolvedChannel);
	return *this;
}