#include <iostream>

namespace SMART_PTR {
	
	template <typename T>
	struct default_deleter_ {
		constexpr default_deleter_() noexcept = default;

		template <class T2>
		default_deleter_(const default_deleter_<T2>&) noexcept {};

		//template <class T2>
		//default_deleter(default_deleter<T2>&&) noexcept = delete;

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

		smart_ptr_(const smart_ptr_& r) = delete;
		smart_ptr_& operator=(const smart_ptr_& r) = delete;
		smart_ptr_(smart_ptr_&& r) = delete;
		smart_ptr_& operator=(smart_ptr_&& r) = delete;

		virtual ~smart_ptr_() {}

		T* operator->() { return ptr; }
		T& operator*() { return *ptr; }

		virtual void reset(T*) = 0;
	};
}