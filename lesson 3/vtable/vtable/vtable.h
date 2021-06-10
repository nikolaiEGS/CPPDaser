#pragma once
#include <string>
#include <functional>
#include <map>


enum FunctionType { VIRTUAL, NON_VIRTUAL };

class Employee {

protected:
	std::string name;
	std::size_t age;

	//TODO - You should find the type T by yourself
	std::map<std::string, std::string(Employee::*)()>* vtable;

	std::string info_() { return name + ',' + std::to_string(age); }
	std::string name_() { return name; }
public:

	Employee(std::string name_ = "Employee Name", std::size_t age_ = 20) : name(name_), age(age_),
		vtable(new std::map<std::string, std::string(Employee::*)()>) {
			(*vtable)["Base_info"] = &Employee::info_;
			(*vtable)["Base_name"] = &Employee::name_;
		//TODO - add a function to the vtable (hint: to know exactly which function you should add look at the virtual std::string get_info())
		//TODO - add a function to the vtable (hint: to know exactly which function you should add look at the virtual std::string get_name())
	}

	//TODO - implement destructor
	virtual ~Employee(){
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
			// TODO - call the appropriate function from the vtable
			const auto& function = vtable->find("Base_info")->second;
			return ((*this).*function)();
		}
		else {
			return info_();
		}
	}

	std::string v_get_name(FunctionType type) {
		if (type == FunctionType::VIRTUAL) {
			// TODO - call the appropriate function from the vtable 
			// >>> I took the solution from your code, as I could not return vtable->find("Base_name")->second;
			const auto& function = vtable->find("Base_name")->second;
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
		// Question: shouldn t class Manager have an own vtabel, as the inherrited vtbale pointer points to the same map.
		(*vtable)["Manager::info_"] = &Manager::info_; // can not assigne to type Manager::
		(*vtable)["Employee::name_"] = &Employee::name_; // error, why cant I access protected member in class Employee?
	}

	std::string get_info() override {
		return info_();
	}
};

