#pragma once
#include<functional>
namespace smartPtr{

	template <typename T, typename F = std::function<void(T*)>>
	class smart_ptr {
		T* ptr;
		F delete_ptr;
	public:
		class shared_ptr;
		class unique_ptr;
		smart_ptr(T* ptr_ = nullptr, F delete_ptr_ = [](T* ptr_) { delete ptr_; }) : ptr(ptr_), delete_ptr(delete_ptr_){}
		
		// copy constructor for shared pointer
		smart_ptr(shared_ptr& copy_ptr) {
			ptr = copy_ptr.ptr;
			delete_ptr = copy_ptr.delete_ptr;
		}

		~smart_ptr() { delete_ptr(this->ptr); }
		T* operator->() { return ptr; }
		T& operator*() { return *ptr; }

		void reset() {
			ptr = nullptr;
			delete_ptr = [](T* ptr_) { delete ptr_; };
		}

		void swap_ptr(const unique_ptr& left, const unique_ptr& right) {
			std::swap(left.ptr, right.ptr);
			std::swap(left.delet_ptr, right.delete_ptr);
		}

	};

	template <typename T, typename F = std::function<void(T*)>>
	class unique_ptr : public smart_ptr<T,F> {

	public:
		unique_ptr(T* ptr_, F delete_ptr_) : smart_ptr<T,F>(ptr_, delete_ptr_){}
		unique_ptr(const unique_ptr& copy) = delete;
		unique_ptr& operator=(const unique_ptr& copyAss) = delete;

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
		int* count_ptr = nullptr;
	public:
		shared_ptr(): count_ptr(new int(0)), smart_ptr<T, F>(){}
		shared_ptr(T* ptr_, F delete_ptr_) : count_ptr(new int(1)), smart_ptr<T, F>(ptr_, delete_ptr_) {}
		shared_ptr(const shared_ptr& copy_ptr) : smart_ptr<T,F>(copy_ptr){
			count_ptr++;
		}

		shared_ptr& operator=(const shared_ptr assign) {
			// case 1: if this->count is 0
			// case 2: if this-> count is 1
			// case 3: if this-> count is larger then 2
			swap_ptr(*this, assign);
		}

	};
}
