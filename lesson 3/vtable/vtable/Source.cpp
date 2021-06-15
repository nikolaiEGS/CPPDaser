#include "vtable.h"
#include <cassert>
#include <iostream>

int main() {
	Employee ee;
	Manager mm;

	Employee* e = &ee;
	Employee* m = &mm;

/*	assert(ee.v_get_info(FunctionType::NON_VIRTUAL) == ee.get_info_nv());
	assert(ee.v_get_name(FunctionType::NON_VIRTUAL) == ee.get_name_nv());
	assert(mm.v_get_info(FunctionType::NON_VIRTUAL) == mm.get_info_nv());
	assert(mm.v_get_name(FunctionType::NON_VIRTUAL) == mm.get_name_nv());*/


	assert(e->v_get_info(FunctionType::VIRTUAL) == e->get_info());
	assert(e->v_get_name(FunctionType::VIRTUAL) == e->get_name());
	assert(m->v_get_info(FunctionType::VIRTUAL) == m->get_info());
	assert(m->v_get_name(FunctionType::VIRTUAL) == m->get_name());

	//std::cout << sizeof(*e) <<std::endl;

	std::string employee_info_nv = ee.v_get_info(FunctionType::NON_VIRTUAL);
	std::string employee_name_nv = ee.v_get_name(FunctionType::NON_VIRTUAL);
	std::cout << employee_info_nv << " : " << employee_name_nv << std::endl;

	std::string manager_info_nv = mm.v_get_info(FunctionType::NON_VIRTUAL);
	std::string manager_name_nv = mm.v_get_name(FunctionType::NON_VIRTUAL);
	std::cout << manager_info_nv << " : " << manager_name_nv << std::endl;

	std::string employee_info_nv_ = ee.get_info_nv();
	std::string employee_name_nv_ = ee.get_name_nv();
	std::cout << employee_info_nv_ << " : " << employee_name_nv_ << std::endl;

	std::string manager_info_nv_ = mm.get_info_nv();
	std::string manager_name_nv_ = mm.get_name_nv();
	std::cout << manager_info_nv_ << " : " << manager_name_nv_ << std::endl;

	std::cout << std::endl;

	// my implementation of virtual
	std::string employee_info = e->v_get_info(FunctionType::VIRTUAL);
	std::string employee_name = e->v_get_name(FunctionType::VIRTUAL);
	std::cout << employee_info << " : " << employee_name << std::endl;

	std::string manager_info = m->v_get_info(FunctionType::VIRTUAL);
	std::string manager_name = m->v_get_name(FunctionType::VIRTUAL);
	std::cout << manager_info << " : " << manager_name << std::endl;

	// C++ virtual
	std::string employee_info_ = e->get_info();
	std::string employee_name_ = e->get_name();
	std::cout << employee_info_ << " : " << employee_name_ << std::endl;

	std::string manager_info_ = m->get_info();
	std::string manager_name_ = m->get_name();
	std::cout << manager_info_ << " : " << manager_name_ << std::endl;


	return 0;
}