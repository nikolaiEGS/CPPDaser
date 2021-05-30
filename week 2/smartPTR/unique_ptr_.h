#pragma once
#include "smart_ptr_.h"
//#include <functional>
#include <iostream>

namespace SMART_PTR {

/*
	template <class _Ty>
	struct smart_ptr::default_deleter;
*/

	template <typename T, typename F = SMART_PTR::default_deleter_<T>>
	class unique_ptr_;

	template <typename T, typename F>
	class unique_ptr_<T[], F> : public smart_ptr_<T[]> {
		using custom_deleter_function = F;

		custom_deleter_function custom_deleter;
		
	public:
		//template <class T2, class F2 = F>
		//unique_ptr_(T2* ptr_) : smart_ptr_<T2[]>(ptr_), custom_deleter(SMART_PTR::default_deleter<T2>()) {}

		template <class T2, class F2 = F>
		unique_ptr_(T2* ptr_, const F2& custom_deleter_) : smart_ptr_<T2[]>(ptr_),  custom_deleter(custom_deleter_) {}
		
		virtual ~unique_ptr_() { 
			custom_deleter(this->ptr); 
		}

		void reset(T* ptr_) override;
	};

	template<typename T, typename F>
	inline void unique_ptr_<T[], F>::reset(T* ptr_)
	{
		this->ptr = ptr_;
	}

	/*
	template<class T, class F> 
	void SMART_PTR::unique_ptr_<T[], F>::reset(T* ptr_) {
		this->ptr = ptr_;
	}
	*/
}