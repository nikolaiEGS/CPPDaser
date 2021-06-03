#include <memory>
#include <iostream>
#include "unique_ptr.h"


struct Test {
	Test() = default;
	Test(int nb) : A(nb){}
	~Test() {
		//std::cout << "DELETE -- Test destructor"<<std::endl;

	}
	void print() {
		std::cout << "print"<<std::endl;
		std::cout << std::endl;
	}

	int A;
};

int main() {

// -------- unique ptr ----------------------------------------------------------------------------------------
	std::unique_ptr<Test> ptr(new Test());
	std::unique_ptr<Test[]> arr(new Test[20]);
	//std::unique_ptr<Test, void (*)(Test*)> t(new Test, [](Test* tt) {tt->print(); });

	smartPtr::unique_ptr<Test, std::function<void(Test*)>> test(new Test, [](Test* XX) { std::cout << "pointerFunction called" << std::endl; });
	test->print();
	(*test).print();
	//test.reset();
	smartPtr::unique_ptr<Test, std::function<void(Test*)>> tt(new Test, [](Test* XX) { /*delete[] XX;*/ std::cout << "pointerFunction called" << std::endl; });
	//std::cout << "print member string: "<<tt->A << std::endl;
	smartPtr::unique_ptr<Test, std::function<void(Test*)>> ttt;
	//ttt = (std::move(tt));
	//tt = test;
	
// -------- shared ptr ----------------------------------------------------------------------------------------	
	smartPtr::shared_ptr<Test, std::function<void(Test*)>> cc(new Test(999));
	smartPtr::shared_ptr<Test, std::function<void(Test*)>> zz;
	smartPtr::shared_ptr<Test, std::function<void(Test*)>> gg(cc);
	smartPtr::shared_ptr<Test, std::function<void(Test*)>> ff(new Test(1111));
	smartPtr::shared_ptr<Test, std::function<void(Test*)>> jj(std::move(ff));
	ff.showCount();
	//ff = gg;
	cc.showCount();
	ff.showCount();


	//gg.showCount();

	//smartPtr::shared_ptr<Test, std::function<void(Test*)>> nn(cc);
	//std::cout << gg->A << std::endl;
	//gg.showCount();



	/*smartPtr::shared_ptr<Test> xx;
	xx->print();
	smartPtr::shared_ptr<Test> yy(xx);
	yy->print();
	smartPtr::shared_ptr<Test> kk;
	kk = yy;*/
	return 0;
}