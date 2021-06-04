#include <memory>
#include <iostream>
#include "unique_ptr.h"
#include "shared_ptr.h"
#include <list>

// ------------ UNIQUE POINTER ------------------------------
template <typename T, typename F>
unique_ptr<T,F>::~unique_ptr() {
	std::cout << "inside unique destructor " << std::endl;
	delete_ptr(this->ptr);
}

template <typename T, typename F>
unique_ptr<T,F>::unique_ptr(unique_ptr&& move_ptr) noexcept : unique_ptr() {
	swap(*this, move_ptr);
}

template <typename T, typename F>
unique_ptr<T,F>& unique_ptr<T,F>::operator=(unique_ptr&& move_ptr) noexcept {
	std::cout << "inside move assignement " << std::endl;
	unique_ptr<T, F> tmp(std::move(move_ptr));
	swap(*this, tmp);
	return *this;
}

template <typename T, typename F>
constexpr void unique_ptr<T,F>::swap(unique_ptr& left, unique_ptr& right) {
	std::swap(left.ptr, right.ptr);
	std::swap(left.delete_ptr, right.delete_ptr);
}

template <typename T, typename F>
void unique_ptr<T, F>::reset(T* t) {
	delete_ptr(this->ptr);
	ptr = t;
}


// ------------ SHARED POINTER ------------------------------
template <typename T, typename F>
shared_ptr<T, F>::~shared_ptr() noexcept {
	if (*count_ptr == 0 || --*count_ptr == 0) { 
		delete_ptr(this->ptr);
		delete count_ptr;
	}
}
template <typename T, typename F>
shared_ptr<T,F>::shared_ptr(const shared_ptr& copy) : ptr(copy.ptr), delete_ptr(copy.delete_ptr), count_ptr(copy.count_ptr) {
		if (ptr) { ++* count_ptr; }
}

template <typename T, typename F>
shared_ptr<T, F>::shared_ptr(shared_ptr&& move_ptr) noexcept : shared_ptr() {
	swap(*this, move_ptr);
}

template <typename T, typename F>
constexpr std::size_t shared_ptr<T,F>::count() const { return *count_ptr; }

template <typename T, typename F>
shared_ptr<T,F>& shared_ptr<T, F>::operator=(shared_ptr& assign) { // what is fi count_prt is 0 ?? count_ptr can not be negative, or??
	shared_ptr<T, F> tmp(assign);
	swap(*this, tmp);
	return *this;
}

template <typename T, typename F>
shared_ptr<T,F>& shared_ptr<T,F>::operator=(shared_ptr&& move_ptr) noexcept {
	shared_ptr tmp(std::move(move_ptr)); // what happens?, is destructor called?
	swap(*this, tmp);
	return *this;
}

template <typename T, typename F = std::function<void(T*)>>
void swap(shared_ptr<T,F>& left, shared_ptr<T,F>& right) {
	std::swap(left.ptr, right.ptr);
	std::swap(left.delete_ptr, right.delete_ptr);
	std::swap(left.count_ptr, right.count_ptr);
}

// ------------ HELP OBJECT ----------------------------------------------
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

	unique_ptr<Test, std::function<void(Test*)>> test(new Test, [](Test* XX) { std::cout << "pointerFunction called" << std::endl; });
	test->print();
	(*test).print();
	//test.reset();
	unique_ptr<Test, std::function<void(Test*)>> tt(new Test, [](Test* XX) { /*delete[] XX;*/ std::cout << "pointerFunction called" << std::endl; });
	//std::cout << "print member string: "<<tt->A << std::endl;
	unique_ptr<Test, std::function<void(Test*)>> ttt;
	//ttt = test;
	//tt = test;
	
// -------- shared ptr ----------------------------------------------------------------------------------------	
	shared_ptr<Test, std::function<void(Test*)>> cc(new Test(999));
	shared_ptr<Test, std::function<void(Test*)>> zz;
	shared_ptr<Test, std::function<void(Test*)>> gg(zz);
	shared_ptr<Test, std::function<void(Test*)>> ff(new Test(1111));
	shared_ptr<Test, std::function<void(Test*)>> jj(std::move(ff));
	jj = std::move(cc);

	return 0;
}