#pragma once
#include "smart_ptr.h"

namespace SMART_PTR {
	
	template <typename T, typename F = SMART_PTR::default_deleter<T>>
	class unique_ptr;

	template <typename T, typename F>
	class unique_ptr : public smart_ptr<T> {
		using custom_deleter_function = F;
		custom_deleter_function custom_deleter;
	public:

		unique_ptr(T* ptr_ = nullptr, const F& custom_deleter_= SMART_PTR::default_deleter<T>()) : smart_ptr<T>(ptr_), custom_deleter(custom_deleter_) {}

		virtual ~unique_ptr() {
			custom_deleter(this->ptr);
		}

		void reset(T* ptr_) override;
	};

	template<typename T, typename F>
	inline void unique_ptr<T, F>::reset(T* ptr_) {
		this->ptr = ptr_;
	}
}