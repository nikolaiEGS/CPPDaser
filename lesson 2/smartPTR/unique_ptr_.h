#pragma once
#include "smart_ptr_.h"
#include <iostream>

namespace SMART_PTR {
	
	template <typename T>
	void f(T* t) {
		std::cout << "delete[]";
		delete[] t;
	}
	
	//template <typename T, typename F = SMART_PTR::default_deleter_<T>>
	//template <typename T, typename F = void(*)(T*)>
	//template <typename T, typename F = typeid(f<T>)>
	template <typename T, typename F = SMART_PTR::default_deleter_<T>>
	class unique_ptr_;

	template <typename T, typename F>
	class unique_ptr_<T[], F> : public smart_ptr_<T[]> {
		using custom_deleter_function = F;
		custom_deleter_function custom_deleter;
	public:
		//template <class T2, class F2 = F>
		//unique_ptr_(T2* ptr_) : smart_ptr_<T2[]>(ptr_), custom_deleter(SMART_PTR::default_deleter<T2>()) {}

		//template <class T2, class F2 = F>
		//unique_ptr_(T2* ptr_, const F2& custom_deleter_) : smart_ptr_<T2[]>(ptr_),  custom_deleter(custom_deleter_) {}
		
		//unique_ptr_(T* ptr_ = nullptr, const F& custom_deleter_ = SMART_PTR::default_deleter_<T>()) : smart_ptr_<T[]>(ptr_), custom_deleter(custom_deleter_) {}

		//template <class T2, class F2 = F>
		//unique_ptr_(T2* ptr_ = nullptr, const F2& custom_deleter_ = SMART_PTR::default_deleter_<T2>()) : smart_ptr_<T2[]>(ptr_), custom_deleter(custom_deleter_) {}

		template <class T2, class F2 = F>
		unique_ptr_(T2* ptr_ = nullptr, const custom_deleter_function& custom_deleter_ = SMART_PTR::default_deleter_<T2>()): smart_ptr_<T2[]>(ptr_), custom_deleter(custom_deleter_) {}

		
		virtual ~unique_ptr_() { 
			//custom_deleter(this->ptr); issue here
		}

		void reset(T* ptr_) override;
	};

	template<typename T, typename F>
	inline void unique_ptr_<T[], F>::reset(T* ptr_)
	{
		this->ptr = ptr_;
	}
}