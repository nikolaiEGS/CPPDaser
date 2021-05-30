#include "unique_ptr_.h"
#include "unique_ptr.h"
#include <iostream>
//#include <memory>
#include <functional>

/*
template <class _Ty, class _Dx>
class u;


template <class _Ty, class _Dx>
class u<_Ty[], _Dx> { // non-copyable pointer to an array object
public:
};
*/


class A {
public:
	~A() { std::cout << "AAAAAAAA\n"; }
};
int main() {

	//smart_ptr::unique_ptr_<int[], void (*) (int*)> ptr(new int[100], [](int* p) {delete []p;  std::cout << "PPPPPPPPP\n"; });

	
	//smart_ptr::unique_ptr_<int[]> ptrr(new int[100]);

	//smart_ptr::unique_ptr_<A[], void (*) (A*)> ptr(new A[10], [](A* p) {delete[] p;  std::cout << "PPPPPPPPP\n"; });




	//smart_ptr::default_deleter<int> d;

	//smart_ptr::default_deleter<int>dd(d);


	//d(new int[10]);
	//dd(new int[10]);

	SMART_PTR::unique_ptr<A> a(new A);


	SMART_PTR::unique_ptr<A, void(*)(A*)> aa(new A, [](A* a) {std::cout << "OPPPPPPPPPPPPPPP\n"; });

	//smart_ptr::unique_ptr_<A[], std::function<void(A*)>> ptr_1(new A[10], [](A* p) {delete[] p;  std::cout << "LLLLL\n"; });

//	smart_ptr::unique_ptr_<A[]> ptr_(new A[10]);

	//ptr.reset(new int[10]);
	// 
	//std::unique_ptr<A[], std::function<void(A*)>> pp(new A[10], [](A* p) {std::cout << "PPPPooo\n"; });
	
	//std::unique_ptr<A[]> pp(new A[10]);

	//std::function<void(int*)> f = smart_ptr::default_deleter<int>();
	//auto ff(f);

	
	return 0;
}