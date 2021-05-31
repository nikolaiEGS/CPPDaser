#include <list>
#include <iostream>
#include "LinkedList.h"


int main() {

	//std::list<int> l({ 1,2,5,10 });
	std::list<int> l = { 1,2,3,5,10 };

	for (std::list<int>::const_iterator i = l.begin(); i != l.end(); ++i) {
		std::cout << *i << ",";
	}
	std::cout << std::endl;

	List<int> tt({ 1,2,9,4,1,9,9,7,8 });

//	List<int> tt;



	return 0;
}