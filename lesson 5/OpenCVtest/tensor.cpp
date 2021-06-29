#include "tensor.h"
#include "Exception.h"
#include <iterator>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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

/*template <typename destIterator>
void Tensor2D::allocate2D(const std::size_t rowSize, const std::size_t columnSize, destIterator it) {
	data = new double* [rowSize];
	for (std::size_t i = 0; i < rowSize; ++i) {
		data[i] = new double[columnSize];
	
		for (std::size_t j = 0; j < columnSize; ++j) {
			data[i][j] = *it++;
		}
	}
}*/

void Tensor2D::allocate2D(const std::size_t rowSize, const std::size_t columnSize, const double defaultVal) {
	data = new double* [rowSize];
	std::vector<double> val(columnSize, defaultVal);
	for (std::size_t i = 0; i < rowSize; ++i) {
		data[i] = new double[columnSize];
		std::copy(val.begin(), val.end(), &data[i][0]);
	}
}

template <typename destIterator>
void Tensor2D::allocate2D(const std::size_t rowSize, const std::size_t columnSize, destIterator it) {
	data = new double* [rowSize];
	for (std::size_t i = 0; i < rowSize; ++i) {
		data[i] = new double[columnSize];
		std::copy(it+(i*columnSize), it+((i+1)*columnSize), &data[i][0]);
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

/*double Tensor2D::convolve3(int i, int j, const std::vector<double>& kernel) {
	int iKernel = 0;
	double res = 0;

	std::pair<int, int> leftTopPoint(i - 1, j - 1);
	std::pair<int, int> rightBottomPoint(i + 1, j + 1);

	double d = data[0][0];
	for (int row = leftTopPoint.first; row <= rightBottomPoint.first; ++row) {
		for (int col = leftTopPoint.second; col <= rightBottomPoint.second; ++col) {
			double pixelValue = 0;
			if (row >=0 && col >= 0 && row < shape[0] && col <= shape[1]) {
				pixelValue = data[row][col];
			}

			res += kernel[iKernel++] * pixelValue;
		}
	}
	return res;
}*/



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
	if (row >= shape[0] || row < 0 || colum >= shape[1] || colum < 0) {
		throw WrongSize();
	}
		data[row][colum] = value;
}

double& Tensor2D::getValue(std::size_t row, std::size_t column ){
	if ( row >= shape[0] || row < 0 || column >= shape[1] || column < 0) {
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
		//std::copy(tmp.begin() + i * right.shape[1], tmp.end() - (right.shape[1]*(right.shape[1]-i+1 )),std::back_inserter(tmpTens.data[i][0]));
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
	for (int row = i-1, index = 0; row < i+2; ++row) {
		for (int col = j-1; col < j+2; ++col) {
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
			Tensor2D tmp_mono(mat);
			data.push_back(tmp_mono);
			shape = { (std::size_t)channels, (std::size_t)mat.rows, (std::size_t)mat.cols };
			break;
		}
		case 3: {
			cv::Mat chans[3];
			cv::split(mat, chans);
			Tensor2D tmp_B(chans[0]), tmp_G(chans[1]), tmp_R(chans[2]);
			data = { tmp_B, tmp_G, tmp_R };
			shape = { (std::size_t)channels, (std::size_t)mat.rows, (std::size_t)mat.cols };
			break;
		}
		default: {
			throw WrongSize();
		}
	}
}
void Tensor3D::pushChannel(const Tensor2D& channel) {
	data.push_back(channel);
	++shape[0];
}
double& Tensor3D::at(std::size_t channel, std::size_t row, std::size_t column) {
	if (channel >= shape[0] || channel < 0 || row >= shape[1] || row < 0 || column >= shape[1] || column < 0) {
		throw WrongSize();
	}
	return data[channel].getValue(row, column);
}

Tensor3D::operator cv::Mat() {
	switch (shape[0]) {
		case 1: {
			cv::Mat tmp = fillDataInMat(shape[0]);
			return tmp;
		}
		case 3: {
			cv::Mat mat;
			std::vector<cv::Mat> channels;
			for (int channel = 1; channel <= shape[0]; ++channel) {
				cv::Mat tmp = fillDataInMat(channel);
				channels.push_back(std::move(tmp));
			}
			cv::merge(channels, mat);
			std::cout << " XXXXXXXXXXXXX  END of operator cv:: MAT function XXXXXXXXXXXXXXXXXX " << std::endl;
			return mat;
		}
		default: { throw WrongSize();}
	}
}

cv::Mat Tensor3D::fillDataInMat(int channel) {
	if (channel <= shape[0] && channel > 0) {
		cv::Mat tmp(shape[1], shape[2], CV_8U);
		for (int row = 0; row < shape[1]; ++row) {
			std::vector<double> row_buffer_double = data[channel-1].getRow(row);
			std::vector<uchar> row_buffer_uchar(row_buffer_double.size());

			/*uchar y = 0;
			std::transform(row_buffer_double.begin(), row_buffer_double.end(),
				std::back_inserter(row_buffer_uchar), [&y](double x) { return y = (uchar)x; });*/

			std::transform(row_buffer_double.begin(), row_buffer_double.end(),
				std::back_inserter(row_buffer_uchar), [](double x) { return (uchar)x; }); // check function !!!

			std::memcpy(tmp.row(row).data, row_buffer_uchar.data(),
				row_buffer_uchar.size() * sizeof(uchar));
		}
		std::cout << " XXXXXXXXXXXXXXX  fill mat  XXXXXXXXXXXXXXXX " << std::endl;
		return tmp;
	}
	else {
		throw WrongSize();
	}
}

Tensor3D::Tensor3D(const std::string& filePath, imreadType type) {
	cv::Mat imag;
	if (type == GRAY) {
		imag = cv::imread(filePath, cv::IMREAD_GRAYSCALE);
	}
	else if (type == RGB) {
		imag = cv::imread(filePath, cv::IMREAD_COLOR);
	}
	Tensor3D tmp(imag);
	swap(*this, tmp);
}
 
bool Tensor3D::operator==(Tensor3D& right) {
	if (shape != right.shape) { return false; }

	for (std::size_t channels = 0; channels < shape[0]; ++channels) {
		for (std::size_t row = 0; row < shape[1]; ++row) {
			for (std::size_t col = 0; col < shape[2]; ++col) {
				if(data[channels].getValue(row,col) != right.data[channels].getValue(row, col)) {
					return false;
				}
			}
		}
	}
	return true;
}

void Tensor3D::setValue(int channel, int row, int column, double value) {
	if (channel >= shape[0] || channel < 0 || row >= shape[1] || row < 0 || column >= shape[1] || column < 0) {
		throw WrongSize();
	}
	data[channel].setValue(row, column, value);
}


void Tensor3D::man_to_0_250() {
	switch (shape[0]) {
		case 3: {
			for (int i = 0; i < shape[1]; ++i) {
				for (int j = 0; j < shape[2]; ++j) {
					if (at(0, i, j) > 100) {
						setValue(0, i, j, 250);
					}
					else {
						setValue(0, i, j, 0);
					}
					if (at(1, i, j) > 100) {
						setValue(1, i, j, 250);
					}
					else {
						setValue(1, i, j, 0);
					}
					if (at(2, i, j) > 100) {
						setValue(2, i, j, 250);
					}
					else {
						setValue(2, i, j, 0);
					}
				}
			}
		}  
	}
}

Tensor3D& Tensor3D::convolve(const std::vector<double>& kernel) {
	for (Tensor2D& channelMat : data) {
		channelMat.convolve(kernel);
	}

	return *this;
}
