#include "tensor.h"
#include "Exception.h"



int main() {
	Tensor1D d({ 1,2,3,4 });
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
	std::cout << "row = " << shape_t[0] << std::endl;
	std::cout << "column = " << shape_t[1] << std::endl;
	std::vector<double> flattend = d.flatten();
	std::cout << "FLATTEND" << std::endl;
	for (auto x : flattend) {
		std::cout << x << std::endl;
	}

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
	zz.transpose();
	zz.printElements();
	try {
		Tensor2D d2({ {1,2,3}, {4,5,6, 7} });
	}
	catch (WrongShapeTensorException& e) {
		std::cout << e.what() << std::endl;
	}
	std::vector<double> flat = zz.flatten();
	for (double x : flat) {
		std::cout << x << " " << std::flush;
	}

	Tensor2D defVal(5, 5, 2.2);
	defVal.printElements();

	Tensor2D empty(5, 5);
	//empty.setValue(99.99);
	//empty.printElements();

	Tensor2D uu({ { 1,2,4 }, { 1,2,3 } });
	Tensor2D ii({ { 1,2,3 }, { 1,2,3 } });


	std::cout << "++++++ TEST TENSOR 3D +++++++" << std::endl;
	Tensor3D ddd({ uu, ii });
	try {
		Tensor3D test({ uu, ii });
		test.printElements();
	}
	catch (WrongShapeTensorException& e) {
		std::cout << e.what() << std::endl;
	}
	//std::cout << "++++++ COPY +++++++" << std::endl;
	//Tensor3D dddd({ uu, ii });
	//Tensor3D copy(dddd);
	//copy.printElements();
	std::cout << "?????????????????????" << std::endl;
	Tensor2D vv(zz);
	vv.printElements();
	std::cout << "?????????????????????" << std::endl;
	//Tensor3D copy(std::move(dddd));
	//copy.printElements();
	std::cout << "++++++ =ASS +++++++" << std::endl;
	//Tensor3D ass;
	//ass = std::move(copy);
	//ass.printElements();
	//ass.transpose();
	//ass.printElements();

	/*std::vector<double> flat3D = ass.flatten();
	for (double x : flat3D) {
		std::cout << x << " " << std::flush;
	}

	Tensor3D xxx({ { { 1,2,4 }, { 1,2,3 } }, { { 1,2,4 }, { 1,2,3 } }, { { 1,2,4 }, { 1,2,3 } } });

	xxx.printElements();*/

	return 0;
}