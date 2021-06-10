#include "tensor.h"

int main() {

	Tensor1D d (758.54);

	d.printElements();
	d.flatten();


	Tensor2D d2({ {1,2,3}, {4,5,6} });
	d2.printElements();
	return 0;
}