#pragma once
#include <string>
#include <functional>
#include <map>

enum FunctionType { VIRTUAL, NON_VIRTUAL };

class Employee {

protected:
	std::string name;
	std::size_t age;

	T* vtable; //TODO - You should find the type T by yourself

	std::string info_() { return name + ',' + std::to_string(age); }
	std::string name_() { return name; }
public:

	Employee(std::string name_ = "Employee Name", std::size_t age_ = 20) : name(name_), age(age_), vtable(new T ) {

		//TODO - add a function to the vtable (hint: to know exactly which function you should add look at the virtual std::string get_info())
		//TODO - add a function to the vtable (hint: to know exactly which function you should add look at the virtual std::string get_name())
	}

//TODO - implement destructor


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
		}
		else {
			return info_();
		}
	}

	std::string v_get_name(FunctionType type) {
		if (type == FunctionType::VIRTUAL) {
			// TODO - call the appropriate function from the vtable 
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
		//TODO - add a function to the vtable (hint: to know exactly which function you should add look at the virtual std::string get_info()) ----- override only get_info, not get_name
	}

	std::string get_info() override {
		return info_();
	}
};
