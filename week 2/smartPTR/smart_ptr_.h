#pragma once
#include <iostream>

namespace SMART_PTR {
	
	template <typename T>
	struct default_deleter_ {
		constexpr default_deleter_() noexcept = default;

		template <class T2>
		default_deleter_(const default_deleter_<T2>&) noexcept {};

		void operator()(T* _Ptr) const noexcept { // delete a pointer array
			//static_assert(0 < sizeof(_Ty), "can't delete an incomplete type");
			std::cout << "delete[]";
			delete[] _Ptr;
		}
	};


	template <typename T>
	class smart_ptr_;

	template <typename T>
	class smart_ptr_<T[]> {
	protected:
		T* ptr;
	public:
		smart_ptr_(T* ptr_ = nullptr) : ptr(ptr_) {}
		virtual ~smart_ptr_() {}

		T* operator->() { return ptr; }
		T& operator*() { return *ptr; }

		virtual void reset(T*) = 0;
	};
}