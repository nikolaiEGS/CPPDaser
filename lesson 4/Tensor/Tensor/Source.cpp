#include "tensor.h"

int main() {
	/*Tensor1D d({1,2,3,4}, ORIENTATION::VERTICAL);
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
	}*/

	//-------------------- TENSOR 2D -------------------------------------------------------------------
	Tensor2D tt({ { 10,20,30,40 }, {10, 20, 99, 44} });
	tt.printElements();
	//Tensor2D yy(tt);
	Tensor2D yy(std::move(tt));
	yy.printElements();
	std::cout << "COPYASS" << std::endl;
	//Tensor2D zz = yy;
	Tensor2D zz = std::move(yy);
	zz.printElements();
	
	std::array<std::size_t, 2> shape_2D = zz.getShape();
	std::cout << "SHAPE 2 D" << std::endl;
	std::cout << "row = " << shape_2D[0] << std::endl;
	std::cout << "column = " << shape_2D[1] << std::endl;
	//zz.transpose();
	//zz.printElements();
	
	/*Tensor2D d2({ {1,2,3}, {4,5,6, 7} });
	d2.printElements();*/
	return 0;
}