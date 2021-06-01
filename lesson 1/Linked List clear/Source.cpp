#include <list>
#include <iostream>
#include "LinkedList.h"


int main() {

	std::list<int> l = { 1,2,3,5,10 };

	for (std::list<int>::const_iterator i = l.begin(); i != l.end(); ++i) {
		std::cout << *i << ",";
	}
	std::cout << std::endl;

	List<int> tt({ 1,2,9,4,1,9,9,7,8 });

//	List<int> tt;

	List<int>::const_iterator it;

	tt.testPrint();

	size_t s = sizeof(List<double>({ 1,200,500 }));
	List<double>* pp = new List<double>({ 1,200,500 });

	pp->printElements();

	std::cout << *pp << std::endl;
	delete pp;

	std::cout << "############################################\n";

	List<int> tt1(std::move(tt)); // testing move ctor

	tt1.printElements();
	tt.printElements();


	List<int> ll({ 0,0,-50,300});
	//ll = tt1;
	ll = std::move(tt1);// testing move assignment operator ----- ambiguous ctor resolution --- it just swapped two lists, but didn't move
	std::cout << "ll elements: " << ll;
	std::cout << "tt1 elements: " << tt1; // tt1 should have no elements here




	List<int> lll({ 1400, 0,0,-50,300 });

	std::cout << "ll size: " << ll.sizef() << "ll elements: " << ll; // wrong sizes 
	std::cout << "lll size: " << lll.sizef() << "lll elements: " << lll;
	swap(ll, lll); // swap should be accessible here, so you should change it to use "friend" not static 
	std::cout << "ll size: " << ll.sizef() << "ll elements: " << ll;
	std::cout << "lll size: " << lll.sizef() << "lll elements: " << lll;

	return 0;
}