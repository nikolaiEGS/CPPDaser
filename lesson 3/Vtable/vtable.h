#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <map>

enum FunctionType {VIRTUAL, NON_VIRTUAL};

class Employee {
	
protected:
	std::string name;
	std::size_t age;

	using fpType = std::string(Employee::*)();
	std::map<std::string, fpType>* vtable;

	std::string info_() { return name + ',' + std::to_string(age); }
	std::string name_() { return name; }
public:

	Employee(std::string name_ = "Employee Name", std::size_t age_ = 20) : name(name_), age(age_), vtable (new std::map<std::string, fpType>) {
		(*vtable)["v_get_info"] = &Employee::info_;
		(*vtable)["v_get_name"] = &Employee::name_;
	}
	
	virtual ~Employee() {
		delete vtable;
	}
	

	virtual std::string get_info() { 
		//std::cout << "EMPLOYEE: get_info"; 
		return info_();
	}

	virtual std::string get_name() {
		return name_();
	}

	std::string v_get_info(FunctionType type) {
		if (type == FunctionType::VIRTUAL) {
			const auto& function = vtable->find("v_get_info")->second;
			return ((*this).*function)();
		}
		else {
			return info_();
		}
	}

	std::string v_get_name(FunctionType type) {
		if (type == FunctionType::VIRTUAL) {
			const auto& function = vtable->find("v_get_name")->second;
			return ((*this).*function)();
		}
		else {
			return name_();
		}
	}

	std::string friend _info(Employee& e) {
		return e.info_();
	}
};

class Manager : public Employee {
	std::string level;
	std::string info_() { return name + ',' + std::to_string(age) + ' ' + level; }
public:
	Manager(std::string name_ = "Manager Name", std::size_t age_ = 20, std::string level_ = "top") : Employee(name_, age_), level(level_) {
		(*vtable)["v_get_info"] = &Manager::info_;
		(*vtable)["v_get_name"] = &Employee::name_;
	}
};
