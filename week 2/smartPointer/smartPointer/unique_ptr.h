#pragma once
#include<functional>
namespace smartPtr{

	template <typename T, typename F = std::function<void(T*)>>
	class smart_ptr {
		T* ptr;
		F delete_ptr;
	public:
		smart_ptr(T* ptr_ = nullptr, F delete_ptr_ = [](T* ptr_) { delete ptr_; }) : ptr(ptr_), delete_ptr(delete_ptr_){}
		smart_ptr(T* ptr_copy) : ptr(ptr_copy.ptr){}
		~smart_ptr() { delete_ptr(this->ptr); }
		T* operator->() { return ptr; }
		T& operator*() { return *ptr; }
		void reset() {
			ptr = nullptr;
			delete_ptr_ = [](T* ptr_) { delete ptr_; };
		}

	};

	template <typename T, typename F = std::function<void(T*)>>
	class unique_ptr : public smart_ptr<T,F> {

	public:
		unique_ptr(T* ptr_, F delete_ptr_) : smart_ptr<T,F>(ptr_, delete_ptr_){}
		unique_ptr(const unique_ptr& copy) = delete;
		unique_ptr& operator=(const unique_ptr& copyAss) = delete;

		void swap_ptr(const unique_ptr& left, const unique_ptr& right) {
			std::swap(left.ptr, right.ptr);
			std::swap(left.delet_ptr, right.delete_ptr);
		}

		unique_ptr(unique_ptr&& move_ptr) noexcept {
			swap_ptr(*this, move_ptr);
			return *this;
		}

		unique_ptr& operator=(unique_ptr&& move_ptr) noexcept {
			swap_ptr(*this, move_ptr);
			return *this;
		}
		// constexpr, noexept
	};

	template <typename T, typename F = std::function<void(T*)>>
	class shared_ptr : public smart_ptr<T, F> {
		int count = 0;
	public:

		shared_ptr(T* ptr_, F delete_ptr_) : smart_ptr<T, F>(ptr_, delete_ptr_) { count++; }
		//shared_ptr(const shared_ptr& ptr_) : smart_ptr<T, F>(ptr_){
		//	count++;
		//}

	};
}
