#include "vtable.h"

int main() {
	Employee e;
	std::cout << sizeof(e) <<std::endl;


	//e.vtable->push_back(&Employee::info);
	//e.f = &Employee::info;

	std::string s = e.v_get_info(FunctionType::VIRTUAL);
	std::cout << s << std::endl;
	return 0;
}