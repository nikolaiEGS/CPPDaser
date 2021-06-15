#include "tensor.h"

int main() {
	Tensor1D d({1,2,3,4}, ORIENTATION::VERTICAL);
	d.printElements();
	Tensor1D dd(d);
	dd.printElements();
	//Tensor1D ddd(std::move(d));
	//ddd.printElements();
	Tensor1D c({ 3,3,3,3 });
	//d = c;
	d = std::move(c);
	d.printElements();
	Tensor1D t({ 10,20,30,40 });
	t.printElements();
	t.transpose();
	t.printElements();
	std::array<std::size_t, 2> shape_t = t.getShape();
	std::cout << "SHAPE" << std::endl;
	std::cout << "row = " <<shape_t[0]<< std::endl;
	std::cout << "column = " << shape_t[1]<<std::endl;
	std::vector<double> flattend =	d.flatten();
	std::cout << "FLATTEND" << std::endl;
	for (auto x : flattend) {
		std::cout << x << std::endl;
	}
	Tensor2D tt({ { 10,20,30,40 }, {10, 20, 99, 99} });
	//tt.printElements();

	
	
	
	
	/*Tensor2D d2({ {1,2,3}, {4,5,6, 7} });
	d2.printElements();*/
	return 0;
}