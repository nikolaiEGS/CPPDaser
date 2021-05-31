#pragma once
#include <iostream>

namespace SMART_PTR {

	template <typename T>
	struct default_deleter {
		constexpr default_deleter() noexcept = default;

		template <class T2>
		default_deleter(const default_deleter<T2>&) noexcept {};

		void operator()(T* _Ptr) const noexcept { // delete a pointer
			//static_assert(0 < sizeof(_Ty), "can't delete an incomplete type");
			std::cout << "delete\n";
			delete _Ptr;
		}
	};


	template <typename T>
	class smart_ptr;

	template <typename T>
	class smart_ptr {
	protected:
		T* ptr;
	public:
		smart_ptr(T* ptr_ = nullptr) : ptr(ptr_) {}

		virtual ~smart_ptr() {}

		T* operator->() { return ptr; }
		T& operator*() { return *ptr; }

		virtual void reset(T*) = 0;
	};
}