#pragma once
#include <vector>
#include <array>

class Tensor {
public:
	virtual ~Tensor() noexcept {}
	virtual std::array<std::size_t, 2> getShape() const = 0;
	virtual std::vector<double> flatten() const = 0;
	virtual void transpose() = 0;
	virtual void printElements() const = 0;
};
