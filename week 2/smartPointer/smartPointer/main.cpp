#include <memory>
#include <iostream>
#include "unique_ptr.h"


struct Test {

	~Test() {
		std::cout << "DELETE"<<std::endl;
	}
	void print() {
		std::cout << "print"<<std::endl;
		std::cout << std::endl;
	}
};

int main() {
	std::unique_ptr<Test> ptr(new Test());
	std::unique_ptr<Test[]> arr(new Test[20]);
	//std::unique_ptr<Test, void (*)(Test*)> t(new Test, [](Test* tt) {tt->print(); });

	smartPtr::unique_ptr<Test, std::function<void(Test*)>> test(new Test, [](Test* XX) { std::cout << "pointerFunction called" << std::endl; });
	test->print();
	(*test).print();
	test.reset();
	smartPtr::unique_ptr<Test, std::function<void(Test*)>> tt(new Test, [](Test* XX) { std::cout << "pointerFunction called" << std::endl; });
	//tt = test;
	//smartPtr::unique_ptr<Test, std::function<void(Test*)>> cc(test);
	smartPtr::shared_ptr<Test> xx;
	xx->print();
	smartPtr::shared_ptr<Test> yy(xx);
	yy->print();
	smartPtr::shared_ptr<Test> kk;
	kk = yy;
	return 0;
}