#include "vtable.h"

int main() {
	Employee e;
	std::cout << sizeof(e) <<std::endl;


	//e.vtable->push_back(&Employee::info);
	//e.f = &Employee::info;

	std::string employee_info = e.v_get_info(FunctionType::VIRTUAL);
	std::string employee_name = e.v_get_name(FunctionType::VIRTUAL);
	std::cout << employee_info << " : " << employee_name << std::endl;
	return 0;
}