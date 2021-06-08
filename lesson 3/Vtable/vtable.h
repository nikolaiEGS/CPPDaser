#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <functional>

enum FunctionType {VIRTUAL, NON_VIRTUAL};


std::string ff() {
	return "AAAA";
}

class Employee {
	//std::string info() const noexcept { return "Employee: " + name + ',' + std::to_string(age); }
protected:
	std::string name;
	std::size_t age;

	//template <typename T>
	//std::vector<std::function<std::string(FunctionType)>>* vtable;
	//std::vector<std::string(Employee::*)()>* vtable;
public:
	typedef std::string(Employee::* fp)();

//	fp f;
	std::string info() { return "Employee: " + name + ',' + std::to_string(age); }
	std::vector<fp>* vtable;

	Employee(std::string name_ = std::string(), std::size_t age_ = 0) : name(name_), age(age_), vtable (new std::vector<fp>) {
		//vtable->push_back(ff);
		//vtable->push_back(&Employee::info);
		vtable->push_back(&Employee::info);
	}
	
	//virtual std::size_t get_age() const noexcept { std::cout << "EMPLOYEE: get_age";  return age; }
	//virtual std::string get_name() const noexcept { std::cout << "EMPLOYEE: get_name";  return name; }

	virtual std::string get_info() { 
		//std::cout << "EMPLOYEE: get_info"; 
		return info();
	}

	std::string v_get_info(FunctionType type) {
		if (type == FunctionType::VIRTUAL) {
			// find from vtable
	//		return ((*this).*f)();
			//return ((*this).*vtable)[0]();

		
			for (const auto& function : *vtable) {
				if (function) {
					return ((*this).*function)();
					//return "AAA";
				}
			}
			
		}
		else {
			return info();
		}
	}
};