#pragma once
#include <string>
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
		return info_();
	}

	virtual std::string get_name() {
		return name_();
	}

	std::string get_info_nv() {
		return info_();
	}

	std::string get_name_nv() {
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

};

class Manager : public Employee {
	std::string level;

	std::string info_() { return name + ',' + std::to_string(age) + ' ' + level; }
public:
	using Employee::name_;

	Manager(std::string name_ = "Manager Name", std::size_t age_ = 25, std::string level_ = "top") : Employee(name_, age_), level(level_) {
		(*vtable)["v_get_info"] = reinterpret_cast<std::string(Employee::*)()>(&Manager::info_); // override
	}

	std::string get_info() override {
		return info_();
	}
};
