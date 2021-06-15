#pragma once


class Exception {
	std::string msg_;
public:
	Exception(const std::string& msg) : msg_(msg) {}
	~Exception() {}

	std::string getMessage() const { return(msg_); }
	
};
