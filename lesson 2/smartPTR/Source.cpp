#include <iostream>
#include "mmemory.h"
#include <memory>
#include <utility>

class A {
	int a;
	std::string name;
public:
	explicit A(std::string name_, int aa = 0) : name(name_), a(aa) {}
	~A() { std::cout << std::endl << "destruct: " << name <<std::endl; }

	void printName() const { std::cout << std::endl << "name: " << name << std::endl; }
	/*
	A(A&& aa) : A("") {
		std::swap(a, aa.a);
		std::swap(name, aa.name);
	}

	A& operator=(A&& aa) {
		//a = std::move(aa.a);
		//name = std::move(aa.name);
		A tmp(std::move(aa));
		std::swap(name, tmp.name);
		std::swap(a, tmp.a);
		return *this;
	}
	*/
};

int main() {

	{
		//SMART_PTR::unique_ptr<A, void(*)(A*)> aa(new A, [](A* a) {std::cout << "OPPPPPPPPPPPPPPP\n"; });

		SMART_PTR::shared_ptr<A> a(new A("a", 5));

		{
			SMART_PTR::shared_ptr<A> b(a);
			SMART_PTR::shared_ptr<A> c(new A("c", 5));

			a->printName();
			b->printName();
		}
		a->printName();


		std::cout << "------------------\n";
		SMART_PTR::shared_ptr<int> z(new int);
		std::cout << "------------------\n";
		SMART_PTR::shared_ptr<int> zz(new int);

	}






	// #################### unique_ptr tests ##########################
	// 
	//A d("David", 5);
	//A v("VVVVVV", 7);


	//d = std::move(v);

	//A dd(std::move(v));
	//int c = 7;
/*
	{
		//SMART_PTR::unique_ptr<A, void(*)(A*)> aa(new A, [](A* a) {std::cout << "OPPPPPPPPPPPPPPP\n"; });

		SMART_PTR::unique_ptr<A> a(new A("a", 5));
		SMART_PTR::unique_ptr<A> b(new A("b", 7));
		//std::unique_ptr<A> a(new A("a", 5));
		//std::unique_ptr<A> b(new A("b", 7));

		//SMART_PTR::unique_ptr<int> a(new int(4));
		//SMART_PTR::unique_ptr<int> b(new int(8));

		//std::unique_ptr<int> a(new int(4));
		//std::unique_ptr<int> b(new int(8));

		//SMART_PTR::unique_ptr<A> b(std::move(a));
		a = std::move(b);

		std::cout << "NAME a: ";
		a->printName();
		std::cout << std::endl;

		std::cout << "NAME b: ";
		//b->printName(); // for testing
		std::cout << std::endl;

		a.reset();
		a.reset(new A("c", 50));
		//swap(a, b);
		int g = 7;
		//SMART_PTR::unique_ptr<A> copy_a(a);
	//	SMART_PTR::unique_ptr<A> b;

		//b = a;

		a->printName();

		(*a).printName();
	}



	std::cout << "after a\n";

	/*
	std::unique_ptr<A> a(new A);
	std::unique_ptr<A> b(std::move(a));
	int c = 5;
	*/
	//SMART_PTR::unique_ptr_<A[]> b(new A[10]);

	//SMART_PTR::unique_ptr_<A[], void(*)(A*)> bb(new A[10], [](A* a) {std::cout << "UUUUUUUU\n"; }) ;
	
	return 0;
}