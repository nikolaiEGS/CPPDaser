#include "tensor3D.h"

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
			Tensor2D tmp_B(std::move(chans[0])), tmp_G(std::move(chans[1])), tmp_R(std::move(chans[2]));
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
			std::vector<uchar> row_buffer_uchar;
			std::transform(row_buffer_double.begin(), row_buffer_double.end(),
				std::back_inserter(row_buffer_uchar), [](double x) { return (uchar)x; }); // check function !!!

			std::memcpy(tmp.row(row).data, row_buffer_uchar.data(),
				row_buffer_uchar.size() * sizeof(uchar));
		}
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
	Tensor3D tmp(std::move(imag));
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
